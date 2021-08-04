
template<typename T>
struct SomeTemplate
{
    bool operator==(const SomeTemplate<T> &rhs) const
    {
        return  !(static_cast<const T&>(*this) < static_cast<const T&>(rhs)   ||
                  static_cast<const T&>(rhs)   < static_cast<const T&>(*this));
    }
};

struct MyStruct : SomeTemplate<MyStruct>
{

    MyStruct(const int data_) : _data{data_} { }

    int _data;

    bool operator<(const MyStruct& rhs) const
    {
        return _data < rhs._data;
    }

};


MyStruct getValue() 
{
    static int cur_value = 0;
    return MyStruct{++cur_value};
}


int main()
{
    return getValue() == getValue();
}