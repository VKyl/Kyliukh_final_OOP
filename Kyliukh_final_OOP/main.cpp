#include <iostream>
#include "Time.h"


int main()
{
	Time t1 = Time(1, 5, 2);
	Time t2 = Time(59, 58, 6);
	std::cout << ++t2 << std::endl;
	return 0;
}