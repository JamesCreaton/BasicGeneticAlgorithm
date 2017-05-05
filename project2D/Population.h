#pragma once
#include <vector>
#include <list>

#include "Person.h"

class Population
{
public:
	Population();
	Population(int populationSize);
	~Population();

	void GenerateNewPopulation();
	std::vector<Person*>* GetPeople();
	//std::list<Person*>	 GetPeople();


protected:
	std::vector<Person*>			    m_people;
	//std::list<Person*>				m_people;
};

