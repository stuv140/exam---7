
#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include<ctime>
#include <thread>
#include"Command.h"

int main(int argc, char* argv[])
{ 
  
    auto N = -1;

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
  
   
    command test(N);
    test.in();
    
    return N;
}
