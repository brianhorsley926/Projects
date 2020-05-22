#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <fstream>

using std::cout;
using std::string;
using std::vector;
using std::cin;
using std::endl;

class Person
{
	private:
		// 0: Susceptible // -1: Recovered // -2: Innoculated
		int status;
	public:
		Person()
		{
			status = 0;
		}
		Person(int given_status)
		{
			status = given_status;
		}
		string print_status()
		{
			if (status == 0)
			{
				return "Susceptible";
			}
			else if (status == 1)
			{
				return "Recovered";
			}
			else if (status == 2)
			{
				return "Innoculated";
			}
		}
		void update()
		{
			if (status > 1)
			{
				status = status - 1;
			}
			else if (status == 1)
			{
				status = -1;
			}
		}
		void infect(int duration)
		{
			status = duration;
		}
		void is_stable()
		{
			if (status > 0)
			{
				cout << "Sick" << endl;
			}
			else
			{
				cout << "Recovered" << endl;
			}
		}
		int get_status()
		{
			return status;
		}
		void set_status(int new_status)
		{
			status = new_status;
		}
};

class Population : public Person
{
	private:
		int pop_size;
		float contagion;
		vector<Person> pop;
	public:
		Population()
		{
			pop_size = 50;
			contagion = 0.1;
		}
		Population(int size, float probability)
		{
			pop_size = size;
			contagion = probability;
			vector<Person> temp_pop;
			for (int i = 0; i < pop_size; i++)
			{
				temp_pop.push_back(Person(0));
			}
			pop = temp_pop;
		}
		void random_infect(int infection)
		{
			int exit = 0;
			if (infection == 1)
			{
				while (exit == 0)
				{
					int random_person = rand() % (pop_size);
					if (pop[random_person].get_status() == 0)
					{
						pop[random_person].set_status(5);
						exit = 1;
					}
				}
			}
			else
			{
				int random_person = rand() % (pop_size);
				if (pop[random_person].get_status() == 0)
				{
					pop[random_person].set_status(5);
				}
			}
		}
		int count_infected()
		{
			int count = 0;
			for (int i = 0; i < get_pop_size(); i++)
			{
				if (pop[i].get_status() > 0)
				{
					count += 1;
				}
			}
			return count;
		}
		void vaccine(float pop_percentage)
		{
			int counter = 0;
			int random_person;
			int num_vaccinations = pop_percentage * pop_size;
			while (counter < num_vaccinations)
			{
				random_person = rand() % (pop_size);
				if (pop[random_person].get_status() != -2)
				{
					pop[random_person].set_status(-2);
					counter += 1;
				}
			}
		}
		void updater(float pop_percentage)
		{
			int counter = 1;
			int exit = 0;
			vector<int> infections;
			infections.push_back(1);
			while (exit == 0)
			{
				for (int i = 0; i < pop_size; i++)
				{
					pop[i].update();
				}
				for (int i = 0; i < count_infected(); i++)
				{
					for (int j = 0; j < 10; j++)
					{
						float unlucky = (float) rand()/(float)RAND_MAX;
						if (unlucky > (1.0 - get_contagion()))
						{
							random_infect(0);
						}
					}
				}
				infections.push_back(count_infected());
				if (count_infected() == 0)
				{
					exit = 1;
					std::ofstream out_data;
					out_data.open("Brian_Horsley_finalproject.txt", std::ios::out | std::ios::app);
					out_data << "" << endl;
					out_data << counter  << endl;
					out_data << "Vaccinated Population Percentage: " << pop_percentage << "%" << endl;
					for (int i = 0; i < infections.size(); i++)
					{
						out_data << infections[i] << endl;
					}
					out_data.close();
				}
				counter += 1;
			}
		}
		float get_contagion()
		{
			return contagion;	
		}
		int get_pop_size()
		{
			return pop_size;
		}
};

int main()
{
	int num_people;
	float contagion_prob;
	srand(time(NULL));
	cout << "This is a simple disease propagation simulation..." << endl;
	cout << "" << endl;
	cout << "What is the population size in question?" << endl;
	cin >> num_people;
	cout << "" << endl;
	cout << "What probability of infection would you like to test?" << endl;
	cin >> contagion_prob;
	vector<float> vaccination_tests;
	for (int i = 0; i < 10; i++)
	{
		vaccination_tests.push_back(i*0.1);
	}
	for (int i = 0; i < vaccination_tests.size(); i++)
	{
		Population pop(num_people, contagion_prob);
		pop.vaccine(vaccination_tests[i]);
		pop.random_infect(1);
		pop.updater(vaccination_tests[i]);
	}
}
