//
//  Subject.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 18/09/2023.
//

#include <SFML/Graphics.hpp>

#include "Subject.hpp"

template <class T> Subject<T>::Subject(T v) {
    value = v;
}
template <class T> void Subject<T>::subscribe(const Observer* observer, std::function<void(T)> callback) {
    observers.insert_or_assign(observer, callback);
}
template <class T> void Subject<T>::unsubscribe(const Observer* observer) {
    observers.erase(observer);
}
template <class T> void Subject<T>::notify() {
    for (const auto& s : observers) {
        s.second(value);
    }
}

template class Subject<float>;
template class Subject<sf::Vector2f>;
template class Subject<bool>;
template class Subject<int>;
