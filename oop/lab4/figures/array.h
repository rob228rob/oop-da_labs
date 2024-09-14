#include <iostream>
#include <memory>

namespace lab4 {

template<class T>
class Array final {
private:
    std::shared_ptr<T[]> data;
    size_t _capacity, _size;
public:
    Array() : data(nullptr), _size(0), _capacity(0) { }

    Array(size_t n) : _size(n), _capacity(n) {
        data = std::shared_ptr<T[]>(new T[n], std::default_delete<T[]>());  // Используем new
    }

    Array(const Array<T>& other) {
        _size = other._size;
        _capacity = other._capacity;
        data = std::shared_ptr<T[]>(new T[other._size], std::default_delete<T[]>());
        for (size_t i = 0; i < _size; i++) {
            data[i] = other.data[i];
        }
    }

    Array(Array<T>&& other) noexcept {
        _size = other._size;
        _capacity = other._capacity;
        data = std::move(other.data);
        other._size = 0;
        other._capacity = 0;
    }

    Array& operator=(const Array<T>& other) {
        if (this != &other) {
            _size = other._size;
            _capacity = other._capacity;
            data = std::shared_ptr<T[]>(new T[other._size], std::default_delete<T[]>());
            for (size_t i = 0; i < _size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    Array& operator=(Array<T>&& other) noexcept {
        if (this != &other) {
            _size = other._size;
            _capacity = other._capacity;
            data = std::move(other.data);
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }

    T& operator[](size_t ind) {
        return data[ind];
    }

    const T& operator[](size_t ind) const {
        return data[ind];
    }

    void erase(size_t ind) {
        if (ind < _size) {
            for (size_t i = ind + 1; i < size(); i++) {
                data[i - 1] = data[i];
            }
            resize(size() - 1);
        }
    }

    size_t size() const {
        return _size;
    }

    void reserve(size_t n) {
        if (n > _capacity) {
            _capacity = n;
            auto oldData = std::move(data);
            data = std::shared_ptr<T[]>(new T[_capacity], std::default_delete<T[]>());
            for (size_t i = 0; i < _size; i++) {
                data[i] = oldData[i];
            }
        }
    }

    void resize(size_t n) {
        if (n > _capacity) {
            reserve(n);
        }
        _size = n;
    }

    void pushBack(const T& a) {
        resize(size() + 1);
        data[size() - 1] = a;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Array& array) {
        for (size_t i = 0; i < array.size(); i++) {
            stream << array.data[i] << " ";
        }
        return stream;
    }
};
}
