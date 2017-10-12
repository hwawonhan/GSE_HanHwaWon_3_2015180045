#pragma once

class Vector3;

class Object
{
private:
	float m_x, m_y, m_z;
public:
	Object();
	Object(Vector3 v);
	Object(const Object& object);
	Object(Object&& object);
	void getPosition(Vector3 v);
	Object& operator=(const Object& object);
	Object& operator=(Object&& object);
	~Object();
};

class Vector3
{
public:
	float x, y, z;
	Vector3();
	Vector3(float x, float y, float z);
	~Vector3();
};