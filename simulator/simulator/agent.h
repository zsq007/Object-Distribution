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
	pair<int,int> current;
	int s;					//move s steps
	double k;				//slope of the line
	double b;				//intercept on y of the line
	int id;
	pair<int,int> dir;		//(-1,-1)left&down (-1,0)left (-1,1)left&up (0,1)up (1,1)right&up (1,0)right (1,-1)right&down (0,-1)down
	bool flagx =0;				//to distinguish whether the last step is a move in the y direction or the x direction

public:
	agent(int _id);
	~agent();
	pair<int,int> move();
	void communicate();
};

#endif