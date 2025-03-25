#include <iostream>
#include <vector>
#include <cstdlib> 

size_t quick_sort_partition(std::vector<float> &vec, size_t left, size_t right, size_t const pivot) {
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

void quick_sort(std::vector<float> &vec, size_t const left, size_t const right) {
    if (left < right) {
        size_t pivot = left + std::rand() % (right - left + 1);
        size_t newPivot = quick_sort_partition(vec, left, right, pivot);

        if (newPivot > 0) quick_sort(vec, left, newPivot - 1);
        quick_sort(vec, newPivot + 1, right);
    }
}

void quick_sort(std::vector<float> &vec) {
    quick_sort(vec, 0, vec.size() - 1);
}


int main() {
    std::vector<float> vec = {64, 34, 25, 12, 22, 11, 90};
    quick_sort(vec);
    for (float v : vec) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
    return 0;
}
