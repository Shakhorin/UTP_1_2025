#include <iostream>       // Для ввода-вывода (cin, cout)
#include <fstream>        // Для работы с файлами (ifstream, ofstream)
#include <vector>         // Для использования контейнера vector (хотя в коде не используется)
#include <string>         // Для работы со строками string
#include <iomanip>        // Для форматирования вывода (setw, setprecision)
//#include <conio.h>        // Для функций ввода (не используется в коде)
using namespace std; // Использование стандартного пространства имён

// Класс Student представляет студента с его характеристиками
class Student {
private:
    int id; // Уникальный идентификатор студента
    string name; // Имя студента
    string lastname; // Фамилия студента
    string father_name; // Отчество студента
    int level; // Курс обучения
    string group; // Группа
    int first_year; // Год поступления
    int marks[5]; // Массив из 5 оценок

public:
    static int next_id; // Статическая переменная для генерации уникальных ID

    // Конструктор по умолчанию - инициализирует все поля нулевыми значениями
    Student() : id(0), level(0), first_year(0) {
        for (int i = 0; i < 5; i++) marks[i] = 0; // Инициализация оценок нулями
    }

    // Параметризированный конструктор - создает объект с заданными параметрами
    Student(string n, string l_n, string f_n, int l, string g, int f_y, int m[5]) {
        addObj(n, l_n, f_n, l, g, f_y, m); // Вызов метода для инициализации
    }

    // Метод для добавления/обновления данных студента
    void addObj(string n, string l_n, string f_n, int l, string g, int f_y, int m[5]) {
        id = next_id++; // Присвоение уникального ID и инкремент счетчика
        name = n; // Установка имени
        lastname = l_n; // Установка фамилии
        father_name = f_n; // Установка отчества
        level = l; // Установка курса
        group = g; // Установка группы
        first_year = f_y; // Установка года поступления
        for (int i = 0; i < 5; i++) {
            marks[i] = m[i]; // Копирование оценок из массива
        }
    }

    // Метод для отображения данных студента в консоли
    void display() const {
        // Вывод всех полей через табуляции в формате таблицы
        cout << id << "\t" << lastname << "\t" << name << "\t" << father_name << "\t"
                << level << "\t" << group << "\t" << first_year << "\t";
        for (int i = 0; i < 5; i++) {
            cout << marks[i] << " "; // Вывод всех оценок через пробел
        }
        cout << endl; // Переход на новую строку
    }

    // Геттеры (методы получения значений) для доступа к приватным полям:

    int getId() const { return id; } // Получить ID
    string getName() const { return name; } // Получить имя
    string getLastName() const { return lastname; } // Получить фамилию
    string getFatherName() const { return father_name; } // Получить отчество
    int getLevel() const { return level; } // Получить курс
    string getGroup() const { return group; } // Получить группу
    int getFirstYear() const { return first_year; } // Получить год поступления
    const int *getMarks() const { return marks; } // Получить указатель на массив оценок

    // Сеттеры (методы установки значений) для изменения приватных полей:

    void setName(string n) { name = n; } // Установить имя
    void setLastName(string ln) { lastname = ln; } // Установить фамилию
    void setFatherName(string fn) { father_name = fn; } // Установить отчество
    void setLevel(int l) { level = l; } // Установить курс
    void setGroup(string g) { group = g; } // Установить группу
    void setFirstYear(int fy) { first_year = fy; } // Установить год поступления
    void setMarks(int m[5]) {
        // Установить оценки
        for (int i = 0; i < 5; i++) marks[i] = m[i]; // Копирование нового массива оценок
    }

    // Метод для расчета средней оценки студента
    double getAverage() const {
        double sum = 0;
        for (int i = 0; i < 5; i++) {
            sum += marks[i]; // Суммирование всех оценок
        }
        return sum / 5.0; // Возврат среднего арифметического
    }
};

// Инициализация статической переменной (начальное значение ID = 1)
int Student::next_id = 1;

// Глобальный массив для хранения студентов (фиксированный размер на 10 записей)
Student students[10];

