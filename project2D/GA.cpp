#include "GA.h"
#include <ctime>
#include <iostream>

#define RANDOM_NUM		((float)rand()/(RAND_MAX+1))

GA::GA(b2Vec2 Target)
	:m_randEngine(std::random_device()()),
	m_totalFitness(0),
	m_target(Target),
	m_currentGeneration(1),
	m_simulationStarted(true),
	m_solutionFound(false)
{
	m_population = new Population(POP_SIZE);
	for (int i = 0; i < POP_SIZE; i++) {
		Person* reference = (*m_population->GetPeople())[i];
		for (int j = 0; j < GENE_LENGTH; j++) {
			reference->SetInstructionSet(GenerateRandomGenome().m_genome[j].m_bits);
		}
	}
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

	a_person->SetFitness(10000 - distance);

	int success = 0;
	for (int i = 0; i < a_person->GetInstructionSet().size(); i++) {
		if (a_person->GetInstructionSet()[i] == "01") {
			success++;
		}
	}

	if (success == GENE_LENGTH) {
		m_solutionFound = true;
	}
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

	m_highestFitness = m_top50[0]->GetFitness();
}

void GA::NewGeneration()
{
	//Breed the top 50%
	BreedPopulation(&m_top50);

	//Mutate the bottom 50%
	MutateBottom50(&m_bottom50);

	m_currentGeneration++;
}

void GA::UpdatePopulation(float dt)
{
	if (m_simulationStarted) {
		int generationFinished = 0;
		for (auto& person : *m_population->GetPeople()) {
			person->Update(dt);
			generationFinished++;
		}
		if (generationFinished = (*m_population->GetPeople()).size() * 3) {

			//Evaluate the fitness
			TestGeneration();
			CalculateGenerationFitness(m_population);

			if (m_solutionFound) {
				m_simulationStarted = false;
				std::cout << "Solution found at generation: " << m_currentGeneration << std::endl;
			}
			else {
				if (m_currentGeneration != MAX_ALLOWABLE_GENERATIONS) {
					NewGeneration();
				}
				else {
					m_simulationStarted = false;
				}
				generationFinished = 0;
			}
		}
	}
}

void GA::DrawPopulation(aie::Renderer2D* renderer)
{
	for (auto& person : (*m_population->GetPeople())) {
		person->Draw(renderer);
	}
}

void GA::DrawGUI(aie::Renderer2D* renderer, aie::Font* a_font)
{
	std::string generation = std::to_string(m_currentGeneration);
	std::string maxFitness = std::to_string(m_highestFitness);

	renderer->drawText(a_font, "Generation: ", 10, 680);
	renderer->drawText(a_font, generation.c_str(), 90, 680);

	renderer->drawText(a_font, "Best Fitness So Far: ", 10, 600);
	renderer->drawText(a_font, maxFitness.c_str(), 150, 600);
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

	//for (int i = 0; i < m_population->GetPeople()->size() / 2; i++) {

		/*	Person* parent1 = GetWeightedRandomPerson(*a_people);
			Person* parent2 = GetWeightedRandomPerson(*a_people);

			child1->init(parent1->GetWorld(), glm::vec2(640.0f, 360.0f), glm::vec2(25.0f, 25.0f));
			child2->init(parent1->GetWorld(), glm::vec2(640.0f, 360.0f), glm::vec2(25.0f, 25.0f));

			children.push_back(child1);
			children.push_back(child2);
		}
		for (int i = 0; i < a_people->size(); i++) {
			(*a_people)[i] = children[i];
		}*/
		//	}
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

void GA::MutateBottom50(std::vector<Person*>* a_people)
{
	std::uniform_int_distribution<int> dist(0, 4);

	for (int i = 0; i < a_people->size(); i++) {
		int r = dist(m_randEngine);

		switch (r) {
		case 0:
			MutateGenome1(*a_people->at(i));
			break;
		case 1:
			MutateGenome2(*a_people->at(i));
			break;
		case 2:
			MutateGenome3(*a_people->at(i));
			break;
		case 3:
			MutateGenome4(*a_people->at(i));
			break;
		}
	}
}


void GA::MutateGenome1(Person& a_person)
{
	m_currentGeneration;
	std::uniform_int_distribution<int> dist(0, a_person.GetInstructionSet().size() - 1);
	int rnd = dist(m_randEngine);

	std::vector<std::string> mutatedGenome = a_person.GetInstructionSet();
	mutatedGenome[rnd] = GenRandomBits(CHROMO_LENGTH);

	a_person.ClearInstructionSet();

	for (int i = 0; i < mutatedGenome.size(); i++) {
		a_person.SetInstructionSet(mutatedGenome[i]);
		a_person.SetCurrentMove(0);
	}
}

void GA::MutateGenome2(Person& a_person)
{
	std::uniform_int_distribution<int> dist(0, a_person.GetInstructionSet().size() - 1);
	int rnd = dist(m_randEngine);

	std::vector<std::string> mutatedGenome = a_person.GetInstructionSet();
	mutatedGenome[rnd] = GenRandomBits(CHROMO_LENGTH);
	mutatedGenome[rnd] = GenRandomBits(CHROMO_LENGTH);

	a_person.ClearInstructionSet();

	for (int i = 0; i < mutatedGenome.size(); i++) {
		a_person.SetInstructionSet(mutatedGenome[i]);
	}
	a_person.SetCurrentMove(0);
}

void GA::MutateGenome3(Person& a_person)
{
	std::uniform_int_distribution<int> dist(0, a_person.GetInstructionSet().size() - 1);
	int rnd = dist(m_randEngine);

	std::vector<std::string> mutatedGenome = a_person.GetInstructionSet();
	mutatedGenome[rnd] = GenRandomBits(CHROMO_LENGTH);
	mutatedGenome[rnd] = GenRandomBits(CHROMO_LENGTH);
	mutatedGenome[rnd] = GenRandomBits(CHROMO_LENGTH);

	a_person.ClearInstructionSet();

	for (int i = 0; i < mutatedGenome.size(); i++) {
		a_person.SetInstructionSet(mutatedGenome[i]);
		a_person.SetCurrentMove(0);
	}
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

	a_person.ClearInstructionSet();

	for (int i = 0; i < mutatedGenome.size(); i++) {
		a_person.SetInstructionSet(mutatedGenome[i]);
		a_person.SetCurrentMove(0);
	}
}