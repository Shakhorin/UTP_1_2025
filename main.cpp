#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

string name[10], lastname[10], fathername[10], group[10];
int id[10] = {0}, level[10] = {0}, first_year[10] = {0}, marks1[10] = {0}, marks2[10] = {0}, marks3[10] = {0}, marks4[
        10] = {0}, marks5[10] = {0};

vector<int> free_id{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Функции работы с массивами
void addStudent(string name_new, string lastname_new, string father_name_new, int level_new, string group_new,
                int first_year_new, int marks_new[5]);

void deleteStudent(int student_id);

int searchStudent();

// Прототипы функций
void showMenu();

void inputFromKeyboard();

void loadFromTextFile();

void loadFromBinaryFile();

void displayStudents();

void displayStudents(vector<int>);

void saveToFile(vector<int>);

void saveToFile();

void processQuery();

void exportToTextFile();

void convertTextToBinary();

void addStudentMenu();

void editStudent();

void deleteStudentMenu();

void sortStudents();

void exitProgram();

double getAverage(int);

void preBase();

void finalExport();

int main()
{
    system("chcp 65001");
    preBase();
    //cin.ignore();

    int userInput{};
    do
    {
        showMenu();
        cin >> userInput;
        cin.ignore();

        switch (userInput)
        {
        case 1: inputFromKeyboard();
            break;
        case 2: loadFromTextFile();
            break;
        case 3: loadFromBinaryFile();
            break;
        case 4: displayStudents();
            break;
        case 5: saveToFile();
            break;
        case 6: processQuery();
            break;
        case 7: exportToTextFile();
            break;
        case 8: convertTextToBinary();
            break;
        case 9: addStudentMenu();
            break;
        case 10: editStudent();
            break;
        case 11: deleteStudentMenu();
            break;
        case 12: sortStudents();
            break;
        case 13: exitProgram();
            break;
        default: cout << "Неверный номер\n" << endl;
        }
        system("cls");
        if (userInput != 13)
        {
            // cout << "\nНажмите Enter для продолжения...";
            // cin.get();
        }
        system("cls");
    }
    while (userInput != 13);
    finalExport();
    return 0;
}

void preBase()
{
    bool fullBase = false;
    ifstream base("C:/Users/book/CLionProjects/UTP_1_2025/cmake-build-debug/Main_database.csv");

    if (base.is_open())
    {
        string line;
        while (getline(base, line))
        {
            // Проверяем, что строка не пустая и не состоит только из пробелов
            if (!line.empty())
            {
                fullBase = true;
                break;
            }
        }
        base.close();
    }
    else
    {
        cout << "Не удалось открыть файл базы данных" << endl;
        return;
    }

    if (fullBase)
    {
        char useInput{};
        cout << "Хотите ли вы загрузить данные последнего сохранения? (y/n): ";
        cin >> useInput;
        cin.ignore(); // Очистка буфера после ввода символа

        if (useInput == 'y' or useInput == 'Y')
        {
            // Загрузка данных
            ifstream dataFile("C:/Users/book/CLionProjects/UTP_1_2025/cmake-build-debug/Main_database.csv");

            if (!dataFile.is_open())
            {
                cout << "Ошибка открытия файла для загрузки данных" << endl;
                return;
            }
            vector<string> data{};
            string line{};
            int countStudents{};

            // Читаем все строки файла
            while (getline(dataFile, line))
            {
                if (!line.empty())
                {
                    data.push_back(line); // Добавляем строку в вектор
                    countStudents++;
                }
            }
            dataFile.close();

            // Выводим заголовок и данные
            if (!data.empty())
            {
                cout << "\n=== ЗАГРУЖЕННЫЕ ДАННЫЕ ===" << endl;
                for (int i = 0; i < data.size(); i++)
                {
                    cout << data[i] << endl;
                    string i_line{data[i]}, lot{};
                    int arrNum{1};

                    for (int j = 0; j < i_line.length(); j++)
                    {
                        if (i_line[j] != ';')
                        {
                            lot = lot + i_line[j];
                        }
                        else
                        {
                            switch (arrNum)
                            {
                            case 1:
                                id[i] = stoi(lot);
                                free_id.erase(remove(free_id.begin(), free_id.end(), id[i]), free_id.end());
                                break;
                            case 2:
                                lastname[i] = lot;
                                break;
                            case 3:
                                name[i] = lot;
                                break;
                            case 4:
                                fathername[i] = lot;
                                break;
                            case 5:
                                level[i] = stoi(lot);
                                break;
                            case 6:
                                group[i] = lot;
                                break;
                            case 7:
                                first_year[i] = stoi(lot);
                                break;
                            case 8:
                                marks1[i] = stoi(lot);
                                break;
                            case 9:
                                marks2[i] = stoi(lot);
                                break;
                            case 10:
                                marks3[i] = stoi(lot);
                                break;
                            case 11:
                                marks4[i] = stoi(lot);
                                break;
                            case 12:
                                marks5[i] = stoi(lot);
                                break;
                            default:
                                cout << "Ошибка в свиче" << endl;
                                break;
                            }
                            ++arrNum;
                            lot = "";
                        }
                    }
                }
                cout << "Загружено записей: " << countStudents << " студентов" << endl;
            }
            // Добавление данный в массивы завершено
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


void finalExport()
{
}


void addStudent(string name_new, string lastname_new, string father_name_new, int level_new, string group_new,
                int first_year_new, int marks_new[5])
{
    if (free_id.empty())
    {
        cout << "Ошибка: нет свободных ID для добавления студента" << endl;
        return;
    }

    const int IDSTUDENT = free_id[0];
    int index = IDSTUDENT - 1;

    id[index] = IDSTUDENT;
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

    free_id.erase(free_id.begin());
    cout << "Студент добавлен с ID: " << IDSTUDENT << endl;
}

void addStudentMenu()
{
    if (free_id.empty())
    {
        cout << "Внесено максимальное количество студентов" << endl;
        return;
    }

    cout << "=== ДОБАВЛЕНИЕ НОВОГО СТУДЕНТА ===\n" << endl;

    string name_new, lastname_new, father_name_new, group_new;
    int level_new, first_year_new;
    int marks_new[5];

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

    addStudent(name_new, lastname_new, father_name_new, level_new, group_new, first_year_new, marks_new);
}

void displayStudents()
{
    vector<int> notEmpty;
    for (int i = 0; i < 10; i++)
    {
        if (id[i] != 0)
        {
            notEmpty.push_back(i);
        }
    }

    if (notEmpty.empty())
    {
        cout << "Студенты еще не внесены в базу" << endl;
        return;
    }

    cout << "=== СПИСОК ВСЕХ СТУДЕНТОВ ===\n" << endl;
    cout << "ID\tФамилия\tИмя\tОтчество\tКурс\tГруппа\tГод\tОценки" << endl;
    cout << "----------------------------------------------------------------" << endl;

    for (int i : notEmpty)
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

    char userInput;
    cout << "Хотите сохранить данные в файл?(y/n)\n" << endl;
    cin >> userInput;
    cin.ignore(); // Очистка буфера
    if (userInput == 'y' || userInput == 'Y')
    {
        saveToFile(notEmpty);
    }
}

void inputFromKeyboard()
{
    addStudentMenu();
}

void deleteStudent(int student_id)
{
    if (student_id < 1 || student_id > 10)
    {
        cout << "Неверный ID студента" << endl;
        return;
    }

    int index = student_id - 1;
    if (id[index] == 0)
    {
        cout << "Студент с ID " << student_id << " не найден" << endl;
        return;
    }

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

    free_id.push_back(student_id);
    sort(free_id.begin(), free_id.end());
    cout << "Студент с ID " << student_id << " удален" << endl;
}

void deleteStudentMenu()
{
    vector<int> notEmpty;
    for (int i = 0; i < 10; i++)
    {
        if (id[i] != 0)
        {
            notEmpty.push_back(i);
        }
    }

    if (notEmpty.empty())
    {
        cout << "Студенты еще не внесены в базу" << endl;
        return;
    }

    cout << "=== СПИСОК ВСЕХ СТУДЕНТОВ ===\n" << endl;
    cout << "ID\tФамилия\tИмя\tОтчество\tКурс\tГруппа\tГод\tОценки" << endl;
    cout << "----------------------------------------------------------------" << endl;

    for (int i : notEmpty)
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
    int student_id{};
    cout << "Введите ID студента для удаления: ";
    cin >> student_id;
    deleteStudent(student_id);
}

int searchStudent()
{
    return 0;
}

void showMenu()
{
    cout << "Нажмите Enter для продолжения" << endl;
    cin.ignore();
    //system("cls");
    cout << "========== СИСТЕМА УПРАВЛЕНИЯ СТУДЕНТАМИ ==========\n" << endl;
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
    cout << "\nВведите номер команды: ";
}

void processQuery()
{
    vector<int> notEmpty;
    for (int i = 0; i < 10; i++)
    {
        if (id[i] != 0)
        {
            notEmpty.push_back(i);
        }
    }

    if (notEmpty.empty())
    {
        cout << "Студенты еще не внесены в базу" << endl;
        return;
    }
    vector<int> two_mans;
    for (int i : notEmpty)
    {
        int count = 0;
        if (marks1[i] == 2) count++;
        if (marks2[i] == 2) count++;
        if (marks3[i] == 2) count++;
        if (marks4[i] == 2) count++;
        if (marks5[i] == 2) count++;

        if (count >= 3)
        {
            two_mans.push_back(i);
        }
    }
    if (two_mans.empty())
    {
        cout << "Двоечников нет" << endl;
        return;
    }
    displayStudents(two_mans);
}

void displayStudents(vector<int> two_mansOut)
{
    cout << "=== СПИСОК ВСЕХ СТУДЕНТОВ С ТРЕМЯ ДВОЙКАМИ ===\n" << endl;
    cout << "ID\tФамилия\tИмя\tОтчество\tКурс\tГруппа\tГод\tОценки" << endl;
    cout << "----------------------------------------------------------------" << endl;

    for (int i : two_mansOut)
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
    char userInput;
    cout << "Хотите сохранить данные в файл?(y/n)\n" << endl;
    cin >> userInput;
    cin.ignore(); // Очистка буфера
    if (userInput == 'y' || userInput == 'Y')
    {
        saveToFile(two_mansOut);
    }
}

// Основная функция сохранения
void saveToFile(vector<int> NumTuExport)
{
    if (NumTuExport.empty())
    {
        cout << "База данных пуста! Нечего экспортировать." << endl;
        return;
    }

    string file_name;
    cout << "Введите название файла: ";
    cin >> file_name;
    cin.ignore(); // Очистка буфера

    ofstream outFile(file_name + ".csv");
    if (!outFile.is_open())
    {
        cout << "Ошибка создания файла!" << endl;
        return;
    }

    outFile << "ID;Familiya;Imya;Otchestvo;Kurs;Gruppa;God postupleniya;"
        << "Otsenka 1;Otsenka 2;Otsenka 3;Otsenka 4;Otsenka 5;Srednii ball" << endl;

    for (int i : NumTuExport)
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
    cout << "Данные успешно экспортированы в файл: " << file_name + ".csv" << endl;
}

double getAverage(int i)
{
    return (marks1[i] + marks2[i] + marks3[i] + marks4[i] + marks5[i]) / 5.0;
}

// Упрощенная версия saveToFile() без параметров
void saveToFile()
{
    vector<int> notEmpty;
    for (int i = 0; i < 10; i++)
    {
        if (id[i] != 0)
        {
            notEmpty.push_back(i);
        }
    }
    saveToFile(notEmpty); // Просто вызываем основную функцию
}

// Заглушки
void loadFromTextFile() { cout << "Функция загрузки из текстового файла в разработке." << endl; }
void loadFromBinaryFile() { cout << "Функция загрузки из бинарного файла в разработке." << endl; }
void exportToTextFile() { cout << "Функция экспорта в текстовый файл в разработке." << endl; }
void convertTextToBinary() { cout << "Функция конвертации в бинарный файл в разработке." << endl; }
void editStudent() { cout << "Функция редактирования в разработке." << endl; }
void sortStudents() { cout << "Функция сортировки в разработке." << endl; }
void exitProgram() { cout << "Выход из программы." << endl; }
