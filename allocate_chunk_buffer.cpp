#include <vector>
#include <memory_resource>



int main()
{

    std::byte stackBuf[2048];
    std::pmr::monotonic_buffer_resource rsrc(stackBuf, sizeof stackBuf);

    std::pmr::vector<int> vectorOfThings{{1,2,3,4,5,6}, &rsrc};

    return 0;
}