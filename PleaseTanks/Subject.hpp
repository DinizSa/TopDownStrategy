//
//  ISubject.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 18/09/2023.
//

#pragma once
#include <iostream>
#include <set>
#import "Observer.hpp"

template <class T>
class Subject {
    T value;
    std::set<Observer<T>*> observers;
    
public:
    virtual ~Subject(){};
    void operator=(T newValue){
        value = newValue;
        notify();
    }
    T operator()() const{
        return value;
    }
//    const T& get() const;
//    void set(T val);
    void subscribe(Observer<T>* observer);
    void unsubscribe(Observer<T>* observer);
    void notify();
};
