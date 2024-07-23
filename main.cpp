#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <cstring>
#include <cfloat> // Для FLT_MAX
using namespace std;

struct SharedData {
    float numbers[1024];
    bool inputCompleted;
};

int main() {
    string filename;
    cout << "Введите имя файла: ";
    cin >> filename;
    

    // Создание разделяемой памяти
    SharedData *shared_memory = (SharedData *)mmap(0, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_memory == MAP_FAILED) {
        cerr << "Ошибка при создании разделяемой памяти" << endl;
        return 1;
    }
    shared_memory->inputCompleted = false;

    pid_t pid = fork();

    if (pid == -1) {
        cerr << "Ошибка при создании дочернего процесса" << endl;
        return 1;
    } else if (pid == 0) {
        // Код дочернего процесса
        while (!shared_memory->inputCompleted) {
            sleep(1); // Ждем завершения ввода
        }

        float sum = 0;
        for (int i = 0; shared_memory->numbers[i] != FLT_MAX; ++i) {
            sum += shared_memory->numbers[i];
        }

        ofstream outputFile(filename);
        if (!outputFile.is_open()) {
            cerr << "Ошибка при открытии файла" << endl;
            return 1;
        }
        outputFile << "Сумма чисел: " << sum << endl;
        outputFile.close();

        munmap(shared_memory, sizeof(SharedData));
        return 0;
    } else {
        // Код родительского процесса
        cout << "Введите числа (для завершения ввода введите &):" << endl;
        string input;
        int count = 0;
        while (true) {
            cin >> input;
            if (input == "&") {
                break;
            }
            try {
                shared_memory->numbers[count++] = stof(input);
            } catch (const invalid_argument& ia) {
                cerr << "Неверный ввод: " << input << endl;
                continue;
            }
        }
        shared_memory->numbers[count] = FLT_MAX; // Маркер конца данных
        shared_memory->inputCompleted = true;

        wait(NULL); // Ждем завершения дочернего процесса
        munmap(shared_memory, sizeof(SharedData));
    }

    return 0;
}
