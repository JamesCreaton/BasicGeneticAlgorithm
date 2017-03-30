#include "Rigidbody.h"


Rigidbody::Rigidbody()
{
}

Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position,
	glm::vec2 velocity, float rotation, float mass)
{
}


Rigidbody::~Rigidbody()
{
}

bool Rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	return false;
}

void Rigidbody::debug()
{
}
