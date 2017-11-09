#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	m_Renderer = new Renderer(500, 500);
	buildingbullettime = 0;
	if (!m_Renderer->IsInitialized())
	{
		cout << "Renderer could not be initialized.. \n";
	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = NULL;
	for (int i = 0; i < 100; ++i)
		BuildingBullet[i] = NULL;
	//ºôµù»ý¼º
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
	buildingbullettime = 0;
	if (!m_Renderer->IsInitialized())
	{
		cout << "Renderer could not be initialized.. \n";
	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = NULL;
	for (int i = 0; i < 100; ++i)
		BuildingBullet[i] = NULL;
	//ºôµù»ý¼º
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
			m_Renderer->DrawSolidRect(m_objects[i]->m.x, m_objects[i]->m.y, m_objects[i]->m.z, m_objects[i]->size,
				m_objects[i]->color.r, m_objects[i]->color.g, m_objects[i]->color.b, m_objects[i]->color.a);
		}
	}
	for (int i = 0; i < 100; ++i)
	{
		if(BuildingBullet[i] != NULL)
			m_Renderer->DrawSolidRect(BuildingBullet[i]->m.x, BuildingBullet[i]->m.y, BuildingBullet[i]->m.z, BuildingBullet[i]->size,
				BuildingBullet[i]->color.r, BuildingBullet[i]->color.g, BuildingBullet[i]->color.b, BuildingBullet[i]->color.a);
	}
}

void SceneMgr::Update(float time)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		if (m_objects[i] != NULL)
			m_objects[i]->Update(time);
	for (int i =0; i < 100; ++i )
	{
		if(BuildingBullet[i] != NULL)
		BuildingBullet[i]->Update(time);
	}
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
	//ºôµù ÃÑ¾Ë ½Ã°£ »èÁ¦
	for (int i = 0; i < 100; ++i)
	{
		if (BuildingBullet[i] != NULL)
		{
			if (BuildingBullet[i]->getlifetime() < 0)
			{
				delete BuildingBullet[i];
				BuildingBullet[i] = NULL;
				printf("ÃÑ¾Ë »èÁ¦\n");
			}
		}
	}

	//ºôµùÃÑ¾Ë »ý¼º
	buildingbullettime += time;
	if(buildingbullettime > 0.5f)
	{
		for (int i = 0; i < 100; ++i)
		{
			if (BuildingBullet[i] == NULL)
			{
				BuildingBullet[i] = new Object(0, 0, 0, OBJECT_BULLET);
				BuildingBullet[i]->setSize((rand() % 10) + 10);
				BuildingBullet[i]->setDirection((rand() % 3) - 1, (rand() % 3) - 1, 0);
				BuildingBullet[i]->setColor(1, 0, 1, 1);
				BuildingBullet[i]->setSpeed(100);
				BuildingBullet[i]->lifetime = 10;
				BuildingBullet[i]->Damage = 1;
				break;
			}
		}
		buildingbullettime = 0;
	}
	if (m_objects[0] != NULL)
		printf("%d\n", m_objects[0]->collisioncount);
	BoxColistion();
}


void SceneMgr::BoxColistion()
{
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
						m_objects[i]->life -= 1;
						m_objects[j]->life -= 1;
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
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			if (m_objects[i] != NULL && BuildingBullet[j] != NULL)
			{
				if (m_objects[i]->type == OBJECT_CHARACTER)
				{
					float left1 = m_objects[i]->m.x - (m_objects[i]->size / 2);
					float right1 = m_objects[i]->m.x + (m_objects[i]->size / 2);
					float top1 = m_objects[i]->m.y - (m_objects[i]->size / 2);
					float bottom1 = m_objects[i]->m.y + (m_objects[i]->size / 2);

					float left2 = BuildingBullet[j]->m.x - (BuildingBullet[j]->size / 2);
					float right2 = BuildingBullet[j]->m.x + (BuildingBullet[j]->size / 2);
					float top2 = BuildingBullet[j]->m.y - (BuildingBullet[j]->size / 2);
					float bottom2 = BuildingBullet[j]->m.y + (BuildingBullet[j]->size / 2);

					if (left1 < right2 && right1 > left2  && top1 < bottom2 && bottom1 > top2)
					{
						m_objects[i]->life -= BuildingBullet[j]->Damage;
						delete BuildingBullet[j];
						BuildingBullet[j] = NULL;
						return;
					}
					else
					{
						if (m_objects[i]->type == 1)
							m_objects[i]->setColor(1.0f, 1.0f, 1.0f, 1.0f);
						if (BuildingBullet[j]->type == 1)
							BuildingBullet[j]->setColor(1.0f, 1.0f, 1.0f, 1.0f);
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
			m_objects[i]->setSize((rand() % 10) + 10);
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
