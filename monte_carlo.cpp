
#include <iostream>
#include <pthread.h>
#include <vector>
#include <random>

using namespace std;

struct ThreadData {
    int rounds; 
    int successCount = 0;
};

void* simulate(void* arg) {
    ThreadData* data = reinterpret_cast<ThreadData*>(arg);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 52);

    for (int i = 0; i < data->rounds; ++i) {
        int card1 = dis(gen) % 13;
        int card2 = dis(gen) % 13;
        if (card1 == card2) {
            data->successCount++;
        }
    }

    return nullptr;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <rounds> <max_threads>" << endl;
        return EXIT_FAILURE;
    }

    int rounds = stoi(argv[1]);
    int maxThreads = stoi(argv[2]);
    vector<ThreadData> threadData(maxThreads);
    vector<pthread_t> threads(maxThreads);

    int roundsPerThread = rounds / maxThreads;

    for (int i = 0; i < maxThreads; ++i) {
        threadData[i].rounds = roundsPerThread;
        if (pthread_create(&threads[i], nullptr, simulate, &threadData[i])) {
            cerr << "Error creating thread" << endl;
            return EXIT_FAILURE;
        }
    }
    int totalSuccess = 0;
    for (int i = 0; i < maxThreads; ++i) {
        pthread_join(threads[i], nullptr);
        totalSuccess += threadData[i].successCount;
    }

    double probability = static_cast<double>(totalSuccess) / rounds;
    cout << "Estimated Probability: " << probability << endl;

    return EXIT_SUCCESS;
} 
