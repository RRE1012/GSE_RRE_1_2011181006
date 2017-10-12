#pragma once

//#include <utility>
class Object
{
private:
	float posX, posY, posZ;
	float objSize;
	//pair<float, float> speed;
	float speedX, speedY;
	float red, green, blue;
	int count;
public:
	Object();
	Object(float px, float py, float pz, float size,float speed);
	~Object();
	float GetPosX();
	float GetPosY();
	float GetPosZ();
	float GetSize();
	float GetColorR();
	float GetColorG();
	float GetColorB();

	void SetPos(float, float, float);
	void Update();
};

