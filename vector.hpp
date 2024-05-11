#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <optional>
#include <functional>

template<typename T> class vector {
private:
    size_t m_cap;
    size_t m_size;
    std::unique_ptr<T[]> array;
public:
    vector();
    vector(const vector<T> &vec);
    ~vector();

    int size() const;
    void push(const T &elm);
    const std::optional<T* const> get(int index) const;
    const std::optional<T> pop();

    void for_each(std::function<void(const T&)> func) const;
    vector<T> map(std::function<T(const T&)> func) const;
};
#endif
