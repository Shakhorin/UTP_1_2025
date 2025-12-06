#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <memory>
#include <sstream>
#include <regex>
#include <numeric>
#define NOMINMAX
#include <windows.h>

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
vector<int> FreeId{ 1,2,3,4,5,6,7,8,9,10 };
int UserType{};
// Конец области переменных

// Область объявления функций
int getLoginPass();//-
int loadChekUserData(string login, string password);//-
void userMenu();//+
void adminMenu();//+
void loadFromTextFile();//-
void loadFromBinFile();
void loadFromKeyboard();//+
void parsingText(vector<string>);//+
void fixStreamState();//-
int getCorrectValue();//+
bool freeIdCheck();//+
int getCorrectMark();//+
int getCorrectLevel();//+
int getCorrectFirstYear();//+
int getCorrectId();//+
int getCorrectFormat();//+
char getCorrectChar();//+
string getCorrectFIO();//+
string getCorrectGroup();//+
void studentsWithBadMarksChek();//+
void getIdStudentForChange();//+
void loadChangeDataFromKeyboard(int);//+
string toLower(string&);//+
int getAverage(int[]);//+
// Функции взаимодействия с базой
void addNewStudent(vector<string>);//+
void addNewStudent(vector<Student>);
void printAllDataFromBase();//+
void printStudentsFromVector(vector<Student>);//+
void delStudentFromBase();//+
void changeStudentData(vector<string>, int);//+
void preSortDataFromBase();
void sortStudent(int, int, vector<Student>);
template<typename Iterator, typename Comparator>
void mySort(Iterator, Iterator, Comparator);
void preExportFromList(vector<Student>);
void preExportFromMenu();
void exportTxt(string, vector<Student>);
void exportBin(string, vector<Student>);
// Конец область функций

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    getLoginPass();
    switch (UserType)
    {
    case 1:
    {

        // Пользователь
        int userChoice{};
        do
        {
            userMenu();
            userChoice = getCorrectValue();
            switch (userChoice)
            {
            case 1:
                loadFromTextFile();
                break;
            case 2:
                loadFromBinFile();
                break;
            case 3:
                printAllDataFromBase();
                break;
            case 4:
                studentsWithBadMarksChek();
                break;
            case 5:
                preExportFromMenu();
                break;
            case 6:
                preSortDataFromBase();
                break;
            case 7:
                break;
            default:
                cout << "Введен неверный номер" << endl;
            }
        } while (userChoice != 7);
        break;
    }
    case 2:
    {
        // Администратор
        int adminChoice{};
        do
        {
            adminMenu();
            adminChoice = getCorrectValue();
            switch (adminChoice)
            {
            case 1:
                loadFromKeyboard();
                break;
            case 2:
                loadFromTextFile();
                break;
            case 3:
                loadFromBinFile();
                break;
            case 4:
                printAllDataFromBase();
                break;
            case 5:
                studentsWithBadMarksChek();
                break;
            case 6:
                preExportFromMenu();
                break;
            case 7:
                getIdStudentForChange();
                break;
            case 8:
                delStudentFromBase();
                break;
            case 9:
                preSortDataFromBase();
                break;
            case 10:
                break;
            default:
                cout << "Введен неверный номер" << endl;
            }
        } while (adminChoice != 10);
        break;
    }
    default:
        cout << "Ошибка авторизации" << endl;
    }

    return 0;
}

// Область реализации функций

