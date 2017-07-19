#include "controller.h"

int controller::run_naive(int _move_para)
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
			msg = agt[i].send_message();							// i send the msg
			for( j = 0; j < agent_num; j++)
			{
				if(i != j & same_position(agt[i].get_current_position(), agt[j].get_current_position()))		// judge whether agent i and j are in the same position
				{
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
				objnum = agt[i].naive_decision(same_pos_agt[i][j]);						// Run the distributed algorithm
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
