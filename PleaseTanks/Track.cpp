//
//  Track.cpp
//  PleaseTanks
//
//  Created by Diniz Sá on 14/09/2023.
//

#include "Track.hpp"

Track::Track(sf::Vector2<float> size, sf::Vector2<float> deltaCenter) : Drawable(size, deltaCenter, "/Users/Shared/merda/PleaseTanks/images/Track_1_A.png") {
    Drawable::rect.setSize(size);
    Drawable::rect.setOrigin({size.x/2, size.y/2});
}
