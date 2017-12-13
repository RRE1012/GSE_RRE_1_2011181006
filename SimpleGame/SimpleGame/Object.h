#pragma once

//#include <utility>
#define TEAM_1 1001
#define TEAM_2 2002
#define LEVEL_GOD 0
#define LEVEL_SKY 0.1
#define LEVEL_GROUND 0.2
#define LEVEL_UNDERGROUND 0.3
#define LEVEL_WORST 0.9

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
	int team;
	float level;
	int aniXcount;
	int aniYcount;
	int aniWidth;
	int aniHeight;
	float e_time;
public:
	Object();
	Object(float px, float py,int ty, int teamname);
	Object(float px, float py, float pz, float size,float speed,int type);
	Object(float x,float y,float z ,float r, float g, float b, float size, float speed,float heart,int ty);

	~Object();
	float GetPosX();
	float GetPosY();
	float GetPosZ();
	float GetSpeedX();
	float GetSpeedY();
	int GetTeam();
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
	void SetAniCount(int sizeX,int sizeY);
	int GetXCount();
	int GetYCount();
	int GetAniWidth();
	int GetAniHeight();
	float GetElapsedTime() {
		return e_time;
	}
	void SetLife(float);
	void SetFollow(int);
	void SetSpeed(float a,float b) {
		speedX = a;
		speedY = b;
	};
	int GetFollow();
	float GetLevel() { return level; };
	void Update(float );

};

