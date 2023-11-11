#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>
#include <limits>

class Shoe {
private:
    std::string brand;
    std::string model;
    int size;
    double price;
    int quantity;

public:
    Shoe(std::string brand, std::string model, int size, double price, int quantity)
        : brand(brand), model(model), size(size), price(price), quantity(quantity) {}

    static bool compareByBrand(const Shoe& a, const Shoe& b) {
        return a.getBrand() < b.getBrand();
    }

    static bool compareBySize(const Shoe& a, const Shoe& b) {
        return a.size < b.size;
    }

    static bool compareByPrice(const Shoe& a, const Shoe& b) {
        return a.price < b.price;
    }
    void setQuantity(int newQuantity) {
        quantity = newQuantity;
    }

    friend std::ostream& operator<<(std::ostream& out, const Shoe& shoe) {
        out << shoe.brand << " " << shoe.model << " " << shoe.size << " " << shoe.price << " " << shoe.quantity;
        return out;
    }

    static bool containsSubstring(const std::string& str, const std::string& substr) {
        std::string lowerStr = str;
        std::string lowerSubstr = substr;
        std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        std::transform(lowerSubstr.begin(), lowerSubstr.end(), lowerSubstr.begin(), ::tolower);

        // Если подстрока состоит только из цифр, ищем любое вхождение подстроки в строку
        if (std::all_of(lowerSubstr.begin(), lowerSubstr.end(), ::isdigit)) {
            return lowerStr.find(lowerSubstr) != std::string::npos;
        }
        else {
            return lowerStr.find(lowerSubstr) != std::string::npos;
        }
    }

    bool containsSubstring(const std::string& substr) const {
        return containsSubstring(brand, substr) || containsSubstring(model, substr);
    }

    std::string getBrand() const {
        return brand;
    }

    std::string getModel() const {
        return model;
    }

    int getSize() const {
        return size;
    }

    double getPrice() const {
        return price;
    }

    int getQuantity() const {
        return quantity;
    }
};

class ShoeStore {
private:
    std::vector<Shoe> shoes;

public:
    void printShoes() const {
        for (const auto& shoe : shoes) {
            std::cout << shoe << std::endl;
        }
    }

    void addShoe(const Shoe& shoe) {
        shoes.push_back(shoe);
    }

    void addShoe(const Shoe& shoe, int quantity) {
        // Проверяем, есть ли уже такая обувь в магазине
        auto it = std::find_if(shoes.begin(), shoes.end(), [&](const Shoe& s) {
            return s.getBrand() == shoe.getBrand() && s.getModel() == shoe.getModel() && s.getSize() == shoe.getSize();
            });

        if (it != shoes.end()) {
            // Если обувь уже есть в магазине, увеличиваем количество пар
            it->setQuantity(it->getQuantity() + quantity);
        }
        else {
            // Иначе добавляем новую обувь в магазин
            Shoe newShoe(shoe.getBrand(), shoe.getModel(), shoe.getSize(), shoe.getPrice(), quantity);
            shoes.push_back(newShoe);
        }
    }

    std::vector<Shoe> searchShoes(const std::string& substr) const {
        std::vector<Shoe> result;
        for (const auto& shoe : shoes) {
            if (shoe.containsSubstring(substr)) {
                result.push_back(shoe);
            }
        }
        return result;
    }

    void sortShoesByBrand() {
        std::sort(shoes.begin(), shoes.end(), [](const Shoe& a, const Shoe& b) {
            return a.getBrand() < b.getBrand();
            });
    }

    void sortShoesBySize() {
        std::sort(shoes.begin(), shoes.end(), Shoe::compareBySize);
    }

    void sortShoesByPrice() {
        std::sort(shoes.begin(), shoes.end(), Shoe::compareByPrice);
    }

    std::vector<Shoe> searchShoesByBrandAndModel(const std::string& brand, const std::string& model) const {
        std::vector<Shoe> result;
        for (const auto& shoe : shoes) {
            if (shoe.containsSubstring(brand) && shoe.containsSubstring(model)) {
                result.push_back(shoe);
            }
        }
        return result;
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& shoe : shoes) {
                file << shoe << std::endl;
            }
            file.close();
            std::cout << "Данные сохранены в файл: " << filename << std::endl;
        }
        else {
            std::cerr << "Ошибка при открытии файла для записи." << std::endl;
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string brand, model;
            int size;
            double price;
            int quantity;

            while (file >> brand >> model >> size >> price >> quantity) {
                Shoe shoe(brand, model, size, price, quantity);
                addShoe(shoe);
            }

            std::cout << "Данные загружены из файла: " << filename << std::endl;
            file.close();
        }
        else {
            std::cerr << "Ошибка при открытии файла для чтения." << std::endl;
        }
    }

    void removeShoe(const std::string& brand, const std::string& model, int size) {
        auto it = std::find_if(shoes.begin(), shoes.end(), [&](const Shoe& s) {
            return s.getBrand() == brand && s.getModel() == model && s.getSize() == size;
            });

        if (it != shoes.end() && it->getQuantity() > 1) {
            // Если есть более одной пары такой обуви, уменьшаем количество пар на 1
            it->setQuantity(it->getQuantity() - 1);
        }
        else if (it != shoes.end() && it->getQuantity() == 1) {
            // Если есть только одна пара такой обуви, удаляем объект Shoe из вектора
            shoes.erase(it);
        }
    }
};

