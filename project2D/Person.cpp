#include "Person.h"



Person::Person()
	:m_fitness(1.0f),
	m_currentMove(0),
	m_probabilityOfBreeding(0)
{
}
Person::~Person()
{
}

void Person::init(b2World * world, const glm::vec2 & position, const glm::vec2 & dimensions)
{
	m_world = world;

	m_dimensions = dimensions;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	//bodyDef.type = b2_kinematicBody;
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

void Person::Update(float dt)
{
	//Get curret position
	//Apply force towards next position
	if (m_currentMove <= 3) {
		MoveAgent(m_currentMove);
	}
}

void Person::Draw(aie::Renderer2D * renderer)
{
	renderer->drawBox(m_body->GetPosition().x, m_body->GetPosition().y,
		m_dimensions.x, m_dimensions.y);
}

void Person::SetInstructionSet(std::string instructions)
{
	m_instructions.push_back(instructions);
}

void Person::SetInstructionSetAtIndex(std::string instructions, int index)
{
	m_instructions[index] = instructions;
}

void Person::ClearInstructionSet()
{
	m_instructions.clear();
}

int	Person::BinToDec(std::string bits)
{
	int val = 0;
	int value_to_add = 1;

	for (int i = bits.length(); i > 0; i--) {
		if (bits.at(i - 1) == '1')
			val += value_to_add;
		value_to_add *= 2;
	}
	return val;
}
void Person::MoveAgent(int move)
{
	if (m_instructions.size() > 0) {
		switch (BinToDec(m_instructions[move]))
		{
		case 0: /*Left*/ {
			m_body->SetTransform(m_body->GetPosition() + b2Vec2(-50.0f, 0.0f), m_body->GetAngle());
			break;
		}
		case 1: /*Right*/ {
			m_body->SetTransform(m_body->GetPosition() + b2Vec2(50.0f, 0.0f), m_body->GetAngle());
			break;
		}
		case 2: /*Up*/ {
			m_body->SetTransform(m_body->GetPosition() + b2Vec2(0.0f, 50.0f), m_body->GetAngle());
			break;
		}
		case 3: /*Down*/ {
			m_body->SetTransform(m_body->GetPosition() + b2Vec2(0.0f, -50.0f), m_body->GetAngle());
			break;
		}
	 }
		m_currentMove++;
   }
}

void Person::SetFitness(float a_fitness) 
{
	m_fitness = a_fitness;
}

void Person::SetProbability(float a_probablity)
{
	m_probabilityOfBreeding = a_probablity;
}

float Person::GetFitness()
{
	return m_fitness;
}

std::vector<std::string> Person::GetInstructionSet()
{
	return m_instructions;
}

float Person::GetProbability()
{
	return m_probabilityOfBreeding;
}

