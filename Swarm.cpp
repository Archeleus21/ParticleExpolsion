#include "pch.h"
#include "Swarm.h"


Swarm::Swarm()
{
	m_pParticles = new Particle[NPARTICLES];
}


Swarm::~Swarm()
{
	delete[] m_pParticles;
}

void Swarm::Update()
{
	//cycles through the particle array
	for (int i = 0; i < Swarm::NPARTICLES; i++)
	{
		m_pParticles[i].Update();
	}
}