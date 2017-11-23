#include "stdafx.h"
#include "Object.h"


Object::Object() : m(0,0,0), size(10)
{
}

Object::Object(float x, float y, float z, int _type)
{
	m.x = x;
	m.y = y;
	m.z = z;
	size = 10;
	speed = 0.1f;
	life = 1;
	lifetime = 10;
	type = _type;
	collisioncount = 0;
	ArrowSpawnTime = 0;
	Damage = 1;
}

Object::Object(float x, float y, float z, int _size, int _type)
{
	m.x = x;
	m.y = y;
	m.z = z;
	size = _size;
	speed = 0.1f;
	life = 1;
	lifetime = 10;
	type = _type;
	collisioncount = 0;
	ArrowSpawnTime = 0;
	Damage = 1;
}

Object::Object(Vector3 v, int _type) : m(v.x, v.y, v.z), size(10), speed(0.1f)
{
	type = _type;
}

Object::Object(Vector3 v, int _size, int _type)
{
	m = v;
	size = _size;
	speed = 0.1f;
	type = _type;
}


void Object::setDirection(float x, float y, float z)
{
	Direction.x = x;
	Direction.y = y;
	Direction.z = z;
}

void Object::setSize(int n)
{
	size = n;
}

void Object::setColor(float r, float g, float b, float a)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

void Object::setSpeed(float s)
{
	speed = s;
}

void Object::setLifeTime(float time)
{
	lifetime = time;
}

void Object::setLife(float _life)
{
	//life = _life*2 - 1;
	life = _life;
}

void Object::getPosition(Vector3& v)
{
	v.x = m.x;
	v.y = m.y;
	v.z = m.z;
}

int Object::getsize()
{
	return size;
}

float Object::getlifetime()
{
	return lifetime;
}


void Object::Update(float time)
{
	m.x += Direction.x * speed* time;
	m.y += Direction.y * speed* time;
	m.z += Direction.z * speed* time;
	lifetime -= time;
	ArrowSpawnTime += time;
	if (m.x + (size / 2) > 250 || m.x - (size / 2) < -250)
	{
		Direction.x *= -1;
	}
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
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
}

Vector3 & Vector3::operator=(Vector3 && object)
{
	//���� ������ �̵��ϴ� ���� �ʿ����.
	if (this == &object)
		return *this;
	//�ٸ�model�� data�� �����´�.
	x = object.x;
	y = object.y;
	z = object.z;
	//�ٸ�model�� ���� �ʱ�ȭ�Ѵ�.
	object.x = 0;
	object.y = 0;
	object.z = 0;
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
}

Vector3::~Vector3()
{
}
