#include <iostream>
namespace it {
    template<class T>
    class iterator {
        T* it;
    public:
        using iterator_category = std::random_access_iterator_tag;

        iterator() {
            it = nullptr;
        }

        iterator(T* iter) {
            it = iter;
        }

        iterator(const iterator<T>& other) {
            this->it = other->it;
        }

        iterator<T>& operator++() {
            it++;
            return it;
        }

        iterator<T>& operator--() {
            it--;
            return it;
        }

        iterator<T>& operator++(int) {
            it++;
            return it;
        }

        iterator<T>& operator--(int) {
            it--;
            return it;
        }

        iterator<T>& operator->() {
            return it;
        }

        bool operator<(iterator other) {
            return this->it < other->it;
        }

        bool operator>(iterator other) {
            return this->it > other->it;
        }

        bool operator!=(iterator other) {
            return this->it != other->it;
        }

        bool operator==(iterator other) {
            return this->it == other->it;
        }

        iterator& operator=(iterator& other) {
            it = other->it;
            return *this;
        }

        iterator& operator=(iterator* other) {
            it = other->it;
            return *this;
        }

        iterator operator+(int n) {
            it += n;
            return *this;
        }

        iterator operator-(int n) {
            it -= n;
            return *this;
        }

        size_t operator-(iterator n) {
            return it - n.it;
        }

        iterator<T> operator*() {
            return *it;
        }

        iterator<T>& get_pointer() const {
            return it;
        }
    };

    template<class T>
    class const_iterator {
        const T* it;
    public:
        using iterator_category = std::random_access_iterator_tag;

        const_iterator() {
            it = nullptr;
        }

        const_iterator(T* iterator) {
            it = iterator;
        }

        const_iterator(const const_iterator<T>& other) {
            this->it = other->it;
        }

        const T* operator->() {
            return it;
        }

        bool operator!=(const const_iterator& other) {
            return it != other->it;
        }

        const_iterator& operator=(const const_iterator& other) {
            it = other->it;
            return *this;
        }

        const T& operator*() {
            return *it;
        }
        const T* get_pointer() {
            return it;
        }
    };

    template<class T>
    class reverse_iterator {
    protected:
        T* it;
    public:
        using iterator_category = std::random_access_iterator_tag;

        reverse_iterator() {
            it = nullptr;
        }

        explicit reverse_iterator(T* iter) {
            it = iter;
        }

        explicit reverse_iterator(const iterator<T>& other) {
            this->it = other->it;
        }

        reverse_iterator<T>& operator++() {
            it--;
            return *this;
        }

        reverse_iterator<T>& operator--() {
            it++;
            return *this;
        }

        reverse_iterator<T>& operator++(int) {
            it--;
            return *this;
        }

        reverse_iterator<T>& operator--(int) {
            it++;
            return *this;
        }

        T* operator->() {
            return it;
        }

        bool operator!=(reverse_iterator other) {
            return this->it != other->it;
        }

        bool operator==(reverse_iterator other) {
            return this->it == other->it;
        }

        reverse_iterator& operator=(const reverse_iterator& other) {
            it = other.it;
            return *this;
        }

        reverse_iterator& operator=(const reverse_iterator* other) {
            it = other->it;
            return *this;
        }

        reverse_iterator operator+(int n) {
            it += n;
            return *this;
        }

        reverse_iterator operator-(int n) {
            it -= n;
            return *this;
        }

        size_t operator-(reverse_iterator n) {
            return it - n.it;
        }

        T& operator*() {
            return *it;
        }

        T* get_pointer() const {
            return it;
        }
    };
}
