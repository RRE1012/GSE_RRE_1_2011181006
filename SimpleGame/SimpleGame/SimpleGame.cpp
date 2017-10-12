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

Renderer *g_Renderer = NULL;
Object obj;
Object obj2(5.0f, 2.0f, 1.0f, 15, 0.9f);
bool g_LButtonDown = false;
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	g_Renderer->DrawSolidRect(0, 0, 0, 4, 1, 0, 1, 1);
	g_Renderer->DrawSolidRect(obj.GetPosX(), obj.GetPosY(), obj.GetPosZ(), obj.GetSize(), 1, 0.4f, 0, 1);
	g_Renderer->DrawSolidRect(obj2.GetPosX(), obj2.GetPosY(), obj2.GetPosZ(), obj2.GetSize(), 1, 1, 0, 1);
	
	glutSwapBuffers();
}
void Loop(int state) {
	obj.Update();
	obj2.Update();
	glutTimerFunc(1, Loop, 0);

}

void Idle(void)
{
	RenderScene();
	
	//glutTimerFunc(20, obj2.Update, 0);
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
		if (g_LButtonDown) {
			obj.SetPos(x-250, -(y-250), obj.GetPosZ());
			printf("x : %d\ny : %d\n", x,y);
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
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");
	Loop(1);
	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;

    return 0;
}

