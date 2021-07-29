#include <iomanip>
#include <iostream>
#include <sstream>

class HashTable
{
public:
    struct Entry
    {
        std::string Data;
        std::string Status = "never used";
    };

    HashTable() = default;
    static const int Size = 26;

    void Print()
    {
        for (int i = 0; i < Size; i++)
        {
            std::cout << std::setfill(' ') << std::setw(2) << i << "(" << (char)('a' + i) << ") - "
                      << m_Entries[i].Data << " (" << m_Entries[i].Status << ")" << "\n";
        }
    }

    void Add(const std::string& entryString)
    {
        bool exists = Find(entryString);
        if (exists)
            return;
        int insertIndex = GetInsertIndex(entryString);
        std::cout << "Inserting: " << entryString << " in position " << insertIndex << "\n";
        m_Entries[insertIndex].Data = entryString;
        m_Entries[insertIndex].Status = "occupied";
    }

    void Delete(const std::string& entryString)
    {

    }

    int GetIndex(const std::string& entryString)
    {
        std::cout << "GetIndex : " << entryString << " - " << entryString.back() << " - " << entryString.back() - 'a' << "\n";
        return entryString.back() - 'a';
    }

    bool Find(const std::string& entryString)
    {
        int index = GetIndex(entryString);
        while(true)
        {
            if(m_Entries[index].Data == entryString)
                return true;

            if(m_Entries[index].Status == "never used")
                return false;

            index = (index + 1 ) % Size;
        }

        return false;
    }

    bool GetInsertIndex(const std::string& entryString)
    {
        int index = GetIndex(entryString);
        while(true)
        {
            // if(m_Entries[index].Data == entryString)
            //     return true;

            if(m_Entries[index].Status == "never used" ||
               m_Entries[index].Status == "tombstone")
                return index;

            index = (index + 1 ) % Size;
        }
        return -1;
    }
private:
    Entry m_Entries[Size];
};

int main()
{
    // Aapple Aorange Astrawberry hpech woeijrflwkdf 30u2
    // orange strawberry

    HashTable hashTable;

    std::string input;
    getline(std::cin, input);
    std::stringstream ss(input);
    while(ss.good())
    {
        std::string token;
        ss >> token;
        std::string entryName = token.substr(1);

        if(token[0] == 'A')
        {
            std::cout << "Add - " << entryName << "\n";
            hashTable.Add(entryName);
        }
        else if (token[0] == 'D')
        {
            std::cout << "Delete - " << entryName << "\n";
            hashTable.Delete(entryName);
        }
    }

    hashTable.Print();

    return 0;
}







