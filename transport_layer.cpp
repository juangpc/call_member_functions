
// https://stackoverflow.com/questions/4788965/when-would-anyone-use-a-union-is-it-a-remnant-from-the-c-only-days
// extracted from 
 
union Bee
{
    B1 b1;
    .
    .
    .
    Bn bn;
};

enum BeesTypes { TYPE_B1, ..., TYPE_BN };

class A
{
private:
    std::unordered_map<int, Bee> data; // C++11, otherwise use std::map

public:
    Bee get(int); // the implementation is obvious: get from the unordered map
};


