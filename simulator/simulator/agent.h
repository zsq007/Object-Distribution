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
		pair<int,int> dest;	//destination coordinate
		vector<int> met_agents;
	};
	message ctx;
	pair<int,int> start;
	pair<int,int> dest;
	pair<int,int> now;
	int k;					//move k steps
	int id;

public:
	agent(int _id);
	~agent();
	pair<int,int> move();
	void communicate();
};

#endif