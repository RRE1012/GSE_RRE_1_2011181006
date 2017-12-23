#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	renderer = new Renderer(WINSIZEX, WINSIZEY);
	is_GameOver = false;
	you_Win = false;
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
	 m_texParticle_Snow = renderer->CreatePngTexture("./Textures/SnowParticle.png");
	 m_texParticle_Rain = renderer->CreatePngTexture("./Textures/ParticleRain.png");
	 m_textRobot01 = renderer->CreatePngTexture("./Textures/Character_Robot.png"); //560X225
	 m_textTank01 = renderer->CreatePngTexture("./Textures/Character_Tank.png");
	 m_textMissile01 = renderer->CreatePngTexture("./Textures/Missile.png");
	 m_win = renderer->CreatePngTexture("./Textures/you_win.png");
	 m_lose = renderer->CreatePngTexture("./Textures/gameover.png");

	 m_sound = new Sound();
	 soundBG = m_sound->CreateSound("./SoundSamples/Exciting.mp3");
	 winBG = m_sound->CreateSound("./SoundSamples/PiCCa.mp3");
	 loseBG = m_sound->CreateSound("./SoundSamples/ophelia.mp3");

	// m_sound->PlaySound(soundBG, true, 0.5f);
	
	 m_sound->PlaySound(soundBG, true, 0.5f);

}


