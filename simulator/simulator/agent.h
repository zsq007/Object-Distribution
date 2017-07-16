#ifndef _agent_h
#define _agent_h

#include <iostream>
#include "controller.h"
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;

class agent
{
private:
	struct message
	{
		pair<int,int> start;
		pair<int,int> dest;	//destination coordinate
		vector<int> met_agents;
		vector<vector <vector <bool> > > memory_map;
		vector<trk> track_map;
	};
	message ctx;

	struct track
	{
		pair<int,int> start;
		pair<int,int> dest;
	};
	track trk;
	vector<vector <object> > mem_obj_pool;
	vector<vector <bool> > private_mem_map;
	vector<vector <vector <bool> > > public_mem_map;
	vector<trk> mem_trk_pool;
	pair<int,int> start;
	pair<int,int> dest;
	pair<int,int> now;
	int k;					//move k steps
	int id;

public:
	agent(int _id);
	~agent();
	pair<int,int> move();
	bool is_intersect(int p_id);
	message send_message();
	void recv_message(message msg, int from_id);
	object send_object(pair<int,int> object_number);
	void recv_object(object obj, int from_id);
	vector<trk> merge_mem_trk_pool(vector<trk> my_pool, vector<trk> other_pool);
	vector<vector <vector <bool> > > merge_mem_map(vector<vector <vector <bool>>> my_map, vector<vector <vector <bool>>> other_map);
	vector<pair <int,int> > decision(int to_id);

	vector<vector <bool> > get_prv_mem_map()
	{
		return private_mem_map;
	}
	vector<vector <vector <bool> > > get_pub_mem_map()
	{
		return public_mem_map;
	}
};

#endif