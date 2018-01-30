#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include "../Color.h"

typedef struct point_xy
{
    float x;
    float y;
} point_xy;

class Particle
{
public:
    point_xy position;
    point_xy velocity;
    point_xy acceleration;
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
