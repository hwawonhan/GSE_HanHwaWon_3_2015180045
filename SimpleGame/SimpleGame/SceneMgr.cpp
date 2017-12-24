#include "stdafx.h"
#include "SceneMgr.h"
#include <cmath>
SceneMgr::SceneMgr()
{
	m_Renderer = new Renderer(500, 800);
	Init();
}

SceneMgr::SceneMgr(int w, int h)
{
	m_Renderer = new Renderer(w, h);
	Init();
}

void SceneMgr::Init()
{
	m_Sound = new Sound();
	BGsound = m_Sound->CreateSound("./Sounds/111.mp3");
	Shootsound = m_Sound->CreateSound("./Sounds/Shot.wav");
	Bulidingsound = m_Sound->CreateSound("./Sounds/crush.wav");
	m_Sound->PlaySound(BGsound, true, 0.2f);
	if (!m_Renderer->IsInitialized())
	{
		cout << "Renderer could not be initialized.. \n";
	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = NULL;
	for (int i = 0; i < MAX_BULLET_COUNT; ++i)
		Bullet[i] = NULL;

	m_texPlayerBuilding = m_Renderer->CreatePngTexture("./Textures/PNGs/PlayerBuilding.png");
	m_texEnemyBuilding = m_Renderer->CreatePngTexture("./Textures/PNGs/EnemyBuliding.png");
	m_texBackGround = m_Renderer->CreatePngTexture("./Textures/PNGs/Background.png");
	m_texPlayerCharacter = m_Renderer->CreatePngTexture("./Textures/PNGs/Character.png");
	m_texParticle = m_Renderer->CreatePngTexture("./Textures/PNGs/CircleParticle.png");
	m_texSkill = m_Renderer->CreatePngTexture("./Textures/PNGs/skill_1.png");
	m_texSkillPoint = m_Renderer->CreatePngTexture("./Textures/PNGs/ellicsur.png");
	CreateBuliding();

	BuildingTime = 0;
	ParticleTime = 0;
	UiTime = 0;
	PlayerCharSelect = 0;
	skillpointguage = 0;
	skillpoint = 0;
	uisill = 0;
}

void SceneMgr::CreateBuliding()
{
	m_objects[0] = new Object(-160, 230, 0, OBJECT_BUILDING);
	m_objects[0]->setSize(80);
	m_objects[0]->setDirection(0, 0, 0);
	if (m_objects[0] != NULL)
		m_objects[0]->setColor(1, 1, 1, 1);
	m_objects[0]->setSpeed(0);
	m_objects[0]->setLife(500);
	m_objects[0]->TeamNum = BLACK;

	m_objects[1] = new Object(0, 300, 0, OBJECT_BUILDING);
	m_objects[1]->setSize(90);
	m_objects[1]->setDirection(0, 0, 0);
	if (m_objects[1] != NULL)
		m_objects[1]->setColor(1, 1, 1, 1);
	m_objects[1]->setSpeed(0);
	m_objects[1]->setLife(500);
	m_objects[1]->TeamNum = BLACK;

	m_objects[2] = new Object(155, 230, 0, OBJECT_BUILDING);
	m_objects[2]->setSize(80);
	m_objects[2]->setDirection(0, 0, 0);
	if (m_objects[2] != NULL)
		m_objects[2]->setColor(1, 1, 1, 1);
	m_objects[2]->setSpeed(0);
	m_objects[2]->setLife(500);
	m_objects[2]->TeamNum = BLACK;

	
	m_objects[3] = new Object(-160, -200, 0, OBJECT_BUILDING);
	m_objects[3]->setSize(80);
	m_objects[3]->setDirection(0, 0, 0);
	if (m_objects[3] != NULL)
		m_objects[3]->setColor(1, 1, 1, 1);
	m_objects[3]->setSpeed(0);
	m_objects[3]->setLife(500);
	m_objects[3]->TeamNum = WHITE;

	m_objects[4] = new Object(-2, -270, 0, OBJECT_BUILDING);
	m_objects[4]->setSize(90);
	m_objects[4]->setDirection(0, 0, 0);
	if (m_objects[4] != NULL)
		m_objects[4]->setColor(1, 1, 1, 1);
	m_objects[4]->setSpeed(0);
	m_objects[4]->setLife(500);
	m_objects[4]->TeamNum = WHITE;

	m_objects[5] = new Object(155, -200, 0, OBJECT_BUILDING);
	m_objects[5]->setSize(80);
	m_objects[5]->setDirection(0, 0, 0);
	if (m_objects[5] != NULL)
		m_objects[5]->setColor(1, 1, 1, 1);
	m_objects[5]->setSpeed(0);
	m_objects[5]->setLife(500);
	m_objects[5]->TeamNum = WHITE;

	
}



Object** SceneMgr::GetObjects()
{
	return m_objects;
}

void SceneMgr::DrawAllObjects()
{
	m_Renderer->DrawTexturedRect(0, 0, 0, 800,1.0f, 1.0f, 1.0f, 1.0f, m_texBackGround, 0.9f);
	m_Renderer->DrawParticleClimate(0, 0, 0, 0.9f, 1, 1, 1, 0.5f, -1, -1, m_texParticle, ParticleTime, 0.01f);
	m_Renderer->DrawSolidRectGauge(-25, -350, 0, 300, 10, 1.0f, 0.0f, 1.0f, 1.0f, skillpointguage, 0.9f);
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			if (m_objects[i]->type == OBJECT_BUILDING)
			{
				if (m_objects[i]->TeamNum == BLACK)
				{
					m_Renderer->DrawTexturedRect(m_objects[i]->m.x, m_objects[i]->m.y, m_objects[i]->m.z, m_objects[i]->size,
						m_objects[i]->color.r, m_objects[i]->color.g, m_objects[i]->color.b, 1.0f, m_texEnemyBuilding, 0.1f);
					m_Renderer->DrawSolidRectGauge(m_objects[i]->m.x, m_objects[i]->m.y + m_objects[i]->size / 2 + 5, m_objects[i]->m.z, m_objects[i]->size, 5, 1, 0, 0, 1, m_objects[i]->life / 500.0f, 0.1f);
				}
				else
				{
					m_Renderer->DrawTexturedRect(m_objects[i]->m.x, m_objects[i]->m.y, m_objects[i]->m.z, m_objects[i]->size,
						m_objects[i]->color.r, m_objects[i]->color.g, m_objects[i]->color.b, 1.0f, m_texPlayerBuilding, 0.1f);
					m_Renderer->DrawSolidRectGauge(m_objects[i]->m.x, m_objects[i]->m.y + m_objects[i]->size / 2 + 5, m_objects[i]->m.z, m_objects[i]->size, 5, 0, 0, 1, 1, m_objects[i]->life / 500.0f, 0.1f);
				}
			}
			else
			{
				if (m_objects[i]->TeamNum == BLACK)
				{
					m_Renderer->DrawTexturedRectSeq(m_objects[i]->m.x, m_objects[i]->m.y, m_objects[i]->m.z, m_objects[i]->size,
						m_objects[i]->color.r, m_objects[i]->color.g, m_objects[i]->color.b, m_objects[i]->color.a, m_texPlayerCharacter, m_objects[i]->AnimationCount % 5, 1, 5, 2, 0.2f);
				}
				else
				{
					m_Renderer->DrawTexturedRectSeq(m_objects[i]->m.x, m_objects[i]->m.y, m_objects[i]->m.z, m_objects[i]->size,
						m_objects[i]->color.r, m_objects[i]->color.g, m_objects[i]->color.b, m_objects[i]->color.a, m_texPlayerCharacter, m_objects[i]->AnimationCount % 5, 0, 5, 2, 0.2f);
				}
				m_Renderer->DrawSolidRectGauge(m_objects[i]->m.x, m_objects[i]->m.y + 20, m_objects[i]->m.z, 30, 5,
					m_objects[i]->color.r, m_objects[i]->color.g, m_objects[i]->color.b, m_objects[i]->color.a, m_objects[i]->life / 10.0f, 0.2f);
			}
		}
	}

	//총알
	for (int i = 0; i < MAX_BULLET_COUNT; ++i)
	{
		if (Bullet[i] != NULL)
		{
			if (Bullet[i]->type == OBJECT_BULLET)
			{
				if (Bullet[i]->TeamNum == WHITE)
				{
					m_Renderer->DrawParticle(Bullet[i]->m.x, Bullet[i]->m.y, Bullet[i]->m.z, Bullet[i]->size,
						0.2f, 0.8f, Bullet[i]->color.b, Bullet[i]->color.a, -Bullet[i]->Direction.x, -Bullet[i]->Direction.y, m_texParticle, Bullet[i]->particletime, 0.3f);
					m_Renderer->DrawSolidRect(Bullet[i]->m.x, Bullet[i]->m.y, Bullet[i]->m.z, Bullet[i]->size,
						Bullet[i]->color.r, Bullet[i]->color.g, Bullet[i]->color.b, 1.0f, 0.3f);
				}
				else
				{
					m_Renderer->DrawParticle(Bullet[i]->m.x, Bullet[i]->m.y, Bullet[i]->m.z, Bullet[i]->size,
						Bullet[i]->color.r, 0.2, 0.8f , Bullet[i]->color.a, -Bullet[i]->Direction.x, -Bullet[i]->Direction.y, m_texParticle, Bullet[i]->particletime, 0.3f);
					m_Renderer->DrawSolidRect(Bullet[i]->m.x, Bullet[i]->m.y, Bullet[i]->m.z, Bullet[i]->size,
						Bullet[i]->color.r, Bullet[i]->color.g, Bullet[i]->color.b, 1.0f, 0.3f);
				}
			}
			else if(Bullet[i]->type == OBJECT_ARROW)
			{
				m_Renderer->DrawSolidRect(Bullet[i]->m.x, Bullet[i]->m.y, Bullet[i]->m.z, Bullet[i]->size,
					Bullet[i]->color.r, Bullet[i]->color.g, Bullet[i]->color.b, Bullet[i]->color.a, 0.3f);
			}
			else if (Bullet[i]->type == OBJECT_SKILL)
			{
				m_Renderer->DrawSolidRect(Bullet[i]->m.x, Bullet[i]->m.y, Bullet[i]->m.z, Bullet[i]->size,
					0.5f, 0.5f, 1.0f, 0.5f, 0.2f);
				m_Renderer->DrawTexturedRectSeq(Bullet[i]->m.x, Bullet[i]->m.y, Bullet[i]->m.z, Bullet[i]->size *1.5,
					1.0f,1.0f,1.0f,1.0f, m_texSkill, Bullet[i]->AnimationCount % 5, 2, 5, 5, 0.2f);
			}
		}
	}

	m_Renderer->DrawTexturedRect(-200, -350, 0, 50, 1.0f, 1.0f, 1.0f, 1.0f, m_texSkillPoint, 0.01f);
	char buf[10];
	sprintf_s(buf,"%d",skillpoint);
	m_Renderer->DrawText(-200, -350, GLUT_BITMAP_9_BY_15, 0.0f, 0.0f, 0.0f, buf);
	switch (PlayerCharSelect)
	{
	case 0:
		m_Renderer->DrawSolidRect(200, -350, 0, 50,
			1.0f, 1.0f, 1.0f, 0.5f, 0.01f);
		m_Renderer->DrawTexturedRectSeq(200, -350, 0, 50,
			1.0f, 1.0f, 1.0f, 1.0f, m_texPlayerCharacter, uisill%3, 2, 5, 2, 0.01f);
		break;
	case 1:
		m_Renderer->DrawSolidRect(200, -350, 0, 50,
			1.0f, 1.0f, 1.0f, 0.5f, 0.01f);
		m_Renderer->DrawTexturedRectSeq(200, -350, 0, 50*1.5,
			1.0f, 1.0f, 1.0f, 1.0f, m_texSkill, uisill%5, 2, 5, 5, 0.01f);
		break;
	default:
		break;
	}
}
void SceneMgr::Update(float time)
{
	UiTime += time;
	if (UiTime > 0.1f)
	{
		uisill += 1;
		UiTime = 0;
	}
	ParticleTime += time;
	//객체업데이트
	skillpointguage += time;
	if (skillpointguage > 1.0f)
	{
		if (skillpoint < 10)
		{
			skillpointguage = 0;
			skillpoint += 1;
		}
	}


	//캐릭터 빌딩 업데이트
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
			m_objects[i]->Update(time);
	}
	//총알 업데이트
	for (int i = 0; i < MAX_BULLET_COUNT; ++i)
	{
		if (Bullet[i] != NULL)
			Bullet[i]->Update(time);
	}

	//캐릭터 life에 의한 삭제
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			if (m_objects[i]->life < 0)
			{
				if (m_objects[i]->type == OBJECT_BUILDING)
				{
					m_Sound->PlaySound(Bulidingsound, false, 0.1f);
				}
				delete m_objects[i];
				m_objects[i] = NULL;
			}
		}
	}

	//캐릭터 lifetime에 의한 삭제
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			if (m_objects[i]->type != OBJECT_BUILDING)
			{
				if (m_objects[i]->getlifetime() < 0)
				{
					delete m_objects[i];
					m_objects[i] = NULL;
				}
			}
		}
	}


	//총알 lifetime 삭제
	for (int i = 0; i < MAX_BULLET_COUNT; ++i)
	{
		if (Bullet[i] != NULL)
		{
			if (Bullet[i]->getlifetime() < 0)
			{
				delete Bullet[i];
				Bullet[i] = NULL;
			}
		}
	}

	//빌딩총알생성
	BuildingTime += time;
	if (BuildingTime > 2.0f)
	{
		for (int j = 0; j < MAX_OBJECTS_COUNT; ++j)
		{
			if (m_objects[j] != NULL)
			{
				for (int i = 0; i < MAX_BULLET_COUNT; ++i)
				{
					if (Bullet[i] == NULL)
					{
						if (m_objects[j]->type == OBJECT_BUILDING)
						{
							m_Sound->PlaySound(Shootsound, false, 0.01f);
							if (m_objects[j]->TeamNum == BLACK)
							{
								Bullet[i] = new Object(m_objects[j]->m.x, m_objects[j]->m.y, m_objects[j]->m.z, OBJECT_BULLET);
								if (Bullet[i] != NULL)
									Bullet[i]->setColor(1, 0, 0, 1);
								Bullet[i]->setSize(5);
								Bullet[i]->setDirection(0, 0, 0);
								for (int k = 0; k < MAX_OBJECTS_COUNT; ++k)
								{
									if (m_objects[k] != NULL)
									{
										if (m_objects[k]->type == OBJECT_CHARACTER && m_objects[k]->TeamNum == WHITE)
										{
											float temp = sqrt(m_objects[k]->m.x - m_objects[j]->m.x*m_objects[k]->m.x - m_objects[j]->m.x + m_objects[k]->m.y - m_objects[j]->m.y*m_objects[k]->m.y - m_objects[j]->m.y);
											Bullet[i]->setDirection((m_objects[k]->m.x - m_objects[j]->m.x) / temp, (m_objects[k]->m.y - m_objects[j]->m.y) / temp, 0);
											break;
										}
									}
								}
								if(Bullet[i]->Direction.x ==0 && Bullet[i]->Direction.y == 0)
									Bullet[i]->setDirection((rand() % 3) - 1, -1, 0);
								Bullet[i]->setSpeed(100);
								Bullet[i]->life = 15;
								Bullet[i]->lifetime = 15;
								Bullet[i]->TeamNum = BLACK;
								Bullet[i]->setParticleLifeTime(0);
								Bullet[i]->disapearPoint = true;
								Bullet[i]->Damage = m_objects[j]->life;
							}
							else if (m_objects[j]->TeamNum == WHITE)
							{
								Bullet[i] = new Object(m_objects[j]->m.x, m_objects[j]->m.y, m_objects[j]->m.z, OBJECT_BULLET);
								if (Bullet[i] != NULL)
									Bullet[i]->setColor(0, 0, 1, 1);
								Bullet[i]->setSize(5);
								Bullet[i]->setDirection(0, 0, 0);
								for (int k = 0; k < MAX_OBJECTS_COUNT; ++k)
								{
									if (m_objects[k] != NULL)
									{
										if (m_objects[k]->type == OBJECT_CHARACTER && m_objects[k]->TeamNum == BLACK)
										{
											float temp = sqrt(m_objects[k]->m.x - m_objects[j]->m.x*m_objects[k]->m.x - m_objects[j]->m.x + m_objects[k]->m.y - m_objects[j]->m.y*m_objects[k]->m.y - m_objects[j]->m.y);
											Bullet[i]->setDirection((m_objects[k]->m.x - m_objects[j]->m.x) / temp, (m_objects[k]->m.y - m_objects[j]->m.y) / temp, 0);
											break;
										}
									}
								}
								if (Bullet[i]->Direction.x == 0 && Bullet[i]->Direction.y == 0)
									Bullet[i]->setDirection((rand() % 3) - 1, 1, 0);
								Bullet[i]->setSpeed(100);
								Bullet[i]->life = 15;
								Bullet[i]->lifetime = 15;
								Bullet[i]->TeamNum = WHITE;
								Bullet[i]->disapearPoint = true;
								Bullet[i]->setParticleLifeTime(0);
								Bullet[i]->Damage = m_objects[j]->life;
							}
						}
						break;
					}
				}
			}
		}
		BuildingTime = 0;
	}

	//적생성
	EnemySpawnTime += time;
	if (EnemySpawnTime > 1.0f)
	{
		int temp = 0;
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		{
			if (m_objects[i] != NULL)
			{
				if (m_objects[i]->type == OBJECT_CHARACTER)
				{
					if (m_objects[i]->TeamNum == BLACK)
					{
						temp++;
					}
				}
			}
		}
		if (temp < 10)
		{
			for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
			{
				if (m_objects[i] == NULL)
				{
					m_objects[i] = new Object((rand() % 500) - 250, 400 - (rand() % 400), 0, OBJECT_CHARACTER);
					m_objects[i]->setSize(30);
					int cnt = 0;
					for (int j = 0; j < MAX_OBJECTS_COUNT; ++j)
					{
						if (m_objects[j] != NULL)
						{
							if (m_objects[j]->type == OBJECT_BUILDING && m_objects[j]->TeamNum == WHITE)
							{
								float temp = sqrt(m_objects[j]->m.x - m_objects[i]->m.x*m_objects[j]->m.x - m_objects[i]->m.x + m_objects[j]->m.y - m_objects[i]->m.y*m_objects[j]->m.y - m_objects[i]->m.y);
								m_objects[i]->setDirection((m_objects[j]->m.x - m_objects[i]->m.x) / temp, (m_objects[j]->m.y - m_objects[i]->m.y) / temp, 0);
								break;
							}
							else
								cnt++;
						}
						else
						{
							cnt++;
						}
					}
					if(cnt > MAX_OBJECTS_COUNT - 3)
						m_objects[i]->setDirection((rand() % 3) - 1, -1, 0);
					if (m_objects[i] != NULL)
						m_objects[i]->setColor(1, 0, 0, 1);
					m_objects[i]->setSpeed(100);
					m_objects[i]->life = 25;
					m_objects[i]->TeamNum = BLACK;
					break;
				}
			}
			EnemySpawnTime = 0;
		}
	}

	//화살 생성
	for (int j = 0; j < MAX_OBJECTS_COUNT; ++j)
	{
		if (m_objects[j] != NULL && m_objects[j]->type == OBJECT_CHARACTER)
		{
			if (m_objects[j]->ArrowSpawnTime > 0.5f)
			{
				for (int i = 0; i < MAX_BULLET_COUNT; ++i)
				{
					if (Bullet[i] == NULL)
					{
						if (m_objects[j]->TeamNum == WHITE)
						{
							Bullet[i] = new Object(m_objects[j]->m.x - 10, m_objects[j]->m.y - 10, 0, OBJECT_ARROW);
							if (Bullet[i] != NULL)
								Bullet[i]->setColor(1, 1, 0, 1);
							Bullet[i]->setSize(5);
							Bullet[i]->setDirection((rand() % 3) - 1, 1, 0);
							Bullet[i]->setSpeed(100);
							Bullet[i]->lifetime = 10;
							Bullet[i]->life = 10;
							Bullet[i]->Damage = m_objects[j]->life;
							Bullet[i]->TeamNum = WHITE;
							m_objects[j]->ArrowSpawnTime = 0;
							break;
						}
						else if (m_objects[j]->TeamNum == BLACK)
						{
							Bullet[i] = new Object(m_objects[j]->m.x - 10, m_objects[j]->m.y - 10, 0, OBJECT_ARROW);
							if (Bullet[i] != NULL)
								Bullet[i]->setColor(0.5f, 0.2f, 0.7f, 1.0f);
							Bullet[i]->setSize(5);
							Bullet[i]->setDirection((rand() % 3) - 1, -1, 0);
							Bullet[i]->setSpeed(100);
							Bullet[i]->lifetime = 10;
							Bullet[i]->life = 10;
							Bullet[i]->Damage = m_objects[j]->life;
							Bullet[i]->TeamNum = BLACK;
							m_objects[j]->ArrowSpawnTime = 0;
							break;
						}
					}
				}
			}
		}
	}


	//화면에서 넘어갈 시 Bullet, Arrow 삭제
	for (int i = 0; i < MAX_BULLET_COUNT; ++i)
	{
		if (Bullet[i] != NULL)
		{
			if( (Bullet[i]->m.y + (Bullet[i]->size / 2) > 400 || Bullet[i]->m.y - (Bullet[i]->size / 2) < -400) || (Bullet[i]->m.x + (Bullet[i]->size / 2) > 250 || Bullet[i]->m.x - (Bullet[i]->size / 2) < -250))
			{
				delete Bullet[i];
				Bullet[i] = NULL;
			}
		}
	}
	Colistion();
}


