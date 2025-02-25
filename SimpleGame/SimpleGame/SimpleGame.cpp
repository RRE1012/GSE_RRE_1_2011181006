/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"

#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Renderer.h"
#include "Sound.h"


SceneMgr *s_Mgr=NULL; //포인터 NULL값으로 초기화 반드시 할 것


bool g_LButtonDown = false;
bool g_RButtonDown = false;
DWORD g_prevTime = 0;


void RenderScene(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	
	// Renderer Test
	

	
	DWORD currTime = GetTickCount();
	DWORD elapsedTime = currTime - g_prevTime;
	s_Mgr->DrawObject(elapsedTime);
	g_prevTime = currTime; //현재 elapse된 시간을 다시 갱신
//2017.09->	g_Renderer->DrawSolidRect(s_Mgr.GetObject0(i).GetPosX(), s_Mgr.GetObject0(i).GetPosY(), s_Mgr.GetObject0(i).GetPosZ(), s_Mgr.GetObject0(i).GetSize(), s_Mgr.GetObject0(i).GetColorR(), s_Mgr.GetObject0(i).GetColorG(), s_Mgr.GetObject0(i).GetColorB(), 1);
	s_Mgr->UpdateObj(elapsedTime);
	s_Mgr->MakeObj(elapsedTime);
	glutSwapBuffers();
}
int tempcount = 0;
void Loop(int state) {
	
	tempcount=(tempcount+1)%500;
	if (tempcount % 100 == 0)
		printf("life :%f\n",s_Mgr->GetObject0(0).GetLife());
	glutTimerFunc(1, Loop, 0);

}

void Idle(void)
{
	RenderScene();
}


//button
//GLUT_LEFT_BUTTON,GLUT_MIDDLE_BUTTON,GLUT_RIGHT_BUTTON
//state
//GLUT_UP,GLUT_DOWN
void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		g_LButtonDown = true;

	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		//특정 위치에 마우스 클릭 시 아군 생성
		if (g_LButtonDown) {
			if(y>WINSIZEY/2)
			{
				if (y > 650 && s_Mgr->GetCoolTime() >= 2.0f) {
					s_Mgr->AddActorObject(x - (WINSIZEX / 2), -(y - (WINSIZEY / 2)), OBJECT_CHARACTER, 0);
					s_Mgr->ResetCoolTime();
				}
				else if (y <= 650 && s_Mgr->GetCoolTime2() >= 1.0f) {
					s_Mgr->AddActorObject(x - (WINSIZEX / 2), -(y - (WINSIZEY / 2)), OBJECT_ROBOT, 0);
					s_Mgr->ResetCoolTime2();
				}
			}
			
			//obj.SetPos(x-250, -(y-250), obj.GetPosZ());
			printf("x : %d\ny : %d\n", x,y);
			g_LButtonDown = false;
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		g_RButtonDown = true;
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		//특정 위치에 마우스 클릭 시 아군 생성
		if (g_RButtonDown) {
			if (y>(WINSIZEY / 2)&& s_Mgr->GetCoolTime3() >= 7.0f)
			{
				if (x - (WINSIZEX / 2)>0)
					s_Mgr->AddActorObject(x - (WINSIZEX / 2), -(y - (WINSIZEY / 2)), OBJECT_TANK, 0);
				else
					s_Mgr->AddActorObject(x - (WINSIZEX / 2), -(y - (WINSIZEY / 2)), OBJECT_TANK, 0);
				s_Mgr->ResetCoolTime3();
			}

			//obj.SetPos(x-250, -(y-250), obj.GetPosZ());
			printf("x : %d\ny : %d\n", x, y);
			g_LButtonDown = false;
		}
	}
	//MouseOnOff(button, state, x, y);
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINSIZEX, WINSIZEY);
	glutCreateWindow("Game Software Engineering KPU");
	
	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}
	
	s_Mgr = new SceneMgr();
	s_Mgr->AddActorObject(150,320, OBJECT_BUILDING,0);
	s_Mgr->AddActorObject(0, 350, OBJECT_BUILDING, 0);
	s_Mgr->AddActorObject(-150, 320, OBJECT_BUILDING, 0);
	s_Mgr->AddActorObject(150, -320, OBJECT_BUILDING, 0);
	s_Mgr->AddActorObject(0, -350, OBJECT_BUILDING, 0);
	s_Mgr->AddActorObject(-150, -320, OBJECT_BUILDING, 0);

	
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	g_prevTime = GetTickCount();
	glutMainLoop();
	
	//delete g_Renderer;
	delete s_Mgr;
    return 0;
}

