
#include <iostream> 

namespace MNE {

class Sendable {
public: 
int s1;
int s2;
int s3;
void print() {
    std::cout << "s1: " << s1 << "\n";
    std::cout << "s2: " << s2 << "\n";
    std::cout << "s3: " << s3 << "\n";
}
};

Sendable* store;

void archive(const char* id, Sendable s) {
    std::cout << "Archiving object with id: " << id << "\n";
    s.print();
    store = new Sendable(s);
}
template<typename T>
T retrieve(const char* id) {
    std::cout << "Retrieving object: " << id << "\n";
    T retrievedObj(*store);
    return retrievedObj;
}

} //MNE namespace

class A {
public: 
    A(int first, int second, int third)
        : uno(first), dos(second), tres(third) {
    };
    A(MNE::Sendable s) 
        : uno(s.s1), dos(s.s2), tres(s.s3) {
    };

    operator MNE::Sendable() { 
        MNE::Sendable newSendable;
        newSendable.s1 = this->uno;
        newSendable.s2 = this->dos;
        newSendable.s3 = this->tres;
        return newSendable;
    }
    void print() {
        std::cout << "uno: " << uno << "\n";
        std::cout << "dos: " << dos << "\n";
        std::cout << "tres: " << tres << "\n";
    }
private:
    int uno;
    int dos;
    float tres;
};

void pipeline1() {
    A a(1, 4, 6);
    MNE::archive("important_variable_123", a);
}

void pipeline2() {
    A a2 = MNE::retrieve<A>("important_variable_123");
    a2.print();    
}

int main() {

    pipeline1();
    
    pipeline2();
    
    delete MNE::store;
    return 0;
}
