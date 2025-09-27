#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
using namespace std;

// Константы
const int MAX_STUDENTS = 10;
const int MARKS_COUNT = 5;

// Структура для хранения данных студента
struct Student {
    int id = 0;
    string name, lastname, fathername, group;
    int level = 0, first_year = 0;
    int marks[MARKS_COUNT] = {0};
};

// Глобальные данные
Student students[MAX_STUDENTS];
vector<int> free_ids;

// Прототипы функций
void initializeData();
void addStudent(const string& name, const string& lastname, const string& fathername,
                int level, const string& group, int first_year, const int marks[]);
void deleteStudent(int student_id);
void showMenu();
int getValidInput(const string& prompt, int minVal, int maxVal);
void inputFromKeyboard();
void loadFromFile();
void displayStudents(bool showPrompt = true);
void displayStudents(const vector<int>& indices);
void saveToFile(const vector<int>& indices = {});
void processQuery();
void exportData();
void editStudent();
double calculateAverage(const Student& s);
bool hasThreeOrMoreTwos(const Student& s);
void preloadData();
void finalSave();
void clearScreen();

int main() {
    system("chcp 65001");
    initializeData();
    preloadData();

    int choice;
    do {
        showMenu();
        choice = getValidInput("Введите номер команды: ", 1, 13);

        clearScreen();
        switch (choice) {
            case 1: inputFromKeyboard(); break;
            case 2: loadFromFile(); break;
            case 3: displayStudents(); break;
            case 4: saveToFile(); break;
            case 5: processQuery(); break;
            case 6: exportData(); break;
            case 7: editStudent(); break;
            case 8: deleteStudent(getValidInput("Введите ID для удаления: ", 1, MAX_STUDENTS)); break;
            case 9: cout << "Сортировка в разработке\n"; break;
            case 10: cout << "Экспорт в разработке\n"; break;
            case 11: cout << "Конвертация в разработке\n"; break;
            case 12: displayStudents(false); break;
            case 13: break;
            default: cout << "Неверная команда!\n";
        }

        if (choice != 13) {
            cout << "\nНажмите Enter для продолжения...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            clearScreen();
        }
    } while (choice != 13);

    finalSave();
    return 0;
}

void initializeData() {
    free_ids.clear();
    for (int i = 1; i <= MAX_STUDENTS; i++) {
        free_ids.push_back(i);
    }
}

void clearScreen() {
    system("cls");
}

int getValidInput(const string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < minVal || value > maxVal) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Введите число от " << minVal << " до " << maxVal << "\n";
        } else {
            cin.ignore();
            return value;
        }
    }
}

void addStudent(const string& name, const string& lastname, const string& fathername,
                int level, const string& group, int first_year, const int marks[]) {
    if (free_ids.empty()) {
        cout << "Ошибка: достигнут лимит студентов (" << MAX_STUDENTS << ")\n";
        return;
    }

    int new_id = free_ids.front();
    int index = new_id - 1;

    students[index] = {new_id, name, lastname, fathername, group, level, first_year};
    copy(marks, marks + MARKS_COUNT, students[index].marks);

    free_ids.erase(free_ids.begin());
    cout << "Студент добавлен с ID: " << new_id << "\n";
}

void deleteStudent(int student_id) {
    if (student_id < 1 || student_id > MAX_STUDENTS) {
        cout << "Неверный ID студента\n";
        return;
    }

    int index = student_id - 1;
    if (students[index].id == 0) {
        cout << "Студент с ID " << student_id << " не найден\n";
        return;
    }

    students[index] = Student();
    free_ids.push_back(student_id);
    sort(free_ids.begin(), free_ids.end());
    cout << "Студент с ID " << student_id << " удален\n";
}

void showMenu() {
    cout << "========== СИСТЕМА УПРАВЛЕНИЯ СТУДЕНТАМИ ==========\n\n";
    const char* menuItems[] = {
        "1. Ввод информации с клавиатуры",
        "2. Загрузка из файла",
        "3. Просмотр всех студентов",
        "4. Сохранение в файл",
        "5. Поиск двоечников",
        "6. Экспорт данных",
        "7. Редактирование студента",
        "8. Удаление студента",
        "9. Сортировка данных",
        "10. Экспорт в текст",
        "11. Конвертация в бинарный",
        "12. Быстрый просмотр",
        "13. Выход"
    };

    for (const auto& item : menuItems) {
        cout << item << "\n";
    }
    cout << "\n";
}

