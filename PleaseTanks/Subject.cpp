//
//  Subject.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 18/09/2023.
//

#include <SFML/Graphics.hpp>

#include "Subject.hpp"

template <class T> void Subject<T>::subscribe(const Observer* observer, std::function<void(T)> callback) {
    std::cout << "subscribe" << std::endl;
    observers.insert_or_assign(observer, callback);
//    std::cout << "number of subscribers: " << observers.size() << std::endl;
}
template <class T> void Subject<T>::unsubscribe(const Observer* observer) {
    std::cout << "unsubscribe" << std::endl;
    observers.erase(observer);
//    std::cout << "number of subscribers: " << observers.size() << std::endl;
}
template <class T> void Subject<T>::notify() {
//    std::cout << "notify" << std::endl;
    for (const auto& s : observers) {
        s.second(value);
    }
}

template class Subject<float>;
template class Subject<sf::Vector2f>;
