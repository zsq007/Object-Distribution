#include "controller.h"
#include "agent.h"
#include <cstdlib>

void controller::run()
{
	int i, j, k;
	agent agt[n];
	message msg;
	vector<vector <int> > same_pos_agt;
	vector<pair <int,int> >	objnum;
	object obj;

	for(i = 0; i < n; i++)
		agt[i].agent(i);
	controller.round = 0;

	while(!controller.check_terminate())
	{
		if(controller.get_round() >= MAX_RUN_TIME)	break;

		same_pos_agt.swap(vector<vector <int> >());					// clear the vector same_pos_agt
		for(i - 0; i < n; i++)
		{
			agt[i].move();
		}

		for(i = 0; i < n; i++)
		{
			for( j = 0; j < n; j++)
			{
				if(controller.same_position(i, j) && i != j)		// judge whether agent i and j are in the same position
				{
					msg = agt[i].send_message();							// i send the msg to j
					agt[j].recv_message(msg, i);
					same_pos_agt[i].push_back(j);
				}
			}
		}

		for(i = 0; i < n; i++)
		{
			for(j = 0; j < same_pos_agt[i].size(); j++)
			{
				objnum.swap(vector<int>());							// clear the vector obj_num
				objnum = agt[i].decision(j);						// Run the distributed algorithm
				if(objnum.empty())
					continue;
				for(k = 0; k < objnum.size(); k++)
				{
					obj = agt[i].send_object(objnum[k]);
					agt[j].recv_object(obj, i);
				}
			}

		}
		controller.round++;
	}

	if(controller.get_round() < MAX_RUN_TIME)
	{
		printf("Finished. Run time is %d.\n", controller.get_round());
	}
	else
	{
		printf("Time out. Failed to send the messages.\n");
	}
}


bool controller::check_terminate()
{
	I = get_interest_matrix();

	for(i = 0; i < n; i++)
	{
		bit_map = agt[i].get_prv_mem_map();
		for(j = 0; j < I[i].size(); j++)
		{
			for(k = 0; k < I[i][j].size(); k++)
			{
				if(!(I[i][j][k] & bit_map[j][k]))	return false;
			}
		}
	}
	return true;
}

bool controller::same_position(int i, int j)
{
	if(agt.[i].now.first == agt.[j].now.first
		&& agt[i].now.second == agt[j].now.second)
	{
		return True;
	}
	else return False;
}
