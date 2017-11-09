#pragma once

struct Color
{
	float r, g, b, a;
};


class Vector3
{
public:
	float x, y, z;
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3& object);
	Vector3(Vector3&& object);
	Vector3& operator=(const Vector3& object);
	Vector3& operator=(Vector3&& object);

	~Vector3();
};

class Object
{
public:
	Vector3 m;
	Vector3 Direction;
	Color color;
	int size;
	float speed;
	float lifetime;		//이시간이지나면 사라지게
	float life;			//목숨갯수
	int type;
	int collisioncount;
	int Damage;
public:
	Object();
	Object(float x, float y, float z, int _tpye);
	Object(float x, float y, float z, int _size, int _tpye);
	Object(Vector3 v, int _tpye);
	Object(Vector3 v, int _size, int _tpye);

	void Update(float time);

	void setDirection(float x, float y, float z);
	void setSize(int n);
	void setColor(float r, float g, float b, float a);
	void setSpeed(float s);
	void setLifeTime(float time);
	void setLife(float _life);

	int getsize();
	float getlifetime();
	void getPosition(Vector3& v);

	~Object();
};
