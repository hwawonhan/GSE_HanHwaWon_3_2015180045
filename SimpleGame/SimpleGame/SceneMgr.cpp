#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	m_Renderer = new Renderer(500, 800);
	BuildingTime = 0;
	if (!m_Renderer->IsInitialized())
	{
		cout << "Renderer could not be initialized.. \n";
	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = NULL;
	for (int i = 0; i < MAX_BULLET_COUNT; ++i)
		Bullet[i] = NULL;

	m_texCharacter = m_Renderer->CreatePngTexture("./Textures/PNGs/Mybuilding.png");
	m_texEnemy = m_Renderer->CreatePngTexture("./Textures/PNGs/building.png");
	PlayerCharacterSpawnCount = 1;
	//빌딩생성
	for (int i = 0; i < 3; ++i)
	{
		m_objects[i] = new Object(150 * i - 150, 300, 0, OBJECT_BUILDING);
		m_objects[i]->setSize(100);
		m_objects[i]->setDirection(0, 0, 0);
		m_objects[i]->setColor(1, 0, 1, 1);
		m_objects[i]->setSpeed(0);
		m_objects[i]->setLife(500);
		m_objects[i]->TeamNum = BLACK;
	}
	for (int i = 3; i < 6; ++i)
	{
		m_objects[i] = new Object(150 * (i - 3) - 150, -300, 0, OBJECT_BUILDING);
		m_objects[i]->setSize(100);
		m_objects[i]->setDirection(0, 0, 0);
		m_objects[i]->setColor(1, 0, 1, 1);
		m_objects[i]->setSpeed(0);
		m_objects[i]->setLife(500);
		m_objects[i]->TeamNum = WHITE;
	}
}

SceneMgr::SceneMgr(int w, int h)
{
	m_Renderer = new Renderer(w, h);
	BuildingTime = 0;
	if (!m_Renderer->IsInitialized())
	{
		cout << "Renderer could not be initialized.. \n";
	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = NULL;
	for (int i = 0; i < MAX_BULLET_COUNT; ++i)
		Bullet[i] = NULL;

	m_texCharacter = m_Renderer->CreatePngTexture("./Textures/PNGs/Mybuilding.png");
	m_texEnemy = m_Renderer->CreatePngTexture("./Textures/PNGs/building.png");
	PlayerCharacterSpawnCount = 1;

	//빌딩생성
	for (int i = 0; i < 3; ++i)
	{
		m_objects[i] = new Object(150 * i - 150, 300, 0, OBJECT_BUILDING);
		m_objects[i]->setSize(100);
		m_objects[i]->setDirection(0, 0, 0);
		m_objects[i]->setColor(1, 0, 1, 1);
		m_objects[i]->setSpeed(0);
		m_objects[i]->setLife(500);
		m_objects[i]->TeamNum = BLACK;
	}
	for (int i = 3; i < 6; ++i)
	{
		m_objects[i] = new Object(150 * (i - 3) - 150, -300, 0, OBJECT_BUILDING);
		m_objects[i]->setSize(100);
		m_objects[i]->setDirection(0, 0, 0);
		m_objects[i]->setColor(1, 0, 1, 1);
		m_objects[i]->setSpeed(0);
		m_objects[i]->setLife(500);
		m_objects[i]->TeamNum = WHITE;
	}
}

Object** SceneMgr::GetObjects()
{
	return m_objects;
}

void SceneMgr::DrawAllObjects()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			if (m_objects[i]->type == OBJECT_BUILDING)
			{
				if (m_objects[i]->TeamNum == BLACK)
				{
					m_Renderer->DrawTexturedRect(m_objects[i]->m.x, m_objects[i]->m.y, m_objects[i]->m.z, m_objects[i]->size,
						m_objects[i]->color.r, m_objects[i]->color.g, m_objects[i]->color.b, m_objects[i]->color.a, m_texEnemy);
				}
				else
				{
					m_Renderer->DrawTexturedRect(m_objects[i]->m.x, m_objects[i]->m.y, m_objects[i]->m.z, m_objects[i]->size,
						m_objects[i]->color.r, m_objects[i]->color.g, m_objects[i]->color.b, m_objects[i]->color.a, m_texCharacter);
				}
			}
			else
			{
				m_Renderer->DrawSolidRect(m_objects[i]->m.x, m_objects[i]->m.y, m_objects[i]->m.z, m_objects[i]->size,
					m_objects[i]->color.r, m_objects[i]->color.g, m_objects[i]->color.b, m_objects[i]->color.a);
			}
		}
	}
	for (int i = 0; i < MAX_BULLET_COUNT; ++i)
	{
		if (Bullet[i] != NULL)
		{
			m_Renderer->DrawSolidRect(Bullet[i]->m.x, Bullet[i]->m.y, Bullet[i]->m.z, Bullet[i]->size,
				Bullet[i]->color.r, Bullet[i]->color.g, Bullet[i]->color.b, Bullet[i]->color.a);
		}
	}
}

