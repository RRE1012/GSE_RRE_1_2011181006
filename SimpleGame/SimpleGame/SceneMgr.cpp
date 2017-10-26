#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	renderer = new Renderer(500, 500);
	if (!renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	memset(dead_ob, NULL, sizeof(dead_ob));
}


SceneMgr::~SceneMgr()
{
	for (int i = 0; i < push_count; ++i) {
		delete m_ob[i];
	}
	delete renderer;
}
void SceneMgr::AddObject() {
	m_ob[push_count] = new Object();
	push_count++;
}
void SceneMgr::AddObject(int i) {
	m_ob[i] = new Object();
	
}
void SceneMgr::MaxAdd() {
	
	for (int i = push_count; i < MAX_OBJECTS_COUNT; ++i) {
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
void SceneMgr::DrawObject() {
	for (int i = 0; i < push_count; ++i) {
		renderer->DrawSolidRect(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(), m_ob[i]->GetColorR(), m_ob[i]->GetColorG(), m_ob[i]->GetColorB(), 1);
	}
}

void SceneMgr::IsCollide(int num) {
	for (int i = 0; i < push_count; ++i) {
		if (num != i) {
			bool a = m_ob[num]->GetPosX() - m_ob[num]->GetSize() / 2 <=m_ob[i]->GetPosX() + m_ob[i]->GetSize()/2;
			bool b = m_ob[num]->GetPosX() + m_ob[num]->GetSize() / 2 >=m_ob[i]->GetPosX() - m_ob[i]->GetSize() / 2;
			bool c = m_ob[num]->GetPosY() - m_ob[num]->GetSize() / 2 <= m_ob[i]->GetPosY() + m_ob[i]->GetSize() / 2;
			bool d = m_ob[num]->GetPosY() + m_ob[num]->GetSize() / 2 >= m_ob[i]->GetPosY() - m_ob[i]->GetSize() / 2;
			//m_ob[num]->ReturnColor();
			if (a&&b&&c&&d) {
				m_ob[num]->SetLife();
				m_ob[num]->SetCollideColor();
			}
			
		}
	}
}

void SceneMgr::UpdateObj(float time) {
	live_count += 1;
	
	for (int i = 0; i < push_count; ++i) {
		m_ob[i]->Update(time);
		IsCollide(i);
		if (m_ob[i]->GetLife() <= 0.0f) {
			memset(m_ob[i], NULL, sizeof(Object));
			dead_ob[i] = 1;
		}
		if (live_count % 100 == 0) {
			if (dead_ob[i] == 1) {
				AddObject(i);
				dead_ob[i]=0;
			}
			
		}
	}
	
}

