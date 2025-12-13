#!/bin/bash

g++ ./src/main.cpp -o matrix-proc -std=c++23 -Wall -Wextra -O2

if [ $? -eq 0 ]; then
    echo "Компиляция прошла успешно!"
    echo "Запуск: ./matrix-proc <размер> <процессы>"
else
    echo "Ошибка компиляции!"
fi
