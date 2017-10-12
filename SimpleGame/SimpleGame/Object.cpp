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
	// TODO: 여기에 반환 구문을 삽입합니다.
}

Object & Object::operator=(Object && object)
{
	//나를 나에게 이동하는 것은 필요없다.
	if (this == &object)
		return *this;
	//다른model의 data를 가져온다.
	m_x = object.m_x;
	m_y = object.m_y;
	m_z = object.m_z;
	//다른model의 값을 초기화한다.
	object.m_x = 0;
	object.m_y = 0;
	object.m_z = 0;
	// TODO: 여기에 반환 구문을 삽입합니다.
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