// Прототипы функций (объявления перед их использованием в main)
void showMenu(); // Показать главное меню
void inputFromKeyboard(); // Ввод данных с клавиатуры
void loadFromTextFile(); // Загрузка из текстового файла (заглушка)
void loadFromBinaryFile(); // Загрузка из бинарного файла (заглушка)
void displayAllStudents(); // Отображение всех студентов
void saveToFile(); // Сохранение данных в файл
void saveToFileFiltr(vector<Student> &students_with2);

void processQuery(); // Выполнение запроса (заглушка)
void exportToTextFile(); // Экспорт в текстовый файл (заглушка)
void convertTextToBinary(); // Конвертация в бинарный файл (заглушка)
void addStudent(); // Добавление записи (заглушка)
void editStudent(); // Изменение записи (заглушка)
void deleteStudent(); // Удаление записи (заглушка)
void sortStudents(); // Сортировка данных (заглушка)
void exitProgram(); // Выход из программы (заглушка)

// Главная функция программы - точка входа
int main() {
    system("chcp 65001"); // Установка кодировки UTF-8 для корректного отображения русских символов

    int userInput; // Переменная для хранения выбора пользователя

    // Основной цикл программы
    do {
        showMenu(); // Отображение меню
        cin >> userInput; // Чтение выбора пользователя
        cin.ignore(); // Очистка буфера ввода от символа новой строки

        // Обработка выбора пользователя с помощью switch
        switch (userInput) {
            case 1: inputFromKeyboard();
                break; // Ввод с клавиатуры
            case 2: loadFromTextFile();
                break; // Загрузка из текстового файла
            case 3: loadFromBinaryFile();
                break; // Загрузка из бинарного файла
            case 4: displayAllStudents();
                break; // Вывод всех студентов
            case 5: saveToFile();
                break; // Сохранение в файл
            case 6: processQuery();
                break; // Выполнение запроса
            case 7: exportToTextFile();
                break; // Экспорт в текстовый файл
            case 8: convertTextToBinary();
                break; // Конвертация в бинарный
            case 9: addStudent();
                break; // Добавление записи
            case 10: editStudent();
                break; // Изменение записи
            case 11: deleteStudent();
                break; // Удаление записи
            case 12: sortStudents();
                break; // Сортировка данных
            case 13: exitProgram();
                break; // Выход из программы
            default: cout << "Неверный номер\n" << endl; // Неправильный ввод
        }

        // Пауза перед продолжением (кроме выхода)
        if (userInput != 13) {
            cout << "\nНажмите Enter для продолжения...";
            cin.get(); // Ожидание нажатия Enter
        }

        system("cls"); // Очистка экрана консоли
    } while (userInput != 13); // Цикл до выбора выхода

    return 0; // Завершение программы
}

// Функция отображения главного менюl
void showMenu() {
    system("cls"); // Очистка консоли
    cout << "========== СИСТЕМА УПРАВЛЕНИЯ СТУДЕНТАМИ ==========\n" << endl;
    // Пункты меню:
    cout << "1. Ввод информации с клавиатуры" << endl;
    cout << "2. Загрузка из текстового файла" << endl;
    cout << "3. Загрузка из бинарного файла" << endl;
    cout << "4. Вывод данных в виде таблицы" << endl;
    cout << "5. Сохранение данных в файл" << endl;
    cout << "6. Выполнение запроса" << endl;
    cout << "7. Экспорт в текстовый файл" << endl;
    cout << "8. Конвертация в бинарный файл" << endl;
    cout << "9. Добавление записи" << endl;
    cout << "10. Изменение записи" << endl;
    cout << "11. Удаление записи" << endl;
    cout << "12. Сортировка данных" << endl;
    cout << "13. Выход" << endl;
    cout << "\nВведите номер команды: "; // Приглашение к вводу
}

