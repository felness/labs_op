#include <iostream>
#include <dlfcn.h>
#include <vector>
#include <sstream>

// Типы функций
typedef float (*DerivativeFunc)(float, float);
typedef int* (*SortFunc)(int*, int);

int main() {
    void* lib_handle = nullptr;
    DerivativeFunc Derivative = nullptr;
    SortFunc Sort = nullptr;

    bool lib_loaded = false;
    int lib_choice = 0;  // Начинаем с первой библиотеки

    std::string input_line;
    while (std::getline(std::cin, input_line)) {
        std::istringstream iss(input_line);
        int command;
        iss >> command;

        if (command == 0) {
            // Смена библиотеки
            if (lib_handle) {
                dlclose(lib_handle);
                lib_handle = nullptr;
                lib_loaded = false;
            }
            lib_choice = 1 - lib_choice; // Переключаемся между 0 и 1
            
            std::string lib_name = lib_choice ? "./mathfunctions2.so" : "./mathfunctions1.so";
            lib_handle = dlopen(lib_name.c_str(), RTLD_LAZY);
            if (!lib_handle) {
                std::cerr << "Ошибка загрузки библиотеки: " << dlerror() << std::endl;
                continue;
            }

            Derivative = (DerivativeFunc)dlsym(lib_handle, "Derivative");
            Sort = (SortFunc)dlsym(lib_handle, "Sort");
            
            if (!Derivative || !Sort) {
                std::cerr << "Ошибка получения адреса функции: " << dlerror() << std::endl;
                dlclose(lib_handle);
                lib_handle = nullptr;
                continue;
            }

            lib_loaded = true;
            std::cout << "Библиотека переключена на " << lib_name << std::endl;
        } else if (command == 1) {
            if (!lib_loaded) {
                std::cerr << "Библиотека не загружена." << std::endl;
                continue;
            }

            float A, deltaX;
            iss >> A >> deltaX;
            std::cout << "Результат Derivative: " << Derivative(A, deltaX) << std::endl;

        } else if (command == 2) {
            if (!lib_loaded) {
                std::cerr << "Библиотека не загружена." << std::endl;
                continue;
            }

            std::vector<int> nums;
            int num;
            while (iss >> num) nums.push_back(num);

            Sort(&nums[0], nums.size());
            
            std::cout << "Отсортированный массив: ";
            for (auto n : nums) {
                std::cout << n << " ";
            }
            std::cout << std::endl;
        } else {
            std::cerr << "Неизвестная команда." << std::endl;
        }
    }

    if (lib_handle) {
        dlclose(lib_handle);
    }

    return 0;
}
