#include "GA.h"
#include <ctime>

#define RANDOM_NUM		((float)rand()/(RAND_MAX+1))

GA::GA()
{
	//	srand((int)time)(NULL);
	m_population = new Population(POP_SIZE);

	for (int i = 0; i < POP_SIZE; i++) {
		Person* reference = m_population->GetPeople()[i];
		for (int j = 0; j < GENE_LENGTH; j++) {
			reference->SetInstructionSet(GenerateRandomGenome().m_genome[j].m_bits);
		}
	}
}


GA::~GA()
{
}

void GA::TestGeneration()
{
}

void GA::NewGeneration()
{
	//Run roulette-wheel selection and get the best People from current generation
	//Breed the best people from current generation
	//Add the children created into this new generation
	//Fill the rest of the genreation with new randomized/mutated people


	/*Maybe iterate through all of the current generation ordered descending
	from */

	//for (int i = 0; i < POP_SIZE; i++) {
	//	m_population[i].GetPeople()[i] = new Person(GenerateRandomGenome().m_genome[i].m_bits);
	//}
}

void GA::UpdatePopulation(float dt)
{
	for (auto& person : m_population->GetPeople()) {
		person->Update(dt);
	}
}

void GA::DrawPopulation(aie::Renderer2D* renderer)
{
	for (auto& person : m_population->GetPeople()) {
		person->Draw(renderer);
	}
}

GA::Genome GA::GenerateRandomGenome()
{
	Chromosone	newChromo;
	Genome		newGenome;
	//Randomly Generate genome
	for (int i = 0; i < GENE_LENGTH; i++) {
		newChromo.m_bits = GenRandomBits(CHROMO_LENGTH);
		newGenome.m_genome.push_back(newChromo);
	}
	return newGenome;
}

std::string	GA::GenRandomBits(int length)
{
	std::string bits;

	for (int i = 0; i < length; i++)
	{
		if (RANDOM_NUM > 0.5f)
			bits += "1";
		else
			bits += "0";
	}
	return bits;
}