// Функция ввода данных с клавиатуры
void inputFromKeyboard() {
    // Проверка на переполнение массива
    bool chekArr = false;
    for (int i = 0; i < 10; i++) {
        if (students[i].getId() == 0) {
            chekArr = true;
            break;
        }
    }
    if (chekArr == false) {
        cout << "Внесено максимальное количество студентов" << endl;
        return; // Выход в случае переполнения массива
    }

    cout << "=== РЕЖИМ ВВОДА С КЛАВИАТУРЫ ===\n" << endl;

    // Объявление переменных для данных студента
    string name, lastname, father_name, group;
    int level, first_year;
    int marks[5]; // Массив для 5 оценок

    // Ввод данных с клавиатуры:
    cout << "Введите имя: ";
    cin >> name;
    cout << "Введите фамилию: ";
    cin >> lastname;
    cout << "Введите отчество: ";
    cin >> father_name;
    cout << "Введите курс: ";
    cin >> level;
    cout << "Введите группу: ";
    cin >> group;
    cout << "Введите год поступления: ";
    cin >> first_year;
    cout << "Введите 5 оценок через пробел: ";
    for (int i = 0; i < 5; i++) {
        cin >> marks[i]; // Ввод каждой оценки
    }

    // Создание объекта студента и добавление в массив
    Student newStudent(name, lastname, father_name, level, group, first_year, marks);
    students[newStudent.getId() - 1] = newStudent; // Добавление в массив по индексу (ID-1)

    cout << "\nСтудент добавлен успешно! ID: " << newStudent.getId() << endl;
}

// Функция отображения всех студентов в табличном формате
void displayAllStudents() {
    bool isEmpty = true;

    // Проверка, есть ли хотя бы один студент в массиве
    for (int i = 0; i < 10; i++) {
        if (students[i].getId() != 0) {
            isEmpty = false;
            break;
        }
    }

    if (isEmpty) {
        cout << "База данных пуста!" << endl;
        return; // Выход если нет студентов
    }

    cout << "=== СПИСОК ВСЕХ СТУДЕНТОВ ===\n" << endl;
    // Заголовок таблицы
    cout << "ID\tФамилия\tИмя\tОтчество\tКурс\tГруппа\tГод\tОценки" << endl;
    cout << "----------------------------------------------------------------" << endl;

    // Цикл по всем студентам в массиве
    for (int i = 0; i < 10; i++) {
        if (students[i].getId() != 0) {
            students[i].display(); // Вывод данных каждого студента
        }
    }

    // Предложение сохранить данные в файл
    char userInput;
    cout << "Хотите сохранить данные в файл?(y/n)\n" << endl;
    cin >> userInput;
    if (userInput == 'n') {
        return;
    }
    saveToFile(); // Вызов функции сохранения
}

// Функция сохранения данных в CSV файл
void saveToFile() {
    // Проверка на пустоту базы данных

    bool isEmpty = true;
    for (int i = 0; i < 10; i++) {
        if (students[i].getId() != 0) {
            isEmpty = false;
            break;
        }
    }

    if (isEmpty) {
        cout << "База данных пуста! Нечего экспортировать." << endl;
        return;
    }
    cout << "Сохранение в файл..." << endl;
    string file_name;
    cout << "Введить название файла\n" << endl;
    cin >> file_name;


    // Создаем и открываем CSV файл для записи
    ofstream outFile(file_name + ".csv");

    if (!outFile.is_open()) {
        cout << "Ошибка создания файла!" << endl;
        return;
    }

    // Записываем заголовки столбцов с разделителем ";"
    outFile << "ID;Familiya;Imya;Otchestvo;Kurs;Gruppa;God postupleniya;"
            << "Otsenka 1;Otsenka 2;Otsenka 3;Otsenka 4;Otsenka 5;Srednii ball" << endl;

    // Записываем данные всех студентов
    for (int i = 0; i < 10; i++) {
        if (students[i].getId() != 0) {
            const int *marks = students[i].getMarks();

            // Форматированный вывод данных в CSV формате
            outFile << students[i].getId() << ";"
                    << students[i].getLastName() << ";"
                    << students[i].getName() << ";"
                    << students[i].getFatherName() << ";"
                    << students[i].getLevel() << ";"
                    << students[i].getGroup() << ";"
                    << students[i].getFirstYear() << ";"
                    << marks[0] << ";" << marks[1] << ";" << marks[2] << ";"
                    << marks[3] << ";" << marks[4] << ";"
                    << fixed << setprecision(2) << students[i].getAverage() << endl;
        }
    }

    outFile.close(); // Закрытие файла
    cout << "Данные успешно экспортированы в файл: " << file_name + ".csv" << endl;
    cout << "Файл можно открыть в Microsoft Excel или другой табличной программе." << endl;
    cout << "Нажмите Enter,чтобы продолжить...\n" << endl;
    cin.get();
}

