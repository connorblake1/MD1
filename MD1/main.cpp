
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "molec.hpp"
#include "linearmolec.hpp"
#include "pointmolec.hpp"
#include "PVector.hpp"
using namespace phys;
using namespace chem;
unsigned long t;
const float ts = .02;
const int WINX = 1000;
const int WINY = 800;
const float epsilon = 5000;
const float plusC = 10;
const float sigma = 35;
void initializePointMolecules(int num, pointmolec * m) {
    float scaleP = 200;
    float scaleV = 10;
    for (int i = 0; i < num; i++) {
        int usq =ceil(sqrt(num)+1);
        PVector * rin = new PVector(WINX/(usq)*(i%usq)+200,WINY/(usq)*(i/usq)+200);
        //(*rin).printIt();
        PVector * vin = PVector::rand2DScale(scaleV);
        //(*vin).printIt();
        PVector * ain = PVector::rand2DScale(0);
        //(*ain).printIt();
        m[i] = pointmolec(rin, vin, ain,10,1,1);
    }
}
void initializeLinearMolecules(int num, linearmolec * m) {
    float scaleP = 200;
    float scaleV = 10;
    for (int i = 0; i < num; i++) {
        int usq =ceil(sqrt(num)+1);
        PVector * rin = new PVector(WINX/(usq)*(i%usq)+10,WINY/(usq)*(i/usq)+10);
        //(*rin).printIt();
        PVector * vin = PVector::rand2DScale(scaleV);
        //(*vin).printIt();
        PVector * ain = PVector::rand2DScale(0);
        //(*ain).printIt();
        PVector * sin = PVector::rand2DScale(1);
        m[i] = linearmolec(rin, vin, ain, sin, 3, 120, 1, 1, .1);
    }
}
void ljpotforce(pointmolec * other1, pointmolec * other2) {
    float x1 = (*other1).getX();
    float x2 = (*other2).getX();
    float y1 = (*other1).getY();
    float y2 = (*other2).getY();
    float distX = WINX;
    float distY = WINY;
    int ix = -1;
    int iy = -1;
    for (int i = -1; i <= 1; i++) {
        float nDistY = abs(y1-y2+WINY*i);
        float nDistX = abs(x1-x2+WINX*i);
        if (nDistX < distX) {
            distX=nDistX;
            ix=i;}
        if (nDistY < distY) {
            distY=nDistY;
            iy=i;}}
    float angle = atan2(y1-y2+iy*WINY,x1-x2+ix*WINX);
    float n  = sqrt(distX*distX+distY*distY);
    //std::cout << n << std::endl;
    PVector * r = new PVector(cos(angle),sin(angle));
    if (n < pow(2,1/6)*sigma) {
        float fn =48*epsilon/sigma/sigma*(pow(sigma/(n+plusC),13)-.5*pow(sigma/(n+plusC),7));
        std::cout << "fn 2 " << fn << std::endl;
        r = PVector::scalm(r,fn);
        (*(*other1).getF()).add(r);
        (*(*other2).getF()).add(PVector::scalm(r,-1));
    }
}



void spinningljpotforce(linearmolec * other1, linearmolec *other2) {
    
}


