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
	int move_para;
	vector<vector <int> > run_time;
	
//  controller(map_size, agent_number, max_round, distance_range, turning_probability, topic_object);
	controller ctl(100, 100,			10000, make_pair(100, 2000), make_pair(20, 20), make_pair(10, 200));

	run_time.resize(11);
	for (i = 0; i <= 100; i += 10)
	{
		for (j = 0; j < 10; j++)
		{
			run_time[i].push_back(ctl.run(i));
		}
	}

	FILE *fd1;
	fd1 = fopen("run_time_log.txt", "w+");
	for (i = 0; i <= 100; i += 10)
	{
		for (j = 0; j < 10; j++)
		{
			fprintf(fd1, "%d\t", run_time[i][j]);
		}
		fprintf(fd1, "\n");
	}
	fclose(fd1);

    return 0;
}
