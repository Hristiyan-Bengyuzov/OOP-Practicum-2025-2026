

# Задача 1: 

Имплементирайте йерархия от геометрични фигури. Всяка фигура трябва да може да изчислява своето лице и периметър и да се отпечатва.

---

## Клас `Shape`

### Public виртуални методи:
- `virtual double getArea() const = 0`
- `virtual double getPerimeter() const = 0`
- `virtual std::string getName() const = 0`
- `virtual void print(std::ostream& os) const`
  - Формат: `{name}: area={area:.2f}, perimeter={perimeter:.2f}`
- `virtual ~Shape() = default`

---

## Клас `Circle`

### Наследява: `Shape`

### Private полета:
- `double radius`

### Конструктор:
- `Circle(double radius)`
  - Хвърля `std::invalid_argument` ако `radius <= 0`

### Методи:
- Имплементирайте тези от `Shape`

---

## Клас `Rectangle`

### Наследява: `Shape`

### Private полета:
- `double width`
- `double height`

### Конструктор:
- `Rectangle(double width, double height)`
  - Хвърля `std::invalid_argument` ако някое от измеренията е `<= 0`

### Методи:
- Имплементирайте тези от `Shape`

---

## Клас `Triangle`

### Наследява: `Shape`

### Private полета:
- `double a`, `double b`, `double c` (страни)

### Конструктор:
- `Triangle(double a, double b, double c)`
  - Хвърля `std::invalid_argument` ако страните не образуват валиден триъгълник

### Методи:
- Имплементирайте тези от `Shape`

---

## Клас `ShapeCollection`

### Private полета:
- `std::vector<std::unique_ptr<Shape>> shapes`

### Методи:
- `void add(std::unique_ptr<Shape> shape)`
- `double getTotalArea() const`
- `double getTotalPerimeter() const`
- `const Shape* getLargestByArea() const` 
- `const Shape* getSmallestByArea() const`
- `void printAll(std::ostream& os) const`
- `std::vector<const Shape*> filterByMinArea(double minArea) const`

---

# Задача 2:
Имплементирайте разширена версия на камък ножица хартия, използвайки **статичен полиморфизъм** - `std::variant` и **Visitor pattern**. Всеки обект трябва да знае как да се бие срещу всеки друг и да връща резултат от тип `Outcome`.

Правилата на играта:

![Rock Paper Scissors Lizard Spock diagram](https://i.sstatic.net/M6PeTZvp.png)

---

## Enum клас `Outcome`

```cpp
enum class Outcome { Win, Loss, Draw };
```

`Outcome` има и помощна функция за принтиране:

```cpp
std::string toString(Outcome o);
```

---

## Направете си структури за всеки обект и след това ползвайте това:

```cpp
using Gesture = std::variant<Rock, Paper, Scissors, Lizard, Spock>;
```
---

## Visitor `NameVisitor`

`NameVisitor` връща името на жест като `std::string`. Използва се чрез помощната функция `getGestureName`.

```cpp
#pragma once
#include "Outcome.h"
#include "Gestures.h"
#include <iostream>

struct NameVisitor {
    std::string operator()(const Rock& rock) const;
    std::string operator()(const Paper& paper) const;
    std::string operator()(const Scissors& scissors) const;
    std::string operator()(const Lizard& lizard) const;
    std::string operator()(const Spock& spock) const;
};

std::string getGestureName(const Gesture& gesture);
```

---

## Visitor `FightVisitor`

### Описание:
`FightVisitor` е структура, която се подава на `std::visit` и сравнява два обекта от тип `Gesture`. Всяка комбинация `operator()(const A&, const B&)` трябва да е дефинирана.

### Методи (примери):
- `Outcome operator()(const Rock&, const Scissors&) const` -> `Win`
- `Outcome operator()(const Rock&, const Paper&) const` -> `Loss`
- `Outcome operator()(const Rock&, const Rock&) const` -> `Draw`
- ... (всички 25 комбинации)

---

## Функция `fight`

```cpp
Outcome fight(const Gesture& a, const Gesture& b);
```

---

## Клас `Game`

### Private полета:
- `std::vector<std::pair<Gesture, Gesture>> history`
- `int winsA`, `int winsB`, `int draws`

### Методи:
- `Outcome playRound(const Gesture& a, const Gesture& b)`
  - Записва хода в `history` и обновява резултата
- `void printScore(std::ostream& os) const`
  - Формат: `Player A: {winsA} | Draws: {draws} | Player B: {winsB}`
- `void printHistory(std::ostream& os) const`

---

# Задача 3:

Имплементирайте система за обработка на текст, която използва **Strategy pattern** за да смени поведението си по време на изпълнение. Различни стратегии дефинират как текстът се трансформира, филтрира или анализира - без да се променя самият `TextProcessor`.

---

## Интерфейс `TextStrategy`

### Public виртуални методи:
- `virtual std::string apply(const std::string& input) const = 0`
- `virtual std::string name() const = 0`
- `virtual ~TextStrategy() = default`

---

## Стратегии за трансформация

### Клас `UpperCaseStrategy`
#### Наследява: `TextStrategy`
- `apply`: връща текста с всички символи в главни букви
- `name`: `"UpperCase"`

---

### Клас `LowerCaseStrategy`
#### Наследява: `TextStrategy`
- `apply`: връща текста с всички символи в малки букви
- `name`: `"LowerCase"`

---

### Клас `ReverseStrategy`
#### Наследява: `TextStrategy`
- `apply`: връща текста наобратно
- `name`: `"Reverse"`

---

### Клас `TrimStrategy`
#### Наследява: `TextStrategy`
- `apply`: премахва водещи и следващи whitespace символи
- `name`: `"Trim"`

---

### Клас `ReplaceStrategy`
#### Наследява: `TextStrategy`

#### Private полета:
- `std::string from`
- `std::string to`

#### Конструктор:
- `ReplaceStrategy(const std::string& from, const std::string& to)`

#### Методи:
- `apply`: заменя всички срещания на `from` с `to`
- `name`: `"Replace({from} -> {to})"`

---

### Клас `CensorStrategy`
#### Наследява: `TextStrategy`

#### Private полета:
- `std::vector<std::string> bannedWords`

#### Конструктор:
- `CensorStrategy(std::vector<std::string> bannedWords)`

#### Методи:
- `apply`: заменя всяка забранена дума с толкова '*', колкото е дължината на думата
- `name`: `"Censor"`

---

## Клас `TextProcessor`

### Private полета:
- `std::vector<std::unique_ptr<TextStrategy>> pipeline`

### Методи:
- `TextProcessor& addStrategy(std::unique_ptr<TextStrategy> strategy)`
  - Добавя стратегия в края на pipeline-а; връща `*this` за chaining
- `TextProcessor& removeStrategy(const std::string& name)`
  - Премахва стратегия по `name()`
- `std::string process(const std::string& input) const`
  - Прилага всички стратегии последователно
- `void printPipeline(std::ostream& os) const`
  - Формат: `Pipeline: [UpperCase] -> [Trim] -> [Censor]`
- `void clearPipeline()`
