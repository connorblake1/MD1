//
//  molec.cpp
//  MD1
//
//  Created by Connor Blake on 8/21/21.
//  Copyright © 2021 Connor Blake. All rights reserved.
//

#include "pointmolec.hpp"
namespace chem {
//void molec::scaleMag(float scale) {
//    this->v = PVector(this->v.getX()*scale,this->v.getY()*scale);}
//void scaleMag(float scale);
void pointmolec::disp(sf::RenderWindow * wind) {
    //std::cout << "pointmolec print" << std::endl;
    c.setPosition(r.getX(), r.getY());
    (*wind).draw(c);
}
void pointmolec::leapfrogA(float timestep) {
    v.add(PVector::scalm(&f,timestep/2/m));
    r.add(PVector::scalm(&v, timestep));
}
void pointmolec::leapfrogB(float timestep) {
//    std::cout << "the fn" << std::endl;
//    f.printIt();
    v.add(PVector::scalm(&f, timestep/2/m));
}

}
