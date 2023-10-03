//
//  Subject.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 18/09/2023.
//

#pragma once
#include <iostream>
#include <set>
#include <unordered_map>

template <class T>
class Subject {
    T value = T();
    std::unordered_map<int, std::function<void(T)>> observers;
    static int counter;
public:
    Subject() = default;
    Subject(T v);
    virtual ~Subject(){};
    void operator=(T newValue){
        value = newValue;
    }
    T operator()() const{
        return value;
    }

    int subscribe(std::function<void(T)> callback);
    void unsubscribe(int);
    void notify();
};
