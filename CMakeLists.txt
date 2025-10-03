cmake_minimum_required(VERSION 4.0)
project(UTP_1_2025)

set(CMAKE_CXX_STANDARD 20)

# Создание статической библиотеки
add_library(student_lib STATIC student_lib.cpp)

# Создание исполняемого файла
add_executable(UTP_1_2025 main.cpp)

# Связывание библиотеки с исполняемым файлом
target_link_libraries(UTP_1_2025 student_lib)