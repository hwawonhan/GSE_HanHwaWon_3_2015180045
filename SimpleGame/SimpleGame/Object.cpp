#include "stdafx.h"
#include "Object.h"


Object::Object() : m_x(0), m_y(0), m_z(0)
{
}

Object::Object(Vector3 v) : m_x(v.x), m_y(v.y), m_z(v.z)
{
}

Object::Object(const Object & object)
{
	m_x = object.m_x;
	m_y = object.m_y;
	m_z = object.m_z;

}

Object::Object(Object && object)
{
	m_x = object.m_x;
	m_y = object.m_y;
	m_z = object.m_z;
	object.m_x = 0;
	object.m_y = 0;
	object.m_z = 0;
}

void Object::getPosition(Vector3 v)
{
	m_x = v.x;
	m_y = v.y;
	m_z = v.z;
}

Object & Object::operator=(const Object & object)
{
	if (this == &object)
		return *this;
	m_x = object.m_x;
	m_y = object.m_y;
	m_z = object.m_z;
	return *this;
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
}

Object & Object::operator=(Object && object)
{
	//���� ������ �̵��ϴ� ���� �ʿ����.
	if (this == &object)
		return *this;
	//�ٸ�model�� data�� �����´�.
	m_x = object.m_x;
	m_y = object.m_y;
	m_z = object.m_z;
	//�ٸ�model�� ���� �ʱ�ȭ�Ѵ�.
	object.m_x = 0;
	object.m_y = 0;
	object.m_z = 0;
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
}


Object::~Object()
{
}

Vector3::Vector3()
{
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{
}

Vector3::~Vector3()
{
}
