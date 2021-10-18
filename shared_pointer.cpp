#include <iostream>
#include <string>

const std::string strs[8] = {"1","2","3","4","5","6","7","8"};
int num(0);

template<typename T>
class SharedPointer
{
public: 
    SharedPointer():_ptr{nullptr},_count{nullptr}, name(strs[num++])
    {
        std::cout << "constructor default\n";
        std::cout << *this;
     }
    SharedPointer(T* ptr)
    :_ptr{nullptr},_count{nullptr}, name(strs[num++])
    {
        std::cout << "constructor already init.\n";
        std::cout << *this;
        if ( ptr != nullptr )
        {
            _count = new unsigned int;
            *_count = 1;
            _ptr = ptr;
        }
        std::cout << "after constructor\n";
        std::cout << *this;
    }

    SharedPointer(const SharedPointer& other)
    : _ptr{other._ptr}, _count{other._count}, name(strs[num++])
    {
        std::cout << "copy constructor.\n";
        std::cout << *this;
        if( other._ptr != nullptr )
        {
            ++(*_count);
            std::cout << "cpy constructor. inside if\n";
            std::cout << *this;
        }
    }

    SharedPointer(SharedPointer&& other)
    {
        std::cout << "move constructor\n";
        std::cout << *this;
        if (other._ptr != nullptr)
        {
            _ptr = other._ptr;
            _count = other._count; 
            other._ptr = nullptr;
            other._count = nullptr;
            std::cout << "move constructor";
            std::cout << *this;
        }
    }

   SharedPointer& operator=(const SharedPointer& other)
    {
        std::cout << "copy assingment operator\n";
        std::cout << *this;
        if( this != &other )
        {
            if ( _ptr != nullptr )
            {
                (*_count)--;
                if ( *_count == 0 )
                {
                    std::cout << "copy assignment deleting pointers\n";
                    delete _count;
                    _count = nullptr;
                    delete _ptr;
                    _ptr = nullptr;
                }
            } 
            _ptr = other._ptr;
            _count = other._count;
            if ( _count != nullptr)
            {
                (*_count)++;
            }
            std::cout << "copy assignment operator\n";
            std::cout << *this;
        }
        return *this;
    }
 
   SharedPointer& operator=(SharedPointer&& other)
    {
        std::cout << "move assingment operator\n";
        std::cout << *this;
        if( this != &other )
        {
            if ( _ptr != nullptr )
            {
                (*_count)--;
                if ( *_count == 0 )
                {
                    std::cout << "move assignment deleting pointers\n";
                    delete _count;
                    _count = nullptr;
                    delete _ptr;
                    _ptr = nullptr;
                }
            } 
            _ptr = other._ptr;
            _count = other._count;
            if ( _count != nullptr)
            {
                (*_count)++;
            }
            std::cout << "move assignment operator\n";
            std::cout << *this;
        }
        return *this;
    }


    ~SharedPointer()
    {
        std::cout << "before destructor\n";
        std::cout << *this;
        if ( _ptr != nullptr )
        {
            (*_count)--;
            if ( *_count == 0 )
            {
                std::cout << "deleting pointers\n";
                delete _count;
                _count = nullptr;
                delete _ptr;
                _ptr = nullptr;
            }
        }
        std::cout << "after desctructor\n";
        std::cout << *this;
    }

    T* operator->()
    {
        return _ptr;
    }

    T* data()
    {
        return _ptr;
    }

    template<typename T2>
    friend std::ostream& operator<< ( std::ostream& os, const SharedPointer<T2>& ptr);
private:
    T* _ptr;
    unsigned int* _count;
    const std::string name;
};

template<typename T>
std::ostream& operator<< ( std::ostream& os, const SharedPointer<T>& ptr ) 
{
    os << "name: " << ptr.name << "\n";
    os << "_ptr: " << ptr._ptr << "\n";
    os << "_count Address: " << ptr._count << "\n";
    if (ptr._count)
    {
        os << "_count Value : " << *(ptr._count) << "\n";
    }
    os << "\n";

    return os;
}


int main()
{
    std::cout << "Starting app.\n\n";

    std::cout << "default constructor =========================\n";
    SharedPointer<int> p1, p2;
    
    std::cout << "constructor =========================\n";
    SharedPointer<int> p3(new int);

    std::cout << "copy constructor =========================\n";
    SharedPointer<int> p4 = p3;
    
    std::cout << "copy assignment ==========================\n";
    p1 = p2;
    p1 = p3;

    std::cout << "move assignment ==========================\n";
    SharedPointer<int> p5(new int);
    p5 = std::move(p3);


    std::cout << "copy assignment ==========================\n";
    p1 = p5;

    std::cout << "end of test ==============================\n\n";


    // SharedPointer<std::string> s1;
    // SharedPointer<std::string> s2(new std::string("blah"));

    return 0;
}