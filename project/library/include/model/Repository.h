#ifndef HOTEL_REPOSITORY_H
#define HOTEL_REPOSITORY_H

#include <functional>
#include <vector>
#include <string>

template<class T>
class Repository {
private:
    std::vector<T> elements;

public:
    Repository();
    virtual ~Repository();

    T get(unsigned int id) const;
    void add(T element);
    T find(const std::function<bool(T)> &predicate) const;
    std::vector<T> findAll(const std::function<bool(T)> &predicate) const;
    std::string report() const; // Wypisuje informacje każdego elemntu w wektorze
    int size() const;
    void remove(T element);
};


#endif //HOTEL_REPOSITORY_H
