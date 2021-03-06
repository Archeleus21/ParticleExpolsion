
#include "pch.h"
#include "Particle.h"
#include <stdlib.h>
#define _USE_MATH_DEFINES  //need to use M_PI and a multitude of other constants see: https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2012/4hwaceh6(v=vs.110)
#include <math.h>


Particle::Particle()
	: m_x(0), m_y(0)
{
	Init();
}


Particle::~Particle()
{

}

void Particle::Init()
{
	m_x = 0;
	m_y = 0;

	/*
	//rand()) / RAND_MAX returns random number between 0 - 1
	//(2.0 * rand()) gives range 0 - 2.0
	//((2.0 * rand()) / RAND_MAX) - 1  gives range from -1 -1
	m_x = ((2.0 * rand()) / RAND_MAX) - 1;
	m_y = ((2.0 * rand()) / RAND_MAX) - 1;
	
	m_xSpeed = 0.001 * (((2.0 * rand()) / RAND_MAX) - 1);   //random number made into a decimal
	m_ySpeed = 0.001 * (((2.0 * rand()) / RAND_MAX) - 1);   //random number made into a decimal
	*/
	
	//random 360 using radians, 2Pi = 6.3 radians (tau)
	m_direction = (2 * M_PI  * rand()) / RAND_MAX;

	//random speed from 0.0 - 1.0
	m_speed = (0.001 * rand()) / RAND_MAX;

	m_speed * m_speed;
}

void Particle::Update(int interval)
{
	/*
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
	*/

	m_direction += interval * .0005;

	//computes speed of x and y
	double xSpeed = m_speed * cos(m_direction);
	double ySpeed = m_speed * sin(m_direction);

	//moves particles
	m_x += xSpeed * interval;
	m_y += ySpeed * interval;

	//if particles get to edge of screen they return to center and come out again
	if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1)
	{
		Init();
	}

	//if rand which is between 0 - 1, rand_max is a large integer divided by 100
	//if true reinitialized
	if (rand() < RAND_MAX / 100)
	{
		Init();
	}
}