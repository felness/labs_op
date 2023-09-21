#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
// Функция, которая будет выполняться в дочернем процессе
void childProcess(const vector<float>& numbers, const string& filename) {
    float sum = 0;

    // Вычисление суммы чисел
    for (float number : numbers) {
        sum += number;
    }

    // Запись суммы в файл
    ofstream file(filename);
    if (file.is_open()) {
        file << "Sum: " << sum << endl;
        file.close();
    } else {
        cerr << "Unable to open the file." << endl;
    }
}

int main() {
    string input;
    vector<float> numbers;

    cout << "Enter numbers (separated by spaces) followed by '<endine>': ";
    getline(cin, input);

    istringstream iss(input);
    float number;
    while (iss >> number) {
        numbers.push_back(number);
    }

    // Создание дочернего процесса
    pid_t pid = fork();

    if (pid == -1) {
        cerr << "Failed to fork a child process." << endl;
        return 1;
    } else if (pid == 0) {
        // Дочерний процесс
        childProcess(numbers, "sum.txt");
    } else {
        // Родительский процесс
        wait(NULL); // Ожидание завершения дочернего процесса
        cout << "Sum calculation completed." << endl;
    }

    return 0;
}
// ```

// Программа запрашивает у пользователя ввод чисел, разделенных пробелами, и заканчивающихся `<endine>`. Затем она создает дочерний процесс с помощью функции `fork()`. В дочернем процессе выполняется функция `childProcess`, где происходит вычисление суммы чисел и запись результата в файл "sum.txt". В родительском процессе используется функция `wait(NULL)`, чтобы ожидать завершения дочернего процесса. После завершения дочернего процесса выводится сообщение о завершении вычислений.

// Пожалуйста, обратите внимание, что файл "sum.txt" будет создан в том же каталоге, где находится исполняемый файл программы.
// 📬 Для смены темы разговора или режима нажмите кнопку ниже. Это поможет быстро и легко начать обсуждение другой темы.