# В тези задачи контейнерите могат да се направят много по-добре чрез полиморфизъм (с вектор от указатели към базовия клас или чрез `std::variant`). 
# Упражнението обаче е на наследяване, така че ще го направим с отделни вектори

# Quiz: https://wayground.com/admin/quiz/69f103eb4e06d4d45a4b2a61

# Задача 1

## Клас `Animal`

### Private полета:
- `std::string name`
- `std::string species`
- `int age`
- `double weight`

### Конструктор:
- `Animal(std::string name, std::string species, int age, double weight)`

### Методи:
- `const std::string& getName() const`
- `const std::string& getSpecies() const`
- `int getAge() const`
- `double getWeight() const`
- `void displayInfo() const`

### Оператори:
- `bool operator==(const Animal& other) const`
- `auto operator<=>(const Animal& other) const` - първо по `age`, после по `name`
- `friend std::ostream& operator<<(std::ostream&, const Animal&)`

---

## Клас `Dog` : публично наследява `Animal`

### Private полета:
- `std::string breed`
- `bool isTrained`
- `int tricksKnown`

### Конструктор:
- `Dog(std::string name, int age, double weight, std::string breed, bool isTrained)`

### Методи:
- `const std::string& getBreed() const`
- `bool getIsTrained() const`
- `int getTricksKnown() const`
- `void learnTrick()` - увеличава `tricksKnown` с 1, само ако `isTrained` е `true`
- `void train()` - слага `isTrained = true`
- `void displayInfo() const` - принтира информацията от `Animal`, плюс порода, дресировка и брой трикове
- `bool canCompete() const` - връща `true`, ако кучето е дресирано и знае поне 3 трика

---

## Клас `Cat` : публично наследява `Animal`

### Private полета:
- `bool isIndoor`
- `int livesLeft`
- `int scratchCount`

### Конструктор:
- `Cat(std::string name, int age, double weight, bool isIndoor)`
- `livesLeft` се инициализира на `9`
- `scratchCount` се инициализира на `0`

### Методи:
- `bool getIsIndoor() const`
- `int getLivesLeft() const`
- `int getScratchCount() const`
- `void loseLife()` - намалява `livesLeft` с 1, минимум `0`
- `void scratch()` - увеличава `scratchCount` с 1; ако `scratchCount` достигне `5`, извиква `loseLife()` и нулира брояча
- `bool isAlive() const` - връща `true`, ако `livesLeft > 0`
- `void displayInfo() const`

---

## Клас `Shelter`

### Private полета:
- `std::string shelterName`
- `std::vector<Dog> dogs`
- `std::vector<Cat> cats`

### Конструктор:
- `Shelter(std::string shelterName)`

### Методи:
- `void addDog(const Dog& d)`
- `void addCat(const Cat& c)`
- `void removeDogByName(const std::string& name)`
- `void removeCatByName(const std::string& name)`
- `void listDogs() const`
- `void listCats() const`
- `std::vector<Dog> getCompetitiveDogs() const` - връща кучета, за които `canCompete()` е `true`
- `std::optional<Dog> findOldestDog() const`
- `std::optional<Cat> findCatWithMostLives() const`
- `int totalAnimals() const`

### Оператор:
- `explicit operator bool() const` - връща `true`, ако има поне едно животно

---

# Задача 2

## Клас `BankAccount`

### Private полета:
- `std::string owner`
- `std::string iban`
- `double balance`
- `std::vector<std::string> transactionHistory`

### Конструктор:
- `BankAccount(std::string owner, std::string iban, double initialBalance)`

### Методи:
- `const std::string& getOwner() const`
- `const std::string& getIban() const`
- `double getBalance() const`
- `const std::vector<std::string>& getHistory() const`
- `void deposit(double amount)` - добавя запис в историята от вида `"Deposit: +amount"`
- `bool withdraw(double amount)` - връща `false`, ако няма достатъчно средства; добавя запис `"Withdrawal: -amount"`
- `void printHistory() const`
- `void displayInfo() const`

### Оператори:
- `bool operator==(const BankAccount& other) const` - по `iban`
- `auto operator<=>(const BankAccount& other) const` - по `balance`
- `friend std::ostream& operator<<(std::ostream&, const BankAccount&)`

---

## Клас `SavingsAccount` : публично наследява `BankAccount`

### Private полета:
- `double interestRate` - годишна лихва (напр. `0.05` = 5%)
- `int monthsActive`

### Конструктор:
- `SavingsAccount(std::string owner, std::string iban, double initialBalance, double interestRate)`

### Методи:
- `double getInterestRate() const`
- `int getMonthsActive() const`
- `void applyMonthlyInterest()` - прибавя `balance * interestRate / 12` към баланса, увеличава `monthsActive` с 1, добавя запис в историята
- `void displayInfo() const`

---

## Клас `CreditAccount` : публично наследява `BankAccount`

### Private полета:
- `double creditLimit`
- `double debtAmount`
- `double monthlyFeeRate` - такса върху дълга (напр. `0.02` = 2% на месец)

### Конструктор:
- `CreditAccount(std::string owner, std::string iban, double creditLimit, double monthlyFeeRate)`
- `balance` се инициализира на `0`, `debtAmount` на `0`

### Методи:
- `double getCreditLimit() const`
- `double getDebtAmount() const`
- `double getAvailableCredit() const` - `creditLimit - debtAmount`
- `bool borrow(double amount)` - взима сума до наличния кредит; добавя към `debtAmount`; добавя запис в историята; връща `false`, ако надхвърля лимита
- `void repay(double amount)` - намалява `debtAmount` (минимум `0`); добавя запис
- `void applyMonthlyFee()` - добавя `debtAmount * monthlyFeeRate` към `debtAmount`; добавя запис
- `bool isOverdue() const` - връща `true`, ако `debtAmount > creditLimit * 0.9`
- `void displayInfo() const`