void inputFromKeyboard() {
    if (free_ids.empty()) {
        cout << "Достигнут лимит студентов\n";
        return;
    }

    cout << "=== ДОБАВЛЕНИЕ СТУДЕНТА ===\n\n";

    string name, lastname, fathername, group;
    int level, first_year, marks[MARKS_COUNT];

    cout << "Имя: "; cin >> name;
    cout << "Фамилия: "; cin >> lastname;
    cout << "Отчество: "; cin >> fathername;
    cout << "Группа: "; cin >> group;

    level = getValidInput("Курс (1-6): ", 1, 6);
    first_year = getValidInput("Год поступления (2000-2024): ", 2000, 2024);

    cout << "Введите 5 оценок: ";
    for (int i = 0; i < MARKS_COUNT; i++) {
        marks[i] = getValidInput("", 1, 5);
    }

    addStudent(name, lastname, fathername, level, group, first_year, marks);
}

void displayStudents(bool showPrompt) {
    vector<int> existingStudents;
    for (int i = 0; i < MAX_STUDENTS; i++) {
        if (students[i].id != 0) {
            existingStudents.push_back(i);
        }
    }

    if (existingStudents.empty()) {
        cout << "Нет данных о студентах\n";
        return;
    }

    cout << "=== СПИСОК СТУДЕНТОВ ===\n\n";
    printf("%-3s %-15s %-15s %-15s %-4s %-8s %-4s %-15s %-s\n",
           "ID", "Фамилия", "Имя", "Отчество", "Курс", "Группа", "Год", "Оценки", "Ср.балл");
    cout << string(90, '-') << "\n";

    for (int idx : existingStudents) {
        const auto& s = students[idx];
        printf("%-3d %-15s %-15s %-15s %-4d %-8s %-4d %d %d %d %d %d %-6.2f\n",
               s.id, s.lastname.c_str(), s.name.c_str(), s.fathername.c_str(),
               s.level, s.group.c_str(), s.first_year,
               s.marks[0], s.marks[1], s.marks[2], s.marks[3], s.marks[4],
               calculateAverage(s));
    }

    if (showPrompt) {
        char choice;
        cout << "\nСохранить в файл? (y/n): ";
        cin >> choice;
        if (tolower(choice) == 'y') {
            saveToFile(existingStudents);
        }
    }
}

void displayStudents(const vector<int>& indices) {
    if (indices.empty()) {
        cout << "Нет данных для отображения\n";
        return;
    }

    cout << "=== РЕЗУЛЬТАТЫ ПОИСКА ===\n\n";
    printf("%-3s %-15s %-15s %-15s %-4s %-8s %-4s %-s\n",
           "ID", "Фамилия", "Имя", "Отчество", "Курс", "Группа", "Год", "Оценки");
    cout << string(80, '-') << "\n";

    for (int idx : indices) {
        const auto& s = students[idx];
        printf("%-3d %-15s %-15s %-15s %-4d %-8s %-4d %d %d %d %d %d\n",
               s.id, s.lastname.c_str(), s.name.c_str(), s.fathername.c_str(),
               s.level, s.group.c_str(), s.first_year,
               s.marks[0], s.marks[1], s.marks[2], s.marks[3], s.marks[4]);
    }
}

double calculateAverage(const Student& s) {
    double sum = 0;
    for (int i = 0; i < MARKS_COUNT; i++) {
        sum += s.marks[i];
    }
    return sum / MARKS_COUNT;
}

bool hasThreeOrMoreTwos(const Student& s) {
    int count = 0;
    for (int i = 0; i < MARKS_COUNT; i++) {
        if (s.marks[i] == 2) count++;
    }
    return count >= 3;
}

void processQuery() {
    vector<int> badStudents;
    for (int i = 0; i < MAX_STUDENTS; i++) {
        if (students[i].id != 0 && hasThreeOrMoreTwos(students[i])) {
            badStudents.push_back(i);
        }
    }

    if (badStudents.empty()) {
        cout << "Студентов с тремя и более двойками не найдено\n";
        return;
    }

    displayStudents(badStudents);

    char choice;
    cout << "\nСохранить результаты? (y/n): ";
    cin >> choice;
    if (tolower(choice) == 'y') {
        saveToFile(badStudents);
    }
}

