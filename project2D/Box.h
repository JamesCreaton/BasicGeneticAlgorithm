#pragma once
#include <box2d.h>
#include <Renderer2D.h>
#include <glm\glm.hpp>

class Box
{
public:
	Box();
	~Box();

	void init(b2World* world, const glm::vec2& position, const glm::vec2& dimensions);
	void Draw(aie::Renderer2D* renderer);

	b2Body* GetBody() { return m_body; }
	b2Fixture* GetFixture() { return m_fixture; }

private:
	b2Body*		m_body = nullptr;
	b2Fixture*	m_fixture = nullptr;
	glm::vec2	m_dimensions;
};

