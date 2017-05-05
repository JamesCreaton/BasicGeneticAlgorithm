#include "GA.h"
#include <ctime>
#include <iostream>

#define RANDOM_NUM		((float)rand()/(RAND_MAX+1))

GA::GA(b2Vec2 Target)
	:m_randEngine(std::random_device()()),
	m_totalFitness(0),
	m_target(Target),
	m_currentGeneration(1),
	m_simulationStarted(true)
{
	m_population = new Population(POP_SIZE);
	for (int i = 0; i < POP_SIZE; i++) {
		Person* reference = (*m_population->GetPeople())[i];
		for (int j = 0; j < GENE_LENGTH; j++) {
			reference->SetInstructionSet(GenerateRandomGenome().m_genome[j].m_bits);
		}
	}

	//m_population = new Population(POP_SIZE);
	//for (auto& person : m_population->GetPeople()) {
	//	Person* reference = person;
	//	for (int j = 0; j < GENE_LENGTH; j++) {
	//		reference->SetInstructionSet(GenerateRandomGenome().m_genome[j].m_bits);
	//	}
	//}

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

	//get difference between 9600 to 1000 is score

	a_person->SetFitness(10000 - distance);
}

void GA::TestGeneration()
{
	for (auto& Person : (*m_population->GetPeople())) {
		CalculateSuccess(Person);
	};

	SortPeople();

	for (int i = 0; i < m_population->GetPeople()->size() / 2; i++) {
		//Get the top 50%
		m_top50.push_back((*m_population->GetPeople())[i]);
	}

	for (int i = m_population->GetPeople()->size() / 2; i < m_population->GetPeople()->size(); i++) {
		//Get the bottom 50%
		m_bottom50.push_back((*m_population->GetPeople())[i]);
	}

	for (int i = 0; i < m_top50.size(); i++) {
		std::cout << m_top50[i]->GetFitness() << std::endl;
	}

	system("pause");

	for (int i = 0; i < m_bottom50.size(); i++) {
		std::cout << m_bottom50[i]->GetFitness() << std::endl;
	}
	system("pause");

	//m_highestFitness = m_top50[0]->GetFitness();
}

void GA::NewGeneration()
{

}

void GA::UpdatePopulation(float dt)
{
	int generationFinished = 0;
	for (auto& person : *m_population->GetPeople()) {
		person->Update(dt);
		generationFinished++;
	}
	if (generationFinished = (*m_population->GetPeople()).size() * 3) {

		//Evaluate the fitness
		TestGeneration();
		CalculateGenerationFitness(m_population);

		//Breed the top 50%
		BreedPopulation(&m_top50);

		//Mutate the bottom 50%
		MutateBottom50();

		if (m_simulationStarted) {
			if (m_currentGeneration != MAX_ALLOWABLE_GENERATIONS) {
				NewGeneration();
			}
		}
		generationFinished = 0;
	}
}

