#pragma once
#include "Particle.h"

class Swarm
{
public:
	const static int NPARTICLES = 2500;  //creates particles

private:
	Particle *m_pParticles;

public:
	Swarm();
	~Swarm();
	void Update();

	//gets particles
	Particle *const GetParticles() { return m_pParticles; };  //cant change pointer
};

