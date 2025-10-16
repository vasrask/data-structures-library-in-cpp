#ifndef CUSTOMALGORITHM_H
#define CUSTOMALGORITHM_H

#include <vector>

template <typename T>
class CustomAlgorithm {
public:
    static void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

    //Bubble Sort Algorithm
    static void sort(std::vector<T>& arr, bool (*compare)(const T&, const T&)) {
        int n = arr.size();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (compare(arr[j], arr[j + 1])) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
};

#endif // CUSTOMALGORITHM_H
