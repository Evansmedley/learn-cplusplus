// #include <plog/Log.h>
// #include <plog>Initializers/RollingFileInitializer.h>
// #include <iostream>

// int getUserInput()
// {
//     PLOGD << "getUserInput() called";
//     std::cout << "Enter a number: ";
//     int x{};
//     std::cin >> x;
//     return x;
// }

// int main()
// {
//     plog::init(plog::debug, "Logfile.txt"); // Initialize logger

//     PLOGD << "main() called"; // Output to log

//     int x{ getUserInput() };
//     std::cout << "You entered: " << x << '\n';

//     return 0
// }


// DOES NOT WORK UNLESS YOU INSTALL PLOG