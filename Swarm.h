#pragma once
#include "Particle.h"

class Swarm
{
public:
	const static int NPARTICLES = 5000;  //creates particles

private:
	Particle *m_pParticles;
	int lastTime;  //time of last frame

public:
	Swarm();
	~Swarm();
	void Update(int elapsedTime);

	//gets particles
	Particle *const GetParticles() { return m_pParticles; };  //cant change pointer
};

