#pragma once
#include "Particle.h"

class Swarm
{
public:
	const static int NPARTICLES = 5000;  //creates particles

private:
	Particle *m_pParticles;

public:
	Swarm();
	~Swarm();

	//gets particles
	Particle *const GetParticles() { return m_pParticles; };  //cant change pointer
};

