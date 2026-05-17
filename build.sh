#!/bin/bash

# Создаем папку release
mkdir -p release

# Компилируем проект
g++ -std=c++17 -O3 -Iinclude -o release/bulk src/bulk.cpp

# Проверяем успешность компиляции
if [ $? -eq 0 ]; then
    echo "✓ Компиляция успешна!"
    echo "✓ Release создан в папке 'release'"
    exit 0
else
    echo "✗ Ошибка компиляции!"
    exit 1
fi
