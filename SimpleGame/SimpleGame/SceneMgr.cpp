#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	m_Renderer = new Renderer(500, 500);
	TimeCount = 0;
	if (!m_Renderer->IsInitialized())
	{
		cout << "Renderer could not be initialized.. \n";
	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = NULL;
	for (int i = 0; i < MAX_BULLET_COUNT; ++i)
		Bullet[i] = NULL;

	m_texCharacter = m_Renderer->CreatePngTexture("./Textures/PNGs/building.png");

	//빌딩생성
	m_objects[0] = new Object(0, 0, 0, OBJECT_BUILDING);
	m_objects[0]->setSize(50);
	m_objects[0]->setDirection(0, 0, 0);
	m_objects[0]->setColor(1, 0, 1, 1);
	m_objects[0]->setSpeed(0);
	m_objects[0]->setLife(5);
}

SceneMgr::SceneMgr(int w, int h)
{
	m_Renderer = new Renderer(w, h);
	TimeCount = 0;
	if (!m_Renderer->IsInitialized())
	{
		cout << "Renderer could not be initialized.. \n";
	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = NULL;
	for (int i = 0; i < MAX_BULLET_COUNT; ++i)
		Bullet[i] = NULL;

	m_texCharacter = m_Renderer->CreatePngTexture("./Textures/PNGs/building.png");

	//빌딩생성
	m_objects[0] = new Object(0, 0, 0, OBJECT_BUILDING);
	m_objects[0]->setSize(50);
	m_objects[0]->setDirection(0, 0, 0);
	m_objects[0]->setColor(1, 0, 1, 1);
	m_objects[0]->setSpeed(0);
	m_objects[0]->setLife(5);
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
				m_Renderer->DrawTexturedRect(m_objects[i]->m.x, m_objects[i]->m.y, m_objects[i]->m.z, m_objects[i]->size,
					m_objects[i]->color.r, m_objects[i]->color.g, m_objects[i]->color.b, m_objects[i]->color.a, m_texCharacter);
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
		if(Bullet[i] != NULL)
			m_Renderer->DrawSolidRect(Bullet[i]->m.x, Bullet[i]->m.y, Bullet[i]->m.z, Bullet[i]->size,
				Bullet[i]->color.r, Bullet[i]->color.g, Bullet[i]->color.b, Bullet[i]->color.a);
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
	for (int i = 0; i < MAX_BULLET_COUNT; ++i )
	{
		if(Bullet[i] != NULL)
		Bullet[i]->Update(time);
	}

	//캐릭터 lifecount에 의한 삭제
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


	//빌딩 총알 시간 삭제
	for (int i = 0; i < 100; ++i)
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

	//총알 생성
	TimeCount += time;
	if(TimeCount > 0.5f)
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
							Bullet[i] = new Object(m_objects[j]->m.x, m_objects[j]->m.y, m_objects[j]->m.z, OBJECT_BULLET);
							Bullet[i]->setColor(1, 0, 0, 1);
							Bullet[i]->setSize(5);
							Bullet[i]->setDirection((rand() % 3) - 1, (rand() % 3) - 1, 0);
							Bullet[i]->setSpeed(100);
							Bullet[i]->lifetime = 10;
							Bullet[i]->Isme = 0;
							Bullet[i]->Damage = m_objects[j]->life;
						}
						else if(m_objects[j]->type == OBJECT_CHARACTER)
						{
							Bullet[i] = new Object(m_objects[j]->m.x - 10, m_objects[j]->m.y - 10, 0, OBJECT_ARROW);
							Bullet[i]->setColor(0, 1, 0, 1);
							Bullet[i]->setSize(5);
							Bullet[i]->setDirection((rand() % 3) - 1, (rand() % 3) - 1, 0);
							Bullet[i]->setSpeed(100);
							Bullet[i]->lifetime = 10;
							Bullet[i]->life = 10;
							Bullet[i]->Damage = m_objects[j]->life;
							Bullet[i]->Isme = j;
							printf("캐릭터 총알 생성\n");
						}
						break;
					}
				}
			}
		}
		TimeCount = 0;
	}
	BoxColistion();
}


