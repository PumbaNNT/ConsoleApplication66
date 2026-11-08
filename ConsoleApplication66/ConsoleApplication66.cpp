
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Dictionary {
private:
    map<string, vector<string>> words;

public:
    void AddWord() {
        string word;
        int count;

        cout << "Введіть слово: ";
        cin >> word;

        if (words.find(word) != words.end()) {
            cout << "Таке слово вже існує!" << endl;
            return;
        }

        cout << "Кількість перекладів: ";
        cin >> count;

        if (count <= 0) {
            cout << "Некоректна кількість!" << endl;
            return;
        }

        vector<string> translations;

        for (int i = 0; i < count; i++) {
            string translation;
            cout << "Переклад " << i + 1 << ": ";
            cin >> translation;
            translations.push_back(translation);
        }

        words[word] = translations;
        cout << "Слово додано!" << endl;
    }

    void FindWord() {
        string word;

        cout << "Введіть слово для пошуку: ";
        cin >> word;

        auto it = words.find(word);

        if (it == words.end()) {
            cout << "Слово не знайдено!" << endl;
            return;
        }

        cout << "Переклади слова " << word << ":" << endl;

        for (const string& translation : it->second)
            cout << "- " << translation << endl;
    }

    void AddTranslation() {
        string word, translation;

        cout << "Введіть слово: ";
        cin >> word;

        auto it = words.find(word);

        if (it == words.end()) {
            cout << "Слово не знайдено!" << endl;
            return;
        }

        cout << "Введіть новий переклад: ";
        cin >> translation;

        for (const string& t : it->second) {
            if (t == translation) {
                cout << "Такий переклад вже існує!" << endl;
                return;
            }
        }

        it->second.push_back(translation);
        cout << "Переклад додано!" << endl;
    }

    void DeleteWord() {
        string word;

        cout << "Введіть слово для видалення: ";
        cin >> word;

        if (words.erase(word))
            cout << "Слово видалено!" << endl;
        else
            cout << "Слово не знайдено!" << endl;
    }

    void ShowAll() {
        if (words.empty()) {
            cout << "Словник порожній!" << endl;
            return;
        }

        cout << "\nВсі слова словника:\n";

        for (const auto& item : words) {
            cout << item.first << ": ";

            for (const string& translation : item.second)
                cout << translation << " ";

            cout << endl;
        }
    }

    void SaveToFile() {
        ofstream file("dictionary.txt");

        if (!file) {
            cout << "Помилка відкриття файлу!" << endl;
            return;
        }

        file << words.size() << endl;

        for (const auto& item : words) {
            file << item.first << endl;
            file << item.second.size() << endl;

            for (const string& translation : item.second)
                file << translation << endl;
        }

        file.close();
        cout << "Словник збережено у файл!" << endl;
    }

    void LoadFromFile() {
        ifstream file("dictionary.txt");

        if (!file) {
            cout << "Файл не знайдено!" << endl;
            return;
        }

        map<string, vector<string>> temp;
        int count;

        if (!(file >> count) || count < 0) {
            cout << "Помилка читання файлу!" << endl;
            return;
        }

        for (int i = 0; i < count; i++) {
            string word;
            int translationsCount;

            if (!(file >> word >> translationsCount) || translationsCount < 0) {
                cout << "Помилка читання файлу!" << endl;
                return;
            }

            vector<string> translations;

            for (int j = 0; j < translationsCount; j++) {
                string translation;

                if (!(file >> translation)) {
                    cout << "Помилка читання файлу!" << endl;
                    return;
                }

                translations.push_back(translation);
            }

            temp[word] = translations;
        }

        words = temp;
        cout << "Словник завантажено з файлу!" << endl;
    }
};

int main() {
    setlocale(LC_ALL, "ukr");

    Dictionary dictionary;
    int choice;

    do {
        cout << "\n========== СЛОВНИК ==========" << endl;
        cout << "1. Додати слово з перекладами" << endl;
        cout << "2. Знайти переклади слова" << endl;
        cout << "3. Додати переклад до слова" << endl;
        cout << "4. Видалити слово" << endl;
        cout << "5. Показати всі слова" << endl;
        cout << "6. Зберегти словник у файл" << endl;
        cout << "7. Завантажити словник з файлу" << endl;
        cout << "0. Вихід" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case 1:
            dictionary.AddWord();
            break;
        case 2:
            dictionary.FindWord();
            break;
        case 3:
            dictionary.AddTranslation();
            break;
        case 4:
            dictionary.DeleteWord();
            break;
        case 5:
            dictionary.ShowAll();
            break;
        case 6:
            dictionary.SaveToFile();
            break;
        case 7:
            dictionary.LoadFromFile();
            break;
        case 0:
            cout << "Завершення програми!" << endl;
            break;
        default:
            cout << "Неправильний вибір!" << endl;
        }

    } while (choice != 0);

    return 0;
}
