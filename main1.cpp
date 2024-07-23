#include <iostream>
#include <vector>
#include <sstream> // Для использования stringstream
#include "mathfunctions.h" // Включаем ваш заголовочный файл с функциями Derivative и Sort

int main() {
    std::cout << "Вводите команды:\n1 x y - для вычисления производной cos(x) с приращением y.\n2 n1 n2 ... nk - для сортировки массива чисел.\n";
    
    std::string line;
    while(std::getline(std::cin, line)) { // Получаем строку с вводом
        std::stringstream ss(line); // Используем stringstream для обработки строки
        int choice;
        ss >> choice;
        if (choice == 1) {
            // Вычисление производной
            float A, deltaX;
            if (!(ss >> A >> deltaX)) {
                std::cerr << "Неправильный формат ввода для вычисления производной." << std::endl;
                continue; // Продолжаем получать ввод, если ошиблись
            }
            float derivative = Derivative(A, deltaX);
            std::cout << "Производная cos в точке " << A << " равна: " << derivative << std::endl;
        } else if (choice == 2) {
            // Сортировка массива
            std::vector<int> nums;
            int num;
            while(ss >> num) {
                nums.push_back(num);
            }
            if (nums.empty()) {
                std::cerr << "Не указаны числа для сортировки." << std::endl;
                continue;
            }
            Sort(&nums[0], nums.size()); // Предполагаем, что Sort принимает указатель на массив и его размер
            std::cout << "Отсортированный массив: ";
            for (int n : nums) {
                std::cout << n << " ";
            }
            std::cout << std::endl;
        } else {
            std::cerr << "Неверный выбор функции." << std::endl;
        }
        
        std::cout << "Введите новую команду или CTRL+C для выхода.\n";
    }

    return 0;
}
