#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <algorithm>
struct Job {
    std::string id;
    std::string command;
    std::vector<std::string> depends_on;
    std::function<void(const Job&)> onError; // Функция обратного вызова для обработки ошибок
    std::function<bool()> execute; // Функция для выполнения работы
};

bool DFS(const std::unordered_map<std::string, std::vector<std::string>>& graph, const std::string& node,
         std::unordered_set<std::string>& visited, std::unordered_set<std::string>& recStack) {
    if (visited.find(node) == visited.end()) {
        visited.insert(node);
        recStack.insert(node);

        for (const auto& child : graph.at(node)) {
            if (recStack.find(child) != recStack.end() || DFS(graph, child, visited, recStack)) {
                return true; // Цикл найден
            }
        }
    }
    recStack.erase(node);
    return false;
}

bool isConnected(const std::unordered_map<std::string, std::vector<std::string>>& graph) {
    std::unordered_set<std::string> visited;
    if (!graph.empty()) {
        std::unordered_set<std::string> recStack; // Создаем экземпляр lvalue здесь
        DFS(graph, graph.begin()->first, visited, recStack); // Исправленный вызов функции
    }
    return visited.size() == graph.size();
}


bool checkForCycles(const std::vector<Job>& jobs) {
    std::unordered_map<std::string, std::vector<std::string>> graph;
    for (const auto& job : jobs) {
        graph[job.id] = job.depends_on;
    }

    std::unordered_set<std::string> visited, recStack;
    for (const auto& job : jobs) {
        if (DFS(graph, job.id, visited, recStack)) {
            return true; // Найден цикл
        }
    }
    return false;
}

bool checkStartAndEndJobs(const std::vector<Job>& jobs) {
    std::unordered_set<std::string> allJobs, dependentJobs;
    for (const auto& job : jobs) {
        allJobs.insert(job.id);
        dependentJobs.insert(job.depends_on.begin(), job.depends_on.end());
    }

    bool hasStart = false, hasEnd = false;
    for (const auto& job : allJobs) {
        if (dependentJobs.find(job) == dependentJobs.end()) {
            hasEnd = true; // Найдена работа, на которую никто не зависит
        }
        // Находим стартовые работы, проверяем, существует ли вершина без зависимостей
        auto it = find_if(jobs.begin(), jobs.end(), [job](const Job& j){ return j.id == job && j.depends_on.empty(); });
        if (it != jobs.end()) {
            hasStart = true;
        }
    }
    return hasStart && hasEnd;
}

int main() { 
    try { 
        YAML::Node config = YAML::LoadFile("dag.yaml"); 
 
        std::vector<Job> jobs; 
        bool errorOccurred = false; // Флаг для отслеживания ошибок 
 
        for (YAML::const_iterator it = config["jobs"].begin(); it != config["jobs"].end(); ++it) { 
            Job job; 
 
            job.id = (*it)["id"].as<std::string>(); 
            job.command = (*it)["command"].as<std::string>(); 
 
            if ((*it)["depends_on"]) { 
                for (size_t i = 0; i < (*it)["depends_on"].size(); i++) { 
                    job.depends_on.push_back((*it)["depends_on"][i].as<std::string>()); 
                } 
            } 
 
            job.onError = [&errorOccurred, id = job.id](const Job&) { 
                std::cerr << "Error executing job " << id << std::endl; 
                errorOccurred = true; 
            }; 
 
            job.execute = [id = job.id, &job, &errorOccurred]() -> bool { 
                std::cout << "Executing job " << id << std::endl; 
                if (id == "errorJob") { 
                    job.onError(job); 
                    return false; 
                } 
                return true; 
            }; 
 
            jobs.push_back(std::move(job)); 
        } 
 
        // Проверка на зацикливание 
        if (checkForCycles(jobs)) { 
            std::cerr << "Detected cycles in job dependencies. Aborting..." << std::endl; 
            return -1; 
        } 
 
        // Проверка на наличие начальных и конечных задач 
        if (!checkStartAndEndJobs(jobs)) { 
            std::cerr << "Could not determine start/end jobs. Please check job dependencies." << std::endl; 
            return -1; 
        } 
 
        // Выполнение работы 
        for (const auto& job : jobs) { 
            if (!job.execute() || errorOccurred) { 
                std::cerr << "Aborting due to job failure or error occurrence." << std::endl; 
                return -1; 
            } 
        } 
 
        std::cout << "All jobs executed successfully." << std::endl; 
    } catch (const YAML::BadFile& e) { 
        std::cerr << "Failed to load YAML configuration: " << e.what() << std::endl; 
        return -1; 
    } catch (const std::exception& e) { 
        std::cerr << "An error occurred: " << e.what() << std::endl; 
        return -1; 
    } 
 
    return 0; 
}

