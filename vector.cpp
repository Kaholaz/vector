#include "vector.hpp"

#include <cassert>
#include <iostream>

template <typename T> vector<T>::vector() : m_cap(8), m_size(0), array(new T[m_cap]) { };

template <typename T> vector<T>::~vector() = default;

template <typename T> int vector<T>::size() const {
    return m_size;
}

template <typename T> void vector<T>::push(const T &elm) {
    if (m_cap == m_size) {
        m_cap <<= 2;
        std::unique_ptr<T[]> new_array(new T[m_cap]);
        for (size_t i = 0; i < m_size; ++i) {
            new_array.get()[i] = array.get()[i];
        }

        array = std::move(new_array);
    }

    array.get()[m_size] = elm;
    ++m_size;
}

template <typename T> const std::optional<T* const> vector<T>::get(int index) const {
    if (index >= m_size) return std::nullopt;
    
    return &(array.get()[index]);
};

template <typename T> const std::optional<T> vector<T>::pop() {
    if (m_size == 0) return std::nullopt;

    --m_size;
    return array.get()[m_size];
}

int main() {
    vector<int> v1;
    assert(v1.size() == 0);

    v1.push(5);
    assert(v1.size() == 1);
    v1.push(10);
    assert(v1.size() == 2);

    assert(*v1.get(0).value() == 5);
    assert(*v1.get(1).value() == 10);

    auto popped = v1.pop();
    assert(popped.value() == 10);
    assert(v1.size() == 1);

    vector<int> v2;
    for (size_t i = 0; i < 17; ++i) {
        v2.push(i);
    }
    assert(*v2.get(16).value() == 16);

    
    vector<int> empty;
    assert(!empty.pop().has_value());
    return 0;
}