void SceneMgr::Colistion()
{
	//Character <-> Buliding Collision
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		for (int j = 0; j < MAX_OBJECTS_COUNT; ++j)
		{
			if (i != j && m_objects[i] != NULL && m_objects[j] != NULL)
			{
				if(m_objects[j]->type == OBJECT_BUILDING && m_objects[i]->type == OBJECT_CHARACTER)
				{
					if ((m_objects[j]->TeamNum == BLACK && m_objects[i]->TeamNum == WHITE) || (m_objects[j]->TeamNum == WHITE && m_objects[i]->TeamNum == BLACK))
					{
						if (ObjectsColistion(m_objects[i], m_objects[j]))
						{
							m_objects[j]->life -= m_objects[i]->life;
							delete m_objects[i];
							m_objects[i] = NULL;
							if (m_objects[j] != NULL)
							{
								if(m_objects[j]->TeamNum == BLACK)
									m_objects[j]->setColor(1.0f, 0.0f, 0.0f, 1.0f);
								else
									m_objects[j]->setColor(0.0f, 0.0f, 1.0f, 1.0f);
							}
							break;
						}
						else
						{
							if(m_objects[j]!=NULL)
								m_objects[j]->setColor(1.0f, 1.0f, 1.0f, 1.0f);
						}
					}
				}
			}
			else
			{
				if (m_objects[j] != NULL)
					if (m_objects[j]->type == OBJECT_BUILDING)
						m_objects[j]->setColor(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
	}

	//Bullet <-> Charater Collision
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		for (int j = 0; j < MAX_BULLET_COUNT; ++j)
		{
			if (i != j && m_objects[i] != NULL && Bullet[j] != NULL)
			{
				if (m_objects[i]->type == OBJECT_CHARACTER && Bullet[j]->type == OBJECT_BULLET)
				{
					if ((m_objects[i]->TeamNum == BLACK && Bullet[j]->TeamNum == WHITE) || (m_objects[i]->TeamNum == WHITE && Bullet[j]->TeamNum == BLACK))
					{
						if (ObjectsColistion(m_objects[i], Bullet[j]))
						{
							m_objects[i]->life -= Bullet[j]->life;
							delete Bullet[j];
							Bullet[j] = NULL;
							break;
						}
						
					}
				}
			}
		}
	}

	//Bullet <-> Building Collision
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		for (int j = 0; j < MAX_BULLET_COUNT; ++j)
		{
			if (i != j && m_objects[i] != NULL && Bullet[j] != NULL)
			{
				if (m_objects[i]->type == OBJECT_BUILDING && Bullet[j]->type == OBJECT_BULLET)
				{
					if ((m_objects[i]->TeamNum == BLACK && Bullet[j]->TeamNum == WHITE) || (m_objects[i]->TeamNum == WHITE && Bullet[j]->TeamNum == BLACK))
					{
						if (ObjectsColistion(m_objects[i], Bullet[j]))
						{
							m_objects[i]->life -= Bullet[j]->life;
							delete Bullet[j];
							Bullet[j] = NULL;
							if (m_objects[i] != NULL)
							{
								if(m_objects[i]->TeamNum == BLACK)
									m_objects[i]->setColor(1.0f, 0.0f, 0.0f, 1.0f);
								else
									m_objects[i]->setColor(0.0f, 0.0f, 1.0f, 1.0f);
							}
							break;
						}
						else
						{
							if (m_objects[i] != NULL)
								m_objects[i]->setColor(1.0f, 1.0f, 1.0f, 1.0f);
						}
					}
				}
			}
			else
			{
				if (m_objects[i] != NULL)
					if (m_objects[i]->type == OBJECT_BUILDING)
						m_objects[i]->setColor(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
	}

	//Arrow <-> Charater Collision
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		for (int j = 0; j < MAX_BULLET_COUNT; ++j)
		{
			if (i != j && m_objects[i] != NULL && Bullet[j] != NULL)
			{
				if (m_objects[i]->type == OBJECT_CHARACTER && Bullet[j]->type == OBJECT_ARROW)
				{
					if ((m_objects[i]->TeamNum == BLACK && Bullet[j]->TeamNum == WHITE) || (m_objects[i]->TeamNum == WHITE && Bullet[j]->TeamNum == BLACK))
					{
						if (ObjectsColistion(m_objects[i], Bullet[j]))
						{
							m_objects[i]->life -= Bullet[j]->life;
							delete Bullet[j];
							Bullet[j] = NULL;
							break;
						}
					}
				}
			}
		}
	}
	
	//Arrow <-> Buliding Collision
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		for (int j = 0; j < MAX_BULLET_COUNT; ++j)
		{
			if (i != j && m_objects[i] != NULL && Bullet[j] != NULL)
			{
				if (m_objects[i]->type == OBJECT_BUILDING && Bullet[j]->type == OBJECT_ARROW)
				{
					if ((m_objects[i]->TeamNum == BLACK && Bullet[j]->TeamNum == WHITE) || (m_objects[i]->TeamNum == WHITE && Bullet[j]->TeamNum == BLACK))
					{
						if (ObjectsColistion(m_objects[i], Bullet[j]))
						{
							m_objects[i]->life -= Bullet[j]->life;
							delete Bullet[j];
							Bullet[j] = NULL;
							if (m_objects[i] != NULL)
							{
								if(m_objects[i]->TeamNum == BLACK)
									m_objects[i]->setColor(1.0f, 0.0f, 0.0f, 1.0f);
								else
									m_objects[i]->setColor(0.0f, 0.0f, 1.0f, 1.0f);
							}
							break;
						}
						else
						{
							if (m_objects[i] != NULL)
								m_objects[i]->setColor(1.0f, 1.0f, 1.0f, 1.0f);
						}
					}
				}
			}
		}
	}

	//EnemyCharacter Collision <-> skill  
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		for (int j = 0; j < MAX_BULLET_COUNT; ++j)
		{
			if (i != j && m_objects[i] != NULL && Bullet[j] != NULL)
			{
				if (m_objects[i]->type == OBJECT_CHARACTER && Bullet[j]->type == OBJECT_SKILL)
				{
					if ((m_objects[i]->TeamNum == BLACK && Bullet[j]->TeamNum == WHITE))
					{
						if (ObjectsColistion(m_objects[i], Bullet[j]))
						{
							delete m_objects[i];
							m_objects[i] = NULL;
							break;
						}
					}
				}
			}
		}
	}

	
}

