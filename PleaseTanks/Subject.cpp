//
//  Subject.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 18/09/2023.
//

#include <SFML/Graphics.hpp>

#include "Subject.hpp"

//template <class T> const T& Subject<T>::get() const {
//    return value;
//}
//template <class T> void Subject<T>::set(T val) {
//    value = val;
//    notify();
//}
template <class T> void Subject<T>::subscribe(Observer<T>* observer) {
    std::cout << "subscribe" << std::endl;
    observers.insert(observer);
}
template <class T> void Subject<T>::unsubscribe(Observer<T>* observer) {
    std::cout << "unsubscribe" << std::endl;
    observers.erase(observer);
}
template <class T> void Subject<T>::notify() {
    std::cout << "notify" << std::endl;
    for (Observer<T>* s : observers) {
        s->update(value);
    }
}

template class Subject<float>;
template class Subject<sf::Vector2<float>>;
