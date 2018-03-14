#ifndef BITMAP_CPP
#define BITMAP_CPP
#include "BitMap.hpp"
#include "Helper.cpp"
#include <iostream>
#include <cstring>
#define MASKSZ 32
#define MAPSZ 32

BitMap::BitMap()
{

    int j;
    for(j=0; j< MAPSZ; j++)
    {
        map[j] = 0;
    }
    mask[MASKSZ-1] = 1;
    for(j= MASKSZ-2; j>=0; j--)
    {
        mask[j] = mask[j+1] <<1;
    }

}
BitMap::~BitMap(){}

void BitMap::clear_bitmap()
{
    int i;
    for(i=0; i< MAPSZ; i++)
    {
        map[i] = 0;
    }
}
int* BitMap::get_bitmap()
{
    return map;
}
void BitMap::set_bit(int i)
{
    map[i/MAPSZ] = map[i/MAPSZ] | mask[i%MASKSZ];
}
void BitMap::clr_bit(int i)
{
    int tempmask[MASKSZ];
    int j;
    for(j=0; j<MASKSZ; j++)
    {
        tempmask[j] = ~mask[j];
    }
    map[i/MAPSZ] = map[i/MAPSZ] & tempmask[i%MASKSZ];    

}
int BitMap::get_first_unallocated_bit()
{
    int i,j, temp;
    for(i=0; i<MAPSZ; i++)
    {
        for(j=0; j<MASKSZ; j++)
        {
            temp = map[i] & mask[j];
            if(!temp)
            {
                return i*MAPSZ + j;
            }
        }
    }
    return 1;
}
int BitMap::get_first_unallocated_pair()
{
    int i;
    int total = MAPSZ*MASKSZ-1;
    for(i=0; i< total; i++)
    {
        if(!get_index(i) && !get_index(i+1))
        {
            return i;
        }
    }
    return -1;

}
int BitMap::get_index(int i)
{
    int temp = i;
    int j,k;
    for(j=0; j<MAPSZ; j++)
    {
        for(k=0; k<MASKSZ; k++)
        {
            temp = map[j] & mask[k];
            if(!i)
            {
                return temp;
            }
            i--;
        }
    }
    return -1;
}
#endif /* BITMAP_CPP */