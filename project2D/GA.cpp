#include "GA.h"
#include <ctime>
#include <iostream>

#define RANDOM_NUM		((float)rand()/(RAND_MAX+1))

GA::GA(b2Vec2 Target)
{
	//	srand((int)time)(NULL);
	m_population = new Population(POP_SIZE);


	for (int i = 0; i < POP_SIZE; i++) {
		Person* reference = m_population->GetPeople()[i];
		for (int j = 0; j < GENE_LENGTH; j++) {
			reference->SetInstructionSet(GenerateRandomGenome().m_genome[j].m_bits);
		}
	}

	m_simulationStarted = true;
	m_currentGeneration = 1;
	m_target = Target;
}


GA::~GA()
{
}

void GA::CalculateSuccess(Person* a_person)
{
	b2Vec2 a_person_position = a_person->GetBody()->GetPosition();

	int distancex = (m_target.x - a_person_position.x) * (m_target.x - a_person_position.x);
	int distancey = (m_target.y - a_person_position.y) * (m_target.y - a_person_position.y);

	double distance = sqrt(distancex - distancey);

	a_person->SetFitness(2000 - distance);
}

void GA::TestGeneration()
{
	for (auto& Person : m_population->GetPeople()) {
		CalculateSuccess(Person);
	}

	std::vector<Person*> sortedPeople = SortPeople();

	for (int i = sortedPeople.size() / 2; i < sortedPeople.size(); i++) {
		//Get the top 50%
		m_top50.push_back(sortedPeople[i]);
	}

	for (int i = 0; i < sortedPeople.size() / 2; i++) {
		//Get the bottom 50%
		m_bottom50.push_back(sortedPeople[i]);
	}
	std::reverse(m_top50.begin(), m_top50.end());
	std::reverse(m_bottom50.begin(), m_bottom50.end());
}

void GA::NewGeneration()
{
	//Find the best from the last generation
	TestGeneration();

	//Breed the top 50%
	BreedTop50();

	//Mutate the bottom 50%
	MutateBottom50();

	if (m_simulationStarted) {
		if (m_currentGeneration != MAX_ALLOWABLE_GENERATIONS) {

		}
	}

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
	int generationFinished = 0;
	for (auto& person : m_population->GetPeople()) {
		person->Update(dt);
		generationFinished++;
	}
	if (generationFinished = m_population->GetPeople().size() * 3) {
		//The generation has finihsed trying to solve the problem
		
		//Evaluate the fitness
		NewGeneration();

		//breed the top 50%

		//mutate the bottom 50%


		generationFinished = 0;
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

std::vector<Person*> GA::SortPeople()
{
	std::vector<Person*> sortedPeople;
	Person* highestScoringPerson = new Person();
	highestScoringPerson->SetFitness(2000);

	for (int i =0; i < m_population->GetPeople().size(); i++)
	{
		if (m_population->GetPeople()[i]->GetFitness() < highestScoringPerson->GetFitness())
		{
			highestScoringPerson = m_population->GetPeople()[i];
		}
		sortedPeople.push_back(highestScoringPerson);
	}

	return sortedPeople;
}

void BreedTop50()
{

}

void MutateBottom50()
{

}