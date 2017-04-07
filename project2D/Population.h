#pragma once
#include <vector>

#include "Person.h"

class Population
{
public:
	Population();
	Population(int populationSize);
	~Population();

	void GenerateNewPopulation();
	std::vector<Person*> GetPeople();


protected:
	std::vector<Person*>		m_people;
};