// Функции авторизации
int getLoginPass()
{
    string login{}, password{};
    do
    {
        cout << "Введите логин:" << endl;
        cin >> login;
        cin.ignore();
    } while (login.empty());
    do
    {
        cout << "Введите пароль" << endl;
        cin >> password;
        cin.ignore();
    } while (password.empty());

    return  loadChekUserData(login, password);
}
int loadChekUserData(string login, string password)
{
    // Загрузка данных
    vector<string> loginsAdmin{}, passwordsAdmin{};
    vector<string> loginsUsers{}, passwordsUsers{};

    ifstream userPassFile("Login_pass_user.txt");
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
                }
                else
                {
                    loginsUsers.push_back(line);
                }
            }
        }
        userPassFile.close();
    }
    else
    {
        cout << "Ошибка. Файл с данными пользователей не открылся" << endl;
    }
    ifstream adminPassFile("Login_pass_admin.txt");
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
                }
                else
                {
                    loginsAdmin.push_back(line);
                }
            }
        }
        adminPassFile.close();
    }
    else
    {
        cout << "Ошибка. Файл с данными администраторов не открылся" << endl;
    }

    // Авторизация

    if (count(loginsUsers.begin(), loginsUsers.end(), login) != 0)
    {
        if (passwordsUsers[distance(loginsUsers.begin(), find(loginsUsers.begin(), loginsUsers.end(), login))] == password)
        {
            cout << "Вы авторизованы как пользователь" << endl;
            UserType = 1;
        }
        else
        {
            cout << "Неверный пароль. Повторите попытку" << endl;
            getLoginPass();
        }
    }
    else if (count(loginsAdmin.begin(), loginsAdmin.end(), login) != 0)
    {
        if (passwordsAdmin[distance(loginsAdmin.begin(), find(loginsAdmin.begin(), loginsAdmin.end(), login))] == password)
        {
            cout << "Вы авторизованы как администратор" << endl;
            UserType = 2;
        }
        else
        {
            cout << "Неверный пароль. Повторите попытку" << endl;
            getLoginPass();
        }
    }
    else
    {
        cout << "Неверный логин. Повторите попытку" << endl;
        getLoginPass();
    }
    if (UserType != 1 and UserType != 2) UserType = 0;
    return UserType;
}
// Функции меню
void adminMenu()
{
    cout << "\n";
    cout << "========== СИСТЕМА УПРАВЛЕНИЯ СТУДЕНТАМИ ==========\n" << endl;
    cout << "***ФУНКЦИИ ВВОДА***" << endl;
    cout << "1. Ввод информации с клавиатуры" << endl;
    cout << "2. Загрузка из текстового файла" << endl;
    cout << "3. Загрузка из бинарного файла" << endl;
    cout << "\n";
    cout << "***ФУНКЦИИ ВЫВОДА НА ЭКРАН***" << endl;
    cout << "4. Вывод данных в виде таблицы" << endl;
    cout << "5. Выполнение запроса (поиск двоечников)" << endl;
    cout << "\n";
    cout << "***ФУНКЦИИ ЭКСПОРТА***" << endl;
    cout << "6. Экспорт в файл" << endl;
    cout << "\n";
    cout << "***ФУНКЦИИ РЕДАКТИРОВАНИЯ ДАННЫХ***" << endl;
    cout << "7. Изменение записи" << endl;
    cout << "8. Удаление записи" << endl;
    cout << "9. Сортировка данных" << endl;
    cout << endl;
    cout << "10. Выход" << endl;
    cout << "\nВведите номер команды: ";
}
void userMenu()
{
    cout << "\n";
    cout << "========== СИСТЕМА УПРАВЛЕНИЯ СТУДЕНТАМИ ==========\n" << endl;
    cout << "***ФУНКЦИИ ВВОДА***" << endl;
    cout << "1. Загрузка из текстового файла" << endl;
    cout << "2. Загрузка из бинарного файла" << endl;
    cout << "\n";
    cout << "***ФУНКЦИИ ВЫВОДА НА ЭКРАН***" << endl;
    cout << "3. Вывод данных в виде таблицы" << endl;
    cout << "4. Выполнение запроса (поиск двоечников)" << endl;
    cout << "\n";
    cout << "***ФУНКЦИИ ЭКСПОРТА***" << endl;
    cout << "5. Экспорт файл" << endl;
    cout << "\n";
    cout << "***ФУНКЦИИ РЕДАКТИРОВАНИЯ ДАННЫХ***" << endl;
    cout << "6. Сортировка данных" << endl;
    cout << endl;
    cout << "7. Выход" << endl;
    cout << "\nВведите номер команды: ";
}
// Функции ввода
void loadFromTextFile()
{
    vector<string> txtLines{};
    cout << "Введите полный адрес файла (c/user/documents/doc.txt)" << endl;
    string linkFile{};
    cin >> linkFile;
    cin.ignore();
    // Проверка формата
    reverse(linkFile.begin(), linkFile.end());
    int index{};
    try
    {
        string formatFile = string(1, linkFile.at(index++)) + string(1, linkFile.at(index++)) + string(1, linkFile.at(index++)) + string(1, linkFile.at(index++));
        reverse(linkFile.begin(), linkFile.end());
        if (formatFile == ".txt")
        {
            ifstream txtFile(linkFile);
            if (txtFile.is_open())
            {
                cout << "Файл открыт успешно" << endl;
                string txtLine{};
                while (getline(txtFile, txtLine) and !txtLine.empty())
                {
                    txtLines.push_back(txtLine);
                }
                parsingText(txtLines);
            }
            else
            {
                cout << "Ошибка открытия файла! Проверьте наличие файла и правильность пути." << endl;
            }
        }
        else
        {
            cout << "Неверное расширение файла. Файл должен быть в формате .txt" << endl;
        }
    }
    catch (...)
    {
        cout << "Ошибка! Неверный формат." << endl;
    }
}
void loadFromBinFile()
{
    vector<Student> studentsFromFile{};
    cout << "Введите полный адрес файла (c/user/documents/doc.dat)" << endl;
    string linkFile{};
    cin >> linkFile;
    cin.ignore();
    // Проверка формата
    reverse(linkFile.begin(), linkFile.end());
    int index{};
    try
    {
        string formatFile = string(1, linkFile.at(index++)) + string(1, linkFile.at(index++)) + string(1, linkFile.at(index++)) + string(1, linkFile.at(index++));
        reverse(linkFile.begin(), linkFile.end());
        if (formatFile == ".dat" or formatFile == ".bin")
        {
            ifstream binFile(linkFile, ios::binary);
            if (binFile.is_open())
            {
                cout << "Файл открыт успешно" << endl;
                Student student{};
                while (binFile.read(reinterpret_cast<char*>(&student), sizeof(student)))
                {
                    studentsFromFile.push_back(student);
                }
                addNewStudent(studentsFromFile);
            }
            else
            {
                cout << "Ошибка открытия файла! Проверьте наличие файла и правильность пути." << endl;
            }
        }
        else
        {
            cout << "Неверное расширение файла. Файл должен быть в формате .dat или .bin" << endl;
        }
    }
    catch (...)
    {
        cout << "Ошибка! Неверный формат." << endl;
    }
}
void loadFromKeyboard()
{
    if (!freeIdCheck())
    {
        cout << "В базу занесено максимальное количество студентов" << endl;
        return;
    }
    vector<string> dataOneStudent{};
    cout << "Введите фамилию(Если будет введена строка с пробелом, то будет использовано только первое слово)" << endl;
    string lastname{};
    lastname = getCorrectFIO();
    dataOneStudent.push_back(lastname);
    cout << "Введите имя(Если будет введена строка с пробелом, то будет использовано только первое слово)" << endl;
    string name{};
    name = getCorrectFIO();
    dataOneStudent.push_back(name);
    cout << "Введите отчество(Если будет введена строка с пробелом, то будет использовано только первое слово)" << endl;
    string fathername{};
    fathername = getCorrectFIO();
    dataOneStudent.push_back(fathername);
    cout << "Введите курс(Если будет введена строка с пробелом, то будет использовано только первое слово)" << endl;
    int level_i{};
    string level{};
    level_i = getCorrectLevel();
    level = to_string(level_i);
    dataOneStudent.push_back(level);
    cout << "Введите группу заглавными буквами(Если будет введена строка с пробелом, то будет использовано только первое слово)" << endl;
    string group{};
    group = getCorrectGroup();
    dataOneStudent.push_back(group);
    cout << "Введите год поступления(Если будет введена строка с пробелом, то будет использовано только первое слово)" << endl;
    string firstYear{};
    int firstYear_i{};
    firstYear_i = getCorrectFirstYear();
    firstYear = to_string(firstYear_i);
    dataOneStudent.push_back(firstYear);
    cout << "Введите 5 оценок(Если будет введена строка с пробелом, то будут использованы первые пять оценок)" << endl;
    cout << "Вводите оценки в порядке: Матан, ВП, Рус.яз, Англ.яз, Химия" << endl;
    int marks[5]{};
    for (int i = 0; i < 5; i++)
    {
        marks[i] = getCorrectMark();
        string mark = to_string(marks[i]);
        dataOneStudent.push_back(mark);
    }
    fixStreamState();
    addNewStudent(dataOneStudent);
}
void loadChangeDataFromKeyboard(int idStudentForChange)
{
    Student studentForChange{};
    for (Student student : Students)
    {
        if (student.id == idStudentForChange)
        {
            studentForChange = student;
            break;
        }
    }
    vector<string> dataOneStudent{};
    cout << "ВНИМАНИЕ! ДЛЯ ВВОДА ДАННЫХ ИСПОЛЬЗУЙТЕ ЛАТИНСКИЙ АЛФАВИТ" << endl;
    cout << "Введите фамилию(Если будет введена строка с пробелом, то будет использовано только первое слово)" << endl;
    cout << "Старое значение:" << studentForChange.lastname << endl;
    string lastname{};
    lastname = getCorrectFIO();
    dataOneStudent.push_back(lastname);
    cout << "Введите имя(Если будет введена строка с пробелом, то будет использовано только первое слово)" << endl;
    cout << "Старое значение:" << studentForChange.name << endl;
    string name{};
    name = getCorrectFIO();
    dataOneStudent.push_back(name);
    cout << "Введите отчество(Если будет введена строка с пробелом, то будет использовано только первое слово)" << endl;
    cout << "Старое значение:" << studentForChange.fathername << endl;
    string fathername{};
    fathername = getCorrectFIO();
    dataOneStudent.push_back(fathername);
    cout << "Введите курс(Если будет введена строка с пробелом, то будет использовано только первое слово)" << endl;
    cout << "Старое значение:" << studentForChange.level << endl;
    int level_i{};
    string level{};
    level_i = getCorrectLevel();
    level = to_string(level_i);
    dataOneStudent.push_back(level);
    cout << "Введите группу заглавными буквами(Если будет введена строка с пробелом, то будет использовано только первое слово)" << endl;
    cout << "Старое значение:" << studentForChange.group << endl;
    string group{};
    group = getCorrectGroup();
    dataOneStudent.push_back(group);
    cout << "Введите год поступления(Если будет введена строка с пробелом, то будет использовано только первое слово)" << endl;
    cout << "Старое значение:" << studentForChange.firstYear << endl;
    string firstYear{};
    int firstYear_i{};
    firstYear_i = getCorrectFirstYear();
    firstYear = to_string(firstYear_i);
    dataOneStudent.push_back(firstYear);
    cout << "Введите 5 оценок(Если будет введена строка с пробелом, то будут использованы первые пять оценок)" << endl;
    cout << "Вводите оценки в порядке: Матан, ВП, Рус.яз, Англ.яз, Химия" << endl;
    cout << "Старое значение: ";
    for (int mark : studentForChange.marks)
    {
        cout << mark << " ";
    }
    cout << endl;
    int marks[5]{};
    for (int i = 0; i < 5; i++)
    {
        marks[i] = getCorrectMark();
        string mark = to_string(marks[i]);
        dataOneStudent.push_back(mark);
    }
    fixStreamState();
    changeStudentData(dataOneStudent, idStudentForChange);
}
// Функции взаибодействия с массивом
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
    int studentId{ FreeId[0] };
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
        Students[studentId - 1] = newStudent;
        cout << "Студент добавлен c ID:" << newStudent.id << endl;
    }
    catch (...)
    {
        cout << "Данные в файле в неверном формате" << endl;
    }
}
void addNewStudent(vector<Student> studentsToAdd)
{
    if (FreeId.empty())
    {
        cout << "Мест в базе нет" << endl;
        return;
    }
    mySort(FreeId.begin(),FreeId.end(),[](int a, int b)->bool{return a < b;});
    Student newStudent{};
    for (Student &student : studentsToAdd)
    {
        if (FreeId.empty())
        {
            cout << "Загружено максимальное количество студентов" << endl;
            break;
        }
        int idStudent{ FreeId[0] };
        try
        {
            FreeId.erase(FreeId.begin());
            newStudent.id = idStudent;
            newStudent.lastname = student.lastname;
            newStudent.name = student.name;
            newStudent.fathername = student.fathername;
            newStudent.level = student.level;
            newStudent.group = student.group;
            newStudent.firstYear = student.firstYear;
            newStudent.marks[0] = student.marks[0];
            newStudent.marks[1] = student.marks[1];
            newStudent.marks[2] = student.marks[2];
            newStudent.marks[3] = student.marks[3];
            newStudent.marks[4] = student.marks[4];
            Students[idStudent-1] = newStudent;
            cout << "Студент добавлен c ID:" << newStudent.id << endl;
        }
        catch (...)
        {
            cout << "Данные в файле в неверном формате" << endl;
        }
    }
}
void delStudentFromBase()
{
    char accept{};
    int idForDel{};
    bool flagExit{ false };
    do {
        if (flagExit)
        {
            char exitChar{};
            cout << "Вы все ещё хотите удалить какого-либо студента?(y/n)" << endl;
            exitChar = getCorrectChar();
            if (exitChar == 'n' or exitChar == 'N')
            {
                return;
            }
        }
        printAllDataFromBase();
        cout << "Введите ID студента для удаления" << endl;
        idForDel = getCorrectId();
        cout << "Вы действительно хотите удалить студента с ID:" << idForDel << "?(y/n)(Если вы введете слово, будет использован первый символ)" << endl;
        accept = getCorrectChar();
        flagExit = true;
    } while (accept == 'n' or accept == 'N');
    int indexStudentForDel{};
    for (Student student : Students)
    {
        if (student.id == idForDel)
        {
            FreeId.push_back(idForDel);
            Student newStudent{};
            Students[indexStudentForDel] = newStudent;
            break;
        }
        indexStudentForDel++;
    }
}
void changeStudentData(vector<string> updataOneStudent, int idStudentForChange)
{
    int indexInVec{};
    try
    {
        Student newStudent{};
        newStudent.id = idStudentForChange;
        newStudent.lastname = updataOneStudent[indexInVec++];
        newStudent.name = updataOneStudent[indexInVec++];
        newStudent.fathername = updataOneStudent[indexInVec++];
        newStudent.level = stoi(updataOneStudent[indexInVec++]);
        newStudent.group = updataOneStudent[indexInVec++];
        newStudent.firstYear = stoi(updataOneStudent[indexInVec++]);
        newStudent.marks[0] = stoi(updataOneStudent[indexInVec++]);
        newStudent.marks[1] = stoi(updataOneStudent[indexInVec++]);
        newStudent.marks[2] = stoi(updataOneStudent[indexInVec++]);
        newStudent.marks[3] = stoi(updataOneStudent[indexInVec++]);
        newStudent.marks[4] = stoi(updataOneStudent[indexInVec++]);
        Students[idStudentForChange - 1] = newStudent;
        cout << "Студент изменен c ID:" << newStudent.id << endl;
    }
    catch (...)
    {
        cout << "Данные в файле в неверном формате" << endl;
    }
}
void preSortDataFromBase() {
    vector <Student> studentsForSort{};
    for (Student students : Students)
    {
        studentsForSort.push_back(students);
    }
    if (studentsForSort.empty())
    {
        cout << "База даннных пуста. Сортировка невозможна." << endl;
        return;
    }
    cout << "Выберите направление сортировки" << endl;
    cout << "1 - В порядке возрастания (А-Я)" << endl;
    cout << "2 - В порядке убывания (Я-А)" << endl;
    cout << "Введите номер:" << endl;
    int choiceDirection{};
    bool exitControl{ true };
    do
    {
        choiceDirection = getCorrectValue();
        exitControl = false;
        switch (choiceDirection)
        {
        case 1:
        {
            cout << "Выберите поле для сортировки" << endl;
            cout << "1 - ID" << endl;
            cout << "2 - Фамилия" << endl;
            cout << "3 - Имя" << endl;
            cout << "4 - Отчество" << endl;
            cout << "5 - Курс" << endl;
            cout << "6 - Группа" << endl;
            cout << "7 - Год поступления" << endl;
            cout << "8 - Оценки" << endl;
            cout << "Введите номер:" << endl;
            int choiceSortField{};
            bool exitControlBy1{ false };
            do
            {
                choiceSortField = getCorrectValue();
                exitControlBy1 = false;
                if (choiceSortField < 1 or choiceSortField > 8) exitControl = true;
            } while (exitControlBy1);
            sortStudent(choiceDirection, choiceSortField, studentsForSort);
            break;
        }
        case 2:
        {
            cout << "Выберите поле для сортировки" << endl;
            cout << "1 - ID" << endl;
            cout << "2 - Фамилия" << endl;
            cout << "3 - Имя" << endl;
            cout << "4 - Отчество" << endl;
            cout << "5 - Курс" << endl;
            cout << "6 - Группа" << endl;
            cout << "7 - Год поступления" << endl;
            cout << "8 - Оценки" << endl;
            cout << "Введите номер:" << endl;
            int choiceSortField{};
            bool exitControlBy2{ false };
            do
            {
                choiceSortField = getCorrectValue();
                exitControlBy2 = false;
                if (choiceSortField < 1 or choiceSortField > 8) exitControl = true;
            } while (exitControlBy2);
            sortStudent(choiceDirection, choiceSortField, studentsForSort);
            break;
        }
        default:
        {
            cout << "Введен неверный номер. Повторите попытку." << endl;
            exitControl = true;
        }
        }
    } while (exitControl);
}
void sortStudent(int sortDirection, int sortField, vector<Student> studentsForSort)
{
    switch (sortDirection)
    {
    case 1:
    {
        switch (sortField)
        {
        case 1:
        {
            mySort(begin(studentsForSort), end(studentsForSort), [](Student a, Student b) {return a.id < b.id;});
            printStudentsFromVector(studentsForSort);
            break;
        }
        case 2:
        {
            mySort(begin(studentsForSort), end(studentsForSort), [](Student a, Student b) {return toLower(a.lastname) < toLower(b.lastname);});
            printStudentsFromVector(studentsForSort);
            break;
        }
        case 3:
        {
            mySort(begin(studentsForSort), end(studentsForSort), [](Student a, Student b) {return toLower(a.name) < toLower(b.name);});
            printStudentsFromVector(studentsForSort);
            break;
        }
        case 4:
        {
            mySort(begin(studentsForSort), end(studentsForSort), [](Student a, Student b) {return toLower(a.fathername) < toLower(b.fathername);});
            printStudentsFromVector(studentsForSort);
            break;
        }
        case 5:
        {
            mySort(begin(studentsForSort), end(studentsForSort), [](Student a, Student b) {return a.level < b.level;});
            printStudentsFromVector(studentsForSort);
            break;
        }
        case 6:
        {
            mySort(begin(studentsForSort), end(studentsForSort), [](Student a, Student b) {return a.group < b.group;});
            printStudentsFromVector(studentsForSort);
            break;
        }
        case 7:
        {
            mySort(begin(studentsForSort), end(studentsForSort), [](Student a, Student b) {return a.firstYear < b.firstYear;});
            printStudentsFromVector(studentsForSort);
            break;
        }
        case 8:
        {
            mySort(begin(studentsForSort), end(studentsForSort), [](Student a, Student b) {return getAverage(a.marks) < getAverage(b.marks);});
            printStudentsFromVector(studentsForSort);
            break;
        }
        default:
        {
            return;
        }
        }
        break;
    }
    case 2:
    {
        switch (sortField)
        {
        case 1:
        {
            mySort(begin(studentsForSort), end(studentsForSort), [](Student a, Student b) {return a.id > b.id;});
            printStudentsFromVector(studentsForSort);
            break;
        }
        case 2:
        {
            mySort(begin(studentsForSort), end(studentsForSort), [](Student a, Student b) {return toLower(a.lastname) > toLower(b.lastname);});
            printStudentsFromVector(studentsForSort);
            break;
        }
        case 3:
        {
            mySort(begin(studentsForSort), end(studentsForSort), [](Student a, Student b) {return toLower(a.name) > toLower(b.name);});
            printStudentsFromVector(studentsForSort);
            break;
        }
        case 4:
        {
            mySort(begin(studentsForSort), end(studentsForSort), [](Student a, Student b) {return toLower(a.fathername) > toLower(b.fathername);});
            printStudentsFromVector(studentsForSort);
            break;
        }
        case 5:
        {
            mySort(begin(studentsForSort), end(studentsForSort), [](Student a, Student b) {return a.level > b.level;});
            printStudentsFromVector(studentsForSort);
            break;
        }
        case 6:
        {
            mySort(begin(studentsForSort), end(studentsForSort), [](Student a, Student b) {return a.group > b.group;});
            printStudentsFromVector(studentsForSort);
            break;
        }
        case 7:
        {
            mySort(begin(studentsForSort), end(studentsForSort), [](Student a, Student b) {return a.firstYear > b.firstYear;});
            printStudentsFromVector(studentsForSort);
            break;
        }
        case 8:
        {
            mySort(begin(studentsForSort), end(studentsForSort), [](Student a, Student b) {return getAverage(a.marks) > getAverage(b.marks);});
            printStudentsFromVector(studentsForSort);
            break;
        }
        default:
        {
            return;
        }
        }
        break;
    }
    default:
    {
        return;
    }
    }
}
template<typename Iterator, typename Comparator>
void mySort(Iterator first, Iterator last, Comparator comp) {
    if (first == last) return;
    for (Iterator i = first; i != last; ++i) {
        for (Iterator j = first; j != i; ++j) {
            if (comp(*i, *j)) {
                iter_swap(i, j);
            }
        }
    }
}
// Функции вывода
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
    cout << "|";
    cout << setw(4) << "ID" << " | ";
    cout << setw(12) << "     Фамилия" << " | ";
    cout << setw(12) << "         Имя" << " | ";
    cout << setw(12) << "    Отчество" << " | ";
    cout << setw(4) << "Курс" << " | ";
    cout << setw(10) << "    Группа" << " | ";
    cout << setw(5) << "  Год" << " | ";
    cout << setw(5) << "  Мат" << " | " ;
    cout << setw(5) << "   ВП" << " | " ;
    cout << setw(5) << "  Рус" << " | " ;
    cout << setw(5) << " Англ" << " | " ;
    cout << setw(5) << "Химия" << " | \n" ;

    // Разделитель
    cout << string(119, '=') << "\n";

    // Данные студентов
    vector<Student> dataForExport;
    for (Student student : Students)
    {
        if (student.id == 0) continue;
        dataForExport.push_back(student);
        cout << string(119, '-') << "\n";
        cout << setw(1) << "|";
        cout << setw(4) << student.id << " | ";
        cout << setw(12) << student.lastname << " | ";
        cout << setw(12) << student.name << " | ";
        cout << setw(12) << student.fathername << " | ";
        cout << setw(4) << student.level << " | ";
        cout << setw(10) << student.group << " | ";
        cout << setw(5) << student.firstYear << " | ";
        cout << setw(5) << student.marks[0] << " | ";
        cout << setw(5) << student.marks[1] << " | ";
        cout << setw(5) << student.marks[2] << " | ";
        cout << setw(5) << student.marks[3] << " | ";
        cout << setw(5) << student.marks[4] << " | \n";
    }
    cout << "Нажмите кнопку, чтобы продолжить." << endl;
    cin.get();
}
void printStudentsFromVector(vector<Student> studentsList)
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
    cout << "|";
    cout << setw(4) << "ID" << " | ";
    cout << setw(12) << "     Фамилия" << " | ";
    cout << setw(12) << "         Имя" << " | ";
    cout << setw(12) << "    Отчество" << " | ";
    cout << setw(4) << "Курс" << " | ";
    cout << setw(10) << "    Группа" << " | ";
    cout << setw(5) << "  Год" << " | ";
    cout << setw(5) << "  Мат" << " | " ;
    cout << setw(5) << "   ВП" << " | " ;
    cout << setw(5) << "  Рус" << " | " ;
    cout << setw(5) << " Англ" << " | " ;
    cout << setw(5) << "Химия" << " | \n" ;

    // Разделитель
    cout << string(119, '=') << "\n";

    // Данные студентов
    vector<Student> dataForExport;
    for (Student student : studentsList)
    {
        if (student.id == 0) continue;
        dataForExport.push_back(student);
        cout << string(119, '-') << "\n";
        cout << setw(1) << "|";
        cout << setw(4) << student.id << " | ";
        cout << setw(12) << student.lastname << " | ";
        cout << setw(12) << student.name << " | ";
        cout << setw(12) << student.fathername << " | ";
        cout << setw(4) << student.level << " | ";
        cout << setw(10) << student.group << " | ";
        cout << setw(5) << student.firstYear << " | ";
        cout << setw(5) << student.marks[0] << " | ";
        cout << setw(5) << student.marks[1] << " | ";
        cout << setw(5) << student.marks[2] << " | ";
        cout << setw(5) << student.marks[3] << " | ";
        cout << setw(5) << student.marks[4] << " | \n";
    }
    preExportFromList(dataForExport);
}
// Функции прочие
void getIdStudentForChange()
{
    printAllDataFromBase();
    if (FreeId.size() == 10) return;
    cout << "Введите id студента, данные которого вы хотите изменить." << endl;
    int idStudentForChange{};
    idStudentForChange = getCorrectId();
    cout << "Вы действительно хотите изменить данные студента с id:" << idStudentForChange << "? (y/n)" << endl;
    char acceptAdminForChange{};
    acceptAdminForChange = getCorrectChar();
    if (acceptAdminForChange != 'y' and acceptAdminForChange != 'Y')
    {
        return;
    }
    else
    {
        loadChangeDataFromKeyboard(idStudentForChange);
    }
}
void parsingText(vector<string> txtLines)
{
    vector<string> dataOneStudent{};
    int indexString{};
    for (string txtString : txtLines)
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
        if (dataOneStudent.size() != 11)
        {
            cout << "Неверно отформатирована строка:" << indexString - 1 << endl;
            cout << txtString << endl;
            continue;
        }

        addNewStudent(dataOneStudent);
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
        regex pattern("[^0-9]");
        if ((cin >> n).fail()) {
            fixStreamState();
            cout << "Неверный тип данных!" << endl;
            cout << "Введите число(int): " << endl;
            isNotOk = true;
        }
    } while (isNotOk);
    fixStreamState();
    return n;
}
bool freeIdCheck()
{
    if (FreeId.size() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int getCorrectMark()
{
    int n{};
    bool isNotOk{};
    do {
        isNotOk = false;
        if ((cin >> n).fail() or (n < 2 or n > 5)) {
            fixStreamState();
            cout << "Неверное значение!" << endl;
            cout << "Введите оценку: " << endl;
            isNotOk = true;
        }
    } while (isNotOk);
    return n;
}
int getCorrectLevel()
{
    int n{};
    bool isNotOk{};

    do {
        isNotOk = false;
        if ((cin >> n).fail() or (n < 1 or n > 6)) {
            fixStreamState();
            cout << "Неверное значение!" << endl;
            cout << "Введите курс: " << endl;
            isNotOk = true;
        }
    } while (isNotOk);
    fixStreamState();
    return n;
}
int getCorrectFirstYear()
{
    int n{};
    bool isNotOk{};
    do {
        isNotOk = false;
        if ((cin >> n).fail() or (n < 2000 or n > 2025)) {
            fixStreamState();
            cout << "Неверное значение!" << endl;
            cout << "Введите год в промежутке от 2000 до 2025: " << endl;
            isNotOk = true;
        }
    } while (isNotOk);
    fixStreamState();
    return n;
}
int getCorrectId()
{
    int n{};
    bool isNotOk{};

    do {
        isNotOk = true;
        if ((cin >> n).fail() or n < 1 or n > 10 or count(FreeId.begin(), FreeId.end(), n) != 0) {
            fixStreamState();
            cout << "Неверное значение!" << endl;
            cout << "Введите ID: " << endl;
        }
        else {
            for (Student student : Students)
            {
                if (student.id == n)
                {
                    isNotOk = false;
                    break;
                }
            }
        }
    } while (isNotOk);
    fixStreamState();
    return n;
}
int getCorrectFormat()
{
    int n{};
    bool isNotOk{};

    do {
        isNotOk = false;
        regex pattern("[^1-3]");
        if ((cin >> n).fail() or (n < 1 or n > 3)) {
            fixStreamState();
            cout << "Неверные данные!" << endl;
            cout << "Введите число(1-3): " << endl;
            isNotOk = true;
        }
    } while (isNotOk);
    fixStreamState();
    return n;
}
char getCorrectChar()
{
    char n{};
    bool isNotOk{};
    do {
        isNotOk = false;
        if ((cin >> n).fail() or (n != 'y' and n != 'Y' and n != 'n' and n != 'N')) {
            fixStreamState();
            cout << "Неверное значение!" << endl;
            cout << "Повторите попытку: " << endl;
            isNotOk = true;
        }
    } while (isNotOk);
    fixStreamState();
    return n;
}
string getCorrectFIO()
{
    string n{};
    bool isNotOk{};
    do {
        isNotOk = false;
        cin >> n;
        regex pattern("[^A-ZА-Яa-zа-я]");
        if (n.length() < 2 or regex_search(n, pattern)) {
            fixStreamState();
            cout << "Неверное значение!" << endl;
            cout << "Повторите попытку: " << endl;
            isNotOk = true;
        }
    } while (isNotOk);
    fixStreamState();
    return n;
}
string getCorrectGroup()
{
    string n{};
    bool isNotOk{};
    do {
        isNotOk = false;
        cin >> n;
        regex pattern("[^(A-ZА-Я0-9-)]");
        regex letter("[A-ZА-Я]");
        regex number("[0-9]");
        regex dash("[-]");
        if (n.length() < 2 or regex_search(n, pattern) or !regex_search(n, dash) or !regex_search(n, letter) or !regex_search(n, number)) {
            fixStreamState();
            cout << "Неверное значение!" << endl;
            cout << "Повторите попытку: " << endl;
            isNotOk = true;
        }
    } while (isNotOk);
    fixStreamState();
    return n;
}
void studentsWithBadMarksChek()
{
    bool arrayIsEmpty = FreeId.size() == 10;
    if (arrayIsEmpty)
    {
        cout << "База пуста" << endl;
        return;
    }
    vector<Student> studentsWithBadMarks{};
    for (Student student : Students)
    {
        if (student.id == 0) continue;
        int countTwo{};
        for (int i = 0; i < 5; i++)
        {
            if (student.marks[i] == 2) countTwo++;
        }
        if (countTwo >= 3) studentsWithBadMarks.push_back(student);
    }
    if (studentsWithBadMarks.empty())
    {
        cout << "В базе нет студентов с двойками по трем и более предметам" << endl;
        return;
    }
    printStudentsFromVector(studentsWithBadMarks);
}
string toLower(string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(),
        [](char c) { return tolower(c); });
    return result;
}
int getAverage(int* marksPoint)
{
    int average{};
    int sumMarks{};
    for (int i = 0;i < 5;i++)
    {
        sumMarks += marksPoint[i];
    }
    average = sumMarks / 5.000;
    return average;
}
void preExportFromList(vector<Student> studentsForExport)
{
    char exportAccept{};
    cout << "Вы хотите сохранить эти данные в файл? (y/n)" << endl;
    exportAccept = getCorrectChar();
    if (exportAccept == 'y' or exportAccept == 'Y')
    {
        cout << "В каком формате вы хотите сохранить данные?" << endl;
        cout << "1 - .txt" << endl;
        cout << "2 - .dat" << endl;
        cout << "3 - .bin" << endl;
        int userChoiceFormat = getCorrectFormat();
        switch (userChoiceFormat)
        {
            case 1:
                {
                    cout << "Введите имя файла в который вы хотите сохранить данные (без формата)" << endl;
                    string txtFileName{};
                    cin >> txtFileName;
                    fixStreamState();
                    exportTxt(txtFileName, studentsForExport);
                    break;
                }
            case 2:
                {
                    cout << "Введите имя файла в который вы хотите сохранить данные (без формата)" << endl;
                    string datFileName{}, format{".dat"};
                    cin >> datFileName;
                    fixStreamState();
                    datFileName += format;
                    exportBin(datFileName, studentsForExport);
                    break;
                }
            case 3:
                {
                    cout << "Введите имя файла в который вы хотите сохранить данные (без формата)" << endl;
                    string datFileName{}, format{".bin"};
                    cin >> datFileName;
                    fixStreamState();
                    datFileName += format;
                    exportBin(datFileName, studentsForExport);
                    break;
                }
            default:
                {
                    cout << "Ошибочный ввод." << endl;
                }
        }
    }
    else
    {
        return;
    }
}
void preExportFromMenu()
{
    vector<Student> studentsToExport{};
    for (Student student : Students)
    {
        studentsToExport.push_back(student);
    }
    printStudentsFromVector(studentsToExport);
}
void exportTxt(string txtFileName, vector<Student> studentsToExportTxt)
{
    if (studentsToExportTxt.empty())
    {
        cout << "Нет студентов для экспорта" << endl;
        return;
    }
    ofstream txtFile(txtFileName + ".txt");
    if (!txtFile.is_open())
    {
        cout << "Ошибка открытия (создания) файла" << endl;
        return;
    }
    txtFile << "Фамилия;Имя;Отчество;Курс;Группа;Год_поступления;"
        << "Оценка1;Оценка2;Оценка3;Оценка4;Оценка5" << endl;
    for (Student student : studentsToExportTxt)
    {
        txtFile << student.lastname << ";"
            << student.name << ";"
            << student.fathername << ";"
            << student.level << ";"
            << student.group << ";"
            << student.firstYear << ";"
            << student.marks[0] << ";"
            << student.marks[1] << ";"
            << student.marks[2] << ";"
            << student.marks[3] << ";"
            << student.marks[4] << endl;
    }
    txtFile.close();
    cout << "Данные успешно экспортированы в файл " << txtFileName + ".txt" << endl;
}
void exportBin(string binFileName, vector<Student> studentsToExportBin)
{
    if (studentsToExportBin.empty())
    {
        cout << "Нет студентов для экспорта" << endl;
        return;
    }
    ofstream binFile(binFileName, ios::binary);
    for (Student student : studentsToExportBin)
    {
        binFile.write(reinterpret_cast<char*>(&student), sizeof(student));
    }
    binFile.close();
    cout << "Данные успешно экспортированы в файл " << binFileName << endl;
}