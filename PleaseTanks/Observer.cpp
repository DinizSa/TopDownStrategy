//
//  Subject.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 18/09/2023.
//

#include <iostream>
#include "Observer.hpp"

template <class T> void Observer<T>::update(T newValue) {
    std::cout << "Observer update: " << newValue << std::endl;
}

template class Observer<float>;
