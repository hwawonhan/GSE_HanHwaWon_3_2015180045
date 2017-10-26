#pragma once
#include "Object.h"
#include "Renderer.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#define MAX_OBJECTS_COUNT 10

class Renderer;

class SceneMgr
{
private:
	Renderer* m_Renderer;
public:
	Object* m_objects[MAX_OBJECTS_COUNT];
public:
	SceneMgr();
	SceneMgr(int w, int h);
	Object** GetObjects();
	void DrawAllObjects();
	void Update(float time);
	void BoxColistion();
	void Addobject(int x, int y);
	~SceneMgr();
};

