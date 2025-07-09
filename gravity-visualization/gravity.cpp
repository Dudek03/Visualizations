#include <vector>
#include <cmath>


struct Mass{
    int x;
    int y;
    double mass;
};

const double G = 9.81;

std::vector<Mass> gravityPoints;

void vectorDir(int x, int y, double* outFx, double* outFy) {
    double fx = 0;
    double fy = 0;
    for (const auto& mass : gravityPoints) {
        double dx = x - mass.x;
        double dy = y - mass.y;
        double r2 = dx*dx + dy*dy;
        if (r2 < 1e-6) continue;

        double r3 = r2 * std::sqrt(r2);
        fx += -G * mass.mass * dx / r3;
        fy += -G * mass.mass * dy / r3;
    }

    *outFx = fx;
    *outFy = fy;
}

void addMass(int x, int y, double mass){
    gravityPoints.push_back({x,y,mass});
}

void clearMassess(){
    gravityPoints.clear();
}

int main(){



    return 0;
}