---

## Клас `Bank`

### Private полета:
- `std::string bankName`
- `std::vector<SavingsAccount> savingsAccounts`
- `std::vector<CreditAccount> creditAccounts`

### Конструктор:
- `Bank(std::string bankName)`

### Методи:
- `void openSavings(const SavingsAccount& acc)`
- `void openCredit(const CreditAccount& acc)`
- `void closeByIban(const std::string& iban)`
- `void applyAllMonthlyInterest()` - извиква `applyMonthlyInterest()` за всяка спестовна сметка
- `void applyAllMonthlyFees()` - извиква `applyMonthlyFee()` за всяка кредитна сметка
- `std::vector<CreditAccount> getOverdueAccounts() const`
- `std::optional<SavingsAccount> findRichest() const`
- `double totalDebt() const` - сума на всички `debtAmount`

### Оператор:
- `explicit operator bool() const` - връща `true`, ако банката има поне една сметка

---

# Задача 3

## Клас `Character`

### Private полета:
- `std::string name`
- `int health`
- `int maxHealth`
- `int attackPower`
- `int defense`
- `int level`
- `int experience`

### Конструктор:
- `Character(std::string name, int health, int attackPower, int defense)`
- `level` се инициализира на `1`, `experience` на `0`

### Методи:
- `const std::string& getName() const`
- `int getHealth() const`
- `int getMaxHealth() const`
- `int getAttackPower() const`
- `int getDefense() const`
- `int getLevel() const`
- `int getExperience() const`
- `bool isAlive() const`
- `void takeDamage(int amount)` - намалява `health` с `max(0, amount - defense)`; `health` не пада под `0`
- `void heal(int amount)` - увеличава `health` с `amount`, но не над `maxHealth`
- `void gainExperience(int amount)` - натрупва опит; при достигане на `level * 100` точки извиква `levelUp()`
- `void displayInfo() const`

### Protected методи:
- `void levelUp()` - увеличава `level` с 1, нулира `experience`, вика `onLevelUp()`
- `virtual void onLevelUp()` - базовата версия увеличава `maxHealth` с `10` и `health` се попълва до новия максимум

### Оператори:
- `bool operator==(const Character& other) const` - по `name`
- `auto operator<=>(const Character& other) const` - по `level`, после по `health`
- `friend std::ostream& operator<<(std::ostream&, const Character&)`

---

## Клас `Warrior` : публично наследява `Character`

### Private полета:
- `int rage`
- `int maxRage`
- `bool berserkActive`

### Конструктор:
- `Warrior(std::string name, int health, int attackPower, int defense)`
- `rage` се инициализира на `0`, `maxRage` на `100`, `berserkActive` на `false`

### Методи:
- `int getRage() const`
- `bool isBerserk() const`
- `void takeDamage(int amount)` - извиква базовото `takeDamage`, после добавя `10` ярост
- `void activateBerserk()` - ако `rage >= 50`, слага `berserkActive = true` и удвоява `attackPower`; нулира `rage`
- `void deactivateBerserk()` - връща `attackPower` към нормалното, слага `berserkActive = false`
- `void strike(Character& target)` - нанася щета на target; ако `berserkActive`, добавя допълнителни `15` щети
- `void onLevelUp()` - базовото поведение плюс увеличава `maxRage` с `20` и `defense` с `2`
- `void displayInfo() const`

---

## Клас `Mage` : публично наследява `Character`

### Private полета:
- `int mana`
- `int maxMana`
- `int spellPower`
- `int spellsCast`

### Конструктор:
- `Mage(std::string name, int health, int attackPower, int defense, int mana, int spellPower)`

### Методи:
- `int getMana() const`
- `int getMaxMana() const`
- `int getSpellPower() const`
- `int getSpellsCast() const`
- `void restoreMana(int amount)`
- `bool castFireball(Character& target)` - струва `30` мана; нанася `spellPower * 2` щети; връща `false`, ако няма достатъчно мана; увеличава `spellscast` с 1
- `bool castHeal(Character& target)` - струва `20` мана; лекува target с `spellPower`; връща `false`, ако няма достатъчно мана
- `bool castFrostbolt(Character& target)` - струва `15` мана; нанася `spellPower` щети; намалява `attackPower` на target с `5` за целта на тази битка; връща `false` при недостатъчно мана
- `void onLevelUp()` - базовото поведение плюс увеличава `maxMana` с `20`, `mana` се попълва, `spellPower` расте с `5`
- `void displayInfo() const`

---

## Клас `Party`

### Private полета:
- `std::string partyName`
- `std::vector<Warrior> warriors`
- `std::vector<Mage> mages`

### Конструктор:
- `Party(std::string partyName)`

### Методи:
- `void addWarrior(const Warrior& w)`
- `void addMage(const Mage& m)`
- `void removeByName(const std::string& name)`
- `void listAll() const`
- `bool isWiped() const` - връща `true`, ако всички герои имат `isAlive() == false`
- `void restoreAll(int amount)` - извиква `heal(amount)` за всеки жив герой
- `std::optional<Warrior> findStrongestWarrior() const` - по `attackPower`
- `std::optional<Mage> findMostExperienced() const` - по `level`, после по `experience`
- `int totalLevel() const`

### Оператор:
- `explicit operator bool() const` - връща `true`, ако има поне един жив герой
