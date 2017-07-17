#include "agent.h"
#include "controller.h"

agent::agent(int _id, int _d, pair<int,int> _dist, pair<int,int> _turn_para)
{
	id = _id;
	d = _d;
	min_dist = _dist.first;
	max_dist = _dist.second;
	turn_left_para = _turn_para.first;
	turn_right_para = _turn_para.second;
	srand((unsigned)time(NULL));
	start.first = rand() % d;
	start.second = rand() % d;
	s = min_dist + rand() % (max_dist - min_dist + 1);
	current.first = start.first;
	current.second = start.second;
	dir = 1;

	track_generate();
}

void agent::track_generate()
{
	int i;
	enum direction gen_dir;
	enum position_state pos_state;
	int dir_para;
	pair <int,int> new_pos = start;

	if (!private_trk_pool.empty())
		private_trk_pool.clear();

	private_trk_pool.push_back(new_pos);
	dir_para = rand() % 100;
	if (dir_para < 25) gen_dir = up;
	else if (dir_para < 50) gen_dir = down;
	else if (dir_para < 75) gen_dir = left;
	else gen_dir = right;

	for (i = 0; i < s; i++)
	{
		dir_para = rand() % 100;

		if (private_trk_pool[i].first == 0)
		{
			if (private_trk_pool[i].second == 0)
				pos_state = down_left;
			else if (private_trk_pool[i].second == d-1)
				pos_state = up_left;
			else
				pos_state = _left;
		}
		else if (private_trk_pool[i].first == d-1)
		{
			if (private_trk_pool[i].second == 0)
				pos_state = down_right;
			else if (private_trk_pool[i].second == d-1)
				pos_state = up_right;
			else
				pos_state = _right;
		}
		else
		{
			if (private_trk_pool[i].second == 0)
				pos_state = _down;
			else if (private_trk_pool[i].second == d-1)
				pos_state = _up;
			else
				pos_state = middle;
		}

		switch (pos_state)
		{
			case middle:
			{
				switch (gen_dir)
				{
					case left:
					{
						if (dir_para < turn_left_para)
							gen_dir = down;
						else if (dir_para < turn_left_para + turn_right_para)
							gen_dir = up;
						break;
					}
					case up:
					{
						if (dir_para < turn_left_para)
							gen_dir = left;
						else if (dir_para < turn_left_para + turn_right_para)
							gen_dir = right;
						break;
					}
					case down:
					{
						if (dir_para < turn_left_para)
							gen_dir = right;
						else if (dir_para < turn_left_para + turn_right_para)
							gen_dir = left;
						break;
					}
					case right:
					{
						if (dir_para < turn_left_para)
							gen_dir = up;
						else if (dir_para < turn_left_para + turn_right_para)
							gen_dir = down;
						break;
					}
				}
				break;
			}
			case _left:
			{
				switch (gen_dir)
				{
					case left:
					{
						if (dir_para < 50)
							gen_dir = up;
						else
							gen_dir = down;
						break;
					}
					case up:
					case down:
					{
						if (dir_para < turn_left_para + turn_right_para)
							gen_dir = right;
						break;
					}
					case right:
					{
						if (dir_para < turn_left_para)
							gen_dir = up;
						else if (dir_para < turn_left_para + turn_right_para)
							gen_dir = down;
						break;
					}
				}
				break;
			}
			case _right:
			{
				switch (gen_dir)
				{
					case right:
					{
						if (dir_para < 50)
							gen_dir = up;
						else
							gen_dir = down;
						break;
					}
					case up:
					case down:
					{
						if (dir_para < turn_left_para + turn_right_para)
							gen_dir = left;
						break;
					}
					case left:
					{
						if (dir_para < turn_left_para)
							gen_dir = down;
						else if (dir_para < turn_left_para + turn_right_para)
							gen_dir = up;
						break;
					}
				}
				break;
			}
			case _up:
			{
				switch (gen_dir)
				{
					case up:
					{
						if (dir_para < 50)
							gen_dir = left;
						else
							gen_dir = right;
						break;
					}
					case left:
					case right:
					{
						if (dir_para < turn_left_para + turn_right_para)
							gen_dir = down;
						break;
					}
					case down:
					{
						if (dir_para < turn_left_para)
							gen_dir = right;
						else if (dir_para < turn_left_para + turn_right_para)
							gen_dir = left;
						break;
					}
				}
				break;
			}
			case _down:
			{
				switch (gen_dir)
				{
					case down:
					{
						if (dir_para < 50)
							gen_dir = left;
						else
							gen_dir = right;
						break;
					}
					case left:
					case right:
					{
						if (dir_para < turn_left_para + turn_right_para)
							gen_dir = up;
						break;
					}
					case up:
					{
						if (dir_para < turn_left_para)
							gen_dir = left;
						else if (dir_para < turn_left_para + turn_right_para)
							gen_dir = right;
						break;
					}
				}
				break;
			}
			case down_left:
			{
				switch (gen_dir)
				{
					case right:
					{
						if (dir_para < turn_left_para + turn_right_para)
							gen_dir = up;
						break;
					}
					case up:
					{
						if (dir_para < turn_left_para + turn_right_para)
							gen_dir = right;
						break;
					}
					case left:
					{
						gen_dir = up;
						break;
					}
					case down:
					{
						gen_dir = right;
						break;
					}
				}
				break;
			}
			case down_right:
			{
				switch (gen_dir)
				{
					case left:
					{
						if (dir_para < turn_left_para + turn_right_para)
							gen_dir = up;
						break;
					}
					case up:
					{
						if (dir_para < turn_left_para + turn_right_para)
							gen_dir = left;
						break;
					}
					case right:
					{
						gen_dir = up;
						break;
					}
					case down:
					{
						gen_dir = left;
						break;
					}
				}
				break;
			}
			case up_right:
			{
				switch (gen_dir)
				{
					case left:
					{
						if (dir_para < turn_left_para + turn_right_para)
							gen_dir = down;
						break;
					}
					case down:
					{
						if (dir_para < turn_left_para + turn_right_para)
							gen_dir = left;
						break;
					}
					case right:
					{
						gen_dir = down;
						break;
					}
					case up:
					{
						gen_dir = left;
						break;
					}
				}
				break;
			}
			case up_left:
			{
				switch (gen_dir)
				{
					case right:
					{
						if (dir_para < turn_left_para + turn_right_para)
							gen_dir = down;
						break;
					}
					case down:
					{
						if (dir_para < turn_left_para + turn_right_para)
							gen_dir = right;
						break;
					}
					case left:
					{
						gen_dir = down;
						break;
					}
					case up:
					{
						gen_dir = right;
						break;
					}
				}
				break;
			}
		}


		switch (gen_dir)
		{
			case up:
			{
				new_pos.second += 1;
				private_trk_pool.push_back(new_pos);
				break;
			}
			case down:
			{
				new_pos.second -= 1;
				private_trk_pool.push_back(new_pos);
				break;
			}
			case right:
			{
				new_pos.first += 1;
				private_trk_pool.push_back(new_pos);
				break;
			}
			case left:
			{
				new_pos.first -= 1;
				private_trk_pool.push_back(new_pos);
				break;
			}
		}
	}
}

