#include "Dict.h"

#include <iostream>
#include <string>
#include <cassert>

int main()
{
	int i = 5;
	double k = 8;
	Dict<int, double> dict;
	dict.set(i, k);
	assert(dict.is_set(i) == true);
	assert(dict.is_set(5) == false);
	try {
		int d = 4;
		auto key_val = dict.get(d);
	}
	catch (const not_found_exception<int>& e) {
		std::cout << e.what() << " " << e.get_key() << std::endl;
	}
}

