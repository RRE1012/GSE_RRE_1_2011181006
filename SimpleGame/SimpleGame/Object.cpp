#include <stdlib.h>
#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	//std::uniform_int_distribution<__int64> uniformDist(1, 45);

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

Object::Object(float px, float py, float pz, float size, float speed) {
	posX = px;
	posY = py;
	posZ = pz;
	objSize = size;
	speedX = speed;
	speedY = speed;
	count = 0;
	life = 10.0f;
}
Object::~Object()
{
}

float Object::GetPosX() {

	return posX;
}
float Object::GetPosY() {

	return posY;
}
float Object::GetPosZ() {

	return posZ;
}

float Object::GetSize() {

	return objSize;
}
float Object::GetColorR() {
	return red;
}
float Object::GetColorG() {
	return green;
}
float Object::GetColorB() {
	return blue;
}

void Object::SetPos(float x, float y, float z) {
	posX = x;
	posY = y;
	posZ = z;

}
void Object::SetCollideColor() {
	red = 1.0f;
	green = 0.0f;
	blue = 0.0f;
}
void Object::ReturnColor() {
	red = 1.0f;
	green = 1.0f;
	blue = 1.0f;
}

void Object::Update(float time) {
	//count = (count + 1) % (int)objSize;
	float elapsedTime = time/10.0f;

	if (count == 0) {
		posX =posX+ (speedX*elapsedTime);
		posY = posY +(speedY*elapsedTime);
	}
	if (posX + (objSize / 2) > 250) {
		speedX = speedX*(-1);
		life -= 1.0f;
	}
	else if (posX - (objSize / 2) < -250) {
		speedX = speedX*(-1);
		life -= 1.0f;
	}
	if (posY + (objSize / 2) > 250) {
		speedY = speedY*(-1);
		life -= 1.0f;
	}
	else if (posY - (objSize / 2) < -250) {
		speedY = speedY*(-1);
		life -= 1.0f;
	}
	
		
	
}
float Object::GetLife() {
	return life;
}
void Object::SetLife() {
	life = life - 1.0f;;
}
