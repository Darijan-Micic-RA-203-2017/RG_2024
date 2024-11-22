#include <iostream>

int main()
{
	std::cout << "Smart refrigerator." << std::endl;
	for (unsigned int i = 0u; i < 101u; i++)
	{
		std::cout << "Write temperature: " << i << " Celsius degrees" << std::endl;
	}

	return 0;
}
