#!/bin/bash

g++ ./src/main.cpp -o matrix-threads -std=c++23 -Wall -Wextra -O2

if [ $? -eq 0 ]; then
    echo "Компиляция прошла успешно!"
    echo "Запуск: ./matrix-threads <размер> <процессы>"
else
    echo "Ошибка компиляции!"
fi