void saveToFileFiltr(vector<Student> &students_with2) {
    // Проверка на пустоту вектора

    if (students_with2.empty()) {
        cout << "Таких! Нечего экспортировать." << endl;
        return;
    }
    cout << "Сохранение в файл..." << endl;
    string file_name;
    cout << "Введить название файла\n" << endl;
    cin >> file_name;


    // Создаем и открываем CSV файл для записи
    ofstream outFile(file_name + ".csv");

    if (!outFile.is_open()) {
        cout << "Ошибка создания файла!" << endl;
        return;
    } else {
        cout << "Файл создан успешно\n" << endl;
    }

    // Записываем заголовки столбцов с разделителем ";"
    outFile << "ID;Familiya;Imya;Otchestvo;Kurs;Gruppa;God postupleniya;"
            << "Otsenka 1;Otsenka 2;Otsenka 3;Otsenka 4;Otsenka 5;Srednii ball" << endl;

    // Записываем данные всех студентов
    for (int i = 0; i < students_with2.size(); i++) {
        if (students_with2[i].getId() != 0) {
            const int *marks = students_with2[i].getMarks();

            // Форматированный вывод данных в CSV формате
            outFile << students_with2[i].getId() << ";"
                    << students_with2[i].getLastName() << ";"
                    << students_with2[i].getName() << ";"
                    << students_with2[i].getFatherName() << ";"
                    << students_with2[i].getLevel() << ";"
                    << students_with2[i].getGroup() << ";"
                    << students_with2[i].getFirstYear() << ";"
                    << marks[0] << ";" << marks[1] << ";" << marks[2] << ";"
                    << marks[3] << ";" << marks[4] << ";"
                    << fixed << setprecision(2) << students_with2[i].getAverage() << endl;
        }
    }

    outFile.close(); // Закрытие файла
    cout << "Данные успешно экспортированы в файл: " << file_name + ".csv" << endl;
    cout << "Файл можно открыть в Microsoft Excel или другой табличной программе." << endl;
    cout << "Нажмите Enter,чтобы продолжить...\n" << endl;
    cin.get();
}

void processQuery() {
    cout << "Выполнение запроса..." << endl;
    vector<Student> students_with2;
    for (int i = 0; i < 10; i++) {
        int count = 0;
        const int *chekMarks = students[i].getMarks();
        for (int c = 0; c < 5; c++) {
            if (chekMarks[c] == 2) { count++; }
        }
        if (count >= 3) {
            students_with2.push_back(students[i]);
        }
    }
    if (students_with2.empty()) {
        cout << "Студентов с двойками по трем предметам нет\n" << endl;
        return;
    }
    cout << "=== СПИСОК СТУДЕНТОВ С ДВОЙКАМИ ПО ТРЕМ ПРЕДМЕТАМ ===\n" << endl;
    // Заголовок таблицы
    cout << "ID\tФамилия\tИмя\tОтчество\tКурс\tГруппа\tГод\tОценки" << endl;
    cout << "----------------------------------------------------------------" << endl;

    // Цикл по всем студентам в массиве
    for (int i = 0; i < students_with2.size(); i++) {
        if (students_with2[i].getId() != 0) {
            students_with2[i].display(); // Вывод данных каждого студента
        }
    }

    // Предложение сохранить данные в файл
    char userInput;
    cout << "Хотите сохранить данные в файл?(y/n)\n" << endl;
    cin >> userInput;
    if (userInput == 'n') {
        return;
    }
    saveToFileFiltr(students_with2); // Вызов функции сохранения
}

// ЗАГЛУШКИ ФУНКЦИЙ (реализация будет добавлена позже):

void loadFromTextFile() { cout << "Загрузка из текстового файла..." << endl; }
void loadFromBinaryFile() { cout << "Загрузка из бинарного файла..." << endl; }
void exportToTextFile() { cout << "Экспорт в текстовый файл..." << endl; }
void convertTextToBinary() { cout << "Конвертация в бинарный файл..." << endl; }
void addStudent() { cout << "Добавление записи..." << endl; }
void editStudent() { cout << "Изменение записи..." << endl; }
void deleteStudent() { cout << "Удаление записи..." << endl; }
void sortStudents() { cout << "Сортировка данных..." << endl; }
void exitProgram() { cout << "Выход из программы..." << endl; }