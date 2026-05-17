// bulk.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include<ctime>
void Com(std::string str) {
    std::ofstream out("bulk" + std::to_string(std::time(0)) + ".log");
    std::cout << str ;
    out << str << std::endl;
    out.close();
}
bool Is(std::string str)
{
    static int num = 0;

    return true;
}
int main(int argc, char* argv[])
{ 
    std::vector<std::string> batch;
    auto N = -1;
    int dynamicLevel = 0; // Уровень вложенности динамических блоков
    std::string command;
    //std::cout << "number command: " << argc << std::endl;
    try {
        for (auto i = 0; i < argc; i++) {
            //      std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
            if (i == 1) {
                N = atoi(argv[i]);// возвращает 0 при неудачном преобразовании
            }
            if (i > 1)throw std::runtime_error("Error: i > 1 argument");
        }
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        N = -1;
    }
    catch (...) {
        std::cout << "error: " << std::endl;
        N = -2;
    }
    try {
        if (N == 0)throw std::runtime_error("Incorrect argument");
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        N = -1;
    }
   // N = 3;
    while (std::getline(std::cin, command)) {
        if (command == "EOF" || command == "eof")break;
        if (!command.empty()&& Is(command)) {
            if (command == "{") {
                if (dynamicLevel == 0) {
                    if (!batch.empty()) {
                        std::cout << "bulk: ";
                        int i = 0;
                        for (const auto& cmd : batch) {
                            Com(cmd);
                            i++;
                            if (i < batch.size()) {
                                std::cout << ", ";
                            }
                            else
                                std::cout << std::endl;
                        
                        }
                        batch.clear();
                    }
                    N++;
                }
                dynamicLevel++;
                continue;
            }
            
        }
        if (command == "}") {
            if (dynamicLevel > 0) {
                dynamicLevel--;
                if (dynamicLevel == 0) {
                    // Завершаем текущий пакет, если он есть
                    if (!batch.empty()) {
                        std::cout << "bulk: ";
                        int i = 0;
                        for (const auto& cmd : batch) {
                            Com(cmd);

                            i++;
                            if (i < batch.size()) {
                                std::cout << ", ";
                            }
                            else
                                std::cout << std::endl;
                        }
                    
                        batch.clear();
                    }
                    N--;
                }
            }
            continue;
        }
      // if (dynamicLevel > 0) continue;

        // Добавляем команду в пакет
        batch.push_back(command);

        // Если пакет заполнен — обрабатываем его
        if ((int)batch.size() >= N && dynamicLevel==0) { 
            int i = 0;
            std::cout << "bulk: ";
            for (const auto& cmd : batch) {
                Com(cmd);
                i++;
                if (i < batch.size()) {
                    std::cout << ", ";
                }
                else
                    std::cout<<std::endl;
                
            }   

            batch.clear();
        }
    }

    // Если после завершения ввода остались команды вне динамического блока — обрабатываем их
    if (!batch.empty() && dynamicLevel == 0) {   
        std::cout << "bulk: ";
        int i = 0;
        for (const auto& cmd : batch){
            Com(cmd);            
            i++;
            if (i < batch.size()) {
                std::cout << ", ";
            }
            else
                std::cout << std::endl;
        }
        
    }

    //std::cout << "number command N: " << N << std::endl;
    return N;
}

