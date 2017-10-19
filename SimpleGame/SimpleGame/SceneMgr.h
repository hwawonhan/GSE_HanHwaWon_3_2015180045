#pragma once
#include "Object.h"
#include "Renderer.h"

#define MAX_OBJECTS_COUNT 50

class SceneMgr
{
	Object* m_objects[MAX_OBJECTS_COUNT];
	int m_objectsCount;
public:
	SceneMgr();
	Object** GetObjects();
	void DrawAllObjects(Renderer* m_Renderer);
	void Update();
	void setobjectCount(int n);
	void Addobject(int x, int y);
	int getobjectsCount();
	~SceneMgr();
};

