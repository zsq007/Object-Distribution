#include "controller.h"
#include "agent.h"
#include <stdio.h>

controller::controller(int map_size, int agent_number, int max_round, pair<int,int> distance_range, pair<int,int> turning_probability, pair<int,int> topic_object)
{
	int i, j, k;
	agent::object temp_obj;

	srand((unsigned)time(NULL));

	d = map_size;
	max_run_time = max_round;
	agent_num = agent_number;
	dist_range = distance_range;
	turn_para = turning_probability;

	mem_pool.resize(topic_object.first);
	for (i = 0; i < topic_object.first; i++)
	{
		for (j = 0; j < topic_object.second; j++)
		{
			temp_obj.type = i;
			temp_obj.num = j;
			temp_obj.information = "This is the ";
			temp_obj.information.push_back('a' + j - 1);
			temp_obj.information += "th object in ";
			temp_obj.information += ('a' + i - 1);
			temp_obj.information += "th topic";
			mem_pool[i].push_back(temp_obj);
		}
	}

	I.resize(agent_num);
	for(i = 0; i < agent_num; i++)
	{
		I[i].resize(topic_object.first);
		for (j = 0; j < topic_object.first; j++)
		{
			I[i][j].resize(topic_object.second);
			for (k = 0; k < topic_object.second; k++)
				I[i][j][k] = false;
		}
	}
	for(j = 0; j < mem_pool.size(); j++)
	{
		for(k = 0; k < mem_pool[j].size(); k++)
		{
			I[rand() % agent_num][j][k] = true;
		}
	}

	mem_map.resize(agent_num);
	for(i = 0; i < agent_num; i++)
	{
		mem_map[i].resize(topic_object.first);
		for (j = 0; j < topic_object.first; j++)
		{
			mem_map[i][j].resize(topic_object.second);
			for (k = 0; k < topic_object.second; k++)
				mem_map[i][j][k] = false;
		}
	}
	for (j = 0; j < topic_object.first; j++)
	{
		for (k = 0; k < topic_object.second; k++)
		{
			mem_map[rand() % agent_num][j][k] = true;
		}
	}

	for(i = 0; i < agent_num; i++)
	{
		agt.push_back(agent(i, d, dist_range, turn_para, I, trace_pool));
		trace_pool.push_back(agt[i].get_prv_trk_pool());
	}

	printf("Controller initialization finished.\n");
}

int controller::run(int _move_para)
{
	int i, j, k;
	agent::message msg;
	vector<vector <int> > same_pos_agt;
	vector<pair <int,int> >	objnum;
	agent::object obj;

	same_pos_agt.resize(agent_num);
	for(i = 0; i < agent_num; i++)
	{
		same_pos_agt[i].resize(agent_num);
		agt[i].set_mem_map(mem_map[i]);
		agt[i].set_mem_obj_pool(mem_pool);
	}	

	objnum.resize(mem_pool.size()*mem_pool[0].size());

	round = 0;

	while(!check_terminate())
	{
		if(round >= max_run_time)	break;

		for (i = 0; i < agent_num; i++)
			same_pos_agt[i].clear();					// clear the vector same_pos_agt

		for(i = 0; i < agent_num; i++)
		{
			agt[i].move(_move_para);
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
				objnum.clear();							// clear the vector obj_num
				objnum = agt[i].decision(same_pos_agt[i][j]);						// Run the distributed algorithm
				if(objnum.empty())
					continue;
				for(k = 0; k < objnum.size(); k++)
				{
					printf("Round: %d, agent: %d, same_position_agt: %d, obj_to_send: %d, object_coordinate: %d, %d\n", round, i, same_pos_agt[i][j], objnum.size(), objnum[k].first, objnum[k].second);
					obj = agt[i].send_object(objnum[k]);
					agt[same_pos_agt[i][j]].recv_object(obj, objnum[k], i);
				}
			}
		}
		round++;
	}

	if(round < max_run_time)
	{
		printf("Finished. Run time is %d.\n", round);
		return round;
	}
	else
	{
		printf("Time out. Failed to send the messages.\n");
		return -1;
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
				if(I[i][j][k] == true && bit_map[j][k] == false)	return false;
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
