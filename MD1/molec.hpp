//
//  molec.hpp
//  MD1
//
//  Created by Connor Blake on 9/16/21.
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
protected:
    PVector r; //center of mass
    PVector v;
    PVector f;
    float rad, q, m;
public:
    molec() {}
    molec(PVector * inr, PVector * inv, PVector * ina, float radin, float qin, float min) {
        r = PVector((*inr).getX(),(*inr).getY());
        v = PVector((*inv).getX(),(*inv).getY());
        f = PVector((*ina).getX(),(*ina).getY());
        this->rad=radin;
        this->q=qin;
        this->m=min;}
    float getX() {return this->r.getX();}
    float getY() {return this->r.getY();}
    float getVX() {return this->v.getX();}
    float getVY() {return this->v.getY();}
    float getFX() {return this->f.getX();}
    float getFY() {return this->f.getY();}
    float getRad() {return this->rad;}
    float getQ() {return this->q;}
    float getM() {return this->m;}
    virtual float getKE()= 0;
    PVector *getR() {return &r;}
    PVector *getV() {return &v;}
    PVector *getF() {return &f;}
    void setR(PVector * inr) {r = *inr;}
    void setV(PVector * inv) {v = *inv;}
    void setF(PVector * inf) {f = *inf;}
    void setX(float inx) {r.setX(inx);}
    void setY(float iny) {r.setY(iny);}
    void setZ(float inz) {r.setZ(inz);}
    void resetA() {f = PVector(0,0);}
    virtual void disp(sf::RenderWindow * wind) = 0;
    virtual void leapfrogA(float timestep) = 0;
    virtual void leapfrogB(float timestep) = 0;
};
}


#endif /* molec_hpp */
