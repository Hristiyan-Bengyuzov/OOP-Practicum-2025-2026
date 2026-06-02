
## Задача 1

*Студиото „Нетфликс за бедни" разработва бойна игра - работното заглавие е „Kombat Mortal". За да не се съдят, са сменили и имената на героите. Вашата задача е да реализирате системата за управление на бойните действия.*

### `Fighter`
- `name` - низ
- `hp` - цяло число [0, 100]
- `rage` - цяло число [0, 10], енергия за специални удари
- `wins` - цяло число ≥ 0
- Може да се извежда на стандартния изход

### `FightCommand` - абстрактна команда
Базов клас с:
- `execute()` - изпълнява действието
- `undo()` - отменя действието
- `describe()` - връща низ с описание

Три конкретни команди:
- `PunchCommand(fighter, damage)` - намалява hp с damage (cap до 0); undo връща старото hp
- `RageChargeCommand(fighter, amount)` - увеличава rage с amount (cap до 10); undo връща старата стойност
- `FinisherCommand(fighter)` - намалява hp до 0 и увеличава wins с 1 на **нападателя**; undo връща hp-то и wins-а; при rage < 5 хвърля изключение

### `CommandHistory`
- `execute(command)` - изпълнява командата и я записва; изчиства redo стека
- `undo()` - отменя последната команда
- `redo()` - повтаря последно отмененото действие
- При `undo()`/`redo()` на празна история - изключение

### Примерен main()
```cpp
Fighter scorpion("Scorpion", 100, 3, 0);
Fighter subzero("Sub-Zero", 100, 8, 2);
CommandHistory history;

history.execute(std::make_unique<PunchCommand>(scorpion, 25));
history.execute(std::make_unique<RageChargeCommand>(scorpion, 4));
std::cout << scorpion; // hp=75, rage=7, wins=0

history.undo();  // rage обратно на 3
history.undo();  // hp обратно на 100
history.redo();  // hp=75

try {
    // rage е само 3, трябват поне 5
    history.execute(std::make_unique<FinisherCommand>(scorpion, subzero));
} catch (const KombatException& e) {
    std::cout << e.what(); // "Not enough rage for finisher"
}
```

---

## Задача 2

*Общинският инспекторат реши да дигитализира работата си. Всеки инспектор обхожда обектите под негов контрол и **записва всички нередности** - не само първата, защото от това му зависи бонусът.*

### Класове

**`Establishment`**
- `name` - низ
- `seatingCapacity` - цяло число > 0
- `hygieneScore` - дробно число [0.0, 10.0]
- `licenseCode` - низ (формат: точно 2 букви + 4 цифри, напр. `"BG0042"`)

**`Employee`**
- `fullName` - низ
- `age` - цяло число [16, 80]
- `hoursPerWeek` - дробно число (0, 60]

**`Inspection`** - протокол от проверка
- `protocolId` - низ, непразен
- `establishment` - обект от тип `Establishment`
- `staff` - вектор от `Employee`

### `Inspector<T>` - базов шаблонен инспектор
Метод `inspect(const T&)` връща `std::vector<std::string>` с всички намерени нередности.

Конкретни инспектори:
- `EstablishmentInspector` - непразно `name`, `seatingCapacity > 0`, `hygieneScore` ∈ [0, 10], `licenseCode` отговаря на формата
- `EmployeeInspector` - непразно `fullName`, `age` ∈ [16, 80], `hoursPerWeek` ∈ (0, 60]
- `InspectionInspector` - непразен `protocolId`, поне един служител; инспектира заведението чрез `EstablishmentInspector`; инспектира всеки служител чрез `EmployeeInspector`; събира всички нередности в общ списък

### Примерен main()
```cpp
Establishment bar{"", 0, 11.5, "bg42"};       // 4 нередности
Employee e1{"", 14, 75.0};                     // 3 нередности
Inspection inspection{"", bar, {e1}};          // + 1 за protocolId

InspectionInspector inspector;
auto issues = inspector.inspect(inspection);
for (const auto& issue : issues)
    std::cerr << "Нередност: " << issue << "\n";
// Очакват се 8 реда
```

---

## Задача 3

*Годината е 2077. Найт Сити никога не спи, а подмрежите на местните фиксери управляват трафика на модифицирани кибер-возила. Системата им работи на C++, защото дори след Корпоративните войни, legacy кодът живее вечно.*

### `CyberRide` - абстрактен базов клас
- `systemId` - низ, уникален идентификатор в мрежата
- `chooh2Level` - дробно число [0.0, 100.0] (ниво на биогориво CHOOH2)
- `hasIcebreaker` - bool (наличие на софтуер за разбиване на корпоративен ЛЕД)
- `announce()` - чист виртуален метод; извежда информация за превозното средство

