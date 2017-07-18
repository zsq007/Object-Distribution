#include "controller.h"
#include "agent.h"

controller::controller(int map_size, int agent_number, int max_round, pair<int,int> distance_range, pair<int,int> turning_probability, vector<vector <agent::object> > _mem_pool)
{
	int i, j, k;
	FILE *fd1;
	
	fprintf(fopen("track_log.txt", "w+"), "");

	srand((unsigned)time(NULL));

	d = map_size;
	max_run_time = max_round;
	agent_num = agent_number;
	dist_range = distance_range;
	turn_para = turning_probability;

	mem_pool = _mem_pool;

	I.resize(agent_num);
	for(i = 0; i < agent_num; i++)
	{
		I[i].resize(_mem_pool.size());
		for(j = 0; j < _mem_pool.size(); j++)
		{
			I[i][j].resize(_mem_pool[j].size());
			for (k = 0; k < I[i][j].size(); k++)
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
	for(i = 0; i < mem_map.size(); i++)
	{
		mem_map[i].resize(_mem_pool.size());
		for(j = 0; j < _mem_pool.size(); j++)
		{
			mem_map[i][j].resize(_mem_pool[j].size());
			for (k = 0; k < mem_map[i][j].size(); k++)
				mem_map[i][j][k] = false;
		}
	}
	for(j = 0; j < mem_pool.size(); j++)
	{
		for(k = 0; k < mem_pool[j].size(); k++)
		{
			mem_map[rand() % agent_num][j][k] = true;
		}
	}

	for(i = 0; i < agent_num; i++)
	{
		agt.push_back(agent(i, d, dist_range, turn_para, I));
		agt[i].set_prv_mem_map(mem_map[i]);
		agt[i].set_mem_obj_pool(mem_pool);

		fd1 = fopen("track_log.txt", "a+");
		fprintf(fd1, "Agent node: %d, roaming distance: %d\n", i, agt[i].get_distance());
		fclose(fd1);
	}

	printf("Controller initialization finished.\n");
}

void controller::run()
{
	int i, j, k;
	agent::message msg;
	vector<vector <int> > same_pos_agt;
	vector<pair <int,int> >	objnum;
	agent::object obj;
	
	srand((unsigned)time(NULL));

	same_pos_agt.resize(agent_num);
	for(i = 0; i < agent_num; i++)
	{
		same_pos_agt[i].resize(agent_num);
	}	

	objnum.resize(mem_pool.size()*mem_pool[0].size());

	round = 0;

	while(!check_terminate())
	{
		if(get_round() >= max_run_time)	break;

		for (i = 0; i < agent_num; i++)
			same_pos_agt[i].clear();					// clear the vector same_pos_agt

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
				objnum.clear();							// clear the vector obj_num
				objnum = agt[i].decision(same_pos_agt[i][j]);						// Run the distributed algorithm
				if(objnum.empty())
					continue;
				for(k = 0; k < objnum.size(); k++)
				{
					printf("Round: %d, agent: %d, same_position_agt: %d, obj_to_send: %d, object_coordinate: %d, %d\n", round, i, same_pos_agt[i][j], objnum.size(), objnum[k].first, objnum[k].second);
					obj = agt[i].send_object(objnum[k]);
					agt[j].recv_object(obj, objnum[k], i);
				}
			}

			//printf("Agent: %d, round %d\n", i, round);
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
				if(I[i][j][k] & !bit_map[j][k])	return false;
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
