# Задача 1: Система за управление на банкови сметки

## Йерархия на изключенията

### Клас `BankException`
#### Наследява: `std::exception`
#### Private полета:
- `std::string message`
#### Конструктор:
- `BankException(const std::string& message)`
#### Методи:
- `const char* what() const noexcept override`

---

### Клас `InsufficientFundsException`
#### Наследява: `BankException`
#### Private полета:
- `double requested`
- `double available`
#### Конструктор:
- `InsufficientFundsException(double requested, double available)`
#### Формат на съобщението:
```
Insufficient funds: requested {requested}, available {available}
```

---

### Клас `InvalidAmountException`
#### Наследява: `BankException`
#### Private полета:
- `double invalidAmount`
#### Конструктор:
- `InvalidAmountException(double amount)`
#### Формат на съобщението:
```
Invalid amount: {amount}. Amount must be positive
```

---

### Клас `AccountFrozenException`
#### Наследява: `BankException`
#### Private полета:
- `std::string accountNumber`
#### Конструктор:
- `AccountFrozenException(const std::string& accountNumber)`
#### Формат на съобщението:
```
Account {accountNumber} is frozen
```

---

### Клас `SelfTransferException`
#### Наследява: `BankException`
#### Конструктор:
- `SelfTransferException()`
#### Формат на съобщението:
```
Cannot transfer money to the same account
```

---

## Клас `BankAccount`
### Private полета:
- `std::string accountNumber`
- `std::string ownerName`
- `double balance`
- `bool isFrozen`
### Конструктор:
- `BankAccount(std::string accNumber, std::string owner, double initialBalance)`
### Валидации в конструктора:
- Ако `accNumber` не е с дължина 10 или съдържа не-цифрени символи -> хвърля `std::invalid_argument`
- Ако `owner` е празен низ -> хвърля `std::invalid_argument`
- Ако `initialBalance` е отрицателен -> хвърля `InvalidAmountException`
### Методи:
- `void deposit(double amount)`
  - Ако сметката е замразена -> хвърля `AccountFrozenException`
  - Ако `amount <= 0` -> хвърля `InvalidAmountException`
  - Ако `amount > 1 000 000` -> хвърля `std::overflow_error("Deposit exceeds maximum limit")`
- `void withdraw(double amount)`
  - Ако сметката е замразена -> хвърля `AccountFrozenException`
  - Ако `amount <= 0` -> хвърля `InvalidAmountException`
  - Ако `amount > balance` -> хвърля `InsufficientFundsException`
- `void transfer(BankAccount& destination, double amount)`
  - Ако текущата сметка е замразена -> хвърля `AccountFrozenException`
  - Ако целевата сметка е замразена -> хвърля `AccountFrozenException`
  - Ако `destination` е същата сметка -> хвърля `SelfTransferException`
  - Ако `amount <= 0` -> хвърля `InvalidAmountException`
  - Ако `amount > balance` -> хвърля `InsufficientFundsException`
- `void freeze()` - замразява сметката
- `void unfreeze()` - размразява сметката

---

## Функция `processTransaction`
```cpp
void processTransaction(BankAccount& from, BankAccount& to, double amount);
```
Извиква `from.transfer(to, amount)` и прихваща изключенията в следния ред:
1. `SelfTransferException` - извежда съобщението за грешка
2. `InsufficientFundsException` - извежда съобщението, поисканата и наличната сума
3. `AccountFrozenException` - извежда съобщението за грешка
4. `InvalidAmountException` - извежда съобщението за грешка
5. `BankException` - извежда общо съобщение за банкова грешка
6. `std::overflow_error` - извежда `System error: {message}`
7. `std::exception` - извежда `Unknown error: {message}`
8. `...` - извежда `Critical unknown error occurred`

Независимо от резултата, винаги извежда: `Transaction processing completed`

# Задача 2: Система за управление на рецепти

## `enum class RecipeError`
```cpp
enum class RecipeError {
    EmptyName,
    InvalidServings,
    InvalidCookingTime,
    IngredientNotFound,
    InsufficientQuantity,
    DuplicateIngredient,
    EmptyRecipe
};
```

---

## Клас `Ingredient`
### Private полета:
- `std::string name`
- `double quantity`
- `std::string unit`
### Конструктор:
- `Ingredient(std::string name, double quantity, std::string unit)`
### Методи:
- `const std::string& getName() const`
- `double getQuantity() const`
- `const std::string& getUnit() const`
- `std::expected<void, RecipeError> adjustQuantity(double factor)`
  - Връща `RecipeError::InvalidServings` ако `factor <= 0`
  - При успех умножава `quantity` по `factor`

---

## Клас `Recipe`
### Private полета:
- `std::string name`
- `int servings`
- `int cookingTimeMinutes`
- `std::vector<Ingredient> ingredients`
### Static factory method:
- `static std::expected<Recipe, RecipeError> create(const std::string& name, int servings, int cookingTimeMinutes)`
  - Връща `RecipeError::EmptyName` ако `name` е празно
  - Връща `RecipeError::InvalidServings` ако `servings <= 0`
  - Връща `RecipeError::InvalidCookingTime` ако `cookingTimeMinutes <= 0`
  - При успех връща валиден `Recipe` обект
### Методи:
- `std::expected<void, RecipeError> addIngredient(const Ingredient& ingredient)`
  - Връща `RecipeError::DuplicateIngredient` ако съставка с това име вече съществува
- `std::expected<void, RecipeError> removeIngredient(const std::string& name)`
  - Връща `RecipeError::IngredientNotFound` ако не е намерена
- `std::optional<Ingredient> findIngredient(const std::string& name) const`
  - Връща `std::nullopt` ако не е намерена
- `std::expected<Recipe, RecipeError> scaleToServings(int targetServings) const`
  - Връща `RecipeError::InvalidServings` ако `targetServings <= 0`
  - Връща `RecipeError::EmptyRecipe` ако рецептата няма съставки
  - При успех връща нова `Recipe` с коригирани количества
- `std::optional<int> estimatedCaloriesPerServing() const`
  - Връща `std::nullopt` ако рецептата няма съставки
  - Иначе връща приблизителна стойност (100 калории на съставка на порция)
- `const std::string& getName() const`
- `int getServings() const`
- `int getCookingTimeMinutes() const`
- `const std::vector<Ingredient>& getIngredients() const`

---

## Клас `RecipeBook`
### Private полета:
- `std::string title`
- `std::vector<Recipe> recipes`
### Конструктор:
- `RecipeBook(const std::string& title)`
### Методи:
- `std::expected<void, RecipeError> addRecipe(const Recipe& recipe)`
  - Връща `RecipeError::DuplicateIngredient` ако рецепта с това име вече съществува (преизползвайте грешката)
- `std::expected<void, RecipeError> removeRecipe(const std::string& name)`
  - Връща `RecipeError::IngredientNotFound` ако не е намерена (преизползвайте грешката)
- `std::optional<Recipe> findRecipe(const std::string& name) const`
  - Връща `std::nullopt` ако не е намерена
- `std::optional<Recipe> findQuickestRecipe() const`
  - Връща рецептата с най-малко `cookingTimeMinutes`, или `std::nullopt` ако книгата е празна
- `std::vector<Recipe> getRecipesUnder(int maxMinutes) const`
  - Връща всички рецепти с `cookingTimeMinutes <= maxMinutes`
- `int totalRecipes() const`

---
