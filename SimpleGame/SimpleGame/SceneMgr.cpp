#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	m_Renderer = new Renderer(500, 500);
	if (!m_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = NULL;
}

SceneMgr::SceneMgr(int w, int h)
{
	m_Renderer = new Renderer(w, h);
	if (!m_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_objects[i] = NULL;
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
}

void SceneMgr::Update(float time)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		if(m_objects[i] != NULL)
			m_objects[i]->Update(time);
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
			if (m_objects[i]->lifetime < 0)
			{
				delete m_objects[i];
				m_objects[i] = NULL;
			}
		}
	}
	BoxColistion();
}


void SceneMgr::BoxColistion()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		for (int j = i+1; j < MAX_OBJECTS_COUNT; ++j)
		{
			if (i != j && m_objects[i] != NULL && m_objects[j] != NULL)
			{
				float left1 = m_objects[i]->m.x - (m_objects[i]->size / 2);
				float right1 = m_objects[i]->m.x + (m_objects[i]->size / 2);
				float top1 = m_objects[i]->m.y - (m_objects[i]->size / 2);
				float bottom1 = m_objects[i]->m.y + (m_objects[i]->size / 2);

				float left2 = m_objects[j]->m.x - (m_objects[j]->size / 2);
				float right2 = m_objects[j]->m.x + (m_objects[j]->size / 2);
				float top2 = m_objects[j]->m.y - (m_objects[j]->size / 2);
				float bottom2 = m_objects[j]->m.y + (m_objects[j]->size / 2);

				if (left1 < right2 &&
					right1 > left2  &&
					top1 < bottom2 &&
					bottom1 > top2)
				{
					m_objects[i]->color.g = 0.0f;
					m_objects[i]->color.b = 0.0f;
					m_objects[j]->color.g = 0.0f;
					m_objects[j]->color.b = 0.0f;
					m_objects[i]->life -= 1;
					m_objects[j]->life -= 1;
					return;
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
}

void SceneMgr::Addobject(int x, int y)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] == NULL)
		{
			m_objects[i] = new Object(x - 250, 250 - y, 0);
			m_objects[i]->setSize((rand() % 10) + 10);
			m_objects[i]->setDirection((rand() % 3) - 1, (rand() % 3) - 1, 0);
			m_objects[i]->setColor(1, 1, 1, 1);
			m_objects[i]->setSpeed(((rand() % 5) + 1) * 10);
			break;
		}
	}
	
}



SceneMgr::~SceneMgr()
{
	delete m_Renderer;
}
