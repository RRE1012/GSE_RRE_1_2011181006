#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	renderer = new Renderer(500, 800);
	if (!renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	memset(dead_ob, NULL, sizeof(dead_ob));
	 m_texCharacter = renderer->CreatePngTexture("./Textures/Building.png");
	 m_texCharacter2 = renderer->CreatePngTexture("./Textures/house.png");
	 m_texCharacter3 = renderer->CreatePngTexture("./Textures/Kid_Enemy01.png");
	m_texCharacter4 = renderer->CreatePngTexture("./Textures/Character_Team05.png");
	 m_texBackGround = renderer->CreatePngTexture("./Textures/Background.png");
	 m_texParticle = renderer->CreatePngTexture("./Textures/Character_Team.png");

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
	//aniX_count = (aniX_count +1)%6;
	//if (aniX_count == 5) {
	////	aniY_count = (aniY_count + 1) % 4;
	//}
	
	renderer->DrawTexturedRect(0, 0, 0, 800, 1, 1, 1, 1, m_texBackGround, LEVEL_WORST);
	float a = 1;
	for (int i = 0; i < push_count; ++i) {
		if (m_ob[i]->GetType() == 1) {
			if (m_ob[i]->GetTeam() == TEAM_1) {
				renderer->DrawTexturedRect(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(), 1, 1, 1, a, m_texCharacter, m_ob[i]->GetLevel());
				renderer->DrawSolidRectGauge(m_ob[i]->GetPosX(), m_ob[i]->GetPosY() + (m_ob[i]->GetSize() / 2), m_ob[i]->GetPosZ(), 50, 10, 0, 0, 1, a, m_ob[i]->GetLife()/500, 0.3);
				
			}
			else {
				renderer->DrawTexturedRect(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(),1, 1, 1, a, m_texCharacter2, m_ob[i]->GetLevel());
				renderer->DrawSolidRectGauge(m_ob[i]->GetPosX(), m_ob[i]->GetPosY() + (m_ob[i]->GetSize() / 2), m_ob[i]->GetPosZ(), 50, 10, 1, 0, 0, a, m_ob[i]->GetLife() / 500, 0.3);
			}
		}
		else if(m_ob[i]->GetType() == 2){

			
			if (m_ob[i]->GetTeam() == TEAM_2) {
				//renderer->DrawTexturedRect(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(), 1, 1, 1, a, m_texCharacter3, m_ob[i]->GetLevel());
				renderer->DrawTexturedRectSeq(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(), 1, 1, 1, a, m_texCharacter3, m_ob[i]->GetXCount(), m_ob[i]->GetYCount(), m_ob[i]->GetAniWidth(), m_ob[i]->GetAniHeight(), m_ob[i]->GetLevel());
				renderer->DrawSolidRectGauge(m_ob[i]->GetPosX(), m_ob[i]->GetPosY() + (m_ob[i]->GetSize() / 2), m_ob[i]->GetPosZ(), 50, 10, 1, 0, 0, a, m_ob[i]->GetLife() / 100, 0.3);
			}
			else {

				renderer->DrawSolidRectGauge(m_ob[i]->GetPosX(), m_ob[i]->GetPosY() + (m_ob[i]->GetSize() / 2), m_ob[i]->GetPosZ(), 50, 10, 0, 0, 1, a, m_ob[i]->GetLife() / 100, 0.3);
				renderer->DrawTexturedRectSeq(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(), 1, 1, 1, a, m_texCharacter4, m_ob[i]->GetXCount(), m_ob[i]->GetYCount(), m_ob[i]->GetAniWidth(), m_ob[i]->GetAniHeight(), m_ob[i]->GetLevel());

//				renderer->DrawTexturedRect(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(), 1, 1, 1, a, m_texCharacter4, m_ob[i]->GetLevel());
			}
		}
		else if (m_ob[i]->GetType() == 4) {
			renderer->DrawSolidRect(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(), m_ob[i]->GetColorR(), m_ob[i]->GetColorG(), m_ob[i]->GetColorB(), 1, m_ob[i]->GetLevel());
		}
		else {
			renderer->DrawParticle(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(), m_ob[i]->GetColorR(), m_ob[i]->GetColorG(), m_ob[i]->GetColorB(), 1,0,0, m_texParticle, m_ob[i]->GetElapsedTime());
			//renderer->DrawSolidRect(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(), m_ob[i]->GetColorR(), m_ob[i]->GetColorG(), m_ob[i]->GetColorB(), 1, m_ob[i]->GetLevel());
		}

	}
}

