#ifndef CUSTOMQUEUE_H
#define CUSTOMQUEUE_H

#include <vector>
#include <functional> // for std::greater

template <typename T>
class CustomQueue {
private:
    std::vector<T> elements;

public:
    // Custom implementation of lower_bound for maintaining sorted order
    template<typename ForwardIt, typename Compare>
    ForwardIt custom_lower_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp) {
    while (first != last) {
        auto mid = std::next(first, std::distance(first, last) / 2);
        if (comp(*mid, value)) {
            first = ++mid;
        } else {
            last = mid;
        }
    }
    return first;
}

    // Pushes an element into the queue while maintaining order
    void push(const T& element) {
        auto it = custom_lower_bound(elements.begin(), elements.end(), element, std::greater<T>());
        elements.insert(it, element);
    }

    // Removes the front element from the queue
    void pop() {
        if (!isEmpty()) {
            elements.erase(elements.begin());
        }
    }

    // Returns the front element
    T& front() {
        return elements.front();
    }

    // Checks if the queue is empty
    bool isEmpty() const {
        return elements.empty();
    }
};

#endif // CUSTOMQUEUE_H
