#include <vector>
#include <iostream>

int search(const std::vector<int>& arr, int value) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == value) {
            return mid;
        } else if (arr[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

int main() {
    std::vector<int> arr;
    int n, value;

    std::cout << "Nombre d'éléments dans le tableau: ";
    std::cin >> n;

    std::cout << "Eléments du tableau trié: ";
    for (int i = 0; i < n; ++i) {
        int element;
        std::cin >> element;
        arr.push_back(element);
    }

    std::cout << "Valeur à rechercher: ";
    std::cin >> value;

    int index = search(arr, value);

    if (index != -1) {
        std::cout << value << " se trouve à l'indice " << index << std::endl;
    } else {
        std::cout << value << " n'est pas présente dans le tableau." << std::endl;
    }

    return 0;
}
