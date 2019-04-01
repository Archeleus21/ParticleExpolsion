#pragma once

//difference between a class and a struct is that a struct's variables are
//by default public and  class is private by default unless specified
struct Particle
{
	//public by default since this is a struct
	double m_x; //x position
	double m_y;  //y position

	//double m_xSpeed;   //used for random number made into a decimal
	//double m_ySpeed;   //used for random number made into a decimal

private:
	double m_speed;
	double m_direction;
	
private:
	void Init();

public:
	Particle();
	~Particle();
	void Update(int interval);
};