BOOL SceneMgr::ObjectsColistion(Object * a, Object * b)
{
	float left1 = a->m.x - (a->size / 2);
	float right1 = a->m.x + (a->size / 2);
	float top1 = a->m.y - (a->size / 2);
	float bottom1 = a->m.y + (a->size / 2);

	float left2 = b->m.x - (b->size / 2);
	float right2 = b->m.x + (b->size / 2);
	float top2 = b->m.y - (b->size / 2);
	float bottom2 = b->m.y + (b->size / 2);

	if (left1 < right2 && right1 > left2  && top1 < bottom2 && bottom1 > top2)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


void SceneMgr::Addobject(int x, int y)
{
	switch (PlayerCharSelect)
	{
	case 0:
		if (skillpoint > 0)
		{
			if (y < 0 && y > -400)
			{
				for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
				{
					if (m_objects[i] == NULL)
					{
						m_objects[i] = new Object(x, y, 0, OBJECT_CHARACTER);
						m_objects[i]->setSize(30);
						int cnt = 0;
						for (int j = 0; j < MAX_OBJECTS_COUNT; ++j)
						{
							if (m_objects[j] != NULL)
							{
								if (m_objects[j]->type == OBJECT_BUILDING && m_objects[j]->TeamNum == BLACK)
								{
									float temp = sqrt(m_objects[j]->m.x - x*m_objects[j]->m.x - x + m_objects[j]->m.y - y*m_objects[j]->m.y - y);
									m_objects[i]->setDirection((m_objects[j]->m.x - x) / temp, (m_objects[j]->m.y - y) / temp, 0);
									break;
								}
								else
									cnt++;
							}
							else
								cnt++;
						}
						if (cnt > MAX_OBJECTS_COUNT - 3)
							m_objects[i]->setDirection((rand() % 3) - 1, -1, 0);
						if (m_objects[i] != NULL)
							m_objects[i]->setColor(0.0f, 0.0f, 1.0f, 1);
						m_objects[i]->setSpeed(100);
						m_objects[i]->life = 25;
						m_objects[i]->TeamNum = WHITE;
						skillpoint -= 1;
						break;
					}
				}
			}
		}
		break;
	case 1:
		if (skillpoint > 3)
		{
			cout << "스킬2" << endl;
			for (int i = 0; i < MAX_BULLET_COUNT; ++i)
			{
				if (Bullet[i] == NULL)
				{
					Bullet[i] = new Object(x, y, 0, OBJECT_SKILL);
					Bullet[i]->setSize(100);
					Bullet[i]->setDirection(0, 0, 0);
					if (Bullet[i] != NULL)
						Bullet[i]->setColor(0.0f, 0.0f, 1.0f, 1);
					Bullet[i]->setSpeed(300);
					Bullet[i]->life = 150;
					Bullet[i]->lifetime = 0.5f;
					Bullet[i]->TeamNum = WHITE;
					skillpoint -= 3;
					break;
				}
			}
		}
		break;
	default:
		break;
	}
}



SceneMgr::~SceneMgr()
{
	delete m_Renderer;
}
