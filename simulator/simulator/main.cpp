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
	//printf("%d, %d", rand() % 100, rand() % 100);

	int t,o;
	vector<vector <agent::object> > mem_pool;
	agent::object obj;
	cout << "input topic numbers:";
	cin >> t;
	cout << "input object number for every topic:";
	cin >> o;
	int i,j;
	mem_pool.resize(t);
	for(i = 0; i < t; i ++)
	{
		for(j = 0; j < o; j++)
		{
			obj.type = 0;
			obj.num = 0;
			obj.information[0] = (i + 1) * (j + 1);
			mem_pool[i].push_back(obj);
		}
	}

	controller ctl(100, 20, 500, make_pair(30,60), make_pair(35,35), mem_pool);
	ctl.run();
	system("pause");
    return 0;
}
