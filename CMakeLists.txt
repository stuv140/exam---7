cmake_minimum_required(VERSION 3.10)
project(BulkProject)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем директорию с заголовочными файлами
include_directories(include)

# Добавляем исполняемый файл из src/bulk.cpp
add_executable(bulk src/bulk.cpp)

# Настройки для release сборки
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
