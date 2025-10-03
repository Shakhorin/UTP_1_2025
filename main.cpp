#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include "student_lib.h"
using namespace std;

int main()
{
    // Установка русской кодировки для корректного отображения текста
    system("chcp 65001");

    // Загрузка данных из файла при запуске программы
    preBase();

    do
    {
        //cin.ignore();
        system("cls");
        // Отображение меню и обработка выбора пользователя
        showMenu();

        cin >> menuItemWhoUserChoised;
        cin.ignore(); // Очистка буфера после ввода числа

        // Обработка выбора пользователя
        switch (menuItemWhoUserChoised)
        {
        case 1: inputFromKeyboard();
            break; //+
        case 2: loadFromTextFile();
            break;
        case 3: loadFromBinaryFile();
            break;
        case 4: displayStudents(true);
            break; //+
        case 5: saveToFile();
            break; //+
        case 6: processQuery();
            break; //+
        case 7: exportToTextFile_calc();
            break;
        case 8: convertTextToBinary();
            break;
        case 9: addStudentMenu();
            break; //+
        case 10: editStudent();
            break; //+
        case 11: deleteStudentMenu();
            break; //+
        case 12: sortStudents();
            break;
        case 13: exitProgram();
            break; //+
        default: cout << "Неверный номер команды!\n" << endl;
        }

        // Пауза перед очисткой экрана (только если не выход)
        if (menuItemWhoUserChoised != 13)
        {
            //system("cls");
            cout << "\nНажмите Enter для продолжения...";
            cin.ignore();
        }
        system("cls"); // Очистка экрана
    }
    while (menuItemWhoUserChoised != 13);

    // Финальное сохранение при выходе
    char userChoice{};
    cout << "Вы хотите сохранить это состояние бд?(y/n)" << endl;
    cin >> userChoice;
    cin.ignore();
    if (userChoice == 'y' or userChoice == 'Y')
    {
        finalExport();
    }
    return 0;
}

