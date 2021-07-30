#include <iostream>
#include <unordered_map>
#include <string> 

class AbstractData;

struct MetaDataExtractor
{
    template<typename T>
    void extract(std::unordered_map<std::string, AbstractData*>, std::string key)
    {

    }
};

class AbstractData
{
public:
    AbstractData() = default;
    ~AbstractData() = default;

    virtual void out(MetaDataExtractor m, std::string k) const = 0;
};

template<typename T>
class Data : public AbstractData
{
public:
    Data() = default;
    Data(T value)
    :_data(value)
    {  }
    
    T value()
    {
        return _data;
    }
    operator T()
    {
        return *_data;
    }

    // void printMetaData() const
    // {
    //     for (auto d : metaData)
    //     {
    //         std::cout << "[" << d.first << "] - " << typeof(d.second) << "\n";
    //     }
    // }
    void insertMetaData(const std::string& key, AbstractData* value)
    {
        _metaData.insert({key, value});
    }

    void out(MetaDataExtractor m, std::string key) const override
    {
        m.extract<T>(this->_metaData, key);
    }

private: 
    T _data;
    std::unordered_map<std::string, AbstractData*> _metaData;
};



int main(int argc, char* argv[])
{
    Data<float> channel1(3.7f);
    channel1.insertMetaData("num_sensors", new Data<int>(336));
    int pp = channel1.metaData("num_sensors");

    std::cout << channel1.value() << "\n";
    //std::cout <<  << "\n";
    // // channel1.printMetaData();

    return 0;
}