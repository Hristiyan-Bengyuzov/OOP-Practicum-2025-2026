

## Задача 1: Система за управление на банкови сметки 

Създайте следната йерархия от изключения:

### `BankException (наследява std::exception)`
#### Изисквания

- Наследява `std::exception`
- Съдържа член-данна:

```
std::string message;
```

- Конструктор `BankException(const std::string& message)`

- Имплементира:
```cpp
const char* what() const noexcept override;
```

### `InsufficientFundsException`

Наследява `BankException`.

#### Допълнителни член-данни

```cpp
double requested;
double available;
```

#### Конструктор

```cpp
InsufficientFundsException(double requested, double available);
```

#### Формат на съобщението

```text
Insufficient funds: requested {requested}, available {available}
```

---

### `InvalidAmountException`

Наследява `BankException`.

#### Член-данна

```cpp
double invalidAmount;
```

#### Формат на съобщението

```text
Invalid amount: {amount}. Amount must be positive
```

---

### `AccountFrozenException`

Наследява `BankException`.

#### Член-данна

```cpp
std::string accountNumber;
```

#### Формат на съобщението

```text
Account {accountNumber} is frozen
```

---

### `SelfTransferException`

Наследява `BankException`.

#### Формат на съобщението

```text
Cannot transfer money to the same account
```

---

# Клас `BankAccount`

## Член-данни

```cpp
std::string accountNumber;
std::string ownerName;
double balance;
bool isFrozen;
```

## Конструктор

```cpp
BankAccount(
    const std::string& accNumber,
    const std::string& owner,
    double initialBalance
);
```

### Валидации

#### Невалиден номер на сметка

Ако номерът:

- не е с дължина 10
- съдържа символи, различни от цифри

трябва да се хвърли:

```cpp
std::invalid_argument
```

---

#### Празно име

Ако името на собственика е празно:

```cpp
throw std::invalid_argument(...)
```

---

#### Отрицателен начален баланс

Ако началният баланс е отрицателен:

```cpp
throw InvalidAmountException(...)
```

---

# Методи
## `deposit`

```cpp
void deposit(double amount);
```

#### Ако сметката е замразена

```cpp
throw AccountFrozenException(...)
```

#### Ако сумата е <= 0

```cpp
throw InvalidAmountException(...)
```

#### Ако сумата е над 1 000 000

```cpp
throw std::overflow_error(
    "Deposit exceeds maximum limit"
);
```
---

## `withdraw`

```cpp
void withdraw(double amount);
```

#### Ако сметката е замразена

```cpp
throw AccountFrozenException(...)
```

#### Ако сумата е <= 0

```cpp
throw InvalidAmountException(...)
```

#### Ако сумата надвишава баланса

```cpp
throw InsufficientFundsException(...)
```

---

## `transfer`

```cpp
void transfer(BankAccount& destination, double amount);
```

### Поведение

#### Ако текущата сметка е замразена

```cpp
throw AccountFrozenException(...)
```

#### Ако целевата сметка е замразена

```cpp
throw AccountFrozenException(...)
```

---

#### Ако се опитва трансфер към същата сметка

```cpp
throw SelfTransferException(...)
```

---

#### Ако сумата е невалидна

```cpp
throw InvalidAmountException(...)
```

---

#### Ако няма достатъчно средства

```cpp
throw InsufficientFundsException(...)
```

---

## `freeze`

```cpp
void freeze();
```

Замразява сметката.

---

## `unfreeze`

```cpp
void unfreeze();
```

Размразява сметката.
---

# Функция `processTransaction`

```cpp
void processTransaction(
    BankAccount& from,
    BankAccount& to,
    double amount
);
```

---

## Поведение

Функцията трябва да извиква:

```cpp
from.transfer(to, amount);
```

---

## Обработка на изключения

Изключенията трябва да се обработват в **следния ред**:

### 1. `SelfTransferException`

Извежда съобщение за грешка.

---

### 2. `InsufficientFundsException`

Извежда:

- съобщението за грешка
- поисканата сума
- наличната сума

---

### 3. `AccountFrozenException`

Извежда съобщение за грешка.

---

### 4. `InvalidAmountException`

Извежда съобщение за грешка.

---

### 5. `BankException`

Извежда общо съобщение за банкова грешка.

---

### 6. `std::overflow_error`

Извежда:

```text
System error: {message}
```

---

### 7. `std::exception`

Извежда:

```text
Unknown error: {message}
```

---

### 8. Catch-all (`...`)

Извежда:

```text
Critical unknown error occurred
```

---

Независимо дали транзакцията е успешна или не, функцията винаги трябва да извежда:

```text
Transaction processing completed
```
