#ifndef _agent_h
#define _agent_h

#include <iostream>
#include "controller.h"
#include "stdlib.h"

using namespace std;

class agent
{
private:
	struct message
	{
		int x;				//destination coordinate
		int y;
		int a[80];
		int n;				//# agents met
	};
	message ctx;
	int start_x;
	int start_y;
	int k;					//move k steps
public:
	agent();
	~agent();
	void move();
	void communicate();
};

#endif