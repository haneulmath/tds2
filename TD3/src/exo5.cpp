#include <iostream>
#include <vector>

void counting_sort(std::vector<int> &vec, int const max) {
    std::vector<int> count(max + 1, 0);

    for (int num : vec) {
        count[num]++;
    }

    int index = 0;
    for (int i = 0; i <= max; i++) {
        while (count[i] > 0) {
            vec[index++] = i;
            count[i]--;
        }
    }
}

int main() {
    std::vector<int> vec = {4, 2, 2, 8, 3, 3, 1};
    int max = 8; 

    std::cout << "Avant le tri : ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    counting_sort(vec, max);

    std::cout << "Après le tri : ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}