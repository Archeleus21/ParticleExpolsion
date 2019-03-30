#include "pch.h"
#include "Particle.h"
#include <stdlib.h>
#include <math.h>


Particle::Particle()
{
	//rand()) / RAND_MAX returns random number between 0 - 1
	//(2.0 * rand()) gives range 0 - 2.0
	//((2.0 * rand()) / RAND_MAX) - 1  gives range from -1 -1
	m_x = ((2.0 * rand()) / RAND_MAX) - 1;  
	m_y = ((2.0 * rand()) / RAND_MAX) - 1;  

	m_xSpeed = 0.001 * (((2.0 * rand()) / RAND_MAX) - 1);   //random number made into a decimal
	m_ySpeed = 0.001 * (((2.0 * rand()) / RAND_MAX) - 1);   //random number made into a decimal

}


Particle::~Particle()
{

}

void Particle::Update()
{
	m_x += m_xSpeed;
	m_y += m_ySpeed;

	//used to keep x particles within window
	if (m_x < -1.0 || m_x >= 1.0)
	{
		m_xSpeed = -m_xSpeed;
	}

	//uesd to keep y paricles within window
	if (m_y <= -1.0 || m_y >= 1.0)
	{
		m_ySpeed = -m_ySpeed;
	}
}