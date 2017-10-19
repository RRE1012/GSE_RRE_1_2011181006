#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
}


SceneMgr::~SceneMgr()
{
	for (int i = 0; i < push_count; ++i) {
		delete m_ob[i];
	}
}
void SceneMgr::AddObject() {
	m_ob[push_count] = new Object();
	push_count++;
}
void SceneMgr::MaxAdd() {
	int temp = push_count;
	for (int i = temp; i < MAX_OBJECTS_COUNT; ++i) {
		m_ob[i] = new Object();
		push_count++;
	}
}
Object SceneMgr::GetObject0(int i) {
	return *m_ob[i];
}
int SceneMgr::GetPushNum() {
	return push_count;
}

void SceneMgr::UpdateObj() {
	for (int i = 0; i < push_count; ++i) {
		m_ob[i]->Update();
	}
	for (int i = 0; i < push_count; ++i) {
		

	}
}
