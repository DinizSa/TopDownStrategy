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

#import "Observer.hpp"

template <class T>
class Subject {
    T value = T();
    std::unordered_map<const Observer*, std::function<void(T)>> observers;
    
public:
    virtual ~Subject(){};
    void operator=(T newValue){
        value = newValue;
    }
    T operator()() const{
        return value;
    }

    void subscribe(const Observer* observer, std::function<void(T)> callback);
    void unsubscribe(const Observer*);
    void notify();
};
