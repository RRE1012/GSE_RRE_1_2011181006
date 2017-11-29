#pragma once
#define MAX_OBJECTS_COUNT 256
#include "Object.h"
#include "Renderer.h"
#include "stdafx.h"
#include <iostream>
#include <map>
#define OBJECT_BUILDING 1//Object(1.0f,1.0f,0.0f,50f,0,500)
#define OBJECT_CHARACTER 2//Object(1.0f,1.0f,1.0f,10f,300,10)
#define OBJECT_BULLET 3//Object(1.0f,0.0f,0.0f,2,600,20)
#define OBJECT_ARROW 4//Object(0.0f,1.0f,0.0f,2,100,100)


class SceneMgr
{
	Renderer *renderer;
	int push_count = 0;
	int bull_count = 0;
	float cooltime = 0;
	float clickCooltime = 0;
	Object* m_ob[MAX_OBJECTS_COUNT];
	Object* bull_ob[MAX_OBJECTS_COUNT];
	int dead_ob[MAX_OBJECTS_COUNT];
	

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
	void DrawObject();
	void DrawObjectPNG();
	void MakeShootBullet(Object&);
	void AddTime(float);
	float GetCoolTime();
	void ResetCoolTime();
	SceneMgr();
	~SceneMgr();
};