void saveToFile(const vector<int>& indices) {
    vector<int> saveIndices;
    if (indices.empty()) {
        for (int i = 0; i < MAX_STUDENTS; i++) {
            if (students[i].id != 0) {
                saveIndices.push_back(i);
            }
        }
    } else {
        saveIndices = indices;
    }

    if (saveIndices.empty()) {
        cout << "Нет данных для сохранения\n";
        return;
    }

    string filename;
    cout << "Имя файла (без .csv): ";
    cin >> filename;
    filename += ".csv";

    ofstream file(filename);
    if (!file) {
        cout << "Ошибка создания файла\n";
        return;
    }

    file << "ID;Фамилия;Имя;Отчество;Курс;Группа;Год;Оценки;Средний\n";
    for (int idx : saveIndices) {
        const auto& s = students[idx];
        file << s.id << ";" << s.lastname << ";" << s.name << ";" << s.fathername << ";"
             << s.level << ";" << s.group << ";" << s.first_year << ";"
             << s.marks[0] << " " << s.marks[1] << " " << s.marks[2] << " "
             << s.marks[3] << " " << s.marks[4] << ";" << fixed << setprecision(2)
             << calculateAverage(s) << "\n";
    }

    file.close();
    cout << "Данные сохранены в " << filename << "\n";
}

void editStudent() {
    displayStudents(false);

    int id = getValidInput("Введите ID студента для редактирования: ", 1, MAX_STUDENTS);
    int index = id - 1;

    if (students[index].id == 0) {
        cout << "Студент не найден\n";
        return;
    }

    auto& s = students[index];
    cout << "Редактирование студента ID " << id << ":\n";

    cout << "Имя (" << s.name << "): ";
    getline(cin, s.name);
    if (s.name.empty()) getline(cin, s.name);

    cout << "Фамилия (" << s.lastname << "): ";
    getline(cin, s.lastname);

    cout << "Отчество (" << s.fathername << "): ";
    getline(cin, s.fathername);

    cout << "Группа (" << s.group << "): ";
    getline(cin, s.group);

    s.level = getValidInput("Курс (" + to_string(s.level) + "): ", 1, 6);
    s.first_year = getValidInput("Год поступления (" + to_string(s.first_year) + "): ", 2000, 2024);

    cout << "Оценки (" << s.marks[0] << " " << s.marks[1] << " " << s.marks[2]
         << " " << s.marks[3] << " " << s.marks[4] << "): ";
    for (int i = 0; i < MARKS_COUNT; i++) {
        s.marks[i] = getValidInput("", 1, 5);
    }

    cout << "Данные обновлены\n";
}

void preloadData() {
    ifstream file("Main_database.csv");
    if (!file) return;

    string line;
    int loaded = 0;

    while (getline(file, line) && loaded < MAX_STUDENTS) {
        if (line.empty() || line.find(';') == string::npos) continue;

        vector<string> fields;
        string field;
        for (char c : line) {
            if (c == ';') {
                fields.push_back(field);
                field.clear();
            } else {
                field += c;
            }
        }
        fields.push_back(field);

        if (fields.size() >= 12) {
            try {
                int id = stoi(fields[0]);
                int index = id - 1;

                if (index >= 0 && index < MAX_STUDENTS) {
                    students[index] = {
                        id, fields[2], fields[1], fields[3], fields[5],
                        stoi(fields[4]), stoi(fields[6]),
                        {stoi(fields[7]), stoi(fields[8]), stoi(fields[9]),
                         stoi(fields[10]), stoi(fields[11])}
                    };

                    free_ids.erase(remove(free_ids.begin(), free_ids.end(), id), free_ids.end());
                    loaded++;
                }
            } catch (...) {
                continue;
            }
        }
    }

    if (loaded > 0) {
        cout << "Загружено " << loaded << " студентов\n";
    }
}

void finalSave() {
    char choice;
    cout << "Сохранить данные перед выходом? (y/n): ";
    cin >> choice;

    if (tolower(choice) == 'y') {
        saveToFile();
    }
    cout << "Выход из программы\n";
}

// Заглушки для нереализованных функций
void loadFromFile() { cout << "Загрузка из файла в разработке\n"; }
void exportData() { cout << "Экспорт в разработке\n"; }