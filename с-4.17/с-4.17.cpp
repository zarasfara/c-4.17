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

    // инициализация массива посылок
    Package packages[] = {
        {"Нижний Новгород", "Ленина", 1, 10, "Иванов", 100.0},
        {"Москва", "Тверская", 5, 20, "Петров", 200.0},

        {"Нижний Новгород", "Московская", 10, 5, "Сидоров", 50.0},
        {"Нижний Новгород", "Московская", 10, 5, "Сидоров", 150.0},
        {"Нижний Новгород", "Московская", 10, 5, "Сидоров", 250.0},
        {"Нижний Новгород", "Горького", 20, 15, "Смирнов", 150.0},

        {"Санкт-Петербург", "Невский", 15, 7, "Козлов", 300.0},
        
        {"Казань", "Кремлевская", 25, 8, "Васильев", 75.0},
        {"Казань", "Кремлевская", 25, 8, "Васильев", 150.0}
    };

    /* 1 часть задачи начало */

    int count = 0; // Подсчет количества посылок, отправленных в г. Нижний Новгород
    for (Package package : packages) {
        if (package.city == "Нижний Новгород") count++;
    }
    std::cout << "Отправлено посылок в г. Нижний Новгород: " << count << std::endl;

    /* 1 часть задачи конец */

    std::cout << "\n";

    /* 2 часть задачи начало */

    // Создаем пустой map для подсчета количества посылок по городам
    std::map<std::string, int> package_counts; // string - название корода, int - количество посылок отправленных в городе с ценностью свыше 100
        
    // Проходим по всем посылкам
    for (Package package : packages) {
        // Если ценность посылки больше 100, то увеличиваем счетчик для соответствующего города
        if (package.value > MINIMUM_VALUE) package_counts[package.city]++;
    }

    std::cout << "Посылки ценностью выше 100 рублей были отправлены в следующие города:\n";
    for (auto [key, count] : package_counts) {
        std::cout << "- " << key << ": " << count << " посылок\n";
    }

    /* 2 часть задачи конец */

    std::cout << "\n";

    /* 3 часть задачи начало */

    std::map<std::string, int> address_counts;

    for (Package package : packages) {
        // Составляем полный адрес
        std::string address = package.city
            + ", " + package.street + ", " 
            + std::to_string(package.house_number)
            + ", " + std::to_string(package.apartment_number);

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