//mathfunctions1.cpp

#include <cmath>
#include <algorithm>

extern "C" {
float Derivative(float A, float deltaX) {
    return (cos(A + deltaX) - cos(A)) / deltaX;
}

int* Sort(int* array, int size) {
    for (int i = 0; i < size-1; i++)   
        for (int j = 0; j < size-i-1; j++)  
            if (array[j] > array[j+1]) 
                std::swap(array[j], array[j+1]);
    return array;
}
}
