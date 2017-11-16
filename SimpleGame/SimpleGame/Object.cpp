#include <stdlib.h>
#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	posX = rand() % 490 -245;
	//posX = 10.0f;
	posY = rand() % 490 -245;
	posZ = 10.0f;
	objSize = 10.0f;
	speedX = (rand()%1-0.5);
	speedY = (rand() % 1 - 0.5);
	count = 0;
	red = 1.0f;
	green = 1.0f;
	blue = 1.0f;
	life = 10.0f;
	
}
Object::Object(float px, float py,int ty, int teamname)
{
	posX = px;
	posY = py;
	speedX = 200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
	speedY = 200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
	team = teamname;
	if (ty == 1)
	{
		speedX = 0.f;
		speedY = 0.f;
		objSize = 100;
		red = 1.0f;
		green = 1.0f;
		blue = 0.0f;
		life = 500.0f;
	}
	else if (ty == 2) 
	{
		speedX = 300.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		speedY = 300.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		objSize = 20;
		if (team == TEAM_1)
		{
			red = 1.0f;
			green = 0.0f;
			blue = 0.0f;
		}
		else
		{
			red = 0.0f;
			green = 0.0f;
			blue = 1.0f;
		}
		life = 10.0f;
	}
	else if (ty == 3) 
	{
		speedX = 600.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		speedY = 600.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		objSize = 5;
		if (team == TEAM_1)
		{
			red = 1.0f;
			green = 0.0f;
			blue = 0.0f;
		}
		else
		{
			red = 0.0f;
			green = 0.0f;
			blue = 1.0f;
		}
		life = 20.0f;
	}
	else if (ty == 4)
	{
		speedX = 100.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		speedY = 100.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		objSize = 10;
		if (team == TEAM_1)
		{
			red = 0.5f;
			green = 0.2f;
			blue = 0.7f;
		}
		else
		{
			red = 1.0f;
			green = 1.0f;
			blue = 0.0f;
		}
		life = 10.0f;
	}
	
	count = 0;
	type = ty;
}

Object::Object(float px, float py, float pz, float size, float speed,int ty)
{
	posX = px;
	posY = py;
	posZ = pz;
	objSize = size;
	speedX = speed;
	speedY = speed;
	count = 0;
	life = 10.0f;
	type = ty;
}
Object::Object(float px, float py, float pz, float r, float g, float b, float size, float speed,float heart,int ty)
{
	posX = px;
	posY = py;
	posZ = pz;
	red = r;
	green = g;
	blue = b;
	objSize = size;
	speedX = speed;
	speedY = speed;
	count = 0;
	life = heart;
	type = ty;
}
Object::~Object()
{
}

float Object::GetPosX() 
{
	return posX;
}
float Object::GetPosY() 
{
	return posY;
}
float Object::GetPosZ() 
{
	return posZ;
}

float Object::GetSize() 
{

	return objSize;
}
float Object::GetColorR()
{
	return red;
}
float Object::GetColorG() 
{
	return green;
}
float Object::GetColorB() 
{
	return blue;
}
float Object::GetSpeedX() 
{
	return speedX;
}
float Object::GetSpeedY() 
{
	return speedY;
}

void Object::SetPos(float x, float y, float z) 
{
	posX = x;
	posY = y;
	posZ = z;

}
void Object::SetCollideColor() 
{
	red = 1.0f;
	green = 0.0f;
	blue = 0.0f;
}
void Object::ReturnColor() 
{
	red = 1.0f;
	green = 1.0f;
	blue = 1.0f;
}
void Object::ReturnColor(int type)
{
	if (type == 1) 
	{
		red = 1.0f;
		green = 1.0f;
		blue = 0.0f;
	}
	if (type == 2&&team==TEAM_1) 
	{
		red = 1.0f;
		green =0.0f;
		blue = 0.0f;
	}
	else if (type == 2 && team == TEAM_2)
	{
		red = 0.0f;
		green = 0.0f;
		blue = 1.0f;
	}
	if (type == 3&&team==TEAM_1) 
	{
		red = 1.0f;
		green = 0.0f;
		blue = 0.0f;
	}
	else if (type == 3 && team == TEAM_2)
	{
		red = 0.0f;
		green = 0.0f;
		blue = 1.0f;
	}
	if (type == 4) 
	{
		if (team == TEAM_1)
		{
			red = 0.5f;
			green = 0.2f;
			blue = 0.7f;
		}
		else
		{
			red = 1.0f;
			green = 1.0f;
			blue = 0.0f;
		}
	}
}
void Object::Update(float time) 
{
	float elapsedTime = time/1000.0f;

	if (count == 0) 
	{
		posX =posX+ (speedX*elapsedTime);
		posY = posY +(speedY*elapsedTime);
	}
	if (posX + (objSize / 2) > 250) 
	{
		speedX = speedX*(-1);
		
	}
	else if (posX - (objSize / 2) < -250)
	{
		speedX = speedX*(-1);
		
	}
	if (posY + (objSize / 2) > 400)
	{
		speedY = speedY*(-1);
		
	}
	else if (posY - (objSize / 2) < -400) 
	{
		speedY = speedY*(-1);
		
	}
	
		
	
}
float Object::GetLife() 
{
	return life;
}
void Object::SetLife(float a) 
{
	if (a < 0)
		life = life - 10.0f;
	else
		life = life - a;
}

int Object::GetType() 
{

	return type;
}
void Object::Cooltime(float a) 
{
	cooltime = cooltime+a;
}

float Object::GetCoolTime() 
{
	return cooltime;

}
void Object::ResetCoolTime() 
{
	cooltime = 0;
}
void Object::SetFollow(int a) 
{
	follow = a;
}

int Object::GetFollow() 
{
	return follow;
}

int Object::GetTeam()
{
	return team;
}