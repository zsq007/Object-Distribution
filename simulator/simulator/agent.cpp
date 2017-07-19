#include "agent.h"

agent::agent(int _id, int _d, pair<int,int> _dist, pair<int,int> _turn_para, vector<vector <vector <bool> > > _I, vector<vector<pair<int,int> > > _trace_pool) :
	id(_id), d(_d), I(_I), agent_num(_I.size()), min_dist(_dist.first), max_dist(_dist.second), 
	turn_left_para(_turn_para.first), turn_right_para(_turn_para.second), dir(1), current_step(0)
{
	// id = _id;
	// d = _d;
	// I = _I;
	// agent_num = _I.size();

	// min_dist = _dist.first;
	// max_dist = _dist.second;
	// turn_left_para = _turn_para.first;
	// turn_right_para = _turn_para.second;

	start.first = rand() % d;
	start.second = rand() % d;
	s = min_dist + rand() % (max_dist - min_dist + 1);

	current.first = start.first;
	current.second = start.second;
	// dir = 1;
	// current_step = 0;

	public_trk_pool.resize(agent_num);
	for(int i = 0; i < agent_num; i++)
	{
		public_trk_pool[i].push_back(make_pair(-1,-1));
	}
		
	bool flag = false;

	track_generate();
	
	while(!flag && !_trace_pool.empty())
	{
		private_trk_pool.clear();
		public_trk_pool[id].clear();
		public_trk_pool[id].push_back(make_pair(-1,-1));
		track_generate();
		for(size_t i = 0; i < _trace_pool.size() && !flag; i++)
		{
			for(size_t j = 0; j < _trace_pool[i].size() && !flag; j++)
			{
				for(size_t k = 0; k < private_trk_pool.size() && !flag; k++)
					if(_trace_pool[i][j] == private_trk_pool[k]) 
					{
						flag = true;
						break;
					}
			}
		}	
	}

	dest = private_trk_pool[s - 1];	
}

void agent::set_mem_map(vector<vector <bool> > _private_mem_map)
{
	private_mem_map = _private_mem_map;

	public_mem_map.resize(agent_num);
	for (int i = 0; i < agent_num; i++)
	{
		public_mem_map[i].resize(_private_mem_map.size());
		for (size_t j = 0; j < _private_mem_map.size(); j++)
		{
			public_mem_map[i][j].resize(_private_mem_map[j].size());
			for (size_t k = 0; k < public_mem_map[i][j].size(); k++)
				public_mem_map[i][j][k] = false;
		}
	}
	public_mem_map[id] = private_mem_map;
}

void agent::set_mem_obj_pool(vector<vector <object> > _mem_obj_pool)
{
	mem_obj_pool.resize(_mem_obj_pool.size());
	for(size_t i = 0; i < _mem_obj_pool.size(); i++)
	{
		mem_obj_pool[i].resize(_mem_obj_pool[i].size());
		for (size_t j = 0; j < mem_obj_pool[i].size(); j++)
		{
			if (private_mem_map[i][j])
				mem_obj_pool[i][j] = _mem_obj_pool[i][j];
			else
			{
				mem_obj_pool[i][j].type = -1;
				mem_obj_pool[i][j].num = -1;
				mem_obj_pool[i][j].information = "";
			}
		}					
	}
}

void agent::move(int _move_para)
{
	if (s == 1 || rand() % 100 < _move_para)
		return;
	
	if (current_step == 0)
		dir = 1;
	else if (current_step == s - 1)
		dir = -1;

	if (dir == 1)
		current_step++;
	else if (dir == -1)
		current_step--;

	current = private_trk_pool[current_step];
}

bool agent::is_intersect(int p_id)
{
	for (size_t i = 0; i < private_trk_pool.size(); i++)
	{
		for (size_t j = 0; j < public_trk_pool[p_id].size(); j++)
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
	public_trk_pool[from_id] = msg.prv_trk_pool;
	public_trk_pool = merge_public_trk_pool(public_trk_pool, msg.track_map);
	
	//public_mem_map = merge_mem_map(public_mem_map, msg.memory_map);
	for(size_t j = 0; j < msg.memory_map[from_id].size(); j++)
	{
		for(size_t k = 0; k < msg.memory_map[from_id][j].size(); k++)
		{
			public_mem_map[from_id][j][k] = msg.memory_map[from_id][j][k];
		}
	}
}

agent::object agent::send_object(pair<int, int> object_number)
{
	return mem_obj_pool[object_number.first][object_number.second];
}

void agent::recv_object(agent::object obj, pair <int,int> obj_coordinate, int from_id)
{	
	mem_obj_pool[obj_coordinate.first][obj_coordinate.second] = obj;
	private_mem_map[obj_coordinate.first][obj_coordinate.second] = true;
	public_mem_map[id][obj_coordinate.first][obj_coordinate.second] = true;
}

vector<vector <pair <int,int> > > agent::merge_public_trk_pool(vector<vector <pair <int,int> > > my_pool, vector<vector <pair <int,int> > > other_pool)
{
	for(size_t i = 0; i < my_pool.size(); i++)
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
	for(size_t i = 0; i < my_map.size(); i++)
	{
		for(size_t j = 0; j < my_map[i].size(); j++)
		{
			for(size_t k = 0; k < my_map[i][j].size(); k++)
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
	vector<pair <int, int> > object_coordinate;

	// Naive method: send all objects
	for(size_t j = 0; j < public_mem_map[to_id].size(); j++)
	{
		for(size_t k = 0; k < public_mem_map[to_id][j].size(); k++)
		{
			if (!public_mem_map[to_id][j][k] && private_mem_map[j][k])
			{
				object_coordinate.push_back(make_pair(j, k));
			}				
		}
	}

	return object_coordinate;
}

void agent::track_generate()
{
	enum direction gen_dir;
	enum position_state pos_state;
	int dir_para;
	pair <int,int> new_pos = start;

	if (!private_trk_pool.empty())
		private_trk_pool.clear();

	private_trk_pool.push_back(new_pos);
	public_trk_pool[id].push_back(new_pos);
	dir_para = rand() % 100;
	if (dir_para < 25) gen_dir = up;
	else if (dir_para < 50) gen_dir = down;
	else if (dir_para < 75) gen_dir = left;
	else gen_dir = right;

	for (int i = 0; i < s; i++)
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
				public_trk_pool[id].push_back(new_pos);
				break;
			}
			case down:
			{
				new_pos.second -= 1;
				private_trk_pool.push_back(new_pos);
				public_trk_pool[id].push_back(new_pos);
				break;
			}
			case right:
			{
				new_pos.first += 1;
				private_trk_pool.push_back(new_pos);
				public_trk_pool[id].push_back(new_pos);
				break;
			}
			case left:
			{
				new_pos.first -= 1;
				private_trk_pool.push_back(new_pos);
				public_trk_pool[id].push_back(new_pos);
				break;
			}
		}
	}
}
