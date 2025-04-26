#include <iostream>
#include "Date.h"

// use date > 1970 month from 0 to 11
int main()
{
	Date d(2, 1, 1970);
	std::cout << d  - 1 << std::endl;
	return 0;
}