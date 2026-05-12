# Изключения

Изключенията позволяват да се отдели логиката за обработка на грешки от нормалния поток на програмата. При грешка **хвърляме** изключение и изпълнението на текущата функция спира незабавно и runtime-ът търси подходящ `catch` блок.

```cpp
void parse(int n) {
    if (n < 0)
        throw std::invalid_argument("n must be positive");
}

int main() {
    try {
        parse(-1);
    }
    catch (const std::invalid_argument& e) { std::cerr << e.what(); }
    catch (const std::logic_error& e)      { std::cerr << e.what(); } // по-общ -> по-надолу
    catch (const std::exception& e)        { std::cerr << e.what(); }
    catch (...)                            { std::cerr << "unknown"; } // винаги последен
}
```

Изключения от не-примитивни типове се хващат **винаги като const reference** - избягва се излишно копиране и се позволява полиморфизъм (`what()` на правилния тип).

**Редът на catch блоковете е важен** - по-специфичните (наследниците) трябва да са *преди* по-общите (базовите класове), иначе по-общият блок ще ги "погълне" преди да стигнат до по-специфичния. `catch(...)` е винаги последен.

---

## Stack Unwinding

При хвърляне на изключение runtime-ът обхожда стека надолу, **унищожавайки всички успешно създадени локални обекти**, докато намери подходящ `catch` блок.

```cpp
void unsafe() {
    X x;
    throw 42;        // ~X() се извиква
}

void middleware() {
    A a;
    B b;
    unsafe();        // ~B() след това ~A() се извикват при unwinding
    C c;             // c никога не е създаден -> деструктор не се извиква
}

int main() {
    try {
        middleware();
    }
    catch (int n) { }
}
```

Редът на унищожаване е **обратен** на реда на създаване - точно като при нормален край на scope.

Ако **не се намери подходящ `catch`** никъде по стека, се извиква `std::terminate()` и програмата се прекратява. В този случай **не е гарантирано** деструкторите да бъдат извикани - затова е важно всяко изключение да може да бъде хванато поне от `catch(...)` на highest level.

> **Никога не хвърляй изключение от деструктор.** По време на stack unwinding вече тече едно изключение. Ако деструктор хвърли второ, runtime-ът извиква `std::terminate()` незабавно. Деструкторите са имплицитно `noexcept`.

---

## Йерархия на Изключенията

```
std::exception
├── std::bad_alloc              // new не може да задели памет
├── std::bad_cast               // dynamic_cast към несъвместим тип
├── std::runtime_error          // грешки, открити само по време на изпълнение
│   ├── std::overflow_error
│   ├── std::underflow_error
│   └── std::range_error
└── std::logic_error            // грешки, които биха могли да се предотвратят
    ├── std::invalid_argument   // подаден е невалиден аргумент
    ├── std::out_of_range       // индекс/стойност извън допустимия диапазон
    ├── std::length_error       // опит за създаване на обект с невалидна дължина
    └── std::domain_error
```

### Собствени изключения

Наследявай от най-специфичния подходящ клас и предефинирай `what()`:

```cpp
class DatabaseError : public std::runtime_error {
public:
    explicit DatabaseError(const std::string& msg)
        : std::runtime_error("DB error: " + msg) {}
};

class ConnectionError : public DatabaseError {
public:
    explicit ConnectionError(const std::string& host)
        : DatabaseError("Can't connect to " + host) {}
};
```

---

## Exception Guarantees

| Гаранция       | Значение |
|----------------|----------|
| **nothrow**    | Функцията никога не хвърля (`noexcept`). Задължително за деструктори, move операции и `swap`. |
| **strong**     | Ако хвърли, състоянието на обекта е *идентично* с преди извикването - "commit or rollback". |
| **basic**      | Ако хвърли, обектът е в *валидно* (но може и различно) състояние. Минималното приемливо ниво. |
| **none**       | Без гаранции. Избягвай. |

---

## Изключения в Конструктори

Деструкторът се извиква само за **напълно създадени** обекти. Ако конструктор хвърли изключение по средата, деструкторът на *текущия обект* не се извиква - но деструкторите на вече създадените член-обекти (от member initializer list) се извикват.

```cpp
// Опасно - ръчно управление на памет:
X::X() {
    first_name = new char[64];
    try {
        last_name = new char[64]; // може да хвърли std::bad_alloc
    }
    catch (...) {
        delete[] first_name;  // ~X() няма да се извика - почистваме сами
        throw;                // препредаваме изключението към извикващия
    }
}

class X {
    std::string first_name; // деструкторът му се извиква автоматично
    std::string last_name;
    // Ако конструкторът на last_name хвърли, first_name се унищожава сам.
};
```

**Тоест:** Ползвай `std::string`, `std::vector`, `std::unique_ptr` - те правят конструкторите exception-safe автоматично.

---

## Съвременни Алтернативи

### `std::optional<T>` - "стойност или нищо"

Използва се когато липсата на стойност е **нормално очаквано поведение**, не грешка.

```cpp
#include <optional>

std::optional<User> find_user(int id) {
    if (/* не е намерен */) return std::nullopt;
    return user;
}

auto u = find_user(42);

if (u.has_value())              // или просто: if (u)
    std::cout << u->name;

// value_or сетва ако не е намерен на нещо, което изберем
User result = u.value_or(guest_user);

// value() хвърля std::bad_optional_access ако е nullopt
std::cout << u.value().name;    // опасно без проверка
```

---

### `std::expected<T, E>` - "стойност или грешка"
Използва се когато неуспехът е **очакван и чест**, нуждаем се от **причина за грешката**, и искаме caller-ът да е *принуден* да обработи грешката.

```cpp
#include <expected>

std::expected<int, std::string> parse_int(const std::string& s) {
    if (s.empty())
        return std::unexpected("empty");
    if (!std::isdigit(s[0]))
        return std::unexpected("not a number: " + s);
    return std::stoi(s);
}

auto result = parse_int("42");
if (result.has_value())
    std::cout << *result;
else
    std::cerr << result.error();
```

За разлика от изключенията, `std::expected` е **part of the return type** - грешката е видима в сигнатурата на функцията и компилаторът може да предупреди ако не я обработиш.
