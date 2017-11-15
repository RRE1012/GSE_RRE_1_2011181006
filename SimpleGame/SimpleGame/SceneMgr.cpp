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
	if (push_count < MAX_OBJECTS_COUNT) {
		m_ob[push_count] = new Object();
		push_count++;
	}
	
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
	GLuint m_texCharacter = renderer->CreatePngTexture("./Textures/Building.png");
	float a = 1;
	for (int i = 0; i < push_count; ++i) {
		if (m_ob[i]->GetType() == 1) {
			renderer->DrawTexturedRect(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(), m_ob[i]->GetColorR(), m_ob[i]->GetColorG(), m_ob[i]->GetColorB(), a, m_texCharacter);
		}
		else
			renderer->DrawSolidRect(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(), m_ob[i]->GetColorR(), m_ob[i]->GetColorG(), m_ob[i]->GetColorB(), 1);
		

	}
}

void SceneMgr::DrawObjectPNG() {
	GLuint m_texCharacter = renderer->CreatePngTexture("./Textures/PNGs/spritestrip_6Seq.png");

	for (int i = 0; i < push_count; ++i) {
		renderer->DrawTexturedRect(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(), m_ob[i]->GetColorR(), m_ob[i]->GetColorG(), m_ob[i]->GetColorB(), 1, m_texCharacter);


	}
}


void SceneMgr::IsCollide(int num) {
	int collisionCount = 0;
	for (int i = 0; i < push_count; ++i) {

		if (num != i) {
			bool a = m_ob[num]->GetPosX() - m_ob[num]->GetSize() / 2 <=m_ob[i]->GetPosX() + m_ob[i]->GetSize()/2;
			bool b = m_ob[num]->GetPosX() + m_ob[num]->GetSize() / 2 >=m_ob[i]->GetPosX() - m_ob[i]->GetSize() / 2;
			bool c = m_ob[num]->GetPosY() - m_ob[num]->GetSize() / 2 <= m_ob[i]->GetPosY() + m_ob[i]->GetSize() / 2;
			bool d = m_ob[num]->GetPosY() + m_ob[num]->GetSize() / 2 >= m_ob[i]->GetPosY() - m_ob[i]->GetSize() / 2;
			bool e = m_ob[i]->GetLife() > 0;
			bool f = m_ob[num]->GetType() != m_ob[i]->GetType();
			bool g = (m_ob[num]->GetType() == 1 && m_ob[i]->GetType() == 2);
			bool h =(m_ob[num]->GetType() == 2 && m_ob[i]->GetType() == 1);
			bool j = (m_ob[num]->GetType() == 3 && m_ob[i]->GetType() == 2);// || (m_ob[num]->GetType() == 2 && m_ob[i]->GetType() == 3);
			bool k = (m_ob[num]->GetType() == 2 && m_ob[i]->GetType() == 3);
			bool l = (m_ob[num]->GetType() == 1 && m_ob[i]->GetType() == 4);
			bool m = (m_ob[num]->GetType() == 2 && m_ob[i]->GetType() == 4);
			bool n = num != m_ob[i]->GetFollow();

			//m_ob[num]->ReturnColor();
			if (a&&b&&c&&d&&e&&((g) || (k) || (l)|| (m&&n))) {
				
				collisionCount++;
				
				
				m_ob[num]->SetLife(m_ob[i]->GetLife());
				memset(m_ob[i], NULL, sizeof(Object));
				dead_ob[i] = 1;
			}
			
			
		}
	}
	if (collisionCount > 0) {
		m_ob[num]->SetCollideColor();

	}
	else {
		m_ob[num]->ReturnColor(m_ob[num]->GetType());
	}
}

std::map<int, bool> isinherited;
void SceneMgr::UpdateObj(float time) {
	live_count += 1;
	bull_count = (bull_count + 1);
	float elapsedTime = time / 1000.0f;
	
	for (int i = 0; i < push_count; ++i) {
		
		m_ob[i]->Cooltime(elapsedTime);
		m_ob[i]->Update(time);
		if (m_ob[i]->GetType() == 1 &&m_ob[i]->GetLife()>0) {
			

			if (m_ob[i]->GetCoolTime() >= 0.5f) {
				AddActorObject(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), 3,i);
				
				m_ob[i]->ResetCoolTime();
			}
		}
		if (m_ob[i]->GetType() == 2 && m_ob[i]->GetLife()>0) {



			if (m_ob[i]->GetCoolTime() >= 0.5f) {
				
				AddActorObject(m_ob[i]->GetPosX(), m_ob[i]->GetPosY() , 4,i);
				m_ob[i]->ResetCoolTime();
			}
		}
		IsCollide(i);
		if (m_ob[i]->GetLife() <= 0.0f) {
			memset(m_ob[i], NULL, sizeof(Object));
			dead_ob[i] = 1;
		}
		
	}
	
}

int tempint = 0;
void SceneMgr::AddActorObject(float a, float b, int o,int f) {
	if (push_count < MAX_OBJECTS_COUNT) {
		if (o == 1)
			m_ob[push_count] = new Object(a, b, 0, 1.0f, 1.0f, 0.0f, 50, 0, 500,o);
		else if (o == 2)
			m_ob[push_count] = new Object(a, b, o);
		else if (o == 3)
			m_ob[push_count] = new Object(a, b, o);
		else if (o == 4)
			m_ob[push_count] = new Object(a, b, o);
		m_ob[push_count]->SetFollow(f);
		push_count++;
		return;
	}
	else if (push_count >= MAX_OBJECTS_COUNT) {
		for (int i = 0; i < push_count; ++i) {
			if (dead_ob[i] == 1) {
				if (o == 1) {
					m_ob[i] = new Object(a, b, 0, 1.0f, 1.0f, 0.0f, 50, 0, 500.0f, o);
					m_ob[i]->SetFollow(f);
					dead_ob[i] = 0;
				}
				else if (o == 2){
					m_ob[i] = new Object(a, b, o);
					m_ob[i]->SetFollow(f);
					dead_ob[i] = 0;
				}
				else if (o == 3){
					m_ob[i] = new Object(a, b, o);
					m_ob[i]->SetFollow(f);
					dead_ob[i] = 0;
				}
				else if (o == 4){
					m_ob[i] = new Object(a, b,  o);
					m_ob[i]->SetFollow(f);
					dead_ob[i] = 0;
				}
				return;
			}
		}
	}

}

void SceneMgr::MakeShootBullet(Object& obj) {
	if (obj.GetLife() > 0) {
		
		

	}
}