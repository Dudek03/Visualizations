
#ifdef __cplusplus
extern "C" {
#endif

struct Mass{
    int x;
    int y;
    double mass;
};

void vectorDir(int x, int y, double* outFx, double* outFy);
void addMass(int x, int y, double mass);
void clearMasses();
void removeMass(int x, int y);
const Mass* getMasses();
const int getMassesCount();

#ifdef __cplusplus
}
#endif
