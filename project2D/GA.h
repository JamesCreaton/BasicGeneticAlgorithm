#pragma once
#include "Population.h"

#define CROSSOVER_RATE	0.7
#define MUTATION_RATE	0.001
#define POP_SIZE		10
#define CHROMO_LENGTH	300
#define GENE_LENGTH		4
#define MAX_ALLOWABLE_GENERATIONS 400
#define CHROMO_LENGTH	2
#define GENE_LENGTH		16

class GA
{
public:
	GA();
	~GA();

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

	Genome GenerateRandomGenome();

	std::vector<Person*> GetPeople() { return m_population->GetPeople(); }

protected:
	
	Population*		m_population;

private:
	std::string GenRandomBits(int length);
};
