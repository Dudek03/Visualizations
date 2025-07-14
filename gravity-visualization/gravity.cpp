#include <algorithm>
#include <vector>
#include <cmath>
#include "gravity.h"


const double G = 9.81;

std::vector<Mass> gravityPoints;

void vectorDir(int x, int y, double* outFx, double* outFy) {
    double fx = 0;
    double fy = 0;
    for (const auto& mass : gravityPoints) {
        double dx = x - mass.x;
        double dy = y - mass.y;
        double r2 = dx*dx + dy*dy;
        constexpr double ESP = 4.0;
        if (r2 < ESP * ESP) continue;

        double softening = 5.0;
        double r3 = std::pow(r2 + softening * softening, 1.5);
        fx += -G * mass.mass * dx / r3;
        fy += -G * mass.mass * dy / r3;
    }

    *outFx = fx;
    *outFy = fy;
}

void addMass(int x, int y, double mass){
    gravityPoints.push_back({x,y,mass});
}


void removeMass(int x, int y){
    gravityPoints.erase(std::remove_if(gravityPoints.begin(), gravityPoints.end(), 
                                       [x,y](const Mass& m){
                                       return m.x == x && m.y == y;
                                       }),
        gravityPoints.end());                
}

void clearMasses(){
    gravityPoints.clear();
}

const Mass* getMasses(){
    return gravityPoints.data();
}

const int getMassesCount(){
    return gravityPoints.size();
}
