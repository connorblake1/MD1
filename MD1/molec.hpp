//
//  molec.hpp
//  MD1
//
//  Created by Connor Blake on 8/21/21.
//  Copyright © 2021 Connor Blake. All rights reserved.
//

#ifndef molec_hpp
#define molec_hpp

#include <stdio.h>
#include "PVector.hpp"
#include <SFML/Graphics.hpp>
using namespace phys;
namespace chem {

class molec {
private:
    PVector r; //center of mass
    PVector v;
    PVector f;
    float rad, q, m;
    sf::CircleShape c;
    sf::RectangleShape tail;
public:
    molec() {}
    molec(PVector * inr, PVector * inv, PVector * ina, float radin, float qin, float min) {
        r = PVector((*inr).getX(),(*inr).getY());
        v = PVector((*inv).getX(),(*inv).getY());
        f = PVector((*ina).getX(),(*ina).getY());
        this->rad=radin;
        this->q=qin;
        this->m=min;
        c.setPosition((*inr).getX(), (*inr).getY());
        c.setRadius(rad);
        c.setFillColor(sf::Color::White);}
    float getX();
    float getY();
    float getVX();
    float getVY();
    float getFX();
    float getFY();
    float getRad();
    float getQ();
    float getM();
    PVector *getR();
    PVector *getV();
    PVector *getF();
    void setR(PVector * inr);
    void setV(PVector * inv);
    void setX(float inx);
    void setY(float iny);
    void setZ(float inz);
    //void scaleMag(float scale);
    void resetA();
    void disp(sf::RenderWindow * wind);
};
}
#endif /* molec_hpp */
