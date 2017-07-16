#ifndef _controller_h
#define _controller_h

#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;

class controller
{
private:
	int round;
	int max_run_time;
	int agent_num;
	vector<vector <obj> > mem_pool;
	static vector<vector <vector <bool> > > I;
	struct object
	{
		int type;
		int num;
		char* content = new(20*sizeof(char));
	}
	object obj;

public:
	static int d;

	controller(int map_size, int max_round);
	~controller();
	void run();
	bool same_position(int i, int j);
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