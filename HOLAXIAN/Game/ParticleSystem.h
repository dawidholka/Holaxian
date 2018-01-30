#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include "../Color.h"

class Particle
{
public:
    fXY position;
    fXY velocity;
    fXY acceleration;
    float lifespan;
    int color;
    Particle();
    void update();
    void render();
    bool isDead();
    void run();
};

class ParticleSystem
{
private:
    std::vector<Particle> p;
    int maximum;
    int created;
    int frame;
public:
    ParticleSystem();
    void run(int x,int y);
};

#endif
