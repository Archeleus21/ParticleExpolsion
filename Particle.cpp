#include "pch.h"
#include "Particle.h"
#include <stdlib.h>


Particle::Particle()
{
	//rand()) / RAND_MAX returns random number between 0 - 1
	//(2.0 * rand()) gives range 0 - 2.0
	//((2.0 * rand()) / RAND_MAX) - 1  gives range from -1 -1
	m_x = ((2.0 * rand()) / RAND_MAX) - 1;  
	m_y = ((2.0 * rand()) / RAND_MAX) - 1;  
}


Particle::~Particle()
{

}
