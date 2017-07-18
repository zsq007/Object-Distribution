#ifndef _agent_h
#define _agent_h

#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <time.h>

using namespace std;

class agent
{
private:
	int d;
	int min_dist, max_dist;
	int turn_left_para, turn_right_para;

	vector<pair <int, int> > private_trk_pool;
	vector<vector <pair <int, int> > > public_trk_pool;

	vector<vector <bool> > private_mem_map;
	vector<vector <vector <bool> > > public_mem_map;

	vector<vector <vector <bool> > > I;
	
	pair<int, int> start;
	pair<int, int> dest;
	pair<int, int> current;
	
	int dir;				// direction on track, 1 for start->dest, -1 for dest->start
	int s;					// move s steps
	int id;
	int current_step;
	int agent_num;
	
	enum direction { up, left, down, right };
	enum position_state { middle, _up, _down, _left, _right, up_left, up_right, down_left, down_right };

public:
	agent(int _id, int _d, pair<int, int> _dist, pair<int, int> _turn_par, vector<vector <vector <bool> > > _I, vector<vector<pair<int,int>>> _trace_pool);
	~agent(){}

	struct object
	{
		int type;
		int num;
		string information;
	};
	object obj;
	vector<vector <object> > mem_obj_pool;

	struct message
	{
		vector<int> met_agents;
		vector<pair <int, int> > prv_trk_pool;
		vector<vector <vector <bool> > > memory_map;
		vector<vector <pair <int,int> > > track_map;
	};
	message ctx;

	void set_mem_map(vector<vector <bool> > _private_mem_map);
	void set_mem_obj_pool(vector<vector <object> > _mem_obj_pool);

	void track_generate();
	void move();
	bool is_intersect(int p_id);

	message send_message();
	void recv_message(message msg, int from_id);
	object send_object(pair <int,int> object_number);
	void recv_object(object obj, pair <int,int> obj_coordinate, int from_id);

	vector<vector <pair <int,int> > > merge_public_trk_pool(vector<vector <pair <int,int> > > my_pool, vector<vector <pair <int,int> > > other_pool);
	vector<vector <vector <bool> > > merge_mem_map(vector<vector <vector <bool> > > my_map, vector<vector <vector <bool> > > other_map);

	vector<pair <int,int> > decision(int to_id);

	vector<vector <bool> > get_prv_mem_map()
	{
		return private_mem_map;
	}
	vector<vector <vector <bool> > > get_pub_mem_map()
	{
		return public_mem_map;
	}
	pair <int, int> get_current_position()
	{
		return current;
	}
	vector<pair<int,int>> get_prv_trk_pool()
	{
		return private_trk_pool;
	}
	int get_distance()
	{
		return s;
	}
};

#endif