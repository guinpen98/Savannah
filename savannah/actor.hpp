#pragma once
#include"init.hpp"
#include<random>
#include <cmath>


class Animal {
private:
    double distance=100.0;
protected:
    double x = 256;
    double y = 256;
    double distinationX = 256;
    double distinationY = 256;
    double spf = 0.0;
    double age = 0.0;
    int oneYear = 24;
public:
    int moveX();
    int moveY();
    bool isDistination();
    void calculateDistance(const double x, const double y, const double dsX, const double dsY);

    void setDistination();

    void getSpf(const double mispf);
};
class Herbivore : public Animal {
private:
    double lifespan=20.0;
public:
    void behavior(int& animalNewX,int& animalNewY,int& animalID,bool& isDie);
};
int Animal::moveX() {
    if (distance == 0.0) {
        setDistination();
        calculateDistance(x, y, distinationX, distinationY);
    }
    double dx = (distinationX - x) / distance;
    x += dx;
    return int(x);
}
int Animal::moveY() {
    if (distance == 0.0) {
        setDistination();
        calculateDistance(x, y, distinationX, distinationY);
    }
    double dy = (distinationY - y) / distance;
    y += dy;
    return int(y);
}
bool Animal::isDistination() {
    if ((x - distinationX) < 1 && (y - distinationY) < 1) return true;
    else return false;
}
void Animal::calculateDistance(const double x, const double y, const double dsX, const double dsY) {
    distance=sqrt(pow(x - dsX, 2) + pow(y - dsY, 2));
}

void Animal::setDistination() {
    constexpr int MIN = 0;
    constexpr int wMAX = windowWidth;
    constexpr int hMAX = windowHeight;
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> wDistr(MIN, wMAX);
    std::uniform_int_distribution<int> hDistr(MIN, hMAX);
    distinationX = wDistr(eng);
    distinationY = hDistr(eng);
}

void Animal::getSpf(const double mispf) {
    spf = mispf / 1000.0;
}
void Herbivore::behavior(int& animalNewX,int& animalNewY,int& animalID,bool& isDie) {
    age += spf;
    isDie = (age > oneYear * lifespan);
    if (isDistination()) setDistination();
    calculateDistance(x,y,distinationX,distinationY);
    animalNewX=moveX();
    animalNewY=moveY();
    animalID = herbivoreE;
}