#include "pch.h"
#include "Swarm.h"

//makes lastTime = 0
Swarm::Swarm() : lastTime(0)
{
	m_pParticles = new Particle[NPARTICLES];
}


Swarm::~Swarm()
{
	delete[] m_pParticles;
}

//ensures runs same on all cpus
void Swarm::Update(int elapsedTime)
{
	int interval = elapsedTime - lastTime;
	
	//cycles through the particle array
	for (int i = 0; i < Swarm::NPARTICLES; i++)
	{
		m_pParticles[i].Update(interval);
	}

	lastTime = elapsedTime;
}