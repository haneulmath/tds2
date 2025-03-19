#include <iostream>
#include <vector>

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

int main() {
    std::vector<int> vec = {64, 34, 25, 12, 22, 11, 90};
    bubble_sort(vec);
    for (int v : vec) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
    return 0;
}
