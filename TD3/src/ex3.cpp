#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "ScopedTimer.hpp"

// Déclarations des fonctions de tri
void bubble_sort(std::vector<int> &vec);
void quick_sort(std::vector<int> &vec);

// Implémentation de quick_sort pour les entiers
size_t quick_sort_partition(std::vector<int> &vec, size_t left, size_t right, size_t const pivot) {
    int pivotValue = vec[pivot];
    std::swap(vec[pivot], vec[right]);
    size_t storeIndex = left;

    for (size_t i = left; i < right; i++) {
        if (vec[i] < pivotValue) {
            std::swap(vec[i], vec[storeIndex]);
            storeIndex++;
        }
    }
    std::swap(vec[storeIndex], vec[right]);
    return storeIndex;
}

void quick_sort(std::vector<int> &vec, size_t const left, size_t const right) {
    if (left < right) {
        size_t pivot = left + std::rand() % (right - left + 1);
        size_t newPivot = quick_sort_partition(vec, left, right, pivot);

        if (newPivot > 0) quick_sort(vec, left, newPivot - 1);
        quick_sort(vec, newPivot + 1, right);
    }
}

void quick_sort(std::vector<int> &vec) {
    quick_sort(vec, 0, vec.size() - 1);
}

// Implémentation de bubble_sort pour les entiers
void bubble_sort(std::vector<int> &vec) {
    bool swapped;
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        swapped = false;
        for (size_t j = 0; j < vec.size() - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void print_vector(const std::vector<int>& vec) {
    for (int v : vec) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::srand(std::time(nullptr));
    std::vector<int> vec(1000);
    for (int &v : vec) {
        v = std::rand() % 1000;
    }

    std::vector<int> vec_copy = vec;

    std::cout << "Original vector:" << std::endl;
    print_vector(vec);

    {
        ScopedTimer timer("Bubble Sort");
        bubble_sort(vec);
    }

    {
        ScopedTimer timer("Quick Sort");
        quick_sort(vec_copy);
    }

    return 0;
}
