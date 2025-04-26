#include <iostream>
#include "Date.h"

// use date > 1970
int main()
{
	Date d(2, 1, 1970);
	std::cout << d  - 1 << std::endl;
	return 0;
}