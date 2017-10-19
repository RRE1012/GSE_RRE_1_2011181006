#pragma once
#define MAX_OBJECTS_COUNT 254
#include "Object.h"
class SceneMgr
{
	int push_count = 0;
public:
	Object* m_ob[MAX_OBJECTS_COUNT];
	void AddObject();
	void MaxAdd();
	void UpdateObj();
	Object GetObject0(int);
	int GetPushNum();
	SceneMgr();
	~SceneMgr();
};

