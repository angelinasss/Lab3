template<typename T_first, typename T_second>
struct pair {
    T_first first;
    T_second second;

    pair() {
        first = T_first();
        second = T_second();
    }

    pair(const T_first& first, const T_second& second) {
        this->first = first;
        this->second = second;
    }

    void swap(pair<T_first, T_second>&);

    pair<T_first, T_second>& operator=(const pair<T_first, T_second>&);
};

    template<typename T_first, typename T_second>
    void pair<T_first, T_second>::swap(pair<T_first, T_second>& other) {
       T_first swapValueF = first;
       first = other.first;
       other.first = swapValueF;
       T_second swapValueS = second;
       second = other.second;
       other.second = swapValueS;
    }

    template<typename T_first, typename T_second>
    pair<T_first, T_second>& pair<T_first, T_second>::operator=(const pair<T_first, T_second>& other) {
       first = other.first;
       second = other.second;
       return *this;
    }

    template<typename T_first, typename T_second>
    pair<T_first, T_second> make_pair(const T_first& first, const T_second& second) {
        return pair<T_first, T_second>(first, second);
    }