SceneMgr::~SceneMgr()
{
	for (int i = 0; i < push_count; ++i) {
		delete m_ob[i];
	}
	delete m_sound;
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
void SceneMgr::DrawObject(float time) {
	aniX_count = (aniX_count +1)%6;
	float elapsedtime = time / 1000.0f;
	snow_cooltime += elapsedtime;
	char* tempchar = "Left_Click\nRobot Gen";
	char* tempchar2 = "Left_Click\nArmy Gen";
	char* tempchar3 = "Right_Click\nTank Gen";
	char* tempchar4 = "Enemy_GenTime\nEnemy Gen";

		//DrawParticleCloud(0, 0, 0, 1, 1, 1, 1, 1, -0.1, -0.1, m_texParticle, time, 0.01);

	renderer->DrawTexturedRect(0, 0, 0, 800, 1, 1, 1, 1, m_texBackGround, LEVEL_WORST);
	if(clickCooltime>=2.0f)
		renderer->DrawSolidRectGauge(0, -300, 0, 500, 200, 0, 1, 0, 1, 1, 0.8);
	if (clickCooltime2 >= 1.0f)
		renderer->DrawSolidRectGauge(0, -100, 0, 500, 200, 1, 1, 1, 1, 1, 0.8);
	
	if (is_GameOver) {
		m_sound->DeleteSound(soundBG);
		renderer->DrawTexturedRect(0, 0, 0, 300, 1, 1, 1, 1, m_lose, LEVEL_UI);
	}
	if (you_Win) {
		m_sound->DeleteSound(soundBG);
		renderer->DrawTexturedRect(0, 0, 0, 300, 1, 1, 1, 1, m_win, LEVEL_UI);
	}
	renderer->DrawSolidRectGauge(0, 450, 0, 50, 50, 1, 0, 0, 1, cooltime /3, 0.3);
	renderer->DrawSolidRectGauge(-200, -460, 0, 50, 30, 0, 1, 0, 1, clickCooltime/2, 0.3);

	renderer->DrawSolidRectGauge(-200, -430, 0, 50, 30, 1, 1, 1, 1, clickCooltime2 / 1, 0.3);
	renderer->DrawSolidRectGauge(200, -450, 0, 50, 50, 1, 1, 0, 1, clickCooltime3/7, 0.3);

	renderer->DrawText(-25, 450, GLUT_STROKE_MONO_ROMAN, 0.0f, 0.0f, 1.0f, tempchar4);

	renderer->DrawText(-225, -430, GLUT_STROKE_MONO_ROMAN, 0.0f, 0.0f, 1.0f, tempchar);
	renderer->DrawText(-225, -460, GLUT_STROKE_MONO_ROMAN, 0.0f, 0.0f, 1.0f, tempchar2);
	renderer->DrawText(175, -450, GLUT_STROKE_MONO_ROMAN, 0.0f, 0.0f, 1.0f, tempchar3);
	
	renderer->DrawParticleClimate(0, 0, 0, 1, 1, 1, 1, 1, -0.1, -0.1, m_texParticle_Snow, snow_cooltime, LEVEL_GOD);
	renderer->DrawParticleClimate(0, 10, 0, 1, 1, 1, 1, 1, 0.1, -0.8, m_texParticle_Rain, snow_cooltime/1.5f, LEVEL_GOD);
	renderer->DrawParticleClimate(-100, -280, 0, 5, 1, 1, 1, 1, 0.1, -0.5, m_texParticle_Rain, snow_cooltime / 1.5f, LEVEL_GOD);
	renderer->DrawParticleClimate(120, 230, 0, 5, 1, 1, 1, 1, 0.1, -0.6, m_texParticle_Rain, snow_cooltime / 1.5f, LEVEL_GOD);

	float a = 1;
	for (int i = 0; i < push_count; ++i) {
		if (m_ob[i]->GetType() == OBJECT_BUILDING) {
			
			if (m_ob[i]->GetTeam() == TEAM_1) {
				renderer->DrawTexturedRect(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(), 1, 1, 1, a, m_texCharacter, m_ob[i]->GetLevel());
				renderer->DrawSolidRectGauge(m_ob[i]->GetPosX(), m_ob[i]->GetPosY() + (m_ob[i]->GetSize() / 2), m_ob[i]->GetPosZ(), 50, 10, 0, 0, 1, a, m_ob[i]->GetLife()/500, 0.3);
				
			}
			else {
				renderer->DrawTexturedRect(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(),1, 1, 1, a, m_texCharacter2, m_ob[i]->GetLevel());
				renderer->DrawSolidRectGauge(m_ob[i]->GetPosX(), m_ob[i]->GetPosY() + (m_ob[i]->GetSize() / 2), m_ob[i]->GetPosZ(), 50, 10, 1, 0, 0, a, m_ob[i]->GetLife() / 500, 0.3);
			}
		}
		else if(m_ob[i]->GetType() == OBJECT_CHARACTER){

			//renderer->SetSceneTransform(aniX_count, 0.0f, 2.0f, 1.0f);
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
		else if (m_ob[i]->GetType() == OBJECT_ARROW) {
			renderer->DrawSolidRect(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(), m_ob[i]->GetColorR(), m_ob[i]->GetColorG(), m_ob[i]->GetColorB(), 1, m_ob[i]->GetLevel());
		}
		else if (m_ob[i]->GetType() == OBJECT_ROBOT) {
			renderer->DrawTexturedRectSeq(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(), 1, 1, 1, a, m_textRobot01, m_ob[i]->GetXCount(), m_ob[i]->GetYCount(), m_ob[i]->GetAniWidth(), m_ob[i]->GetAniHeight(), m_ob[i]->GetLevel());
			renderer->DrawSolidRectGauge(m_ob[i]->GetPosX(), m_ob[i]->GetPosY() + (m_ob[i]->GetSize() / 2), m_ob[i]->GetPosZ(), 50, 10, 0, 0, 1, a, m_ob[i]->GetLife() / 50, 0.3);
		}
		else if(m_ob[i]->GetType() == OBJECT_BULLET){
			if(m_ob[i]->GetTeam()==TEAM_2)
				renderer->DrawParticle(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(), 1, 0, 0, 1,0.5f,0.3f, m_texParticle, m_ob[i]->GetElapsedTime(), LEVEL_GROUND);
			else
				renderer->DrawParticle(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(), 0, 0, 1, 1, -0.1f, -0.3f, m_texParticle, m_ob[i]->GetElapsedTime(), LEVEL_GROUND);
			//renderer->DrawSolidRect(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(), m_ob[i]->GetColorR(), m_ob[i]->GetColorG(), m_ob[i]->GetColorB(), 1, m_ob[i]->GetLevel());
		}
		else if (m_ob[i]->GetType() == OBJECT_TANK) {
			renderer->DrawTexturedRectSeq(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(), 1, 1, 1, a, m_textTank01, m_ob[i]->GetXCount(), m_ob[i]->GetYCount(), m_ob[i]->GetAniWidth(), m_ob[i]->GetAniHeight(), m_ob[i]->GetLevel());
			renderer->DrawSolidRectGauge(m_ob[i]->GetPosX(), m_ob[i]->GetPosY() + (m_ob[i]->GetSize() / 2), m_ob[i]->GetPosZ(), 50, 10, 0, 0, 1, a, m_ob[i]->GetLife() / 500, 0.3);
		}
		else if (m_ob[i]->GetType() == OBJECT_MISSILE) {
			renderer->DrawTexturedRectSeq(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), m_ob[i]->GetPosZ(), m_ob[i]->GetSize(), 1, 1, 1, a, m_textMissile01, m_ob[i]->GetXCount(), m_ob[i]->GetYCount(), m_ob[i]->GetAniWidth(), m_ob[i]->GetAniHeight(), m_ob[i]->GetLevel());
			renderer->DrawSolidRectGauge(m_ob[i]->GetPosX(), m_ob[i]->GetPosY() + (m_ob[i]->GetSize() / 2), m_ob[i]->GetPosZ(), 50, 10, 0, 0, 1, a, m_ob[i]->GetLife() / 100, 0.3);
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
			bool j = (m_ob[num]->GetType() == 1 && m_ob[i]->GetType() == 3);
			bool k = (m_ob[num]->GetType() == 2 && m_ob[i]->GetType() == 3);
			bool l = (m_ob[num]->GetType() == 1 && m_ob[i]->GetType() == 4);
			bool m = (m_ob[num]->GetType() == 2 && m_ob[i]->GetType() == 4);
			bool q = (m_ob[num]->GetType() == 5 && m_ob[i]->GetType() == 4);
			bool p = (m_ob[num]->GetType() == 5 && m_ob[i]->GetType() == 2);
			bool r = (m_ob[num]->GetType() == 5 && m_ob[i]->GetType() == 3); //로봇은 건물과 충돌하지 않는다.
			bool s = (m_ob[num]->GetType() == 6 && m_ob[i]->GetType() == 3);
			bool t = (m_ob[num]->GetType() == 6 && m_ob[i]->GetType() == 4);
			bool u = (m_ob[num]->GetType() == 6 && m_ob[i]->GetType() == 2);
			bool v = (m_ob[num]->GetType() == 7 && m_ob[i]->GetType() == 1);

			bool charvschar = (m_ob[num]->GetType() == 2 && m_ob[i]->GetType() == 2);
			bool o = m_ob[num]->GetTeam() != m_ob[i]->GetTeam();
			if (a&&b&&c&&d&&e&&o&&(g||k||m||j||l||q||p||r||s||t||u||v|| charvschar)) {
				
				collisionCount++;
				if (charvschar) {
					memset(m_ob[num], NULL, sizeof(Object));
					dead_ob[num] = 1;
					memset(m_ob[i], NULL, sizeof(Object));
					dead_ob[i] = 1;
				}
				if (s || t ) {//탱크는 활이나 총알을 맞아도 체력이 달지 않는다.
					m_ob[i]->SetLife(m_ob[num]->GetLife());
				}
				else {
					m_ob[num]->SetLife(m_ob[i]->GetLife());
					m_ob[i]->SetLife(m_ob[num]->GetLife());
				}
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
	
	if (m_ob[0]->GetLife() <= 0 && m_ob[1]->GetLife() <= 0 && m_ob[2]->GetLife() <= 0&&!you_Win) {
		you_Win = true;
		
		m_sound->PlaySound(winBG, true, 0.5f);
	}
	if (m_ob[3]->GetLife() <= 0 && m_ob[4]->GetLife() <= 0 && m_ob[5]->GetLife() <= 0&&!is_GameOver) {
		is_GameOver = true;
		
		m_sound->PlaySound(loseBG, true, 0.5f);
	}
	float elapsedTime = time / 1000.0f;
	for (int i = 0; i < push_count; ++i) {
		m_ob[i]->Cooltime(elapsedTime);
		m_ob[i]->Update(time);
		if (m_ob[i]->GetType() == 1 &&m_ob[i]->GetLife()>0) {
			if (m_ob[i]->GetLife() < 300.0f) { //체력이 300이하일 경우 총알 분배 속도 증가
				if (m_ob[i]->GetCoolTime() >= 0.5f) {
					AddActorObject(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), 3, i);
					m_ob[i]->ResetCoolTime();
				}
			}
			else {
				if (m_ob[i]->GetCoolTime() >= 2.0f) {
					AddActorObject(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), 3, i);
					m_ob[i]->ResetCoolTime();
				}
			}
		}
		if (m_ob[i]->GetType() == 2 && m_ob[i]->GetLife()>0) {
			//적군이 체력이 절반이하일 때, 속도가 점점 빨라지게 된다.
			if (m_ob[i]->GetLife() < 60.0f &&m_ob[i]->GetTeam()==TEAM_2) {
			}
			if (m_ob[i]->GetCoolTime() >= 3.0f) {
				AddActorObject(m_ob[i]->GetPosX(), m_ob[i]->GetPosY() , 4,i);
				m_ob[i]->ResetCoolTime();
			}
		}
		if (m_ob[i]->GetType() == 6 && m_ob[i]->GetLife()>0) {
			//적군이 체력이 절반이하일 때, 속도가 점점 빨라지게 된다.
			if (m_ob[i]->GetLife() < 60.0f &&m_ob[i]->GetTeam() == TEAM_2) {
			}
			if (m_ob[i]->GetCoolTime() >= 4.0f) {
				AddActorObject(m_ob[i]->GetPosX(), m_ob[i]->GetPosY(), OBJECT_MISSILE, i);
				m_ob[i]->ResetCoolTime();
			}
		}

		IsCollide(i);
		bool a = m_ob[i]->GetPosX() > 250 || m_ob[i]->GetPosX() < -250 || m_ob[i]->GetPosY() > 400 || m_ob[i]->GetPosY() < -400;
		bool b = m_ob[i]->GetType() != 2|| m_ob[i]->GetType() == 5;
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
	if(clickCooltime<=4.0f)
		clickCooltime = clickCooltime + elapsedTime;
	if(clickCooltime2<=2.0f)
		clickCooltime2 = clickCooltime2 + elapsedTime;
	if (clickCooltime3 <= 15.0f)
		clickCooltime3 = clickCooltime3 + elapsedTime;

	if (cooltime >= 3.0f) 
	{
		AddActorObject(rand() % 250, rand() % 400, 2, 0);
		AddActorObject(rand() % 250, rand() % 400, 2, 0);
		AddActorObject(rand() % 250, rand() % 400, 2, 0);

		cooltime = 0;
	}
}

float SceneMgr::GetCoolTime() {
	return clickCooltime;
}
float SceneMgr::GetCoolTime2() {
	return clickCooltime2;
}
float SceneMgr::GetCoolTime3() {
	return clickCooltime3;
}

void SceneMgr::ResetCoolTime() {
	clickCooltime = 0.0f;
}
void SceneMgr::ResetCoolTime2() {
	clickCooltime2 = 0.0f;
}
void SceneMgr::ResetCoolTime3() {
	clickCooltime3 = 0.0f;
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
		else if(o==5 ||o==6 || o == 7)
			m_ob[push_count] = new Object(a, b, o, TEAM_1);
		m_ob[push_count]->SetFollow(f);
		push_count++;
		return;
	}
	else if (push_count >= MAX_OBJECTS_COUNT) {
		for (int i = 6; i < MAX_OBJECTS_COUNT; ++i) {
			if (dead_ob[i] == 1) {
				if (o == 1) 
				{
					if (b<0)
						m_ob[i] = new Object(a, b, o, TEAM_1);
					else
						m_ob[i] = new Object(a, b, o, TEAM_2);
				}
				else if (o == 2){
					if (b<0)
						m_ob[i] = new Object(a, b, o, TEAM_1);
					else
						m_ob[i] = new Object(a, b, o, TEAM_2);
				
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
				else if (o == 5 || o == 6 || o == 7) {
					m_ob[i] = new Object(a, b, o,TEAM_1);
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