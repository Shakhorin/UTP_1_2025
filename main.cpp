#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

// Глобальные массивы для хранения данных о студентах (максимум 10 записей)
string name[10], lastname[10], fathername[10], group[10];
int id[10] = {0}, level[10] = {0}, first_year[10] = {0},
    marks1[10] = {0}, marks2[10] = {0}, marks3[10] = {0},
    marks4[10] = {0}, marks5[10] = {0};

// Вектор свободных ID (изначально все ID от 1 до 10 свободны)
vector<int> free_id{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Прототипы функций
void addStudent(string name_new, string lastname_new, string father_name_new,
                int level_new, string group_new, int first_year_new, int marks_new[5]);
void deleteStudent(int student_id);
int searchStudent();
void showMenu();
void inputFromKeyboard();
void loadFromTextFile();
void loadFromBinaryFile();
void displayStudents();
void displayStudents(vector<int> indices);
void saveToFile(vector<int> indices);
void saveToFile();
void processQuery();
void exportToTextFile();
void convertTextToBinary();
void addStudentMenu();
void editStudent();
void deleteStudentMenu();
void sortStudents();
void exitProgram();
double getAverage(int index);
void preBase();
void finalExport();

int main()
{
    // Установка русской кодировки для корректного отображения текста
    system("chcp 65001");

    // Загрузка данных из файла при запуске программы
    preBase();

    int userInput{};
    do
    {
        cin.ignore();
        // Отображение меню и обработка выбора пользователя
        showMenu();
        cin >> userInput;
        cin.ignore(); // Очистка буфера после ввода числа

        // Обработка выбора пользователя
        switch (userInput)
        {
            case 1: inputFromKeyboard(); break;
            case 2: loadFromTextFile(); break;
            case 3: loadFromBinaryFile(); break;
            case 4: displayStudents(); break;
            case 5: saveToFile(); break;
            case 6: processQuery(); break;
            case 7: exportToTextFile(); break;
            case 8: convertTextToBinary(); break;
            case 9: addStudentMenu(); break;
            case 10: editStudent(); break;
            case 11: deleteStudentMenu(); break;
            case 12: sortStudents(); break;
            case 13: exitProgram(); break;
            default: cout << "Неверный номер команды!\n" << endl;
        }

        // Пауза перед очисткой экрана (только если не выход)
        if (userInput != 13)
        {
            cout << "\nНажмите Enter для продолжения...";
            cin.get();
        }
        system("cls"); // Очистка экрана
    }
    while (userInput != 13);

    // Финальное сохранение при выходе
    char userChoice{};
    cout << "Вы хотите сохранить это состояние бд?(y/n)" << endl;
    cin >> userChoice;
    if (userChoice == 'y' or userChoice == 'Y')
    {
        finalExport();
    }
    return 0;
}

/**
 * Функция предварительной загрузки базы данных из файла
 * Проверяет наличие файла и предлагает загрузить данные
 */
void preBase()
{
    bool fullBase = false;
    // Используем относительный путь для совместимости
    ifstream base("Main_database.csv");

    // Проверка существования и содержимого файла
    if (base.is_open())
    {
        string line;
        while (getline(base, line))
        {
            // Проверяем, что строка не пустая и содержит данные
            if (!line.empty() && line.find(';') != string::npos)
            {
                fullBase = true;
                break;
            }
        }
        base.close();
    }
    else
    {
        cout << "Файл базы данных не найден. Будет создан новый?" << endl;
        return;
    }

    // Если файл содержит данные, предлагаем загрузить их
    if (fullBase)
    {
        char useInput{};
        cout << "Хотите загрузить данные из последнего сохранения? (y/n): ";
        cin >> useInput;
        cin.ignore();

        if (useInput == 'y' || useInput == 'Y')
        {
            // Загрузка данных из CSV файла
            ifstream dataFile("Main_database.csv");

            if (!dataFile.is_open())
            {
                cout << "Ошибка открытия файла для загрузки данных" << endl;
                return;
            }

            vector<string> data{};
            string line{};
            int countStudents{};

            // Чтение всех строк файла
            while (getline(dataFile, line))
            {
                if (!line.empty() && line.find(';') != string::npos)
                {
                    data.push_back(line);
                    countStudents++;
                }
            }
            dataFile.close();

            // Обработка загруженных данных
            if (!data.empty())
            {
                cout << "\n=== ЗАГРУЖЕННЫЕ ДАННЫЕ ===" << endl;

                // Ограничиваем количество записей размером массива (10)
                int maxRecords = min((int)data.size(), 10);

                for (int i = 0; i < maxRecords; i++)
                {
                    cout << data[i] << endl;
                    string currentLine = data[i];
                    string currentField = "";
                    int fieldNumber = 1;

                    // Разбор строки на поля по разделителю ';'
                    for (int j = 0; j < currentLine.length(); j++)
                    {
                        if (currentLine[j] != ';')
                        {
                            currentField += currentLine[j];
                        }
                        else
                        {
                            // Заполнение соответствующих массивов данными
                            try {
                                switch (fieldNumber)
                                {
                                    case 1:
                                        id[i] = stoi(currentField);
                                        // Удаляем использованный ID из свободных
                                        free_id.erase(remove(free_id.begin(), free_id.end(), id[i]), free_id.end());
                                        break;
                                    case 2: lastname[i] = currentField; break;
                                    case 3: name[i] = currentField; break;
                                    case 4: fathername[i] = currentField; break;
                                    case 5: level[i] = stoi(currentField); break;
                                    case 6: group[i] = currentField; break;
                                    case 7: first_year[i] = stoi(currentField); break;
                                    case 8: marks1[i] = stoi(currentField); break;
                                    case 9: marks2[i] = stoi(currentField); break;
                                    case 10: marks3[i] = stoi(currentField); break;
                                    case 11: marks4[i] = stoi(currentField); break;
                                    case 12: marks5[i] = stoi(currentField); break;
                                    default: break;
                                }
                            }
                            catch (const exception& e) {
                                cout << "Ошибка преобразования данных в строке " << (i+1) << ", поле " << fieldNumber << endl;
                            }

                            fieldNumber++;
                            currentField = "";
                        }
                    }

                    // Обработка последнего поля (после последней ';')
                    // if (!currentField.empty()) {
                    //     try {
                    //         if (fieldNumber == 12) {
                    //             marks5[i] = stoi(currentField);
                    //         }
                    //     }
                    //     catch (const exception& e) {
                    //         cout << "Ошибка преобразования последнего поля в строке " << (i+1) << endl;
                    //     }
                    // }
                }
                cout << "Загружено записей: " << maxRecords << " студентов" << endl;
            }
        }
        else
        {
            cout << "Используются начальные настройки" << endl;
        }
    }
    else
    {
        cout << "База данных пуста. Используются начальные настройки." << endl;
    }
}

/**
 * Функция финального экспорта при выходе из программы
 * Сохраняет все данные в основной файл
 */
void finalExport()
{
    vector<int> nonEmptyIndices;

    // Собираем индексы непустых записей
    for (int i = 0; i < 10; i++)
    {
        if (id[i] != 0)
        {
            nonEmptyIndices.push_back(i);
        }
    }

    if (nonEmptyIndices.empty())
    {
        cout << "Нет данных для сохранения." << endl;
        return;
    }

    // Сохранение в основной файл базы данных
    ofstream outFile("Main_database.csv");
    if (!outFile.is_open())
    {
        cout << "Ошибка открытия файла базы данных!" << endl;
        return;
    }

    // // Заголовок CSV файла
    // outFile << "ID;Фамилия;Имя;Отчество;Курс;Группа;Год_поступления;"
    //         << "Оценка1;Оценка2;Оценка3;Оценка4;Оценка5;Средний_балл" << endl;

    // Данные студентов
    for (int i : nonEmptyIndices)
    {
        outFile << id[i] << ";"
                << lastname[i] << ";"
                << name[i] << ";"
                << fathername[i] << ";"
                << level[i] << ";"
                << group[i] << ";"
                << first_year[i] << ";"
                << marks1[i] << ";" << marks2[i] << ";" << marks3[i] << ";"
                << marks4[i] << ";" << marks5[i] << ";"
                << fixed << setprecision(2) << getAverage(i) << endl;
    }

    outFile.close();
    cout << "Данные успешно сохранены в Main_database.csv" << endl;
}

/**
 * Добавление нового студента в базу данных
 */
void addStudent(string name_new, string lastname_new, string father_name_new,
                int level_new, string group_new, int first_year_new, int marks_new[5])
{
    if (free_id.empty())
    {
        cout << "Ошибка: нет свободных ID для добавления студента" << endl;
        return;
    }

    // Берем первый свободный ID
    const int newStudentId = free_id[0];
    int index = newStudentId - 1; // Индекс в массивах

    // Заполняем данные студента
    id[index] = newStudentId;
    name[index] = name_new;
    lastname[index] = lastname_new;
    fathername[index] = father_name_new;
    level[index] = level_new;
    group[index] = group_new;
    first_year[index] = first_year_new;
    marks1[index] = marks_new[0];
    marks2[index] = marks_new[1];
    marks3[index] = marks_new[2];
    marks4[index] = marks_new[3];
    marks5[index] = marks_new[4];

    // Удаляем использованный ID из списка свободных
    free_id.erase(free_id.begin());
    cout << "Студент добавлен с ID: " << newStudentId << endl;
}

/**
 * Меню добавления нового студента (ввод с клавиатуры)
 */
void addStudentMenu()
{
    if (free_id.empty())
    {
        cout << "Достигнуто максимальное количество студентов (10)" << endl;
        return;
    }

    cout << "=== ДОБАВЛЕНИЕ НОВОГО СТУДЕНТА ===\n" << endl;

    string name_new, lastname_new, father_name_new, group_new;
    int level_new, first_year_new;
    int marks_new[5];

    // Ввод данных пользователя
    cout << "Введите имя: ";
    cin >> name_new;
    cout << "Введите фамилию: ";
    cin >> lastname_new;
    cout << "Введите отчество: ";
    cin >> father_name_new;
    cout << "Введите курс: ";
    cin >> level_new;
    cout << "Введите группу: ";
    cin >> group_new;
    cout << "Введите год поступления: ";
    cin >> first_year_new;
    cout << "Введите 5 оценок через пробел: ";
    for (int i = 0; i < 5; i++)
    {
        cin >> marks_new[i];
    }

    // Добавление студента в базу
    addStudent(name_new, lastname_new, father_name_new, level_new, group_new, first_year_new, marks_new);
}

/**
 * Отображение всех студентов в виде таблицы
 */
void displayStudents()
{
    vector<int> nonEmptyIndices;

    // Собираем индексы непустых записей
    for (int i = 0; i < 10; i++)
    {
        if (id[i] != 0)
        {
            nonEmptyIndices.push_back(i);
        }
    }

    if (nonEmptyIndices.empty())
    {
        cout << "Студенты еще не внесены в базу" << endl;
        return;
    }

    // Вывод заголовка таблицы
    cout << "=== СПИСОК ВСЕХ СТУДЕНТОВ ===\n" << endl;
    cout << "ID\tФамилия\tИмя\tОтчество\tКурс\tГруппа\tГод\tОценки" << endl;
    cout << "----------------------------------------------------------------" << endl;

    // Вывод данных студентов
    for (int i : nonEmptyIndices)
    {
        cout << id[i] << "\t";
        cout << lastname[i] << "\t";
        cout << name[i] << "\t";
        cout << fathername[i] << "\t\t";
        cout << level[i] << "\t";
        cout << group[i] << "\t";
        cout << first_year[i] << "\t";
        cout << marks1[i] << " ";
        cout << marks2[i] << " ";
        cout << marks3[i] << " ";
        cout << marks4[i] << " ";
        cout << marks5[i] << endl;
    }

    // Предложение сохранения в файл
    char userInput;
    cout << "\nХотите сохранить данные в файл? (y/n): ";
    cin >> userInput;
    cin.ignore();

    if (userInput == 'y' || userInput == 'Y')
    {
        saveToFile(nonEmptyIndices);
    }
}

/**
 * Удаление студента по ID
 */
void deleteStudent(int student_id)
{
    // Проверка корректности ID
    if (student_id < 1 || student_id > 10)
    {
        cout << "Неверный ID студента (должен быть от 1 до 10)" << endl;
        return;
    }

    int index = student_id - 1;

    // Проверка существования студента
    if (id[index] == 0)
    {
        cout << "Студент с ID " << student_id << " не найден" << endl;
        return;
    }

    // Очистка данных студента
    id[index] = 0;
    name[index] = "";
    lastname[index] = "";
    fathername[index] = "";
    group[index] = "";
    level[index] = 0;
    first_year[index] = 0;
    marks1[index] = 0;
    marks2[index] = 0;
    marks3[index] = 0;
    marks4[index] = 0;
    marks5[index] = 0;

    // Возврат ID в список свободных
    free_id.push_back(student_id);
    sort(free_id.begin(), free_id.end()); // Сортировка для удобства
    cout << "Студент с ID " << student_id << " удален" << endl;
}

/**
 * Меню удаления студента
 */
void deleteStudentMenu()
{
    // Сначала показываем всех студентов
    vector<int> nonEmptyIndices;
    for (int i = 0; i < 10; i++)
    {
        if (id[i] != 0)
        {
            nonEmptyIndices.push_back(i);
        }
    }

    if (nonEmptyIndices.empty())
    {
        cout << "Студенты еще не внесены в базу" << endl;
        return;
    }

    cout << "=== ТЕКУЩИЕ СТУДЕНТЫ ===\n" << endl;
    cout << "ID\tФамилия\tИмя" << endl;
    cout << "----------------------" << endl;

    for (int i : nonEmptyIndices)
    {
        cout << id[i] << "\t";
        cout << lastname[i] << "\t";
        cout << name[i] << endl;
    }

    // Запрос ID для удаления
    int student_id{};
    cout << "\nВведите ID студента для удаления: ";
    cin >> student_id;
    deleteStudent(student_id);
}

/**
 * Отображение главного меню программы
 */
void showMenu()
{
    cout << "========== СИСТЕМА УПРАВЛЕНИЯ СТУДЕНТАМИ ==========\n" << endl;
    cout << "1. Ввод информации с клавиатуры" << endl;
    cout << "2. Загрузка из текстового файла" << endl;
    cout << "3. Загрузка из бинарного файла" << endl;
    cout << "4. Вывод данных в виде таблицы" << endl;
    cout << "5. Сохранение данных в файл" << endl;
    cout << "6. Выполнение запроса (поиск двоечников)" << endl;
    cout << "7. Экспорт в текстовый файл" << endl;
    cout << "8. Конвертация в бинарный файл" << endl;
    cout << "9. Добавление записи" << endl;
    cout << "10. Изменение записи" << endl;
    cout << "11. Удаление записи" << endl;
    cout << "12. Сортировка данных" << endl;
    cout << "13. Выход" << endl;
    cout << "\nВведите номер команды: ";
}

/**
 * Выполнение запроса - поиск студентов с тремя и более двойками
 */
void processQuery()
{
    vector<int> nonEmptyIndices;
    for (int i = 0; i < 10; i++)
    {
        if (id[i] != 0)
        {
            nonEmptyIndices.push_back(i);
        }
    }

    if (nonEmptyIndices.empty())
    {
        cout << "Студенты еще не внесены в базу" << endl;
        return;
    }

    vector<int> studentsWithThreeOrMoreTwos;

    // Поиск студентов с 3 и более двойками
    for (int i : nonEmptyIndices)
    {
        int countTwos = 0;
        if (marks1[i] == 2) countTwos++;
        if (marks2[i] == 2) countTwos++;
        if (marks3[i] == 2) countTwos++;
        if (marks4[i] == 2) countTwos++;
        if (marks5[i] == 2) countTwos++;

        if (countTwos >= 3)
        {
            studentsWithThreeOrMoreTwos.push_back(i);
        }
    }

    if (studentsWithThreeOrMoreTwos.empty())
    {
        cout << "Студентов с тремя и более двойками не найдено" << endl;
        return;
    }

    // Отображение результатов запроса
    displayStudents(studentsWithThreeOrMoreTwos);
}

/**
 * Отображение студентов из переданного списка индексов
 */
void displayStudents(vector<int> indicesToDisplay)
{
    cout << "=== РЕЗУЛЬТАТЫ ЗАПРОСА ===\n" << endl;
    cout << "ID\tФамилия\tИмя\tОтчество\tКурс\tГруппа\tГод\tОценки" << endl;
    cout << "----------------------------------------------------------------" << endl;

    for (int i : indicesToDisplay)
    {
        cout << id[i] << "\t";
        cout << lastname[i] << "\t";
        cout << name[i] << "\t";
        cout << fathername[i] << "\t\t";
        cout << level[i] << "\t";
        cout << group[i] << "\t";
        cout << first_year[i] << "\t";
        cout << marks1[i] << " ";
        cout << marks2[i] << " ";
        cout << marks3[i] << " ";
        cout << marks4[i] << " ";
        cout << marks5[i] << endl;
    }

    // Предложение сохранения результатов
    char userInput;
    cout << "\nХотите сохранить результаты в файл? (y/n): ";
    cin >> userInput;
    cin.ignore();

    if (userInput == 'y' || userInput == 'Y')
    {
        saveToFile(indicesToDisplay);
    }
}

/**
 * Сохранение данных в CSV файл
 */
void saveToFile(vector<int> indicesToExport)
{
    if (indicesToExport.empty())
    {
        cout << "Нет данных для экспорта!" << endl;
        return;
    }

    string fileName;
    cout << "Введите название файла (без расширения): ";
    cin >> fileName;
    cin.ignore();

    ofstream outFile(fileName + ".csv");
    if (!outFile.is_open())
    {
        cout << "Ошибка создания файла!" << endl;
        return;
    }

    // Заголовок CSV
    outFile << "ID;Фамилия;Имя;Отчество;Курс;Группа;Год_поступления;"
            << "Оценка1;Оценка2;Оценка3;Оценка4;Оценка5;Средний_балл" << endl;

    // Данные студентов
    for (int i : indicesToExport)
    {
        outFile << id[i] << ";"
                << lastname[i] << ";"
                << name[i] << ";"
                << fathername[i] << ";"
                << level[i] << ";"
                << group[i] << ";"
                << first_year[i] << ";"
                << marks1[i] << ";" << marks2[i] << ";" << marks3[i] << ";"
                << marks4[i] << ";" << marks5[i] << ";"
                << fixed << setprecision(2) << getAverage(i) << endl;
    }

    outFile.close();
    cout << "Данные успешно экспортированы в файл: " << fileName << ".csv" << endl;
}

/**
 * Расчет среднего балла студента
 */
double getAverage(int index)
{
    return (marks1[index] + marks2[index] + marks3[index] + marks4[index] + marks5[index]) / 5.0;
}

/**
 * Сохранение всех данных (без параметров)
 */
void saveToFile()
{
    vector<int> nonEmptyIndices;
    for (int i = 0; i < 10; i++)
    {
        if (id[i] != 0)
        {
            nonEmptyIndices.push_back(i);
        }
    }
    saveToFile(nonEmptyIndices);
}

/**
 * Ввод данных с клавиатуры
 */
void inputFromKeyboard()
{
    addStudentMenu();
}

// Функции в разработке (заглушки)
void loadFromTextFile() {
    cout << "Функция загрузки из текстового файла в разработке." << endl;
}

void loadFromBinaryFile() {
    cout << "Функция загрузки из бинарного файла в разработке." << endl;
}

void exportToTextFile() {
    cout << "Функция экспорта в текстовый файл в разработке." << endl;
}

void convertTextToBinary() {
    cout << "Функция конвертации в бинарный файл в разработке." << endl;
}

void editStudent() {
    cout << "Функция редактирования в разработке." << endl;
}

void sortStudents() {
    cout << "Функция сортировки в разработке." << endl;
}

void exitProgram() {
    cout << "Завершение работы программы..." << endl;
}

int searchStudent() {
    return 0;
}