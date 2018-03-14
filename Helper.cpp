#include <stddef.h>
namespace helper
{
template
<typename T>
    void custom_memset(T* pt, T val, size_t sz)
    {
        int i;
        for(i=0; i< sz; i++)
        {
            pt[i] = val;
        }
    }
}