#include "agent.h"
#include "controller.h"
#include "stdlib.h"
#include "time.h"

agent::agent(int _id)
{
	srand((unsigned)time(NULL));
	start.first = rand() % controller.d;
	start.second = rand() % controller.d;
	dest.first = rand() % controller.d;
	dest.second = rand() % controller.d;
	while(dest.first == start.first)
	{
		dest.first = rand() % controller.d;
	}
	while(dest.second == start.second)
	{
		dest.second = rand() % controller.d;
	}
	s = abs(dest.second - start.second) + abs(dest.first - start.first);
	k = (dest.second - start.second) / (dest.first - start.first);
	b = dest.second - k * dest.first;
	current.first = start.first;
	current.second = start.second;
	ctx.dest.first = dest.first;
	ctx.dest.second = dest.second;
	id = _id;
	if(dest.second - start.second > 0 && dest.first - start.first == 0)
	{
		dir.first = 0;
		dir.second = 1;
	}
	else if(dest.second - start.second < 0 && dest.first - start.first == 0)
	{
		dir.first = 0;
		dir.second = -1;
	}
	else if(dest.second - start.second == 0 && dest.first - start.first > 0)
	{
		dir.first = 1;
		dir.second = 0;
	}
	else if(dest.second - start.second == 0 && dest.first - start.first < 0)
	{
		dir.first = -1;
		dir.second = 0;
	}
	else if(dest.second - start.second > 0 && dest.first - start.first > 0)
	{
		dir.first = 1;
		dir.second = 1;
	}
	else if(dest.second - start.second > 0 && dest.first - start.first < 0)
	{
		dir.first = -1;
		dir.second = 1;
	}
	else if(dest.second - start.second < 0 && dest.first - start.first > 0)
	{
		dir.first = 1;
		dir.second = -1;
	}
	else if(dest.second - start.second < 0 && dest.first - start.first < 0)
	{
		dir.first = -1;
		dir.second = -1;
	}
}

pair<int,int> agent::move()
{
	if(dir.first == 0 && dir.second == 1)
	{
		current.second = current.second + 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = 0;
			dir.second = -1;
		}
	}
	else if(dir.first == 1 && dir.second == 0)
	{
		current.first = current.first + 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = -1;
			dir.second = 0;
		}
	}
	else if(dir.first == 0 && dir.second == -1)
	{
		current.second = current.second - 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = 0;
			dir.second = 1;
		}
	}
	else if(dir.first == -1 && dir.second == 0)
	{
		current.first = current.first - 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = 1;
			dir.second = 0;
		}
	}
	else if(dir.first == 1 && dir.second == 1 && k * current.first + b > current.second)
	{
		current.second = current.second + 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = -1;
			dir.second = -1;
		}
	}
	else if(dir.first == 1 && dir.second == 1 && k * current.first + b <= current.second)
	{
		current.first = current.first + 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = -1;
			dir.second = -1;
		}
	}
	else if(dir.first == 1 && dir.second == -1 && k * current.first + b > current.second)
	{
		current.first = current.first + 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = -1;
			dir.second = 1;
		}
	}
	else if(dir.first == 1 && dir.second == -1 && k * current.first + b <= current.second)
	{
		current.second = current.second - 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = -1;
			dir.second = 1;
		}
	}
	else if(dir.first == -1 && dir.second == 1 && k * current.first + b > current.second)
	{
		current.second = current.second + 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = 1;
			dir.second = -1;
		}
	}
	else if(dir.first == -1 && dir.second == 1 && k * current.first + b <= current.second)
	{
		current.first = current.first - 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = 1;
			dir.second = -1;
		}
	}
	else if(dir.first == -1 && dir.second == -1 && k * current.first + b > current.second)
	{
		current.first = current.first - 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = 1;
			dir.second = 1;
		}
	}
	else if(dir.first == -1 && dir.second == -1 && k * current.first + b <= current.second)
	{
		current.second = current.second - 1;
		if(current.second == dest.second && current.first == dest.first)
		{
			dir.first = 1;
			dir.second = 1;
		}
	}
}

bool agent::is_intersect(int p_id)
{
	if(((start.second-dest.second) * (mem_trk_pool[p_id].start.first-dest.first) - (start.first-dest.first) * (mem_trk_pool[p_id].start.second-dest.second)) *
		((start.second-dest.second) * (mem_trk_pool[p_id].dest.first-dest.first) - (start.first-dest.first) * (mem_trk_pool[p_id].dest.second-dest.second)) <= 0)
		return true;
	else return false;
}

message agent::send_message()
{
	message msg;

	msg.start = start;
	msg.dest = dest;
	met_agent = ;

	return msg;
}

void agent::recv_message(message msg, int from_id)
{
	mem_trk_pool[from_id].start = msg.start;
	mem_trk_pool[from_id].dest = msg.dest;
	mem_trk_pool = merge_mem_trk_pool(mem_trk_pool, msg.track_map);
	
	//public_mem_map = merge_mem_map(public_mem_map, msg.memory_map);
	for(j = 0; j < msg.memory_map[from_id].size(); j++)
	{
		for(k = 0; k < msg.memory_map[from_id][j].size(); k++)
		{
			public_mem_map[from_id][j][k] = msg.memory_map[from_id][j][k];
		}
	}
}

object agent::send_object(pair<int,int> object_number)
{
	return mem_obj_pool[object_number.first][object_number.second];
}

void agent::recv_object(object obj, int from_id)
{
	
	mem_obj_pool[obj.type][obj.num] = obj;
	private_mem_map[obj.type][obj.num] = true;
	public_mem_map[id][obj.type][obj.num] = true;
}

vector<trk> agent::merge_mem_trk_pool(vector<trk> my_pool, vector<trk> other_pool)
{
	for(i = 0; i < n; i++)
	{
		if(my_pool[i] == NULL && other_pool[i] != NULL)
		{
			my_pool[i] = other_pool[i];
		}
	}

	return my_pool;
}

vector<vector <vector <bool> > > agent::merge_mem_map(vector<vector <vector <bool>>> my_map, vector<vector <vector <bool>>> other_map)
{
	for(i = 0; i < my_map.size(); i++)
	{
		for(j = 0; j < my_map[i].size(); j++)
		{
			for(k = 0; k < my_map[i][j].size(); k++)
			{
				if(!my_map[i][j][k] && other_map[i][j][k])
					my_map[i][j][k] = true;
			}
		}
	}

	return my_map;
}

vector<pair <int,int> > agent::decision(int to_id)
{
	vector<pair <int,int> > object_coordinate;

	// Naive method: send all objects
	for(j = 0; j < public_mem_map[to_id].size(); j++)
	{
		for(k = 0; k < public_mem_map[to_id][j].size(); k++)
		{
			if(!public_mem_map[to_id][j][k])
				object_coordinate.push(<j,k>);
		}
	}

	return object_coordinate;
}