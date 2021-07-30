#include <iostream>

class Name
{
public: 
    Name(const std::string& firstName, const std::string& lastName)
    : m_firstName{firstName},
      m_lastName{lastName}
      {

      }

    void print() const 
    {
        std::cout << m_lastName << ", " << m_firstName << "\n";
    }

private:
    std::string m_firstName;
    std::string m_lastName;
};

//mixin 
//mixin invoke a mix of template and inheritance in order to plug a generic functionality onto an existing class.
template<typename Printable>
struct RepeatPrint : Printable
{
    explicit RepeatPrint(Printable const& printable) 
    :Printable(printable)
    {

    }
    
    void repeat(int n) const
    {
        for( int i = 0; i < n; ++i )
        {
            std::cout << i+1 << " ";
            this->print();
        }
    }
};

//we can add a function to make it implicit
template< typename Printable>
RepeatPrint<Printable> repeatPrint(Printable const& printable)
{
    return RepeatPrint<Printable>(printable);
}


int main()
{

    Name pepe("Francisco", "Garcia");
    pepe.print();
    std::cout << "-------------------\n";
    RepeatPrint<Name> pp(pepe);
    pp.repeat(10);
    
    std::cout << "-------------------\n";
    repeatPrint(pepe).repeat(10);
    


    return 0;
}