int main() {
    system("chcp 1251");
    ShoeStore store;

    std::string filename;
    while (true) {
        system("cls");
        std::cout << "Введите имя файла для загрузки данных: ";
        std::cin >> filename;

        std::ifstream file(filename);
        if (file.is_open()) {
            file.close();
            store.loadFromFile(filename);
            break;
        }
        else {
            std::cerr << "Ошибка открытия файла. Пожалуйста, проверьте имя файла и попробуйте снова." << std::endl;
            std::cin.clear();
            std::cout << "Операция завершена. Нажмите Enter, чтобы повторить ввод...";
            std::cin.get();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    while (true) {
        std::system("cls");

        std::cout << "Меню:" << std::endl;
        std::cout << "1. Добавить обувь" << std::endl;
        std::cout << "2. Поиск обуви" << std::endl;
        std::cout << "3. Сортировка обуви по бренду" << std::endl;
        std::cout << "4. Сохранить данные в файл" << std::endl;
        std::cout << "5. Поиск по бренду и модели" << std::endl;
        std::cout << "6. Удалить обувь" << std::endl;
        std::cout << "7. Выход" << std::endl;

        int choice;
        std::cout << "Введите номер пункта меню: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string brand, model;
            int size, quantity; // Определение переменной quantity

            std::cout << "Введите бренд обуви: ";
            std::cin.ignore();
            while (std::getline(std::cin, brand)) {
                if (!brand.empty()) {
                    break;
                }
                std::cout << "Некорректный ввод. Пожалуйста, введите непустую строку для бренда: ";
            }

            std::cout << "Введите модель обуви: ";
            while (std::getline(std::cin, model)) {
                if (!model.empty()) {
                    break;
                }
                std::cout << "Некорректный ввод. Пожалуйста, введите непустую строку для модели: ";
            }

            std::cout << "Введите размер обуви: ";
            while (!(std::cin >> size) || size <= 0) {
                std::cout << "Некорректный ввод. Пожалуйста, введите положительное число для размера: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            std::cout << "Введите количество пар обуви: ";
            while (!(std::cin >> quantity) || quantity <= 0) {
                std::cout << "Некорректный ввод. Пожалуйста, введите положительное число для количества пар обуви: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            double price;
            std::cout << "Введите цену обуви: ";
            while (!(std::cin >> price) || price <= 0) {
                std::cout << "Некорректный ввод. Пожалуйста, введите положительное число для цены: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            Shoe shoe(brand, model, size, price, quantity); // Передача значения quantity в конструктор
            store.addShoe(shoe);
            std::cout << "Обувь добавлена в магазин." << std::endl;

            std::cout << "Операция завершена. Нажмите Enter, чтобы продолжить...";
            std::cin.get();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        case 2: {
            std::string searchSubstring;
            std::cout << "Введите подстроку для поиска: ";
            std::cin >> searchSubstring;

            std::vector<Shoe> searchResult = store.searchShoes(searchSubstring);
            std::cout << "Результаты поиска:" << std::endl;
            for (const auto& shoe : searchResult) {
                std::cout << shoe << std::endl;
            }

            std::cout << "Операция завершена. Нажмите Enter, чтобы продолжить...";
            std::cin.get();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        case 3: {
            
            std::cout << "1. По бренду" << std::endl;
            std::cout << "2. По размеру" << std::endl;
            std::cout << "3. По цене" << std::endl;
            std::cout << "Выберите опцию сортировки: ";
            int sortChoice;
            std::cin >> sortChoice;

            switch (sortChoice) {
            case 1:
                store.sortShoesByBrand();
                store.printShoes();
                break;
            case 2:
                store.sortShoesBySize();
                store.printShoes();
                break;
            case 3:
                store.sortShoesByPrice();
                store.printShoes();
                break;
            default:
                std::cout << "Неверный выбор сортировки. Пожалуйста, попробуйте снова." << std::endl;
                break;
            }

            std::cout << "Операция завершена. Нажмите Enter, чтобы продолжить...";
            std::cin.get();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        case 4: {
            std::string filename;
            std::cout << "Введите имя файла для сохранения данных: ";
            std::cin >> filename;
            store.saveToFile(filename);

            std::cout << "Операция завершена. Нажмите Enter, чтобы продолжить...";
            std::cin.get();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        case 5: {
            std::string searchBrand, searchModel;
            std::cout << "Введите бренд обуви для поиска: ";
            std::cin >> searchBrand;
            std::cout << "Введите модель обуви для поиска: ";
            std::cin >> searchModel;

            std::vector<Shoe> brandModelSearchResult = store.searchShoesByBrandAndModel(searchBrand, searchModel);
            std::cout << "Результаты поиска по бренду и модели:" << std::endl;
            for (const auto& shoe : brandModelSearchResult) {
                std::cout << shoe << std::endl;
            }

            std::cout << "Операция завершена. Нажмите Enter, чтобы продолжить...";
            std::cin.get();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        case 6: {
            std::string removeBrand, removeModel;
            int removeSize;
            store.printShoes();
            std::cout << "Введите бренд обуви для удаления: ";
            std::cin >> removeBrand;
            std::cout << "Введите модель обуви для удаления: ";
            std::cin >> removeModel;
            std::cout << "Введите размер обуви для удаления: ";
            std::cin >> removeSize;

            store.removeShoe(removeBrand, removeModel, removeSize);
            std::cout << "Обувь удалена из магазина." << std::endl;

            std::cout << "Операция завершена. Нажмите Enter, чтобы продолжить...";
            std::cin.get();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        case 7: {
            std::cout << "Выход из программы." << std::endl;
            return 0;
        }
        default: {
            std::cout << "Неверный выбор. Попробуйте снова." << std::endl;

            std::cout << "Нажмите Enter, чтобы продолжить...";
            std::cin.get();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        }
    }

    return 0;
}
