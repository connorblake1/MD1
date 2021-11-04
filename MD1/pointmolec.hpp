//
//  molec.hpp
//  MD1
//
//  Created by Connor Blake on 8/21/21.
//  Copyright © 2021 Connor Blake. All rights reserved.
//

#ifndef pointmolec_hpp
#define pointmolec_hpp

#include <stdio.h>
#include "molec.hpp"
#include "PVector.hpp"
#include <SFML/Graphics.hpp>
using namespace phys;
namespace chem {
class pointmolec : public molec {
private:
    sf::CircleShape c;
public:
    pointmolec() {}
    pointmolec(PVector * inr, PVector * inv, PVector * ina, float radin, float qin, float min) {
        std::cout << "point constructed" << std::endl;
        r = PVector((*inr).getX(),(*inr).getY());
        v = PVector((*inv).getX(),(*inv).getY());
        f = PVector((*ina).getX(),(*ina).getY());
        this->rad=radin;
        this->q=qin;
        this->m=min;
        c.setPosition((*inr).getX(), (*inr).getY());
        c.setOrigin(rad,rad);
        c.setRadius(rad);
        c.setFillColor(sf::Color::White);}
    void disp(sf::RenderWindow * wind);
    float getKE() {return .5*m*v.magsq();}
    void leapfrogA(float timestep);
    void leapfrogB(float timestep);
};
}
#endif /* molec_hpp */
