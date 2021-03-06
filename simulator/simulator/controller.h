#ifndef _controller_h
#define _controller_h

#include "agent.h"

using namespace std;

class controller
{
private:
	int round;
	int max_run_time;
	int agent_num;
	int d;

	pair <int, int> dist_range;
	pair <int, int> turn_para;

	vector<vector <vector <bool> > > I;
	vector<vector <agent::object> > mem_pool;
	vector<vector <vector <bool> > > mem_map;		// Recording the initial memory map of everyone
	vector<agent> agt;
	vector<vector<pair<int, int> > > trace_pool;

public:
	controller(int map_size, int agent_number, int max_round, pair<int, int> distance_range, pair<int, int> turning_probability, pair<int, int> topic_object);
	~controller() {}

	int run(int _move_para);
	bool same_position(pair <int, int> i, pair <int, int> j);
	bool check_terminate();

	int get_max_size()
	{
		return d;
	}
	int get_round()
	{
		return round;
	}

	vector<vector <vector <bool> > > get_interest_matrix()
	{
		return I;
	}
};

#endif
