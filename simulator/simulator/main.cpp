//#include "controller.h"
#include <time.h>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main()
{
	srand((unsigned)time(NULL));
	printf("%d, %d", rand() % 100, rand() % 100);

	//controller ctl(100, 20, 500);
    return 0;
}
