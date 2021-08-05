#include <iostream>
#include <string>

// void print(std::string&& s)
// {
//     std::cout << "1 - " << s << "\n";
// }

// void print(const std::string&& s)
// {
//     std::cout << "2 - " << s << "\n";
// }

void print(const std::string& s)
{
    std::cout << "3 - " << s << "\n";
}

void print(const char s[])
{
    std::cout << "4 - " << s << "\n";
}

int main()
{

    std::string name{"Pepe"};

    print(name);
    print(std::move(name));
    print("Antonio");

    print(name);

    return 0;
}