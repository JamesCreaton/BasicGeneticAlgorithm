#include "Ground.h"

Ground::Ground()
{
}

Ground::~Ground()
{
}


void Ground::init(b2World * world, const glm::vec2 & position, const glm::vec2 & dimensions)
{
	m_dimensions = dimensions;
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);

	m_body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / 2, dimensions.y / 2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	m_fixture = m_body->CreateFixture(&fixtureDef);
}

void Ground::Draw(aie::Renderer2D * renderer)
{
	renderer->drawSprite(nullptr, m_body->GetPosition().x, m_body->GetPosition().y,
		m_dimensions.x, m_dimensions.y);
}
