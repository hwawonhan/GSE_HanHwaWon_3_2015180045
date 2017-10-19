#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = NULL;
	m_objectsCount = 0;

}

Object** SceneMgr::GetObjects()
{
	return m_objects;
}

void SceneMgr::DrawAllObjects(Renderer* m_Renderer)
{
	for (int i = 0; i < m_objectsCount; ++i)
	{
		m_Renderer->DrawSolidRect(m_objects[i]->m.x, m_objects[i]->m.y, m_objects[i]->m.z, m_objects[i]->size,
			m_objects[i]->color.r, m_objects[i]->color.g, m_objects[i]->color.b, m_objects[i]->color.a);
	}
}

void SceneMgr::Update()
{
	for (int i = 0; i < m_objectsCount; ++i)
		m_objects[i]->Update();
	for (int i = 0; i < m_objectsCount; ++i)
	{
		for (int j = 1; j < m_objectsCount; ++j)
		{
			float left1 = m_objects[i]->m.x - (m_objects[i]->size / 2);
			float right1 = m_objects[i]->m.x + (m_objects[i]->size / 2);
			float top1 = m_objects[i]->m.y + (m_objects[i]->size / 2);
			float bottom1 = m_objects[i]->m.y - (m_objects[i]->size / 2);

			float left2 = m_objects[j]->m.x - (m_objects[j]->size / 2);
			float right2 = m_objects[j]->m.x + (m_objects[j]->size / 2);
			float top2 = m_objects[j]->m.y + (m_objects[j]->size / 2);
			float bottom2 = m_objects[j]->m.y - (m_objects[j]->size / 2);

			if ((left1 < right2 &&
				right1 > left2 ) ||
				(top1 < bottom2 &&
				bottom1 > top2))
			{
				m_objects[i]->color.g = 0.0f;
				m_objects[i]->color.b = 0.0f;
				m_objects[j]->color.g = 0.0f;
				m_objects[j]->color.b = 0.0f;
			}
			else
			{
				m_objects[i]->color.g = 1.0f;
				m_objects[i]->color.b = 1.0f;
				m_objects[j]->color.g = 1.0f;
				m_objects[j]->color.b = 1.0f;
			}
		}
	}
}

void SceneMgr::setobjectCount(int n)
{
	m_objectsCount = n;
}

void SceneMgr::Addobject(int x, int y)
{
	m_objects[m_objectsCount] = new Object(x - 250, 250 - y, 0, (rand() % 10) + 10);
	m_objects[m_objectsCount]->setDirection((rand() % 3) - 1, (rand() % 3) - 1, 0);
	m_objects[m_objectsCount]->setColor(1, 1, 1, 1);
	m_objects[m_objectsCount]->setSpeed(rand() % 5 * 0.01f);
	std::cout << m_objectsCount << std::endl;
	m_objectsCount++;
}

int SceneMgr::getobjectsCount()
{
	return m_objectsCount;
}


SceneMgr::~SceneMgr()
{
}
