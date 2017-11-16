#pragma once
#include "Object.h"
#include "Renderer.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include <list>

using namespace std;
#define MAX_OBJECTS_COUNT 26
#define MAX_OBJECTS_CHARACTER_COUNT 10
#define MAX_BULLET_COUNT 200

enum TEAMNUMBER
{
	BLACK = 0,
	WHITE = 1
};

enum objecttype {
	OBJECT_BUILDING,
	OBJECT_CHARACTER,
	OBJECT_BULLET,
	OBJECT_ARROW,
};

class Renderer;

class SceneMgr
{
private:
	Renderer* m_Renderer;
	float BuildingTimeCount;
	float EnemySpawnTimeCount;
	float ArrowSpawnTimeCount;
	unsigned int m_texEnemy;
	unsigned int m_texCharacter;
public:
	Object* m_objects[MAX_OBJECTS_COUNT];
	Object* Bullet[MAX_BULLET_COUNT];
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

