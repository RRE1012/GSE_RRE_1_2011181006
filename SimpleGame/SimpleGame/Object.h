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
	float cooltime =0;
	int follow=0;
public:
	Object();
	Object(float px, float py,int ty);
	Object(float px, float py, float pz, float size,float speed,int type);
	Object(float x,float y,float z ,float r, float g, float b, float size, float speed,float heart,int ty);

	~Object();
	float GetPosX();
	float GetPosY();
	float GetPosZ();
	float GetSpeedX();
	float GetSpeedY();

	float GetSize();
	float GetColorR();
	float GetColorG();
	float GetColorB();
	void Cooltime(float );
	float GetCoolTime();
	void ResetCoolTime();
	void SetCollideColor();
	void ReturnColor();
	void ReturnColor(int type);
	void SetPos(float, float, float);
	int GetType();
	float GetLife();
	void SetLife(float);
	void SetFollow(int);
	int GetFollow();

	void Update(float );

};

