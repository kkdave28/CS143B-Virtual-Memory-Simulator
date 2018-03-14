#include<cstring>
#include<iostream>
#include "Helper.cpp"
int main()
{
    int temp[128];
    std::cout<<sizeof(temp)/sizeof(int)<<std::endl;
    helper::custom_memset<int>(temp, 0, 128);
    helper::custom_memset<int>(temp+4, 5, 16);
    std::cout<<*(temp+3)<<std::endl;
    //std::memset((temp+index_open_bmap_pair*FRAMESZ), 5, (index_open_bmap_pair * FRAMESZ + 2* FRAMESZ));
    
         int i;
         for(i=0; i < 128; i++)
         {
             //temp[i] = 0;
             std::cout<<temp[i];
         }
        return 0;
}