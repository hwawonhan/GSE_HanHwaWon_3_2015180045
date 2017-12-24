/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "SceneMgr.h"

SceneMgr* g_SceneMgr = NULL;
Renderer* g_renderer = NULL;
DWORD timer = timeGetTime();
float t = 0;
unsigned int texloading;
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	DWORD p = timeGetTime() - timer;
	timer = timeGetTime();
	if (g_SceneMgr != NULL)
	{
		g_SceneMgr->DrawAllObjects();
		g_SceneMgr->Update((float)(p / 1000.0f));
	}
	else
	{
		t += (p / 1000.0f);
		g_renderer->DrawTexturedRect(0, 0, 0, 800, 1, 1, 1, 1, texloading, 0.1);
		if (t > 3.0f)
		{
			delete g_renderer;
			g_renderer = NULL;
			g_SceneMgr = new SceneMgr(500, 800);
		}
	}
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)			//GLUT_LEFT_BUTTON, GLUT_DOWN, 
{
	if (g_SceneMgr != NULL)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			if (state == GLUT_UP)
			{
				g_SceneMgr->Addobject(x - 250, 400 - y);
			}
		}
	}
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	if (g_SceneMgr != NULL)
	{
		switch (key)
		{
		case 'q':
			g_SceneMgr->PlayerCharSelect = 0;
			break;
		case 'w':
			g_SceneMgr->PlayerCharSelect = 1;
			break;
		default:
			break;
		}
	}
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
	glutInitWindowSize(500, 800);
	glutCreateWindow("Game Software Engineering KPU 2015180045");
	glewInit();
	g_renderer = new Renderer(500, 800);
	texloading = g_renderer->CreatePngTexture("./Textures/PNGs/loading.png");
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}


	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	return 0;
}