Три конкретни типа:
- `CombatCoup` - бойно купе. Добавя `turretsCount` (цяло число ≥ 0) и `armorClass` (низ); `announce()` извежда systemId и turretsCount
- `CargoAV` - летателен апарат за тежки товари. Добавя `cargoTons` (> 0.0) и `thrustersCount` (цяло число ≥ 2); `announce()` извежда systemId и cargoTons
- `NetVan` - нетрънърски ван за кибер-атаки. Добавя `cyberdeckSlots` (> 0) и `isAutonomous` (bool); `announce()` извежда systemId и cyberdeckSlots

`CyberRide` се създава динамично по текстов тип (`"combatcoup"`, `"cargoav"`, `"netvan"`). При непознат тип - хвърля изключение `CyberwareException`.

### `FixerGrid` - мрежови регистър на фиксера
- `add(ride)` - при вече съществуващ `systemId` операцията се игнорира
- `remove(systemId)`
- `find(systemId)` - връща `std::optional`
- `announceAll()` - вика `announce()` на всички регистрирани возила
- Копирането на обекти от тип `FixerGrid` споделя съществуващите возила (плитко копиране)

### `GridIndex<T>` - шаблонен индекс
- `add`, `find(key)`, `remove(key)`, `size()`
- `CombatCoup` се търси по `systemId`, `CargoAV` по `systemId`, `NetVan` по брой слотове: `cyberdeckSlots` (подаден като низ)
- Реализирайте поне **една template специализация** за `NetVan`

### Примерен main()
```cpp
auto cc = std::make_shared<CombatCoup>("QUADRA-V-66", 85.5, true, 2, "Militech-Heavy");
auto av = std::make_shared<CargoAV>("ZETATECH-ATLAS", 40.0, false, 15.5, 4);
auto nv = std::make_shared<NetVan>("BARTMOSS-MOBILE", 100.0, true, 8, true);

FixerGrid grid;
grid.add(cc); grid.add(av); grid.add(nv);
grid.announceAll();

GridIndex<NetVan> vanIndex;
vanIndex.add(nv);
auto found = vanIndex.find("8"); // търсене по cyberdeckSlots
if (found) (*found)->announce();

try {
    auto unknown = /* непознат тип "ufo" */;
} catch (const CyberwareException& e) {
    std::cout << e.what();
}
```

---

## Задача 4

*Чичо Ицо е аналогов фотограф, принуден да дигитализира бизнеса си. Има нужда от система за обработка на снимки - поредица от филтри, всеки от които модифицира характеристиките на изображението.*

### `Photo`
- `filename` - низ
- `brightness` - цяло число [0, 255]
- `contrast` - цяло число [0, 255]
- `saturation` - цяло число [0, 255]

### `Filter` - абстрактен филтър
- `name` - низ
- `apply(Photo& photo)` - модифицира свойствата на снимката
- Може да се **дублира** - копието е независимо от оригинала

Три конкретни типа:

| Клас | Параметри | Ефект |
|---|---|---|
| `ExposureFilter` | `delta` ∈ [-255, 255] | `brightness += delta`, cap в [0, 255] |
| `ContrastFilter` | `factor` > 0 | `contrast = min(255, (int)(contrast * factor))` |
| `FadeFilter` | `intensity` ∈ [0.0, 1.0] | `saturation -= intensity * 50`, cap до 0 |

### `DarkroomChain` - верига от филтри
- **Единствен собственик** на филтрите си
- `add(filter)` - добавя в края; при вече съществуващо `name` - изключение
- `remove(name)` - премахва по name
- `develop(Photo& photo)` - прилага всички филтри последователно
- **При копиране всеки филтър се дублира независимо** (дълбоко копие)
- При унищожаване веригата унищожава филтрите

### Примерен main()
```cpp
Photo shot{"cetvrti_roden_den.jpg", 120, 100, 200};

DarkroomChain lab1, lab2;
lab1.add(std::make_unique<ExposureFilter>("expo1", 30));
lab1.add(std::make_unique<ContrastFilter>("con1", 1.5));
lab2 = lab1;   // дълбоко копие - промени в lab2 не засягат lab1
lab2.add(std::make_unique<FadeFilter>("fade1", 0.8));

lab1.develop(shot);
std::cout << shot.brightness; // 150
std::cout << shot.contrast;   // 150

try {
    lab1.add(std::make_unique<ExposureFilter>("expo1", 10)); // вече съществува
} catch (const DarkroomException& e) {
    std::cout << e.what();
}
```

---
