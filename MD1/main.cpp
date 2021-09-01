
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
#include "PVector.hpp"
using namespace phys;
using namespace chem;
unsigned long t;
const float ts = .02;
const int WINX = 1600;
const int WINY = 1600;
void initializeMolecules(int num, molec * m) {
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
        m[i] = molec(rin, vin, ain,10,1,1);
    }
}
void ljpotforce(molec * other1, molec * other2) {
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
    PVector * r = new PVector(n*cos(angle),n*sin(angle));
    const float epsilon = 1;
    const float sigma = 20;
    if (n < pow(2,1/6)*sigma) {
        float fn =48*epsilon/sigma/sigma*(pow(sigma/n,13)-.5*pow(sigma/n,7));
        //std::cout << fn << std::endl;
        PVector::scalm(r,fn);
        (*(*other1).getF()).add(r);
        (*(*other2).getF()).add(PVector::scalm(r,-1));
    }
}

int main(int, char const**)
{
    std::cout << "this is the IS branch" << std::endl;
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINX, WINY), "MD Sim 1");
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile("/Users/connorblake/Desktop/MD1-feryaccyafhmklbkcnwifmbynyet/Build/Products/Debug/../../../../../Documents/SORTOld/MD1/MD1/MD_Icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    int num = 100;
    molec* gas = new molec[num];
    srand( (unsigned)time( NULL ) );
    initializeMolecules(num,gas);
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Clear screen
        window.clear();
        float ke = 0;
        for (int i = 0; i < num; i++) {
            (*gas[i].getV()).add(PVector::scalm(gas[i].getF(),ts/2/gas[i].getM()));
            (*gas[i].getR()).add(PVector::scalm(gas[i].getV(),(ts)));
            if (gas[i].getX() > WINX) {
                gas[i].setX(gas[i].getX() - WINX);}
            else if (gas[i].getX() < 0) {
                gas[i].setX(gas[i].getX() + WINX);}
            if (gas[i].getY() > WINY) {
                gas[i].setY(gas[i].getY() - WINY);}
            else if (gas[i].getY() < 0) {
                gas[i].setY(gas[i].getY() + WINY);}
            gas[i].resetA();}
        for (int i = 0; i < num; i++) {
            for (int j = i+1; j < num; j++) {
                ljpotforce(&gas[i],&gas[j]);}}
        for (int i = 0; i < num; i++) {
            (*gas[i].getV()).add(PVector::scalm(gas[i].getF(),ts/2/gas[i].getM()));
            gas[i].disp(&window);
            ke+= (*gas[i].getV()).magsq();
        }
        //std::cout << ke << std::endl;
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
