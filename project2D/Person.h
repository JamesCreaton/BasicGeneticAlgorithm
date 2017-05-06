#pragma once
#include <vector>
#include <Box2D.h>
#include <Renderer2D.h>
#include <glm/glm.hpp>
#include <glm\ext.hpp>

class Person
{
public:

	Person();
	~Person();


	void init(b2World* world, const glm::vec2& position, const glm::vec2& dimensions);
	void Update(float dt);
	void Draw(aie::Renderer2D* renderer);

	//Setters
	void SetInstructionSet(std::string instructions);
	void SetInstructionSetAtIndex(std::string instructions, int index);
	void ClearInstructionSet();
	void SetFitness(float a_fitness);
	void SetProbability(float a_probablity);
	void SetCurrentMove(int a_currentMove) { m_currentMove = a_currentMove; }

	//Getters
	b2World* GetWorld() { return m_world; };
	float GetFitness();
	b2Body* GetBody() { return m_body; }
	b2Fixture* GetFixture() { return m_fixture; }
	std::vector<std::string> GetInstructionSet();
	float GetProbability();
	int GetCurrentMove() { return m_currentMove; }

protected:
	std::vector<std::string>	m_instructions;
	float						m_fitness;

private:
	b2World* 	m_world;
	b2Body*		m_body = nullptr;
	b2Fixture*	m_fixture = nullptr;
	glm::vec2	m_dimensions;

	int BinToDec(std::string bits);
	void MoveAgent(int move);

	float m_probabilityOfBreeding;


	//Testing
	int m_currentMove;
}; 

