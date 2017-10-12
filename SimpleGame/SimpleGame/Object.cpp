#include "stdafx.h"
#include "Object.h"


Object::Object() : m(0,0,0), size(10)
{
}

Object::Object(float x, float y, float z)
{
	m.x = x;
	m.y = y;
	m.z = z;
	size = 10;
}

Object::Object(float x, float y, float z, int _size)
{
	m.x = x;
	m.y = y;
	m.z = z;
	size = _size;
}

Object::Object(Vector3 v) : m(v.x, v.y, v.z), size(10)
{
}

Object::Object(Vector3 v, int _size)
{
	m = v;
	size = _size;
}


void Object::setDirection(float x, float y, float z)
{
	Direction.x = x;
	Direction.y = y;
	Direction.z = z;
}

void Object::setColor(float r, float g, float b, float a)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = b;
}

void Object::getPosition(Vector3& v)
{
	v.x = m.x;
	v.y = m.y;
	v.z = m.z;
}


void Object::Update()
{
	m.x += Direction.x * 0.01f;
	m.y += Direction.y * 0.01f;
	m.z += Direction.z * 0.01f;
	if (m.x > 250 || m.x < -250)
		Direction.x *= -1;
	if (m.y > 250 || m.y < -250)
		Direction.y *= -1;
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

Vector3::Vector3(const Vector3 & object)
{
	x = object.x;
	y = object.y;
	z = object.z;
}

Vector3::Vector3(Vector3 && object)
{
	x = object.x;
	y = object.y;
	z = object.z;
	object.x = 0;
	object.y = 0;
	object.z = 0;
}

Vector3 & Vector3::operator=(const Vector3 & object)
{
	if (this == &object)
		return *this;
	x = object.x;
	y = object.y;
	z = object.z;
	return *this;
	// TODO: 여기에 반환 구문을 삽입합니다.
}

Vector3 & Vector3::operator=(Vector3 && object)
{
	//나를 나에게 이동하는 것은 필요없다.
	if (this == &object)
		return *this;
	//다른model의 data를 가져온다.
	x = object.x;
	y = object.y;
	z = object.z;
	//다른model의 값을 초기화한다.
	object.x = 0;
	object.y = 0;
	object.z = 0;
	// TODO: 여기에 반환 구문을 삽입합니다.
}

Vector3::~Vector3()
{
}
