#include "array.h"

namespace lab3 {

void Array::setCapacity(size_t value) {
    data = reallocate(data, pSize, value);
    capacity = value;
}

Figure** Array::reallocate(Figure** oldData, size_t oldSize, size_t newSize) {
    Figure** data = new Figure* [newSize];
    for (size_t i = 0; i < std::min(oldSize, newSize); i++) {
        data[i] = oldData[i];
    }
    if (oldData != nullptr) {
        delete [] oldData;
    }
    return data;
}

Array::Array() : pSize(0), capacity(0), data(nullptr) { }

Array::Array(size_t n) : pSize(n), capacity(n) {
    data = reallocate(nullptr, 0, n);
}

Array::~Array() {
    delete [] data;
}

Array::Array(const Array& other) {
    data = reallocate(nullptr, 0, other.size());
    for (size_t i = 0; i < other.size(); i++) {
        data[i] = other.data[i];
    }
    pSize = other.size();
    capacity = other.capacity;
}


Array::Array(Array&& other) {
    data = other.data;
    pSize = other.size();
    capacity = other.capacity;
    other.data = nullptr;
}

Figure* & Array::operator[] (size_t ind) {
    return data[ind];
}

Figure* const & Array::operator[] (size_t ind) const {
    return data[ind];
}

size_t Array::size() const {
    return pSize;
}

void Array::resize(size_t newSize) {
    if (newSize > capacity) {
        setCapacity(newSize);
    }
    pSize = newSize;
}

void Array::pushBack(Figure* figure) {
    resize(pSize + 1);
    (*this)[pSize - 1] = figure;
}

void Array::erase(size_t ind) {
    for (size_t i = ind + 1; i < pSize; i++) {
        data[i - 1] = data[i];
    }
    if (ind < pSize) {
        pSize--;
    }
}

}