void GA::DrawPopulation(aie::Renderer2D* renderer)
{
	for (auto& person : (*m_population->GetPeople())) {
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

struct Comparator
{
	bool operator()(Person* a, Person* b) const
	{
		return a->GetFitness() > b->GetFitness();
	}
};

void GA::SortPeople()
{
	std::sort(m_population->GetPeople()->begin(), m_population->GetPeople()->end(), Comparator());
}

bool cmp(Person* a, Person* b) {

	return (a->GetFitness() < b->GetFitness());
}

void GA::CalculateGenerationFitness(Population* a_population)
{
	for (auto& person : (*a_population->GetPeople())) {
		m_totalFitness += person->GetFitness();
	}
}

void GA::BreedPopulation(std::vector<Person*>* a_people)
{

	Person* child1 = new Person();
	Person* child2 = new Person();

	std::vector<Person*> children;

	Chromosone newChromo;
	Genome	   newGenome;

	for (int i = 0; i < m_population->GetPeople()->size() / 2; i++) {

		Person* parent1 = GetWeightedRandomPerson(*a_people);
		Person* parent2 = GetWeightedRandomPerson(*a_people);

		child1->init(parent1->GetWorld(), glm::vec2(640.0f, 360.0f), glm::vec2(25.0f, 25.0f));
		child2->init(parent1->GetWorld(), glm::vec2(640.0f, 360.0f), glm::vec2(25.0f, 25.0f));

		child1->SetInstructionSet(std::string(parent1->GetInstructionSet()[0]));
		child1->SetInstructionSet(std::string(parent1->GetInstructionSet()[1]));
		child1->SetInstructionSet(std::string(parent1->GetInstructionSet()[2]));
		child1->SetInstructionSet(std::string(parent1->GetInstructionSet()[3]));

		child1->SetInstructionSet(std::string(parent2->GetInstructionSet()[4]));
		child1->SetInstructionSet(std::string(parent2->GetInstructionSet()[5]));
		child1->SetInstructionSet(std::string(parent2->GetInstructionSet()[6]));
		child1->SetInstructionSet(std::string(parent2->GetInstructionSet()[7]));

		child2->SetInstructionSet(std::string(parent2->GetInstructionSet()[0]));
		child2->SetInstructionSet(std::string(parent2->GetInstructionSet()[1]));
		child2->SetInstructionSet(std::string(parent2->GetInstructionSet()[2]));
		child2->SetInstructionSet(std::string(parent2->GetInstructionSet()[3]));

		child2->SetInstructionSet(std::string(parent1->GetInstructionSet()[4]));
		child2->SetInstructionSet(std::string(parent1->GetInstructionSet()[5]));
		child2->SetInstructionSet(std::string(parent1->GetInstructionSet()[6]));
		child2->SetInstructionSet(std::string(parent1->GetInstructionSet()[7]));

		children.push_back(child1);
		children.push_back(child2);
	}
	for (int i = 0; i < a_people->size(); i++) {
		(*a_people)[i] = children[i];
	}
}




Person* GA::GetWeightedRandomPerson(std::vector<Person*> a_people)
{
	std::uniform_int_distribution<int> dist(0, m_totalFitness / 2 - 1);

	int r = dist(m_randEngine);

	for (auto& person : a_people) {
		r -= person->GetFitness();
		if (r < 0)
		{
			//This is the person
			return person;
		}
	}
}

void GA::MutateBottom50()
{
}


void GA::MutateGenome1(Person& a_person)
{
	std::uniform_int_distribution<int> dist(0, a_person.GetInstructionSet().size());

	int rnd = dist(m_randEngine);

	std::vector<std::string> mutatedGenome = a_person.GetInstructionSet();
	mutatedGenome[rnd] = GenRandomBits(CHROMO_LENGTH);
}

void GA::MutateGenome2(Person& a_person)
{
	int floor = 0, ceiling = a_person.GetInstructionSet().size(), range = (ceiling - floor);
	int rnd = floor + int((range * rand()) / (RAND_MAX + 1.0));

	std::vector<std::string> mutatedGenome = a_person.GetInstructionSet();
	mutatedGenome[rnd] = GenRandomBits(CHROMO_LENGTH);
	mutatedGenome[rnd] = GenRandomBits(CHROMO_LENGTH);
}

void GA::MutateGenome3(Person& a_person)
{
	int floor = 0, ceiling = a_person.GetInstructionSet().size(), range = (ceiling - floor);
	int rnd = floor + int((range * rand()) / (RAND_MAX + 1.0));

	std::vector<std::string> mutatedGenome = a_person.GetInstructionSet();
	mutatedGenome[rnd] = GenRandomBits(CHROMO_LENGTH);
	mutatedGenome[rnd] = GenRandomBits(CHROMO_LENGTH);
	mutatedGenome[rnd] = GenRandomBits(CHROMO_LENGTH);
}

void GA::MutateGenome4(Person& a_person)
{
	int floor = 0, ceiling = a_person.GetInstructionSet().size(), range = (ceiling - floor);
	int rnd = floor + int((range * rand()) / (RAND_MAX + 1.0));

	std::vector<std::string> mutatedGenome = a_person.GetInstructionSet();
	mutatedGenome[0] = GenRandomBits(CHROMO_LENGTH);
	mutatedGenome[1] = GenRandomBits(CHROMO_LENGTH);
	mutatedGenome[2] = GenRandomBits(CHROMO_LENGTH);
	mutatedGenome[3] = GenRandomBits(CHROMO_LENGTH);
}