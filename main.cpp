#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <memory>
#include <sstream>

using namespace std;

struct Student
{
    int id{};
    string lastname{};
    string name{};
    string fathername{};
    int level{};
    string group{};
    int firstYear{};
    int marks[5]{};
};

// Область объявления переменных
Student Students[10]{};
vector<int> FreeId{1,2,3,4,5,6,7,8,9,10};
int UserType{};

// Конец области переменных

// Область объявления функций
int getLoginPass();
int loadChekUserData(string login,string password);
void userMenu();
void adminMenu();
void loadFromTextFile();
void parsingText(vector<string>);
void fixStreamState();
int getCorrectValue();
// Функции взаимодействия с базой
void addNewStudent(vector<string>);
void printAllDataFromBase();
// Конец область функций

int main()
{
    system("chcp 65001");
    getLoginPass();
    int userChoice{};
    switch (UserType)
    {
    case 1:
        // Пользователь
        do
        {
            userMenu();
            int userChoice = getCorrectValue();
            switch (userChoice)
            {
                case 1:
                    loadFromTextFile();
                    break;
                case 2:
                    break;
                case 3:
                    printAllDataFromBase();
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
                case 8:
                    break;
                default:
                    cout << "Введен неверный номер" << endl;
            }
        }while(userChoice != 8);
        break;
    case 2:
        // Администратор
        do
        {
            adminMenu();
            int userChoice = getCorrectValue();
            switch (userChoice)
            {
            case 1:
                break;
            case 2:
                loadFromTextFile();
                break;
            case 3:
                break;
            case 4:
                printAllDataFromBase();
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
                break;
            case 11:
                break;
            case 12:
                break;
            default:
                cout << "Введен неверный номер" << endl;
            }
        }while(userChoice != 12);
        break;
    default:
        cout << "Ошибка авторизации" << endl;
    }

    return 0;
}