void agent::move()
{
	pair<int,int> tmp_pos;

	if (current_step == 0)
		dir = 1;

	if (current_step == s - 1)
		dir = -1;

	if (dir == 1)
		current_step++;
	else if (dir == -1)
		current_step--;

	current.first = private_trk_pool[current_step].first;
	current.second = private_trk_pool[current_step].second;
}

bool agent::is_intersect(int p_id)
{
	int i, j;
	
	for (i = 0; i < private_trk_pool.size(); i++)
	{
		for (j = 0; j < public_trk_pool[p_id].size(); j++)
		{
			if (private_trk_pool[i].first == public_trk_pool[p_id][j].first
				&& private_trk_pool[i].second == public_trk_pool[p_id][j].second)
				return true;
		}
	}
	return false;
}

agent::message agent::send_message()
{
	message msg;

	msg.prv_trk_pool = private_trk_pool;
	msg.memory_map = public_mem_map;
	msg.track_map = public_trk_pool;

	return msg;
}

void agent::recv_message(message msg, int from_id)
{
	int j, k;
	
	public_trk_pool[from_id] = msg.prv_trk_pool;
	public_trk_pool = merge_public_trk_pool(public_trk_pool, msg.track_map);
	
	//public_mem_map = merge_mem_map(public_mem_map, msg.memory_map);
	for(j = 0; j < msg.memory_map[from_id].size(); j++)
	{
		for(k = 0; k < msg.memory_map[from_id][j].size(); k++)
		{
			public_mem_map[from_id][j][k] = msg.memory_map[from_id][j][k];
		}
	}
}

agent::object agent::send_object(pair<int, int> object_number)
{
	return mem_obj_pool[object_number.first][object_number.second];
}

void agent::recv_object(agent::object obj, int from_id)
{
	
	mem_obj_pool[obj.type][obj.num] = obj;
	private_mem_map[obj.type][obj.num] = true;
	public_mem_map[id][obj.type][obj.num] = true;
}

vector<vector <pair <int,int> > > agent::merge_public_trk_pool(vector<vector <pair <int,int> > > my_pool, vector<vector <pair <int,int> > > other_pool)
{
	int i;

	for(i = 0; i < my_pool.size(); i++)
	{
		if(my_pool[i][0].first == -1 && other_pool[i][0].first != -1)
		{
			my_pool[i] = other_pool[i];
		}
	}

	return my_pool;
}

vector<vector <vector <bool> > > agent::merge_mem_map(vector<vector <vector <bool> > > my_map, vector<vector <vector <bool> > > other_map)
{
	int i, j, k;
	
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
	int j, k;
	pair <int, int> obj_co;
	vector<pair <int, int> > object_coordinate;

	// Naive method: send all objects
	for(j = 0; j < public_mem_map[to_id].size(); j++)
	{
		for(k = 0; k < public_mem_map[to_id][j].size(); k++)
		{
			if (!public_mem_map[to_id][j][k])
			{
				obj_co.first = j;
				obj_co.second = k;
				object_coordinate.push_back(obj_co);
			}				
		}
	}

	return object_coordinate;
}