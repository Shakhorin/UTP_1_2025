//
// Created by book on 03.10.2025.
//
#ifndef STUDENT_LIB_H
#define STUDENT_LIB_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

extern string name[10], lastname[10], fathername[10], group[10];
extern int id[10], level[10], first_year[10];
extern int marks1[10], marks2[10], marks3[10], marks4[10], marks5[10];
extern vector<int> free_id;
extern int menuItemWhoUserChoised ;

// Прототипы функций
void addStudent(string name_new, string lastname_new, string father_name_new,
                int level_new, string group_new, int first_year_new, int marks_new[5]);
void deleteStudent(int student_id);
int searchStudent();
void showMenu();
void inputFromKeyboard();
void loadFromTextFile();
void loadFromBinaryFile();
void displayStudents(bool exportFlag);
void displayStudents(vector<int> indices);
void saveToFile(vector<int> indices);
void saveToFile();
void processQuery();
void exportToTextFile();
void convertTextToBinary();
void addStudentMenu();
void addStudentMenu(int id);
void editStudent();
void addStudentById(int id_new, string name_new, string lastname_new, string father_name_new,
                    int level_new, string group_new, int first_year_new, int marks_new[5]);
void deleteStudentMenu();
void sortStudents();
void exitProgram();
double getAverage(int index);
void preBase();
void finalExport();

#endif //UTP_1_2025_FUNCLIB_H