// Область реализации функций
void adminMenu()
{
    cout <<"\n";
    cout << "========== СИСТЕМА УПРАВЛЕНИЯ СТУДЕНТАМИ ==========\n" << endl;
    cout << "1. Ввод информации с клавиатуры" << endl;
    cout << "2. Загрузка из текстового файла" << endl;
    cout << "3. Загрузка из бинарного файла" << endl;
    cout << "4. Вывод данных в виде таблицы" << endl;
    cout << "5. Выполнение запроса (поиск двоечников)" << endl;
    cout << "6. Экспорт в текстовый файл" << endl;
    cout << "7. Конвертация в бинарный файл" << endl;
    cout << "8. Добавление записи" << endl;
    cout << "9. Изменение записи" << endl;
    cout << "10. Удаление записи" << endl;
    cout << "11. Сортировка данных" << endl;
    cout << "12. Выход" << endl;
    cout << "\nВведите номер команды: ";
}
void printAllDataFromBase()
{
    bool arrayIsEmpty = FreeId.size() == 10;
    if (arrayIsEmpty)
    {
        cout << "База пуста" << endl;
        return;
    }
    cout << string(42, ' ');
    cout << "===== СТУДЕНТЫ =====" << endl;
    cout << endl;

    // Заголовок таблицы
    cout << " | ";
    cout << setw(4) << "ID" << " | ";
    cout << setw(12) << "     Фамилия" << " | ";
    cout << setw(12) << "         Имя" << " | ";
    cout << setw(12) << "    Отчество" << " | ";
    cout << setw(4) << "Курс" << " | ";
    cout << setw(10) << "    Группа" << " | ";
    cout << setw(15) << "Год поступления" << " | ";
    cout << setw(10) << "   Оценки" << " | " << endl;

    // Разделитель
    cout << string(104, '=') << endl;

    // Данные студентов
    for (Student student: Students)
    {
        if (student.id == 0) continue;
        cout << string(104, '-') << endl;
        cout << setw(3) << " | ";
        cout << setw(4) << student.id << " | ";
        cout << setw(12) << student.lastname << " | ";
        cout << setw(12) << student.name << " | ";
        cout << setw(12) << student.fathername << " | ";
        cout << setw(4) << student.level << " | ";
        cout << setw(10) << student.group << " | ";
        cout << setw(15) << student.firstYear << " | ";
        cout << student.marks[0] << ";" << student.marks[1] << ";" << student.marks[2] << ";" << student.marks[3] << ";" << student.marks[4] << " | " << endl;
    }
}
int getLoginPass()
{
    string login{},password{};
    do
    {
        cout<<"Введите логин:" << endl;
        cin >> login;
        cin.ignore();
    }while (login.empty());
    do
    {
        cout << "Введите пароль" << endl;
        cin >> password;
        cin.ignore();
    }while (password.empty());

    return  loadChekUserData(login,password);
}
int loadChekUserData(string login, string password)
{
    // Загрузка данных
    vector<string> loginsAdmin{},passwordsAdmin{};
    vector<string> loginsUsers{},passwordsUsers{};

    ifstream userPassFile ("Login_pass_user.txt");
    if (userPassFile.is_open())
    {
        string line{};
        int rotation{};
        while (getline(userPassFile, line))
        {
            if (!line.empty())
            {
                rotation++;
                if (rotation % 2 == 0)
                {
                    passwordsUsers.push_back(line);
                }else
                {
                    loginsUsers.push_back(line);
                }
            }
        }
        userPassFile.close();
    }else
    {
        cout << "Ошибка. Файл с данными пользователей не открылся" << endl;
    }
    ifstream adminPassFile ("Login_pass_admin.txt");
    if (adminPassFile.is_open())
    {
        string line{};
        int rotation{};
        while (getline(adminPassFile, line))
        {
            if (!line.empty())
            {
                rotation++;
                if (rotation % 2 == 0)
                {
                    passwordsAdmin.push_back(line);
                }else
                {
                    loginsAdmin.push_back(line);
                }
            }
        }
        adminPassFile.close();
    }else
    {
        cout << "Ошибка. Файл с данными администраторов не открылся" << endl;
    }

    // Авторизация

    if (find(loginsUsers.begin(),loginsUsers.end(),login) != loginsUsers.end())
    {
        if (passwordsUsers[distance(loginsUsers.begin(),find(loginsUsers.begin(),loginsUsers.end(),login))] == password)
        {
            cout << "Вы авторизованы как пользователь" << endl;
            UserType = 1;
        }else
        {
            cout << "Неверный пароль. Повторите попытку" << endl;
            getLoginPass();
        }
    }else if (find(loginsAdmin.begin(),loginsAdmin.end(),login) != loginsAdmin.end())
    {
        if (passwordsAdmin[distance(loginsAdmin.begin(),find(loginsAdmin.begin(),loginsAdmin.end(),login))] == password)
        {
            cout << "Вы авторизованы как администратор" << endl;
            UserType = 2;
        }else
        {
            cout << "Неверный пароль. Повторите попытку" << endl;
            getLoginPass();
        }
    }else
    {
        cout << "Неверный логин. Повторите попытку" << endl;
        getLoginPass();
    }
    if (UserType != 1 and UserType != 2) UserType = 0;
    return UserType;
}
void userMenu()
{
    cout <<"\n";
    cout << "========== СИСТЕМА УПРАВЛЕНИЯ СТУДЕНТАМИ ==========\n" << endl;
    cout << "1. Загрузка из текстового файла" << endl;
    cout << "2. Загрузка из бинарного файла" << endl;
    cout << "3. Вывод данных в виде таблицы" << endl;
    cout << "4. Выполнение запроса (поиск двоечников)" << endl;
    cout << "5. Экспорт в текстовый файл" << endl;
    cout << "6. Конвертация в бинарный файл" << endl;
    cout << "7. Сортировка данных" << endl;
    cout << "8. Выход" << endl;
    cout << "\nВведите номер команды: ";
}
void loadFromTextFile()
{
    vector<string> txtLines{};
    cout << "Введите полный адрес файла (c/user/documents/doc.txt)" << endl;
    string linkFile{};
    cin >> linkFile;
    cin.ignore();
    // Проверка формата
    reverse(linkFile.begin(),linkFile.end());
    int index{};
    try
    {
        string formatFile = string(1,linkFile.at(index++)) + string(1,linkFile.at(index++)) + string(1,linkFile.at(index++)) + string(1,linkFile.at(index++));
        reverse(linkFile.begin(),linkFile.end());
        if (formatFile == ".txt")
        {
            ifstream txtFile (linkFile);
            if (txtFile.is_open())
            {
                cout << "Файл открыт успешно" << endl;
                string txtLine{};
                while (getline(txtFile,txtLine) and !txtLine.empty())
                {
                    txtLines.push_back(txtLine);
                }
                parsingText(txtLines);
            }else
            {
                cout << "Ошибка открытия файла! Проверьте наличие файла и правильность пути." << endl;
            }
        }else
        {
            cout << "Неверное расширение файла. Файл должен быть в формате .txt" << endl;
        }
    }catch (...)
    {
        cout << "Ошибка! Неверный формат." << endl;
    }
}
void parsingText(vector<string> txtLines)
{
    vector<string> dataOneStudent{};
    int indexString{};
    for (string txtString :txtLines)
    {
        vector<string> dataOneStudent{};
        if (indexString++ == 0) continue;
        stringstream ss(txtString);
        string word{};
        while (getline(ss, word, ';'))
        {
            if (!word.empty()) {
                dataOneStudent.push_back(word);
            }
        }
        if (size(dataOneStudent) != 11)
        {
            cout << "Неверно отформатирована строка:" << indexString - 1 << endl;
            cout << txtString << endl;
            continue;
        }

        addNewStudent(dataOneStudent);
    }
}
void addNewStudent(vector<string> dataOneStudent)
{
    if (dataOneStudent.size() != 11)
    {
        cout << "В файле неверный формат" << endl;
        return;

    }
    if (FreeId.empty())
    {
        cout << "Достигнуто максимальное количество студентов в базе" << endl;
        return;
    }
    sort(FreeId.begin(), FreeId.end());
    int studentId{FreeId[0]};
    FreeId.erase(FreeId.begin());
    int indexInVec{};
    try
    {
        Student newStudent{};
        newStudent.id = studentId;
        newStudent.lastname = dataOneStudent[indexInVec++];
        newStudent.name = dataOneStudent[indexInVec++];
        newStudent.fathername = dataOneStudent[indexInVec++];
        newStudent.level = stoi(dataOneStudent[indexInVec++]);
        newStudent.group = dataOneStudent[indexInVec++];
        newStudent.firstYear = stoi(dataOneStudent[indexInVec++]);
        newStudent.marks[0] = stoi(dataOneStudent[indexInVec++]);
        newStudent.marks[1] = stoi(dataOneStudent[indexInVec++]);
        newStudent.marks[2] = stoi(dataOneStudent[indexInVec++]);
        newStudent.marks[3] = stoi(dataOneStudent[indexInVec++]);
        newStudent.marks[4] = stoi(dataOneStudent[indexInVec++]);
        Students[studentId-1] = newStudent;
        cout << "Студент добавлен c ID:" << newStudent.id << endl;
    }catch (...)
    {
        cout << "Данные в файле в неверном формате" << endl;
    }
}
void fixStreamState() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
int getCorrectValue() {
    int n{};
    bool isNotOk{};

    do {
        isNotOk = false;
        if ((cin >> n).fail()) {
            fixStreamState();
            cout << "Неверный тип данных!" << endl;
            cout << "Введите число(int): " << endl;
            isNotOk = true;
        }
    } while (isNotOk);

    return n;
}