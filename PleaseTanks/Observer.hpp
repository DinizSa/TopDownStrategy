//
//  ISubject.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 18/09/2023.
//

#pragma once
//#import "IObserver.hpp"

template <typename T>
class Observer {
public:
    virtual ~Observer(){};
    void update(T newValue);
};
