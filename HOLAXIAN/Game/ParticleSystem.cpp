#include "ParticleSystem.h"

float randomrange(float minimum,float maximum)
{
    return (minimum+rand()/(float(RAND_MAX)+1)*(maximum-minimum));
}

Particle::Particle()
{
    position.x=0;
    position.y=0;
    acceleration.x=0;
    acceleration.y=0.5;
    velocity.x=randomrange(-1,1);
    velocity.y=randomrange(-1,0);
    lifespan=10;
    color=255;
}

void Particle::run()
{
    update();
    render();
}

void Particle::render()
{
    setfillstyle(SOLID_FILL,COLOR(255,color,0));
    bar(position.x,position.y,position.x+5,position.y+5);
}

void Particle::update()
{
    velocity.x+=acceleration.x;
    velocity.y+=acceleration.y;
    position.x+=velocity.x;
    position.y+=velocity.y;
    lifespan-=1;
    color-=15;
}

bool Particle::isDead()
{
    if(lifespan<0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

ParticleSystem::ParticleSystem()
{
    maximum=15;
    created=1;
    p.push_back(Particle());
    frame=0;
}

void ParticleSystem::run(int x,int y)
{
    ++frame;
    if((created<=maximum)&&(frame%5==0))
    {
        p.push_back(Particle());
        ++created;
    }
    for(std::vector<Particle>::iterator it=p.begin(); it < p.end(); ++it)
    {
        it->position.x+=x;
        it->position.y+=y;
        it->run();
        if(it->isDead())
        {
            p.erase(it--);
            p.push_back(Particle());
        }
        it->position.x-=x;
        it->position.y-=y;
    }
}
