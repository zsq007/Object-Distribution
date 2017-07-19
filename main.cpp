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
	//vector<vector <int> > run_time;
	FILE *fd1;
	
//  controller(map_size, agent_number, max_round, distance_range, turning_probability, topic_object);
	controller ctl(100, 100, 50000, make_pair(100, 2000), make_pair(20, 20), make_pair(10, 200));
	for(i = 0; i < 50; i ++)
	{
		fd1 = fopen("run_time_log_naive.txt", "a+");
		fprintf(fd1, "%d\t", ctl.run_naive(10));
		fclose(fd1);
		fd1 = fopen("run_time_log_20_random.txt", "a+");
		fprintf(fd1, "%d\t", ctl.run_20_random(10));
		fclose(fd1);
		fd1 = fopen("run_time_log_20_interest.txt", "a+");
		fprintf(fd1, "%d\t", ctl.run_20_interest(10));
		fclose(fd1);
	}

    return 0;
}