void SceneMgr::BoxColistion()
{
	//캐릭터와 빌딩 충돌체크
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		for (int j = i + 1; j < MAX_OBJECTS_COUNT; ++j)
		{
			if (i != j && m_objects[i] != NULL && m_objects[j] != NULL)
			{
				if ( (m_objects[j]->type == OBJECT_CHARACTER && m_objects[i]->type == OBJECT_BUILDING))
				{
					float left1 = m_objects[i]->m.x - (m_objects[i]->size / 2);
					float right1 = m_objects[i]->m.x + (m_objects[i]->size / 2);
					float top1 = m_objects[i]->m.y - (m_objects[i]->size / 2);
					float bottom1 = m_objects[i]->m.y + (m_objects[i]->size / 2);

					float left2 = m_objects[j]->m.x - (m_objects[j]->size / 2);
					float right2 = m_objects[j]->m.x + (m_objects[j]->size / 2);
					float top2 = m_objects[j]->m.y - (m_objects[j]->size / 2);
					float bottom2 = m_objects[j]->m.y + (m_objects[j]->size / 2);

					if (left1 < right2 && right1 > left2  && top1 < bottom2 && bottom1 > top2)
					{
						m_objects[i]->life -= m_objects[j]->Damage;
						m_objects[j]->life -= m_objects[i]->Damage;
						if (m_objects[j]->type == 1)
							m_objects[j]->setColor(1.0f, 0.0f, 0.0f, 1.0f);
						if (m_objects[i]->type == 1)
							m_objects[i]->setColor(1.0f, 0.0f, 0.0f, 1.0f);
						return;
					}
					else
					{
						if (m_objects[i]->type == 1)
							m_objects[i]->setColor(1.0f, 1.0f, 1.0f, 1.0f);
						if (m_objects[j]->type == 1)
							m_objects[j]->setColor(1.0f, 1.0f, 1.0f, 1.0f);
					}
				}
			}
		}
	}
	//캐릭터와 빌딩총알의 충돌 체크
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		for (int j = 0; j < MAX_BULLET_COUNT; ++j)
		{
			if (m_objects[i] != NULL && Bullet[j] != NULL)
			{
				if (m_objects[i]->type == OBJECT_CHARACTER && Bullet[j]->type == OBJECT_BULLET)
				{
					float left1 = m_objects[i]->m.x - (m_objects[i]->size / 2);
					float right1 = m_objects[i]->m.x + (m_objects[i]->size / 2);
					float top1 = m_objects[i]->m.y - (m_objects[i]->size / 2);
					float bottom1 = m_objects[i]->m.y + (m_objects[i]->size / 2);

					float left2 = Bullet[j]->m.x - (Bullet[j]->size / 2);
					float right2 = Bullet[j]->m.x + (Bullet[j]->size / 2);
					float top2 = Bullet[j]->m.y - (Bullet[j]->size / 2);
					float bottom2 = Bullet[j]->m.y + (Bullet[j]->size / 2);

					if (left1 < right2 && right1 > left2  && top1 < bottom2 && bottom1 > top2)
					{
						m_objects[i]->life -= Bullet[j]->Damage;
						delete Bullet[j];
						Bullet[j] = NULL;
						return;
					}
					else
					{
						if (m_objects[i]->type == 1)
							m_objects[i]->setColor(1.0f, 1.0f, 1.0f, 1.0f);
						if (Bullet[j]->type == 1)
							Bullet[j]->setColor(1.0f, 1.0f, 1.0f, 1.0f);
					}
				}
				if (Bullet[j]->type == OBJECT_ARROW && Bullet[j]->Isme != i)
				{
					float left1 = m_objects[i]->m.x - (m_objects[i]->size / 2);
					float right1 = m_objects[i]->m.x + (m_objects[i]->size / 2);
					float top1 = m_objects[i]->m.y - (m_objects[i]->size / 2);
					float bottom1 = m_objects[i]->m.y + (m_objects[i]->size / 2);

					float left2 = Bullet[j]->m.x - (Bullet[j]->size / 2);
					float right2 = Bullet[j]->m.x + (Bullet[j]->size / 2);
					float top2 = Bullet[j]->m.y - (Bullet[j]->size / 2);
					float bottom2 = Bullet[j]->m.y + (Bullet[j]->size / 2);

					if (left1 < right2 && right1 > left2  && top1 < bottom2 && bottom1 > top2)
					{
						m_objects[i]->life -= Bullet[j]->Damage;
						delete Bullet[j];
						Bullet[j] = NULL;
						return;
					}
					else
					{
						if (m_objects[i]->type == 1)
							m_objects[i]->setColor(1.0f, 1.0f, 1.0f, 1.0f);
						if (Bullet[j]->type == 1)
							Bullet[j]->setColor(1.0f, 1.0f, 1.0f, 1.0f);
					}
				}
			}
		}
	}
}

void SceneMgr::Addobject(int x, int y)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] == NULL)
		{
			m_objects[i] = new Object(x - 250, 250 - y, 0, OBJECT_CHARACTER);
			m_objects[i]->setSize(20);
			m_objects[i]->setDirection((rand() % 3) - 1, (rand() % 3) - 1, 0);
			m_objects[i]->setColor(1, 1, 1, 1);
			m_objects[i]->setSpeed(100);
			break;
		}
	}

}



SceneMgr::~SceneMgr()
{
	delete m_Renderer;
}