void SceneMgr::Update(float time)
{
	//객체업데이트

	//캐릭터 빌딩 업데이트
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		if (m_objects[i] != NULL)
			m_objects[i]->Update(time);

	//빌딩 총알 업데이트
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
				if (Bullet[i]->TeamNum == BLACK)
					cout << "적화살" << endl;
				delete Bullet[i];
				Bullet[i] = NULL;
			}
		}
	}

	//빌딩총알생성
	BuildingTime += time;
	//if (BuildingTime > 0.5f)
	if (BuildingTime > 10.0f)
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
							if (m_objects[j]->TeamNum == BLACK)
							{
								Bullet[i] = new Object(m_objects[j]->m.x, m_objects[j]->m.y, m_objects[j]->m.z, OBJECT_BULLET);
								Bullet[i]->setColor(1, 0, 0, 1);
								Bullet[i]->setSize(2);
								Bullet[i]->setDirection((rand() % 3) - 1, -1, 0);
								Bullet[i]->setSpeed(600);
								Bullet[i]->life = 20;
								Bullet[i]->lifetime = 10;
								Bullet[i]->TeamNum = BLACK;
								Bullet[i]->Damage = m_objects[j]->life;
							}
							else if (m_objects[j]->TeamNum == WHITE)
							{
								Bullet[i] = new Object(m_objects[j]->m.x, m_objects[j]->m.y, m_objects[j]->m.z, OBJECT_BULLET);
								Bullet[i]->setColor(0, 0, 1, 1);
								Bullet[i]->setSize(2);
								Bullet[i]->setDirection((rand() % 3) - 1, 1, 0);
								Bullet[i]->setSpeed(600);
								Bullet[i]->life = 20;
								Bullet[i]->lifetime = 10;
								Bullet[i]->TeamNum = WHITE;
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
	if (EnemySpawnTime > 5.0f)
	{
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		{
			if (m_objects[i] == NULL)
			{
				m_objects[i] = new Object((rand() % 500) - 250, 400 - (rand() % 400), 0, OBJECT_CHARACTER);
				m_objects[i]->setSize(10);
				m_objects[i]->setDirection((rand() % 3) - 1, -1, 0);
				m_objects[i]->setColor(1, 0, 0, 1);
				m_objects[i]->setSpeed(300);
				m_objects[i]->TeamNum = BLACK;
				break;
			}
		}
		EnemySpawnTime = 0;
	}

	//화살 생성
	for (int j = 0; j < MAX_OBJECTS_COUNT; ++j)
	{
		if (m_objects[j] != NULL && m_objects[j]->type == OBJECT_CHARACTER)
		{
			if (m_objects[j]->ArrowSpawnTime > 3.0f)
			{
				for (int i = 0; i < MAX_BULLET_COUNT; ++i)
				{
					if (Bullet[i] == NULL)
					{
						if (m_objects[j]->TeamNum == WHITE)
						{
							Bullet[i] = new Object(m_objects[j]->m.x - 10, m_objects[j]->m.y - 10, 0, OBJECT_ARROW);
							Bullet[i]->setColor(1, 1, 0, 1);
							Bullet[i]->setSize(2);
							Bullet[i]->setDirection((rand() % 3) - 1, -1, 0);
							Bullet[i]->setSpeed(100);
							Bullet[i]->lifetime = 10;
							Bullet[i]->life = 10;
							Bullet[i]->Damage = m_objects[j]->life;
							Bullet[i]->TeamNum = WHITE;
							m_objects[j]->ArrowSpawnTime = 0;
							printf("플레이어 화살생성\n");
							break;
						}
						else if (m_objects[j]->TeamNum == BLACK)
						{
							Bullet[i] = new Object(m_objects[j]->m.x - 10, m_objects[j]->m.y - 10, 0, OBJECT_ARROW);
							Bullet[i]->setColor(0.5f, 0.2f, 0.7f, 1.0f);
							Bullet[i]->setSize(2);
							Bullet[i]->setDirection((rand() % 3) - 1, 1, 0);
							Bullet[i]->setSpeed(100);
							Bullet[i]->lifetime = 10;
							Bullet[i]->life = 10;
							Bullet[i]->Damage = m_objects[j]->life;
							Bullet[i]->TeamNum = BLACK;
							m_objects[j]->ArrowSpawnTime = 0;
							printf("적 화살 생성\n");
							break;
						}
					}
				}
			}
		}
	}

	PlayerCharacterSpawnTime += time;
	if (PlayerCharacterSpawnTime > 7.0f)
	{
		PlayerCharacterSpawnCount += 1;
		PlayerCharacterSpawnTime = 0.0f;
	}

	//y 영역 화면에서 넘어갈 시 Character삭제
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			if (m_objects[i]->m.y + (m_objects[i]->size / 2) > 400 || m_objects[i]->m.y - (m_objects[i]->size / 2) < -400)
			{
				delete m_objects[i];
				m_objects[i] = NULL;
			}
		}
	}

	//y 영역 화면에서 넘어갈 시 Bullet, Arrow 삭제
	for (int i = 0; i < MAX_BULLET_COUNT; ++i)
	{
		if (Bullet[i] != NULL)
		{
			if (Bullet[i]->m.y + (Bullet[i]->size / 2) > 400 || Bullet[i]->m.y - (Bullet[i]->size / 2) < -400)
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
							m_objects[j]->setColor(0.0f, 0.0f, 0.0f, 1.0f);
							return;
						}
						else
						{
							if (m_objects[j]->TeamNum == WHITE)
								m_objects[j]->setColor(0.0f, 0.0f, 1.0f, 1.0f);
							if (m_objects[i]->TeamNum == BLACK)
								m_objects[i]->setColor(1.0f, 0.0f, 0.0f, 1.0f);
						}
					}
				}
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
							m_objects[j]->setColor(0.0f, 0.0f, 0.0f, 1.0f);
							delete Bullet[j];
							Bullet[j] = NULL;
							return;
						}
						else
						{
							if (m_objects[i]->TeamNum == BLACK)
								m_objects[i]->setColor(1.0f, 0.0f, 0.0f, 1.0f);
							else
								m_objects[i]->setColor(0.0f, 0.0f, 1.0f, 1.0f);
						}
					}
				}
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
							m_objects[j]->setColor(0.0f, 0.0f, 0.0f, 1.0f);
							delete Bullet[j];
							Bullet[j] = NULL;
							return;
						}
						else
						{
							if (m_objects[i]->TeamNum == BLACK)
								m_objects[i]->setColor(1.0f, 0.0f, 0.0f, 1.0f);
							else
								m_objects[i]->setColor(0.0f, 0.0f, 1.0f, 1.0f);

							if (Bullet[j]->TeamNum == BLACK)
								Bullet[j]->setColor(0.5f, 0.2f, 0.7f, 1.0f);
							else
								Bullet[j]->setColor(1, 1, 0, 1);
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
							return;
						}
						else
						{
							if (Bullet[j]->TeamNum == BLACK)
								Bullet[j]->setColor(0.5f, 0.2f, 0.7f, 1.0f);
							else
								Bullet[j]->setColor(1, 1, 0, 1);
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
	if (PlayerCharacterSpawnCount > 0)
	{
		if (y < 0 && y > -400)
		{
			for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
			{
				if (m_objects[i] == NULL)
				{
					m_objects[i] = new Object(x, y, 0, OBJECT_CHARACTER);
					m_objects[i]->setSize(10);
					m_objects[i]->setDirection((rand() % 3) - 1, 1.0f, 0);
					m_objects[i]->setColor(0.0f, 0.0f, 1.0f, 1);
					m_objects[i]->setSpeed(100);
					m_objects[i]->life = 10;
					m_objects[i]->TeamNum = WHITE;
					PlayerCharacterSpawnCount -= 1;
					break;
				}
			}
		}
	}
}



SceneMgr::~SceneMgr()
{
	delete m_Renderer;
}
