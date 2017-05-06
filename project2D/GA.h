#pragma once
#include "Population.h"
#include <random>

#define CROSSOVER_RATE	0.7
#define MUTATION_RATE	0.1
#define POP_SIZE		10
#define MAX_ALLOWABLE_GENERATIONS 65
#define CHROMO_LENGTH	2
#define GENE_LENGTH		6

class GA
{
public:
	GA(b2Vec2 Target);
	~GA();

	void CalculateSuccess(Person* a_person);

	struct Chromosone {
		std::string m_bits;
	};

	struct Genome {
		std::vector<Chromosone> m_genome;
	};

	void TestGeneration();
	void NewGeneration();

	void UpdatePopulation(float dt);
	void DrawPopulation(aie::Renderer2D* renderer);
	void DrawGUI(aie::Renderer2D* renderer, aie::Font* a_font);

	Genome GenerateRandomGenome();

	std::vector<Person*>* GetPeople() { return m_population->GetPeople(); }

protected:
	
	Population*		m_population;

private:
	std::string GenRandomBits(int length);

	void SortPeople();
	void MutateBottom50(std::vector<Person*>* a_people);
	void BreedPopulation(std::vector<Person*>* a_people);

	Person * GetWeightedRandomPerson(std::vector<Person*> a_people);

	void CalculateGenerationFitness(Population* a_population);

	void MutateGenome1(Person & a_person);
	void MutateGenome2(Person & a_person);
	void MutateGenome3(Person & a_person);
	void MutateGenome4(Person & a_person);

	int				m_currentGeneration;
	bool			m_simulationStarted;

	b2Vec2			m_target;
	std::vector<Person*> m_top50;
	std::vector<Person*> m_bottom50;

	int		m_highestFitness;
	int		m_totalFitness;
	bool	m_solutionFound;

	std::default_random_engine m_randEngine;
};

