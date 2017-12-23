#pragma once
#define MAX_OBJECTS_COUNT 256
#include "Object.h"
#include "Renderer.h"
#include "Sound.h"
#include "stdafx.h"
#include <iostream>
#include <map>
#define OBJECT_BUILDING 1//Object(1.0f,1.0f,0.0f,50f,0,500)
#define OBJECT_CHARACTER 2//Object(1.0f,1.0f,1.0f,10f,300,10)
#define OBJECT_BULLET 3//Object(1.0f,0.0f,0.0f,2,600,20)
#define OBJECT_ARROW 4//Object(0.0f,1.0f,0.0f,2,100,100)
#define OBJECT_ROBOT 5
#define OBJECT_TANK 6
#define OBJECT_MISSILE 7


class SceneMgr
{
	Renderer *renderer;
	int push_count = 0;
	int aniX_count = 0;
	int aniY_count = 0;
	float cooltime = 0;
	float clickCooltime = 0;
	float clickCooltime2 = 0;
	float clickCooltime3 = 0;
	bool is_GameOver = false;
	bool you_Win = false;
	Object* m_ob[MAX_OBJECTS_COUNT];
	Object* bull_ob[MAX_OBJECTS_COUNT];
	int dead_ob[MAX_OBJECTS_COUNT];
	GLuint m_texCharacter; 
	GLuint m_texCharacter2; 
	GLuint m_texCharacter3;
	GLuint m_texCharacter4; 
	GLuint m_textRobot01;
	GLuint m_textTank01;
	GLuint m_textMissile01;

	GLuint m_lose;
	GLuint m_win;

	GLuint m_texBackGround;
	GLuint m_texParticle;
	GLuint m_texParticle_Snow;
	GLuint m_texParticle_Rain;

	float snow_cooltime = 0.0f;
	Sound* m_sound = nullptr;
	int soundBG;
	int winBG;
	int loseBG;

public:
	
	void AddObject();
	void AddObject(int);
	void AddActorObject(float,float,int,int);
	void MaxAdd();
	void UpdateObj(float);
	void MakeObj(float);
	Object GetObject0(int);
	int GetPushNum();
	void IsCollide(int);
	void DrawObject(float);
	void DrawObjectPNG();
	void MakeShootBullet(Object&);
	void AddTime(float);
	float GetCoolTime();
	float GetCoolTime2();
	float GetCoolTime3();
	void ResetCoolTime();
	void ResetCoolTime2();
	void ResetCoolTime3();

	SceneMgr();
	~SceneMgr();
};