void SceneMgr::DrawObjectPNG() {
	GLuint m_texCharacter = renderer->CreatePngTexture("./Textures/PNGs/spritestrip_6Seq.png");

	for (int i = 0; i < push_count; ++i) {
		renderer->DrawTexturedRect(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(), m_ob[i]->GetColorR(), m_ob[i]->GetColorG(), m_ob[i]->GetColorB(), 1, m_texCharacter, m_ob[i]->GetLevel());


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
			//bool h =(m_ob[num]->GetType() == 2 && m_ob[i]->GetType() == 1);
			bool j = (m_ob[num]->GetType() == 1 && m_ob[i]->GetType() == 3);// || (m_ob[num]->GetType() == 2 && m_ob[i]->GetType() == 3);
			bool k = (m_ob[num]->GetType() == 2 && m_ob[i]->GetType() == 3);
			bool l = (m_ob[num]->GetType() == 1 && m_ob[i]->GetType() == 4);
			bool m = (m_ob[num]->GetType() == 2 && m_ob[i]->GetType() == 4);
			//bool n = num != m_ob[i]->GetFollow();
			
			bool o = m_ob[num]->GetTeam() != m_ob[i]->GetTeam();
			if (a&&b&&c&&d&&e&&o&&(g||k||m||j||l)) {
				
				collisionCount++;
				
				
				m_ob[num]->SetLife(m_ob[i]->GetLife());
				m_ob[i]->SetLife(m_ob[num]->GetLife());
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
	
	
	float elapsedTime = time / 1000.0f;
	for (int i = 0; i < push_count; ++i) {
		m_ob[i]->Cooltime(elapsedTime);
		m_ob[i]->Update(time);
		if (m_ob[i]->GetType() == 1 &&m_ob[i]->GetLife()>0) {
			if (m_ob[i]->GetCoolTime() >= 2.0f) {
				AddActorObject(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), 3,i);
				m_ob[i]->ResetCoolTime();
			}
		}
		if (m_ob[i]->GetType() == 2 && m_ob[i]->GetLife()>0) {
			if (m_ob[i]->GetCoolTime() >= 3.0f) {
				AddActorObject(m_ob[i]->GetPosX(), m_ob[i]->GetPosY() , 4,i);
				m_ob[i]->ResetCoolTime();
			}
		}
		IsCollide(i);
		bool a = m_ob[i]->GetPosX() > 250 || m_ob[i]->GetPosX() < -250 || m_ob[i]->GetPosY() > 400 || m_ob[i]->GetPosY() < -400;
		bool b = m_ob[i]->GetType() != 2;
		if (m_ob[i]->GetLife() <= 0.0f ||(a&&b)) {
			memset(m_ob[i], NULL, sizeof(Object));
			dead_ob[i] = 1;
		}
		
	}
	
}
void SceneMgr::AddTime(float time) 
{
	cooltime = cooltime + time;
}
void SceneMgr::MakeObj(float time) {
	float elapsedTime = time / 1000.0f;
	cooltime = cooltime + elapsedTime;
	if(clickCooltime<=7.0f)
		clickCooltime = clickCooltime + elapsedTime;
	if (cooltime >= 5.0f) 
	{
		AddActorObject(rand() % 250, rand() % 400, 2, 0);
		cooltime = 0;
	}
}

float SceneMgr::GetCoolTime() {
	return clickCooltime;
}
void SceneMgr::ResetCoolTime() {
	clickCooltime = 0.0f;
}
int tempint = 0;
void SceneMgr::AddActorObject(float a, float b, int o,int f) {
	if (push_count < MAX_OBJECTS_COUNT) {
		if (o == 1) 
		{
			if(b<0)
				m_ob[push_count] = new Object(a, b, o, TEAM_1);
			else
				m_ob[push_count] = new Object(a, b, o, TEAM_2);
		}
		else if (o == 2)
			if (b<0)
				m_ob[push_count] = new Object(a, b, o, TEAM_1);
			else
				m_ob[push_count] = new Object(a, b, o, TEAM_2);
		else if (o == 3)
			m_ob[push_count] = new Object(a, b, o, m_ob[f]->GetTeam());
		else if (o == 4)
			m_ob[push_count] = new Object(a, b, o, m_ob[f]->GetTeam());
		m_ob[push_count]->SetFollow(f);
		push_count++;
		return;
	}
	else if (push_count >= MAX_OBJECTS_COUNT) {
		for (int i = 0; i < push_count; ++i) {
			if (dead_ob[i] == 1) {
				if (o == 1) 
				{
					if (b<0)
						m_ob[push_count] = new Object(a, b, o, TEAM_1);
					else
						m_ob[push_count] = new Object(a, b, o, TEAM_2);
				}
				else if (o == 2){
					if (b<0)
						m_ob[push_count] = new Object(a, b, o, TEAM_1);
					else
						m_ob[push_count] = new Object(a, b, o, TEAM_2);
				
					dead_ob[i] = 0;
				}
				else if (o == 3){
					m_ob[i] = new Object(a, b, o, m_ob[f]->GetTeam());
					m_ob[i]->SetFollow(f);
					dead_ob[i] = 0;
				}
				else if (o == 4){
					m_ob[i] = new Object(a, b,  o, m_ob[f]->GetTeam());
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