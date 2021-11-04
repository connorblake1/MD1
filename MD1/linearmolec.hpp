//
//  linearmolec.hpp
//  MD1
//
//  Created by Connor Blake on 9/16/21.
//  Copyright © 2021 Connor Blake. All rights reserved.
//

#ifndef linearmolec_hpp
#define linearmolec_hpp

#include <stdio.h>
#include <math.h>
#include "molec.hpp"
#include "PVector.hpp"
#include <SFML/Graphics.hpp>
using namespace phys;
namespace chem {

class linearmolec : public molec {
private:
    PVector s;
    float w, l, i, theta, omega, tq;
    sf::RectangleShape rod;
public:
    linearmolec() {}
    linearmolec(PVector * inr, PVector * inv, PVector * ina, PVector * ins, float win, float lin, float qin, float min, float omegan) {
        std::cout << "rod constructed" << std::endl;
        r = PVector((*inr).getX(),(*inr).getY());
        v = PVector((*inv).getX(),(*inv).getY());
        f = PVector((*ina).getX(),(*ina).getY());
        s = PVector((*ins).getX(),(*ins).getY());
        s.printIt();
        this->theta = atan2(s.getY(),s.getX());
        this->omega = omegan;
        this->w=win;
        this->l=lin;
        this->q=qin;
        this->m=min;
        this->i = m*(l*l)/12;
        rod.setPosition((*inr).getX(), (*inr).getY());
        rod.setSize(sf::Vector2f(l,w));
        rod.setOrigin(l/2,w/2);
        rod.setRotation(theta*180/M_PI);
        rod.setFillColor(sf::Color::White);}
    float getW() {return this->w;}
    float getL() {return this->l;}
    float getI() {return this->i;}
    float getTQ() {return this->tq;}
    float getTheta() {return this->theta;}
    float getOmega() {return this->omega;}
    float getKE() {
        return .5*(m*v.magsq()+i*omega*omega);}
    PVector *getS() {return &s;}
    void modTQ(float intq) {tq+=intq;}
    void resetA() {
        f = PVector(0,0);
        tq = 0;}
    void disp(sf::RenderWindow * wind);
    void leapfrogA(float timestep);
    void leapfrogB(float timestep);
};
}
#endif /* linearmolec_hpp */
