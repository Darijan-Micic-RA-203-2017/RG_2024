#include <iostream>

int main()
{
	std::cout << "Smart refrigerator (2D). UTF-8 znakovi: ČĆŠĐŽžđšćč" << std::endl;
	for (unsigned int i = 0u; i < 101u; i++)
	{
		std::cout << "Write temperature: " << i << " Celsius degrees" << std::endl;
	}

	return 0;
}
