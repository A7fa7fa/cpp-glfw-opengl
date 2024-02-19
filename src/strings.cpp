#include <iostream>
#include <string>

void charArray() {

    const char* name = "my name"; // char string array. pointer points to start of string
    std::cout << name << std::endl;
    char* name_mutabl = (char*)"mutable"; // stack allocated
    std::cout << name_mutabl << std::endl;
    // name_mutabl[1] = 'M'; // undefined behaviour. not allowed to change
    std::cout << name_mutabl << std::endl;

    char name_mutabl2[] = "changed";
    std::cout << name_mutabl2 << std::endl;
    name_mutabl2[0] = 'C';
    name_mutabl2[1] = 'C';
    std::cout << name_mutabl2 << std::endl;

    char name2[5] = {'N', 'a', 'm', 'e', 0}; // init as char arra with null temrination character. length is unknow. but ends at termination character
    std::cout << name2 << std::endl;
};

void stdString() {

    std::string name = "manuel";
    std::cout << name << name.size() << std::endl;

    name += "lastname";
    std::cout << name << std::endl;

    std::string var = std::string("manuel") + "Hello!";
    std::cin.get();
};
