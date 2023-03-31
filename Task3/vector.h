#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include "iterator.cpp"

template<typename T>
class Vector : public it::iterator<T>, public it::const_iterator<T>, public it::reverse_iterator<T>
{
        T* arr;
        size_t size_;
        size_t capacity_;
    public:
        Vector();
        Vector(it::iterator<T>, it::iterator<T>);
        Vector(const Vector&);
        Vector(std::initializer_list<T>);
        ~Vector();
        [[nodiscard]] bool empty() const;
        [[nodiscard]] size_t size() const;
        [[nodiscard]] size_t capacity();
        void reserve(int);
        void resize(size_t, const T & = T());
        void push_back(const T&);
        template<class... Args>
        void emplace_back(Args&&...);
        template<class... Args>
        void emplace(it::iterator<T>, Args&&...);
        void pop_back();
        void erase(it::iterator<T>);
        void erase(it::iterator<T>, it::iterator<T>);
        void insert(it::iterator<T>, const T&);
        template<typename InputIterator>
        void insert(const it::iterator<T>&, InputIterator, InputIterator);
        T& front();
        T& back();
        void clear();
        void swap(Vector<T>&);
        T* data();
        [[nodiscard]] size_t max_size() const;
        void assign(size_t, const T&);
        template<typename InputIterator>
        void assign(InputIterator, InputIterator);
        it::iterator<T> begin() const;
        it::iterator<T> end() const;
        it::const_iterator<T> cbegin() const;
        it::const_iterator<T> cend() const;
        it::reverse_iterator<T> rbegin() const;
        it::reverse_iterator<T> rend() const;
        T& operator[](size_t);
        const T& operator[](size_t) const;
        Vector& operator=(const Vector&);
        T& at(size_t) const;
    };

template<typename T>
Vector<T>::Vector() {
    arr = reinterpret_cast<T*>(new int8_t[sizeof(T)]);
    capacity_ = 1;
    size_ = 0;
}

template<typename T>
Vector<T>::Vector(it::iterator<T> begin, it::iterator<T> end)
{
    size_ = 0;
    capacity_ = 0;
    auto it = begin;
    while (it != end) {
        push_back(*it);
        it++;
    }
}

template<typename T>
Vector<T>::Vector(const Vector& other) {
    if (this != &other) {
        try {
            arr = reinterpret_cast<T*>(new int8_t[other.capacity_ * sizeof(T)]);
            for (int i = 0; i < other.size_; ++i) {
                new (arr + i) T(other.arr[i]);
            }
            size_ = other.size_;
            capacity_ = other.capacity_;
        }
        catch (...) {
            throw;
        }
    }
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> new_vector) {
    size_ = 0;
    capacity_ = 0;
    reserve(new_vector.size());
    auto it = new_vector.begin();
    while (it != new_vector.end()) {
        push_back(*it);
        it++;
    }
}

template<typename T>
Vector<T>::~Vector() {
    for (int i = 0; i < size_; i++) {
        (arr + i)->~T();
    }
    delete[] reinterpret_cast<int8_t*>(arr);
}

template<typename T>
[[nodiscard]] bool Vector<T>::empty() const {
    return size_ == 0;
}

template<typename T>
[[nodiscard]] size_t Vector<T>::size() const {
    return size_;
}

template<typename T>
[[nodiscard]] size_t Vector<T>::capacity() {
    return capacity_;
}

template<typename T>
void Vector<T>::reserve(int n) {
    if (n <= capacity_) return;
    T* new_arr = reinterpret_cast<T*>(new int8_t[n * sizeof(T)]);
    size_t i = 0;
    try {
        for (; i < size_; ++i) {
            new (new_arr + i) T(arr[i]);
        }
    }
    catch (...) {
        for (size_t j = 0; j < i; ++j) {
            (new_arr + j)->~T();
        }
        delete[] reinterpret_cast<int8_t*>(new_arr);
        throw;
    }

        for (int i = 0; i < size_; ++i) {
            (arr + i)->~T();
        }
        delete[] reinterpret_cast<int8_t*>(arr);

    arr = new_arr;
    capacity_ = n;
}

template<typename T>
void Vector<T>::resize(size_t n, const T& value) {
    if (n > capacity_) reserve(capacity_ * 2);
    if (n < size_) {
        for (int i = n - 1; i < size_; ++i) {
            (arr + i)->~T();
        }
    }
    else if (n > size_) {
        try {
            for (int i = size_; i < n; ++i) {
                new (arr + i) T(value);
            }
        }
        catch (...) {
            Vector::clear();
            throw;
        }
    }
    size_ = n;
}

template<typename T>
void Vector<T>::push_back(const T& value) {
    if (size_ >= capacity_) {
        reserve(2 * capacity_);
    }
    new (arr + size_) T(value);
    size_++;
}

template<typename T>
template<typename... Args>
void Vector<T>::emplace_back(Args &&...args) {
    T newObj(args...);
    Vector::push_back(newObj);
}

template<typename T>
template<typename... Args>
void Vector<T>::emplace(it::iterator<T> pos, Args&&... args) {
    pos.get_pointer()->~T();
    new (pos.get_pointer()) T(args...);
}

template<typename T>
void Vector<T>::pop_back() {
    --size_;
    (arr + size_)->~T();
}

