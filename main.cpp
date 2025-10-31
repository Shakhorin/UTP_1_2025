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
#include <regex>
#include <numeric>
#include <cstring>

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
void loadFromKeyboard();
void parsingText(vector<string>);
void fixStreamState();
int getCorrectValue();
bool freeIdCheck();
int getCorrectMark();
int getCorrectLevel();
int getCorrectFirstYear();
int getCorrectId();
char getCorrectChar();
string getCorrectFIO();
string getCorrectGroup();
void studentsWithBadMarksChek();
void getIdStudentForChange();
void loadChangeDataFromKeyboard(int);
string toLower(string&);
int getAverage(int []);
// Функции взаимодействия с базой
void addNewStudent(vector<string>);
void printAllDataFromBase();
void printStudentsFromVector(vector<Student>);
void printStudentsFromVector(vector<int>);
void delStudentFromBase();
void changeStudentData(vector<string>,int);
void preSortDataFromBase();
void sortStudent(int,int,vector<Student>);
void preExportTxtFromList(vector<Student>);
void preExportTxtFromMenu();
void exportTxt(string,vector<Student>);
// Конец область функций

int main()
{
    system("chcp 65001");
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
                    break;
                case 3:
                    printAllDataFromBase();
                    break;
                case 4:
                    studentsWithBadMarksChek();
                    break;
                case 5:
                    preExportTxtFromMenu();
                    break;
                case 6:
                    break;
                case 7:
                    preSortDataFromBase();
                    break;
                case 8:
                    break;
                default:
                    cout << "Введен неверный номер" << endl;
                }
            }while(userChoice != 8);
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
                    break;
                case 4:
                    printAllDataFromBase();
                    break;
                case 5:
                    studentsWithBadMarksChek();
                    break;
                case 6:
                    preExportTxtFromMenu();
                    break;
                case 7:
                    break;
                case 8:
                    getIdStudentForChange();
                    break;
                case 9:
                    delStudentFromBase();
                    break;
                case 10:
                    preSortDataFromBase();
                    break;
                case 11:
                    break;
                default:
                    cout << "Введен неверный номер" << endl;
                }
            }while(adminChoice != 11);
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
// Функции меню
void adminMenu()
{
    cout <<"\n";
    cout << "========== СИСТЕМА УПРАВЛЕНИЯ СТУДЕНТАМИ ==========\n" << endl;
    cout << "***ФУНКЦИИ ВВОДА***" << endl;
    cout << "1. Ввод информации с клавиатуры" << endl;
    cout << "2. Загрузка из текстового файла" << endl;
    cout << "3. Загрузка из бинарного файла" << endl;
    cout <<"\n";
    cout << "***ФУНКЦИИ ВЫВОДА НА ЭКРАН***" << endl;
    cout << "4. Вывод данных в виде таблицы" << endl;
    cout << "5. Выполнение запроса (поиск двоечников)" << endl;
    cout <<"\n";
    cout << "***ФУНКЦИИ ЭКСПОРТА***" << endl;
    cout << "6. Экспорт в текстовый файл" << endl;
    cout << "7. Экспорт в бинарный файл" << endl;
    cout <<"\n";
    cout << "***ФУНКЦИИ РЕДАКТИРОВАНИЯ ДАННЫХ***" << endl;
    cout << "8. Изменение записи" << endl;
    cout << "9. Удаление записи" << endl;
    cout << "10. Сортировка данных" << endl;
    cout << endl;
    cout << "11. Выход" << endl;
    cout << "\nВведите номер команды: ";
}
void userMenu()
{
    cout <<"\n";
    cout << "========== СИСТЕМА УПРАВЛЕНИЯ СТУДЕНТАМИ ==========\n" << endl;
    cout << "***ФУНКЦИИ ВВОДА***" << endl;
    cout << "1. Загрузка из текстового файла" << endl;
    cout << "2. Загрузка из бинарного файла" << endl;
    cout <<"\n";
    cout << "***ФУНКЦИИ ВЫВОДА НА ЭКРАН***" << endl;
    cout << "3. Вывод данных в виде таблицы" << endl;
    cout << "4. Выполнение запроса (поиск двоечников)" << endl;
    cout <<"\n";
    cout << "***ФУНКЦИИ ЭКСПОРТА***" << endl;
    cout << "5. Экспорт в текстовый файл" << endl;
    cout << "6. Конвертация в бинарный файл" << endl;
    cout <<"\n";
    cout << "***ФУНКЦИИ РЕДАКТИРОВАНИЯ ДАННЫХ***" << endl;
    cout << "7. Сортировка данных" << endl;
    cout << endl;
    cout << "8. Выход" << endl;
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
void loadFromKeyboard()
{
    if (!freeIdCheck())
    {
        cout << "В базу занесено максимальное количество студентов" << endl;
        return;
    }
    vector<string> dataOneStudent{};
    cout << "ВНИМАНИЕ! ДЛЯ ВВОДА ДАННЫХ ИСПОЛЬЗУЙТЕ ЛАТИНСКИЙ АЛФАВИТ" << endl;
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
    cout << "Старое значение: " ;
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
void delStudentFromBase()
{
    char accept{};
    int idForDel{};
    bool flagExit{false};
    do{
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
    }while (accept == 'n' or accept == 'N');
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
        Students[idStudentForChange-1] = newStudent;
        cout << "Студент изменен c ID:" << newStudent.id << endl;
    }catch (...)
    {
        cout << "Данные в файле в неверном формате" << endl;
    }
}
void preSortDataFromBase(){
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
    bool exitControl{true};
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
                    bool exitControlBy1{false};
                    do
                    {
                        choiceSortField = getCorrectValue();
                        exitControlBy1 = false;
                        if (choiceSortField < 1 or choiceSortField > 8) exitControl = true;
                    }while (exitControlBy1);
                    sortStudent(choiceDirection,choiceSortField,studentsForSort);
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
                    bool exitControlBy2{false};
                    do
                    {
                        choiceSortField = getCorrectValue();
                        exitControlBy2 = false;
                        if (choiceSortField < 1 or choiceSortField > 8) exitControl = true;
                    }while (exitControlBy2);
                    sortStudent(choiceDirection,choiceSortField,studentsForSort);
                    break;
                }
            default:
                {
                    cout << "Введен неверный номер. Повторите попытку." << endl;
                    exitControl = true;
                }
        }
    }while (exitControl);
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
                            sort(begin(studentsForSort), end(studentsForSort),[](Student a,Student b){return a.id < b.id;});
                            printStudentsFromVector(studentsForSort);
                            break;
                        }
                    case 2:
                        {
                            sort(begin(studentsForSort), end(studentsForSort),[](Student a,Student b){return toLower(a.lastname) < toLower(b.lastname);});
                            printStudentsFromVector(studentsForSort);
                            break;
                        }
                    case 3:
                        {
                            sort(begin(studentsForSort), end(studentsForSort),[](Student a,Student b){return toLower(a.name) < toLower(b.name);});
                            printStudentsFromVector(studentsForSort);
                            break;
                        }
                    case 4:
                        {
                            sort(begin(studentsForSort), end(studentsForSort),[](Student a,Student b){return toLower(a.fathername) < toLower(b.fathername);});
                            printStudentsFromVector(studentsForSort);
                            break;
                        }
                    case 5:
                        {
                            sort(begin(studentsForSort), end(studentsForSort),[](Student a,Student b){return a.level < b.level;});
                            printStudentsFromVector(studentsForSort);
                            break;
                        }
                    case 6:
                        {
                            sort(begin(studentsForSort), end(studentsForSort),[](Student a,Student b){return a.group < b.group;});
                            printStudentsFromVector(studentsForSort);
                            break;
                        }
                    case 7:
                        {
                            sort(begin(studentsForSort), end(studentsForSort),[](Student a,Student b){return a.firstYear < b.firstYear;});
                            printStudentsFromVector(studentsForSort);
                            break;
                        }
                    case 8:
                        {
                            sort(begin(studentsForSort), end(studentsForSort),[](Student a,Student b){return getAverage(a.marks) < getAverage(b.marks);});
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
                            sort(begin(studentsForSort), end(studentsForSort),[](Student a,Student b){return a.id > b.id;});
                            printStudentsFromVector(studentsForSort);
                            break;
                        }
                    case 2:
                        {
                            sort(begin(studentsForSort), end(studentsForSort),[](Student a,Student b){return toLower(a.lastname) > toLower(b.lastname);});
                            printStudentsFromVector(studentsForSort);
                            break;
                        }
                    case 3:
                        {
                            sort(begin(studentsForSort), end(studentsForSort),[](Student a,Student b){return toLower(a.name) > toLower(b.name);});
                            printStudentsFromVector(studentsForSort);
                            break;
                        }
                    case 4:
                        {
                            sort(begin(studentsForSort), end(studentsForSort),[](Student a,Student b){return toLower(a.fathername) >toLower( b.fathername);});
                            printStudentsFromVector(studentsForSort);
                            break;
                        }
                    case 5:
                        {
                            sort(begin(studentsForSort), end(studentsForSort),[](Student a,Student b){return a.level > b.level;});
                            printStudentsFromVector(studentsForSort);
                            break;
                        }
                    case 6:
                        {
                            sort(begin(studentsForSort), end(studentsForSort),[](Student a,Student b){return a.group > b.group;});
                            printStudentsFromVector(studentsForSort);
                            break;
                        }
                    case 7:
                        {
                            sort(begin(studentsForSort), end(studentsForSort),[](Student a,Student b){return a.firstYear > b.firstYear;});
                            printStudentsFromVector(studentsForSort);
                            break;
                        }
                    case 8:
                        {
                            sort(begin(studentsForSort), end(studentsForSort),[](Student a,Student b){return getAverage(a.marks) > getAverage(b.marks);});
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
    vector<Student> dataForExport;
    for (Student student: Students)
    {
        if (student.id == 0) continue;
        dataForExport.push_back(student);
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
    cout << "Нажмите кнопку, чтобы продолжить." << endl;
    cin.get();
    preExportTxtFromList(dataForExport);
}
void printStudentsWithBadMarks(vector<int> idStudentsWithBadMarks)
{
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
    vector<Student> dataForExport;
    for (Student student : Students){
        if (count(idStudentsWithBadMarks.begin(),idStudentsWithBadMarks.end(),student.id) == 0) continue;
        dataForExport.push_back(student);
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
    cout << "Нажмите кнопку, чтобы продолжить." << endl;
    cin.get();
    preExportTxtFromList(dataForExport);
}
void printStudentsFromVector(vector<Student> studentsSortList)
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
    vector<Student> dataForExport;
    for (Student student: studentsSortList)
    {
        if (student.id == 0) continue;
        dataForExport.push_back(student);
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
    cout << "Нажмите кнопку, чтобы продолжить." << endl;
    cin.get();
    preExportTxtFromList(dataForExport);
}
// Функции прочие
void getIdStudentForChange()
{
    printAllDataFromBase();
    if (FreeId.size() == 10) return;
    cout << "Введите id студента, данные которого вы хотите изменить." << endl;
    int idStudentForChange{};
    idStudentForChange = getCorrectId();
    cout << "Вы действительно хотите изменить данные студента с id:" << idStudentForChange << "? (y/n)" <<  endl;
    char acceptAdminForChange{};
    acceptAdminForChange = getCorrectChar();
    if (acceptAdminForChange != 'y' and acceptAdminForChange != 'Y')
    {
        return;
    }else
    {
        loadChangeDataFromKeyboard(idStudentForChange);
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
    }else
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
        if ((cin >> n).fail() or n < 1 or n > 10 or count(FreeId.begin(), FreeId.end(),n) != 0) {
            fixStreamState();
            cout << "Неверное значение!" << endl;
            cout << "Введите ID: " << endl;
        }else{
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
        regex pattern("[^A-Za-z]");
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
        regex pattern("[^(A-Z0-9-)]");
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
void studentsWithBadMarksChek()
{
    bool arrayIsEmpty = FreeId.size() == 10;
    if (arrayIsEmpty)
    {
        cout << "База пуста" << endl;
        return;
    }
    vector<int> idStudentsWithBadMarks{};
    for (Student student : Students)
    {
        if (student.id == 0) continue;
        int countTwo{};
        for (int i = 0; i < 5; i++)
        {
            if (student.marks[i] == 2) countTwo++;
        }
        if (countTwo >= 3) idStudentsWithBadMarks.push_back(student.id);
    }
    if (idStudentsWithBadMarks.empty())
    {
        cout << "В базе нет студентов с двойками по трем и более предметам" << endl;
        return;
    }
    printStudentsWithBadMarks(idStudentsWithBadMarks);
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
void preExportTxtFromList(vector<Student> studentsForExportToTxt)
{
    char exportAccept{};
    cout << "Вы хотите сохранить эти данные в файл? (y/n)" << endl;
    exportAccept = getCorrectChar();
    if (exportAccept == 'y' or exportAccept == 'Y')
    {
        cout << "Введите имя файла в который вы хотите сохранить данные (без формата)" << endl;
        string txtFileName{};
        cin >> txtFileName;
        fixStreamState();
        exportTxt(txtFileName,studentsForExportToTxt);
    }else
    {
        return;
    }
}
void preExportTxtFromMenu()
{
    printAllDataFromBase();
}
void exportTxt(string txtFileName, vector<Student> studentsToExportTxt)
{
    if (studentsToExportTxt.empty())
    {
        cout << "Нет студентов для экспорта" << endl;
        return;
    }
    ofstream txtFile (txtFileName + ".txt");
    if (!txtFile.is_open())
    {
        cout << "Ошибка открытия (создания) файла" << endl;
        return;
    }
    txtFile << "ID;Фамилия;Имя;Отчество;Курс;Группа;Год_поступления;"
        << "Оценка1;Оценка2;Оценка3;Оценка4;Оценка5" << endl;
    for (Student student : studentsToExportTxt)
    {
        txtFile << student.id << ";"
        << student.lastname << ";"
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