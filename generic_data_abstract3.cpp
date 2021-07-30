#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

class AbstractData {
public:
    AbstractData() {}
    ~AbstractData() {}

    virtual void streamOut(std::ostream& osStream) = 0;
};

template<typename T>
class Data : public AbstractData {
private:
    T mT_value;
    std::unordered_map<std::string, std::shared_ptr<AbstractData>> m_metaData;

public:
    Data(T value) : mT_value(value) {}
    ~Data() = default;

    T getValue()
    {
        return mT_value;
    }

    void streamOut(std::ostream& osStream) override
    {
        osStream << *this;
    }

    template<typename T_meta>
    void setMetaData(const std::string& key, T_meta value)
    {
        m_metaData[key] = std::make_shared<Data<T_meta>>(value);
    }

    template<typename T_meta>
    void setMetaData(const std::string& key, Data<T_meta> data)
    {
        m_metaData[key] = std::make_shared<Data<T_meta>>(data);
    }
    
    template<typename T_meta>
    Data<T_meta> getMetaData(const std::string& key) const 
    {
        auto search = m_metaData.find(key);
        if( search != m_metaData.end())
        {
            auto data = static_cast<Data<T_meta>*>(search->second.get());
            return *data;
        }
    }

    void print() const;
};

std::ostream& operator<<(std::ostream& osStream, AbstractData& value)
{
    value.streamOut(osStream);
    return osStream;
}

template<typename T>
std::ostream& operator<<(std::ostream& osStream, Data<T>& data)
{
    data.print();
    return osStream;
}
template<typename T>
void Data<T>::print() const
    {
      std::cout << "Data: " << mT_value << "\n";
      std::cout << "MetaData: \n";
      for (auto md : m_metaData)
      {
        std::cout << md.first << " - " << *md.second << "\n";
      }
    }

int main() {
    Data<int> d0(102);
    d0.setMetaData<std::string>("sensor type", "MEG");
    d0.setMetaData<int>("num sensors", 306);

    std::cout << "Data declared: d0 = " << d0.getValue() << "\n";

    std::cout << "---------------------------------------------\n";

    d0.print();

    std::cout << "---------------------------------------------\n";

    std::cout << d0;


    std::cout << "---------------------------------------------\n";
    
    std::vector<std::shared_ptr<AbstractData>> dataIn;

    std::shared_ptr<AbstractData> d1 = std::make_shared<Data<int>>(102);
    Data<int>* d1_ = static_cast<Data<int>*>(d1.get());
    d1_->setMetaData<std::string>("sensor type", "MEG");
    d1_->setMetaData<int>("num sensors", 306);

    std::shared_ptr<AbstractData> d2 = std::make_shared<Data<double>>(1.5437e-21);
    Data<double>* d2_ = static_cast<Data<double>*>(d2.get());
    d2_->setMetaData<std::string>("sensor type", "MEG");
    d2_->setMetaData<int>("num sensors", 306);

    dataIn.push_back(d1);
    dataIn.push_back(d2);

    for (const auto& d: dataIn)
    {
        std::cout << *d << "\n";
    }

    Data<double>* din2 = static_cast<Data<double>*>(dataIn[1].get());
    int myNumSensors = din2->getMetaData<int>("num sensors").getValue();

    std::cout << "I have " << myNumSensors << " sensors.\n";

    return 0;
}