# Проектирование и реализация класса «Обувной магазин»

Добро пожаловать в репозиторий "Обувной Магазин"! Этот проект представляет собой консольное приложение, созданное на языке программирования C++, которое позволяет управлять данными о продукции в обувном магазине. Программа предоставляет пользователю возможность добавлять новую обувь, искать обувь по различным критериям, сортировать продукцию и сохранять данные в файл для последующего использования.

## Основные Функции

### 1. Добавление Обуви
Пользователь может добавлять новые пары обуви, указывая бренд, модель, размер и цену.

### 2. Поиск Обуви
Поиск обуви можно производить по подстроке в бренде или модели. Программа выводит результаты поиска на экран.

### 3. Сортировка Обуви
Пользователь может сортировать обувь по бренду, размеру или цене, чтобы легко находить нужные пары.

### 4. Сохранение и Загрузка Данных
Программа позволяет сохранять данные о продукции в файл и загружать их из файла для последующего использования.

## Как Использовать

1. **Загрузка данных из файла:** При запуске программы пользователь может указать имя файла, из которого будут загружены данные о продукции. Если файл не найден, можно вручную добавить обувь через меню.

2. **Меню:** Программа предоставляет пользователю удобное текстовое меню для выбора различных операций.

3. **Добавление Обуви:** При выборе соответствующего пункта в меню пользователь может ввести данные о новой обуви, включая бренд, модель, размер и цену.

4. **Поиск Обуви:** Поиск производится по введенной пользователем подстроке в бренде или модели. Результаты отображаются на экране.

5. **Сортировка Обуви:** Пользователь может выбрать опцию сортировки по бренду, размеру или цене. Отсортированные данные выводятся на экран.

6. **Сохранение и Загрузка:** Данные о продукции могут быть сохранены в файл, указанный пользователем. Также можно загрузить данные из файла для продолжения работы.

## Как Запустить Программу

Для запуска программы необходим компилятор C++. Просто склонируйте данный репозиторий на свой локальный компьютер и скомпилируйте исходный файл с помощью компилятора C++ (например, g++). Запустите исполняемый файл и начните использование программы.

## От автора

Этот проект создан с любовью и страстью к программированию. Если у вас есть какие-либо вопросы, предложения или сообщения об ошибках. Ваши отзывы важны для нас и помогут сделать этот проект еще лучше!

Благодарим за ваш интерес к "Обувному Магазину"!




### Класс `Shoe`:
- **Атрибуты**: Класс содержит четыре атрибута - `brand` (бренд обуви), `model` (модель обуви), `size` (размер обуви) и `price` (цена обуви).
- **Методы**:
  - `compareByBrand()`, `compareBySize()`, `compareByPrice()`: Статические методы для сравнения объектов класса `Shoe` по бренду, размеру и цене соответственно.
  - `containsSubstring()`: Статический метод для определения содержит ли переданная строка подстроку (регистронезависимо).
  - `containsSubstring(const std::string& substr) const`: Метод для определения, содержит ли текущий объект подстроку в атрибутах `brand` или `model`.
  - `getBrand() const`: Метод для получения бренда текущего объекта.

### Класс `ShoeStore`:
- **Атрибуты**: Вектор `shoes` для хранения объектов класса `Shoe`.
- **Методы**:
  - `printShoes() const`: Метод для вывода информации о всех обувях в магазине.
  - `addShoe(const Shoe& shoe)`: Метод для добавления обуви в магазин.
  - `searchShoes(const std::string& substr) const`: Метод для поиска обуви по подстроке в бренде или модели.
  - `sortShoesByBrand()`, `sortShoesBySize()`, `sortShoesByPrice()`: Методы для сортировки обуви по бренду, размеру и цене соответственно.
  - `searchShoesByBrandAndModel(const std::string& brand, const std::string& model) const`: Метод для поиска обуви по бренду и модели.
  - `saveToFile(const std::string& filename) const`: Метод для сохранения данных о обуви в файл.
  - `loadFromFile(const std::string& filename)`: Метод для загрузки данных о обуви из файла.

### Функция `main()`:
- **Переменные**: Создается объект класса `ShoeStore` с именем `store` и переменная `filename` для хранения имени файла.
- **Цикл загрузки данных из файла**: Пользователь вводит имя файла, программа пытается открыть файл, если успешно, данные загружаются в магазин. В случае ошибки открытия файла выводится сообщение об ошибке, и пользователю предлагается повторить ввод имени файла.
- **Основное меню**: Пользователю предлагается выбрать одну из опций:
  1. **Добавить обувь**: Пользователь вводит бренд, модель, размер и цену обуви, которую нужно добавить в магазин.
  2. **Поиск обуви**: Пользователь вводит подстроку для поиска и программа выводит все обуви, в названии которых содержится данная подстрока.
  3. **Сортировка обуви**: Пользователь выбирает по какому критерию (бренд, размер, цена) отсортировать обувь, после чего отсортированный список обуви выводится на экран.
  4. **Сохранить данные в файл**: Пользователь вводит имя файла, в который нужно сохранить данные о текущих обувях в магазине.
  5. **Поиск по бренду и модели**: Пользователь вводит бренд и модель обуви, программа выводит обувь, которая соответствует введенным критериям.
  6. **Выход**: Программа завершает выполнение.

Каждый шаг пользователя обрабатывается соответствующим образом, в случае ошибочного ввода выводятся соответствующие сообщения об ошибке. После каждой операции программа ожидает нажатия клавиши Enter для продолжения.
