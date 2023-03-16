#include <iostream>
#include <map>
#include <string>
/*
Опишите, используя структуру, сортировку почтовых посылок (город, улица, дом, квартира, кому, ценность)
Составьте программу, определяющую: 
1) сколько посылок отправлено в г. Нижний Новгород; 
2) сколько и куда отправлено посылок ценностью выше 100 рублей; 
3) есть ли адреса, куда отправлено более 1 посылки, если есть, то сколько и кому.
*/

// Описание структуры для почтовой посылки
struct Package {
    std::string city; // город
    std::string street; // улица
    int house_number; // дом
    int apartment_number; // квартира
    std::string recipient; // получатель
    double value; // ценность 
};

const double MINIMUM_VALUE = 100.0;

int main()
{
    setlocale(LC_ALL, "Russian");

    std::cout << "Введите количество посылок: ";
    int countItems;
    std::cin >> countItems;

    // Инициализация массива посылок
    Package* packages = new Package[countItems];

    for (int i = 0; i < countItems; ++i) {
        std::cout << "\nПосылка #" << i + 1 << "\n";

        std::cout << "Введите город: ";
        std::cin >> packages[i].city;
        if (packages[i].city.empty()) {
            std::cout << "Город не указан\n";
            return 1;
        }

        std::cout << "Введите улицу: ";
        std::cin >> packages[i].street;
        if (packages[i].street.empty()) {
            std::cout << "Улица не указана\n";
            return 1;
        }

        std::cout << "Введите номер дома: ";
        std::cin >> packages[i].house_number;
        if (packages[i].house_number < 0) {
            std::cout << "Некорректное значение номера дома\n";
            return 1;
        }

        std::cout << "Введите номер квартиры: ";
        std::cin >> packages[i].apartment_number;
        if (packages[i].apartment_number < 0) {
            std::cout << "Некорректное значение номера квартиры\n";
            return 1;
        }

        std::cout << "Введите имя получателя: ";
        std::cin >> packages[i].recipient;
        if (packages[i].recipient.empty()) {
            std::cout << "Получатель не указан\n";
            return 1;
        }

        std::cout << "Введите ценность посылки: ";
        std::cin >> packages[i].value;
        if (packages[i].value < 1) {
            std::cout << "Минимальная ценность посылки " << 1 << " руб.\n";
            return 1;
        }
    }

    /* 1 часть задачи начало */

    int count = 0; // Подсчет количества посылок, отправленных в г. Нижний Новгород
    for (int i = 0; i < countItems; ++i) {
        if (packages[i].city == "Нижний Новгород") count++;
    }
    std::cout << "Отправлено посылок в г. Нижний Новгород: " << count << std::endl;

    /* 1 часть задачи конец */

    std::cout << "\n";

    /* 2 часть задачи начало */

    // Создаем пустой map для подсчета количества посылок по городам
    std::map<std::string, int> package_counts; // string - название корода, int - количество посылок отправленных в городе с ценностью свыше 100

    // Проходим по всем посылкам
    for (int i = 0; i < countItems; ++i) {
        // Если ценность посылки больше 100, то увеличиваем счетчик для соответствующего города
        if (packages[i].value > MINIMUM_VALUE) package_counts[packages[i].city]++;
    }

    std::cout << "Посылки ценностью выше 100 рублей были отправлены в следующие города:\n";
    for (const auto& [key, count] : package_counts) {
        std::cout << "- " << key << ": " << count << " посылок\n";
    }

    /* 2 часть задачи конец */

    std::cout << "\n";

    /* 3 часть задачи начало */

    std::map<std::string, int> address_counts;

    for (int i = 0; i < countItems; ++i) {
        // Составляем полный адрес
        std::string address = packages[i].city
            + ", " + packages[i].street + ", "
            + std::to_string(packages[i].house_number)
            + ", " + std::to_string(packages[i].apartment_number);

        address_counts[address]++;
    }

    bool found_duplicates = false;

    for (auto [address, count] : address_counts) {
        if (count > 1) {
            std::cout << "Адресс: " << address << " получил " << count << " поссылки\n";
            found_duplicates = true;
        }
    }

    if (!found_duplicates) std::cout << "Ни на один адрес не поступило более одной посылки\n";

    /* 3 часть задачи конец */
}