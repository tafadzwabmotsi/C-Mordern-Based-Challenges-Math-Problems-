#include <iostream>
#include <stdlib.h>
#include <numeric>
#include <string>
#include <bitset>

#include "Modules.h"

int main()
{
	std::string_view isbn = "0198534531";

	if (validateISNB(isbn)) {
		std::cout << "Valid";
	}

	else {
		std::cout << "Invalid";
	}
	std::printf("\n");
}