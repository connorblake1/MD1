//
//  linearmolec.cpp
//  MD1
//
//  Created by Connor Blake on 9/16/21.
//  Copyright © 2021 Connor Blake. All rights reserved.
//

#include "linearmolec.hpp"
namespace chem {
void linearmolec::disp(sf::RenderWindow * wind) {
    //std::cout << "linearmolec print " << omega << " " << theta << std::endl;
    rod.setPosition(r.getX(), r.getY());
    rod.setRotation(theta*180/M_PI);
    (*wind).draw(rod);
}
void linearmolec::leapfrogA(float timestep) {
    v.add(PVector::scalm(&f,timestep/2/m));
    r.add(PVector::scalm(&v, timestep));
    omega += tq*timestep/2/i;
    theta += omega*timestep;
}
void linearmolec::leapfrogB(float timestep) {
    v.add(PVector::scalm(&f, timestep/2/m));
    omega += tq*timestep/2/i;
}
}
