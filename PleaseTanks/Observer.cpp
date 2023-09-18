//
//  Subject.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 18/09/2023.
//

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Observer.hpp"

template <class T> void Observer<T>::update(T newValue) {
    std::cout << "Observer update with new value " << std::endl;
}

template class Observer<float>;
template class Observer<sf::Vector2<float>>;
