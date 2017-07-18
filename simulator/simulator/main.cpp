#include "controller.h"
#include "agent.h"
#include <time.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
	srand((unsigned)time(NULL));

	int i, j;
	int t, o;

	vector<vector <agent::object> > mem_pool;
	agent::object obj;
	/*cout << "input topic numbers:";
	cin >> t;
	cout << "input object number for every topic:";
	cin >> o;*/
	t = 10;
	o = 20;
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
	controller ctl(20, 50, 500, make_pair(10,30), make_pair(10,10), mem_pool);
	ctl.run();
	system("pause");
    return 0;
}
