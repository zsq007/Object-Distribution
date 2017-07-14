#ifndef _controller_h
#define _controller_h

#include <iostream>
using namespace std;

class controller
{
private:
	int round;
	int **I;

public:
	static int d;

	controller(int r, int size, int **a)
	{
		round = r;
		d = size;
		I = a;
	}
	~controller();
	void run();
	bool check_terminate();
	int get_max_size()
	{
		return d;
	}
	int get_round()
	{
		return round;
	}
	int ** get_interest_matrix()
	{
		return I;
	}
};

#endif