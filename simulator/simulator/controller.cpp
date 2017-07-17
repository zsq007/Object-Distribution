#include "controller.h"
#include "agent.h"

controller::controller(int map_size, int agent_number, int max_round, pair<int,int> distance_range, pair<int,int> turning_probability)
{
	int i;

	d = map_size;
	max_run_time = max_round;
	agent_num = agent_number;
	dist_range = distance_range;
	turn_para = turning_probability;

	for(i = 0; i < agent_num; i++)
		agt.push_back(agent(i, d, dist_range, turn_para));
	
}

void controller::run()
{
	int i, j, k;
	agent::message msg;
	vector<vector <int> > same_pos_agt;
	vector<pair <int,int> >	objnum;
	agent::object obj;


	round = 0;

	while(!check_terminate())
	{
		if(get_round() >= max_run_time)	break;

		same_pos_agt.swap(vector<vector <int> >());					// clear the vector same_pos_agt
		for(i = 0; i < agent_num; i++)
		{
			agt[i].move();
		}

		for(i = 0; i < agent_num; i++)
		{
			for( j = 0; j < agent_num; j++)
			{
				if(same_position(agt[i].get_current_position(), agt[j].get_current_position()) && i != j)		// judge whether agent i and j are in the same position
				{
					msg = agt[i].send_message();							// i send the msg to j
					agt[j].recv_message(msg, i);
					same_pos_agt[i].push_back(j);
				}
			}
		}

		for(i = 0; i < agent_num; i++)
		{
			for(j = 0; j < same_pos_agt[i].size(); j++)
			{
				objnum.swap(vector<pair <int, int> >());							// clear the vector obj_num
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
		round++;
	}

	if(get_round() < max_run_time)
	{
		printf("Finished. Run time is %d.\n",get_round());
	}
	else
	{
		printf("Time out. Failed to send the messages.\n");
	}
}


bool controller::check_terminate()
{
	int i, j, k;
	vector<vector <bool> > bit_map;

	for(i = 0; i < agent_num; i++)
	{
		bit_map = agt[i].get_prv_mem_map();
		for(j = 0; j < I[i].size(); j++)
		{
			for(k = 0; k < I[i][j].size(); k++)
			{
				if(I[i][j][k] ^ bit_map[j][k])	return false;
			}
		}
	}
	return true;
}

bool controller::same_position(pair <int,int> i, pair <int,int> j)
{
	if(i.first == j.first
		&& i.second == j.second)
	{
		return true;
	}
	else return false;
}
