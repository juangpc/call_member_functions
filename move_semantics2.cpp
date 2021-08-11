#include <iostream> 
#include <cstring>
#include <string>

class String
{
public:
    String() = default;
    String(const char* s)
    {
        m_Size = strlen(s);
        m_Data = new char[m_Size];
        memcpy(m_Data, s, m_Size);
        std::cout << "Created! - " << m_Data << "\n";
    }

    ~String()
    {
        if(m_Data)
        {
            std::cout << "Destructed! - " << m_Data << "\n";
            delete m_Data;
        }
    }

    String(const String& other)
    : m_Size{other.m_Size}
    {
        m_Data = new char[m_Size];
        memcpy(m_Data, other.m_Data, m_Size);
        std::cout << "Copied! - " << m_Data << "\n";
    }

    String(String&& other) noexcept
    : m_Size{other.m_Size}
    {
        m_Data = other.m_Data;

        other.m_Size = 0;
        other.m_Data = nullptr;     
        std::cout << "Moved! - " << m_Data << "\n";   
    }

    void print() const
    {
        for (int i = 0; i < m_Size; ++i)
        {
            std::cout << m_Data[i];
        }
        std::cout << "\n";
    }



private:
    char* m_Data;
    uint32_t m_Size;
};

class Entity
{
public:
    Entity(const String& name)
    : m_Name((String&&)name)
    { }
private:
    String m_Name;
};

int main()
{
    Entity e("Pepe");

    String s("lalalala");
    s.print();    


    std::cout << "\n\nbye\n";
    return 0;
}