void halfspinningljpotforce(linearmolec * other1, pointmolec * other2, sf::RenderWindow * win) {
    float mx = (*other2).getX();
    float my = (*other2).getY();
    float lx1 = (*other1).getX();
    float theta =(*other1).getTheta();
    float length = (*other1).getL();
    float lmx1 = lx1+length/2*cos(theta);
    float lmx2 = lx1-length/2*cos(theta);
    float ly1 = (*other1).getY();
    float lmy1 = ly1+length/2*sin(theta);
    float lmy2 = ly1-length/2*sin(theta);
    float A = mx - lmx1;
    float B = my - lmy1;
    float C = lmx2 - lmx1;
    float D = lmy2 - lmy1;
    float dot = A * C + B * D;
    float p = dot/length/length;
    float m = D/C;
    float mmx = (lmx1+lmx2)/2;
    float mmy = (lmy1+lmy2)/2;
    float sign = 1;
    float m1 = tan(atan(m)+M_PI_2);
    if (my > m*(mx-lmx1)+lmy1) {
        sign *= -1;}
    if (my < m1*(mx-mmx)+mmy) {
        sign *= -1;}
    float xi = lmx1+p*C;
    float yi = lmy1+p*D;
    float d = WINX;
    float maf = 0;
    float ma = 0;
    float dy = my-yi;
    float dx = mx-xi;
    maf = 1;
    bool tick = false;
    if ((xi > lmx1 && xi > lmx2) || (xi < lmx1 && xi < lmx2)) {
        dy = fmin(abs(my-lmy1),abs(my-lmy2));
        dx = fmin(abs(mx-lmx1),abs(mx-lmx2));
        d = sqrt(dx*dx+dy*dy);
        dy = my-yi;
        dx = mx-xi;
        maf = sqrt(dx*dx+dy*dy)/d;
        ma = length/2;
        tick = true;
    }
    else {
        dy = my-yi;
        dx = mx-xi;
        maf = 1;
        d = sqrt(dx*dx+dy*dy);
        ma = abs(p-.5)*length;
    }
    float angle = atan2(my-yi,mx-xi);
    //std::cout << n << std::endl;
    PVector * r = new PVector(cos(angle),sin(angle));
    if (d < pow(2,1/6)*sigma) {
//        if (tick) {
            std::cout << "lmx1 " << lmx1 << " lmy1 " << lmy1 << " lmx2 " << lmx2 << " lmy2 " << lmy2 << " mx " << mx << " my " << my << std::endl;
            std::cout << "A " << A << " B " << B << " C " << C << " D " << D << " dot " << dot << " m1 " << m1 << " xi " << xi << " yi " << yi << " d " << d << std::endl;
            std::cout << "p " << p << " m " << m << " sign " << sign << " maf " << maf << " ma " << ma  << std::endl;
//        }
        //std::cout << "angle  " << angle << std::endl;
        float fn =48*epsilon/sigma/sigma*(pow(sigma/(d+plusC),13)-.5*pow(sigma/(d+plusC),7));
        r = PVector::scalm(r,fn);
        (*(*other1).getF()).add(r);
        (*(*other2).getF()).add(PVector::scalm(r,-1));
        float tq = -ma*maf*abs(fn)*sign;
        std::cout << "fn " << fn << std::endl;
        std::cout << "tq " << tq << std::endl;
        (*other1).modTQ(tq);
        
    }
}
template <typename T> void RVstep(int num, T * molecs) {
    for (int i = 0; i < num; i++) {
        molecs[i].leapfrogA(ts);
        if (molecs[i].getX() > WINX) {
            molecs[i].setX(molecs[i].getX() - WINX);}
        else if (molecs[i].getX() < 0) {
            molecs[i].setX(molecs[i].getX() + WINX);}
        if (molecs[i].getY() > WINY) {
            molecs[i].setY(molecs[i].getY() - WINY);}
        else if (molecs[i].getY() < 0) {
            molecs[i].setY(molecs[i].getY() + WINY);}
        molecs[i].resetA();}
}

void ForceStep(int num1, int num2, linearmolec * lins, pointmolec * ps, sf::RenderWindow * win) {
    for (int i = 0; i < num1; i++) {
        for (int j = i+1; j < num1; j++) {
            spinningljpotforce(&lins[i], &lins[j]);}}
    for (int i = 0; i < num1; i++) {
        for (int j = 0; j < num2; j++) {
            halfspinningljpotforce(&lins[i], &ps[j],win);}}
    for (int i = 0; i < num2; i++) {
        for (int j = i+1; j < num2; j++) {
            ljpotforce(&ps[i], &ps[j]);}}
}

template <typename T> void Rstep(int num, T * molecs) {
    for (int i = 0; i < num; i++) {
        molecs[i].leapfrogB(ts);}}

template <typename T> float KEadd(int num, T * molecs) {
    float s = 0;
    for (int i = 0; i < num; i++) {
        s+=molecs[i].getKE();}
    return s;
}

template <typename T> void showMolecs(int num, T * molecs, sf::RenderWindow * win) {
    for (int i = 0; i < num; i++) {
        molecs[i].disp(win);}}

int main(int, char const**)
{
    std::cout << "this is the phospholipid branch" << std::endl;
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINX, WINY), "MD Sim Phospholipid");
    // Set the Icon
//    sf::Image icon;
//    if (!icon.loadFromFile("/Users/connorblake/Desktop/MD1-feryaccyafhmklbkcnwifmbynyet/Build/Products/Debug/../../../../../Documents/SORTOld/MD1/MD1/MD_Icon.png")) {
//        return EXIT_FAILURE;
//    }
    //window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    int num = 8;
    //molec * gas[num];
    linearmolec * linears = new linearmolec[num/2];
    pointmolec * points = new pointmolec[num/2];
    srand( (unsigned)time( NULL ) );
    initializeLinearMolecules(num/2, linears);
    initializePointMolecules(num/2, points);
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();}
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();}}

        // Clear screen
        window.clear();
        
        RVstep(num/2,linears);
        RVstep(num/2,points);
        ForceStep(num/2,num/2, linears,points,&window);
        Rstep(num/2,linears);
        Rstep(num/2,points);
        float ke = 0;
        ke += KEadd(num/2, linears);
        ke += KEadd(num/2, points);
        std::cout << ke << std::endl;
        showMolecs(num/2,linears,&window);
        showMolecs(num/2,points,&window);
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
