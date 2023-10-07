//
//  Health.hpp
//  PleaseTanks
//
//  Created by Diniz Sá on 26/09/2023.
//

#pragma once

class Health {
protected:
    float maxHealth, currentHealth, armour;
    bool alive = true;
public:
    Health(float maxHealth, float armour);
    virtual ~Health(){};
    virtual float receiveDamage(float damage, float armourPenetration);
    virtual float getCurrentHealth() const;
    virtual float getMaxHealth() const;
    virtual float getArmour() const;
    virtual float getHealthRacio() const;
    virtual bool isAlive() const;
};