template<typename T>
void Vector<T>::erase(it::iterator<T> itErase) {
    size_t ind = 0;
    for (auto it = begin(); it != itErase && ind < size_; it++) {
        ind++;
    }
    itErase->~T();
    try {
        for (size_t i = ind + 1; i < size_; i++) {
            new (arr + i - 1) T(arr[i]);
            (arr + i)->~T();
        }
        size_--;
    }
    catch (...) {
        throw;
    }
}

template<typename T>
void Vector<T>::erase(it::iterator<T> begin, it::iterator<T> end) {
    size_t ind = 0;
    for (auto it = Vector::begin(); it != end; it++) {
        ind++;
    }
    size_t count = 0;
    for (auto it = begin; it != end; ++it) {
        it->~T();
        count++;
    }
    for (size_t i = ind; i < size_; i++) {
        new (arr + i - count) T(arr[i]);
        (arr + i)->~T();
    }
    size_ -= count;
}

template<typename T>
void Vector<T>::insert(it::iterator<T> position, const T& value) {
    it::iterator<T> it = Vector::begin();
    size_t ind = 0;
    while (it != position) {
        ind++;
        it++;
    }
    if (capacity_ <= size_ + 1)
        Vector::reserve(capacity_ * 2);
    it = Vector::begin();
    for (int i = 0; i < ind; ++i) {
        it++;
    }
    size_t i;
    try {
        for (i = size_; i > ind; --i) {
            new (&arr[i]) T(arr[i - 1]);
            (arr + i - 1)->~T();
        }
        new (&*it) T(value);
        size_++;
    }
    catch (...) {
        Vector::clear();
        throw;
    }
}

template<typename T>
template<typename InputIterator>
void Vector<T>::insert(const it::iterator<T>& position, InputIterator begin, InputIterator end) {
    auto other = begin;
    size_t count = 0;
    while (other != end) {
        other++;
        count++;
    }
    it::iterator<T> it = Vector::begin();
    size_t ind = 0;
    while (it != position) {
        ind++;
        it++;
    }
    if (size_ + count >= capacity_) Vector::reserve(capacity_ * 2);
    try {
        for (size_t i = size_ - 1 + count; i > ind; --i) {
            new (&arr[i]) T(arr[i - count]);
            (arr + i - count)->~T();
        }
        other = begin;
        for (size_t i = ind; other != end; ++i) {
            new (arr + i) T(*(other++));
        }
        size_ += count;
    }
    catch (...) {
        Vector::clear();
        throw;
    }
}

template<typename T>
T& Vector<T>::front() {
    return arr[0];
}

template<typename T>
T& Vector<T>::back() {
    return arr[size_ - 1];
}

template<typename T>
void Vector<T>::clear() {
    for (int i = 0; i < size_; ++i) {
        (arr + i)->~T();
    }
    size_ = 0;
    capacity_ = 1;
}

template<typename T>
void Vector<T>::swap(Vector<T>& other) {
    auto tmp = arr;
    arr = other.arr;
    other.arr = tmp;
    size_t tmpCapacity = capacity_;
    capacity_ = other.capacity_;
    other.capacity_ = tmpCapacity;
    size_t tmpSize = size_;
    size_ = other.size_;
    other.size_ = tmpSize;
}

template<typename T>
T* Vector<T>::data() {
    return &arr[0];
}

template<typename T>
[[nodiscard]] size_t Vector<T>::max_size() const {
    return ULLONG_MAX;
}

template<typename T>
void Vector<T>::assign(size_t count, const T& value) {
    clear();
    for (int i = 0; i < count; ++i) {
        push_back(value);
    }
}

template<typename T>
template<typename InputIterator>
void Vector<T>::assign(InputIterator _begin, InputIterator _end) {
    Vector::clear();
    auto it = _begin;
    while (it != _end) {
        Vector::push_back(*it++);
    }
}

template<typename T>
it::iterator<T> Vector<T>::begin() const {
    return it::iterator(arr);
}

template<typename T>
it::iterator<T> Vector<T>::end() const {
    return it::iterator(arr + size_);
}

template<typename T>
it::const_iterator<T> Vector<T>::cbegin() const {
    return it::const_iterator(arr);
}

template<typename T>
it::const_iterator<T> Vector<T>::cend() const {
    return it::const_iterator(arr + size_);
}

template<typename T>
it::reverse_iterator<T> Vector<T>::rbegin() const {
    return it::reverse_iterator<T>(arr + size_ - 1);
}

template<typename T>
it::reverse_iterator<T> Vector<T>::rend() const {
    return it::reverse_iterator<T>(arr - 1);
}

template<typename T>
T& Vector<T>::operator[](size_t ind) {
    return arr[ind];
}

template<typename T>
const T& Vector<T>::operator[](size_t ind) const {
    return arr[ind];
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        try {
            Vector::clear();
            Vector::reserve(other.capacity_);
            Vector::resize(other.size_);
            for (int i = 0; i < other.size_; ++i) {
                new (arr + i) T(other.arr[i]);
            }
        }
        catch (...) {
            Vector::clear();
            throw;
        }
    }
    return *this;
}

template<typename T>
T& Vector<T>::at(size_t ind) const {
    if (ind >= size_)
        throw std::out_of_range("index out of the range");
    return arr[ind];
}

#endif // VECTOR_H
