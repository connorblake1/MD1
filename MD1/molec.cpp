//
//  molec.cpp
//  MD1
//
//  Created by Connor Blake on 8/21/21.
//  Copyright © 2021 Connor Blake. All rights reserved.
//

#include "molec.hpp"
namespace chem {
//void molec::scaleMag(float scale) {
//    this->v = PVector(this->v.getX()*scale,this->v.getY()*scale);}
float molec::getX() {return this->r.getX();}
float molec::getY() {return this->r.getY();}
float molec::getVX() {return this->v.getX();}
float molec::getVY() {return this->v.getY();}
float molec::getFX() {return this->f.getX();}
float molec::getFY() {return this->f.getY();}
float molec::getRad() {return this->rad;}
float molec::getQ() {return this->q;}
float molec::getM() {return this->m;}
PVector *molec::getR() {return &r;}
PVector *molec::getV() {return &v;}
PVector *molec::getF() {return &f;}
void molec::setR(PVector * inr) {r = *inr;}
void molec::setV(PVector * inv) {v = *inv;}
void molec::setX(float inx) {r.setX(inx);}
void molec::setY(float iny) {r.setY(iny);}
void molec::setZ(float inz) {r.setZ(inz);}
//void scaleMag(float scale);
void molec::resetA() {f = PVector(0,0);}
void molec::disp(sf::RenderWindow * wind) {
    c.setPosition(r.getX(), r.getY());
    tail.setPosition(r.getX(), r.getY());
    (*wind).draw(c);
    //(*wind).draw(tail);
}

}
