#pragma once
#include "Object.h"
#include "Renderer.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Sound.h"
#include <list>

using namespace std;
#define MAX_OBJECTS_COUNT 26
#define MAX_OBJECTS_CHARACTER_COUNT 10
#define MAX_BULLET_COUNT 200



class Renderer;
class SceneMgr
{
private:
	Renderer* m_Renderer;
	Sound* m_Sound;
	int BGsound;
	int Shootsound;
	int Bulidingsound;
	float BuildingTime;
	float EnemySpawnTime;
	float ParticleTime;
	unsigned int m_texEnemyBuilding;
	unsigned int m_texEnemyCharacter;
	unsigned int m_texPlayerBuilding;
	unsigned int m_texPlayerCharacter;
	unsigned int m_texBackGround;
	unsigned int m_texParticle;

	int PlayerCharacterSpawnCount;
	float PlayerCharacterSpawnTime;
public:
	Object* m_objects[MAX_OBJECTS_COUNT];
	Object* Bullet[MAX_BULLET_COUNT];
public:
	SceneMgr();
	SceneMgr(int w, int h);
	void Init();
	void CreateBuliding();
	Object** GetObjects();
	void DrawAllObjects();
	void Update(float time);
	void Colistion();
	BOOL ObjectsColistion(Object* a, Object* b);
	void Addobject(int x, int y);
	~SceneMgr();
};

