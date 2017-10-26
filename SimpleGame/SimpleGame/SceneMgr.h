#pragma once
#define MAX_OBJECTS_COUNT 10
#include "Object.h"
#include "Renderer.h"
#include "stdafx.h"
#include <iostream>
class SceneMgr
{
	Renderer *renderer;
	int push_count = 0;
	Object* m_ob[MAX_OBJECTS_COUNT];
	int dead_ob[MAX_OBJECTS_COUNT];
	int live_count = 0;

public:
	
	void AddObject();
	void AddObject(int);

	void MaxAdd();
	void UpdateObj(float);
	Object GetObject0(int);
	int GetPushNum();
	void IsCollide(int);
	void DrawObject();
	
	SceneMgr();
	~SceneMgr();
};

