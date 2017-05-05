#include "Population.h"
#include <glm\glm.hpp>
#include <glm\ext.hpp>

Population::Population()
{
}

Population::Population(int populationSize)
{
	for (int i = 0; i < populationSize; i++) {
		m_people.push_back(new Person());
	}
}


Population::~Population()
{
}

void Population::GenerateNewPopulation()
{

}

std::vector<Person*>* Population::GetPeople()
{
	return &m_people;
}

//std::list<Person*> Population::GetPeople()
//{
//	return m_people;
//}
