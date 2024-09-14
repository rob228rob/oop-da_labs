#pragma once

#include <iostream>
#include <memory>

namespace lab5 {

template<class T, class Allocator = std::allocator<T> >
class Vector {
public:
    class Iterator {
    private:
        Vector<T, Allocator>& vector;
        size_t ind;
        friend class Vector<T, Allocator>;
    public:
        using difference_type = int;
        using value_type = typename Vector<T, Allocator>::value_type;
        using reference = typename Vector<T, Allocator>::value_type&;
        using pointer = typename Vector<T, Allocator>::value_type*;
        using iterator_category = std::forward_iterator_tag;

        Iterator(Vector &v, size_t i) : vector(v), ind(i) { }

        Iterator& operator++() {
            ++ind;
            return *this;
        }

        Iterator& operator--() {
            --ind;
            return *this;
        }

        reference operator*() {
            return vector[ind];
        }

        pointer operator->() {
            return &vector[ind];
        }

        bool operator!=(const Iterator& other) const {
            if (ind != other.ind) return true;
            if (&vector != &(other.vector)) return true;
            return false;
        }

        bool operator==(const Iterator& other) const {
            if (ind != other.ind) return false;
            if (&vector != &(other.vector)) return false;
            return true;
        }
    };

    class ConstIterator {
    private:
        Vector<T, Allocator>& vector;
        size_t ind;
        friend class Vector<T, Allocator>;
    public:
        using difference_type = int ;
        using value_type = typename Vector<T, Allocator>::value_type;
        using reference = const typename Vector<T, Allocator>::value_type& ;
        using pointer = const typename Vector<T, Allocator>::value_type*;
        using iterator_category = std::forward_iterator_tag;

        ConstIterator(Vector &v, size_t i) : vector(v), ind(i) { }

        ConstIterator& operator++() {
            ++ind;
            return *this;
        }

        ConstIterator& operator--() {
            --ind;
            return *this;
        }

        reference operator*() {
            return vector[ind];
        }

        pointer operator->() {
            return &vector[ind];
        }

        bool operator!=(const ConstIterator& other) const {
            if (ind != other.ind) return true;
            if (&vector != &(other.vector)) return true;
            return false;
        }

        bool operator==(const ConstIterator& other) const {
            if (ind != other.ind) return false;
            if (&vector != &(other.vector)) return false;
            return true;
        }
    };

private:
    Allocator alloc;
    T* data;
    size_t _capacity, _size;
public:
    using value_type = T;

    Vector() : data(nullptr), _size(0), _capacity(0) { }

    Vector(size_t n) : _size(n), _capacity(n) {
        data = alloc.allocate(n);
    }

    Vector(const std::initializer_list<T> &list) {
        _size = list.size();
        data = alloc.allocate(_size);
        _capacity = _size;
        std::copy(list.begin(), list.end(), begin());
    }

    Vector(const Vector<T>& other) {
        _size = other._size;
        _capacity = other._capacity;
        data = alloc.allocate(other.size());
        for (size_t i = 0; i < _size; i++) {
            data[i] = other.data[i];
        }
    }

    Vector(Vector<T>&& other) noexcept {
        _size = other._size;
        _capacity = other._capacity;
        data = other.data;
        other._size = 0;
        other._capacity = 0;
        other.data = nullptr;
    }

    Vector operator=(const Vector<T>& other) {
        _size = other._size;
        _capacity = other._capacity;
        data = alloc.allocate(other.size());
        for (size_t i = 0; i < _size; i++) {
            data[i] = other.data[i];
        }
        return *this;
    }

    Vector operator=(Vector<T>&& other) noexcept {
        _size = other._size;
        _capacity = other._capacity;
        data = other.data;
        other._size = 0;
        other._capacity = 0;
        other.data = nullptr;
        return *this;
    }

    T & operator[] (size_t ind) {
        return data[ind];
    }

    const T & operator[] (size_t ind) const {
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
            size_t oldCapacity = _capacity;
            _capacity = n;
            T* oldData = data;
            data = alloc.allocate(_capacity);
            for (size_t i = 0; i < _capacity; i++) {
                new (&data[i]) T();
            }
            for (size_t i = 0; i < size(); i++) {
                data[i] = oldData[i];
            }
        }
    }

    void resize(size_t n) {
        if (n > _capacity) {
            size_t newCapacity = (_capacity == 0 ? 1 : _capacity);
            while (n > newCapacity) {
                newCapacity *= 2;
            }
            reserve(newCapacity);
        }
        _size = n;
    }

    void pushBack(const T &a) {
        resize(size() + 1);
        data[size() - 1] = a;
    }

    friend std::ostream& operator<<(std::ostream &stream, const Vector &vector) {
        for (size_t i = 0; i < vector.size(); i++) {
            stream << vector.data[i] << " ";
        }
        return stream;
    }

    // Iterators

    Iterator begin() {
        return Iterator(*this, 0);
    }

    Iterator end() {
        return Iterator(*this, _size);
    }

    Iterator cbegin() {
        return ConstIterator(*this, 0);
    }

    Iterator cend() {
        return ConstIterator(*this, _size);
    }
};

}
