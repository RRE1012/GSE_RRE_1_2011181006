#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	posX = 10.0f;
	posY = 10.0f;
	posZ = 10.0f;
	objSize = 20.0f;
	speedX = 0.5f;
	speedY = 0.8f;
	count = 0;
}

Object::Object(float px, float py, float pz, float size, float speed) {
	posX = px;
	posY = py;
	posZ = pz;
	objSize = size;
	speedX = speed;
	speedY = speed;
	count = 0;

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

void Object::SetPos(float x, float y, float z) {
	posX = x;
	posY = y;
	posZ = z;

}
void Object::Update() {
	//count = (count + 1) % (int)objSize;
	float elapsedTime = 1.5f;

	if (count == 0) {
		posX =posX+ (speedX*elapsedTime);
		posY = posY +(speedY*elapsedTime);
	}
	if (posX+(objSize/2) > 250)
		speedX = speedX*(-1);
	else if (posX - (objSize / 2) < -250)
		speedX = speedX*(-1);
	if (posY + (objSize / 2) > 250)
		speedY = speedY*(-1);
	else if (posY - (objSize / 2) < -250)
		speedY = speedY*(-1);
}