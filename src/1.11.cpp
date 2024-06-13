#include <iostream>

int one_point_eleven() 
{
    std::cout << "Enter an integer: ";

    int num{ };
    std::cin >> num;

    std::cout << "Double that number is: " << num * 2 << '\n';

    return 0;
}