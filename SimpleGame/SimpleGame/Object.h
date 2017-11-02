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
	float life;
	int type;
public:
	Object();
	Object(float px, float py, float pz, float size,float speed,int type);
	Object(float,float,float,float , float , float , float , float ,float,int);

	~Object();
	float GetPosX();
	float GetPosY();
	float GetPosZ();
	float GetSize();
	float GetColorR();
	float GetColorG();
	float GetColorB();
	void SetCollideColor();
	void ReturnColor();
	void SetPos(float, float, float);
	int GetType();
	float GetLife();
	void SetLife(float);
	

	void Update(float );

};

