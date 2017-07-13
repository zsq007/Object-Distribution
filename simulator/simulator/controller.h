#include <iostream>
using namespace std;

class controller
{
private:
	int round;
	int d;
	int **I;

public:
	controller(int r, int size, int **a)
	{
		round = r;
		d = size;
		I = a;
	}
	~controller();
	void run();
	bool check_terminate();
}