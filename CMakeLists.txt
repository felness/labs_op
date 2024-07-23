cmake_minimum_required(VERSION 3.16.3)

# Найти пакет Threads, предоставляемый CMake
find_package(Threads REQUIRED)

add_executable(control_node control_node.cpp)
add_executable(calculation_node calculation_node.cpp)

# Ссылка на библиотеку ZeroMQ
target_link_libraries(control_node PRIVATE libzmq.so Threads::Threads)
target_link_libraries(calculation_node PRIVATE libzmq.so Threads::Threads)
