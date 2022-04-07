#include <string>
#include <iostream>

//#include <Infrastructure>
class Infrastructure {

};

class Pepe {
    public:
    Pepe(int _n, const std::string& _s) 
    : s(_s), n(_n) {    }
    Pepe(Infrastructure inf) {
        //very smart logic
        (void) inf;
        s = "Done deal";
        n = 33;
    }
    std::string s;
    int n;
    operator int() {
        return n;
    }
    operator std::string() {
        return s;
    } 
};


int main() {

    Pepe p(3, "Pepismo");
    float a = p;
    std::string s = p;
    std::cout << " a = " << a << "\n";
    std::cout << " s = " << s << "\n";

    Infrastructure i;
    Pepe p2(i);

    return 0;
}
