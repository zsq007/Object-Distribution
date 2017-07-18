#include "controller.h"
#include "agent.h"
#include <time.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	srand((unsigned)time(NULL));

	int i, j, k;
	int t, o;

	vector<vector <agent::object> > mem_pool;
	agent::object obj;
	/*cout << "input topic numbers:";
	cin >> t;
	cout << "input object number for every topic:";
	cin >> o;*/
	t = 10;
	o = 200;
	mem_pool.resize(t);
	for(i = 0; i < t; i ++)
	{
		for(j = 0; j < o; j++)
		{
			obj.type = i;
			obj.num = j;
			obj.information = "This is the ";
			obj.information.push_back('a' + j - 1);
			obj.information += "th object in ";
			obj.information += ('a' + i - 1);
			obj.information += "th topic";
			mem_pool[i].push_back(obj);
		}
	}

	// controller(map_size, agent_number, max_round, distance_range, turning_probability, _mem_pool);
	//controller ctl(10, 50, 50, make_pair(5,15), make_pair(20,20), mem_pool, 50);
	/*
	vector<vector <vector <bool> > > I;
	I = ctl.get_interest_matrix();
	for(i = 0; i < I.size(); i++)
	{
		cout << "for" << i << "------" << endl;
		for(j = 0; j < I[i].size(); j++)
		{
			for(k = 0; k < I[i][j].size(); k++)
			{
				cout << I[i][j][k] << "\t";
			}
			cout << endl;
		}
	}
	system("pause");
	*/
	FILE *fd1 = fopen("probability.txt", "a+");
	FILE *fd2 = fopen("round.txt", "a+");
	controller ctl(100, 100, 10000, make_pair(100,2000), make_pair(20,20), mem_pool);
	for(i = 20; i < 80; i = i + 5)
	{
		ctl.set_move_prob(i);
		ctl.run();
		fprintf(fd1, "%d\n", i);
		fclose(fd1);
		fprintf(fd2, "%d\n", ctl.get_round());
		fclose(fd2);
	}
	system("pause");
    return 0;
}
