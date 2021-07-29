enum Outer { a = 1, b = 2, c = 3 };

template <typename>
struct S { enum Inner { a = 100, b = 102 }; };

template <int>
struct G { typedef int b; };

int main()
{
    // return S<G< 0 >>::c>::b>::a;
//    G< 0 >>::c>::b;
//    G< 0 >>::c>::b
    return S<int>::b>::a;
}