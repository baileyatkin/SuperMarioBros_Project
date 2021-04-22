#pragma once
#include "Commons.h"
#include "Character.h"#

class Character;

class Collisions
{
public:
	~Collisions();

	static Collisions* Instance();

	bool Circle(CollisionCircle object1, CollisionCircle object2);
	bool Box(Rect2D rect1, Rect2D rect2);

private:
	Collisions();

	static Collisions* m_instance;
};

