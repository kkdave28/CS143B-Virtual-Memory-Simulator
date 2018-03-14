#ifndef TLB_CPP
#define TLB_CPP
#include "TLB.hpp"
#define CACHESIZE 4
#define NOT_FOUND -1
#define HIT 1
#define MISS 0
#define RESET 3
#define INIT -1
#include <climits>
#include <iostream>
TLB::CacheLine::CacheLine()
{
    LRU = INIT;
    segmetaddr = INIT;
    frame = INIT;
}
void TLB::CacheLine::set_addr(int addr)
{
    segmetaddr = addr;
}
void TLB::CacheLine::set_frame(int f)
{
    frame = f;
}
void TLB::CacheLine::set_LRU(int i)
{
    LRU = i;
}
int TLB::CacheLine::get_addr()
{
    return segmetaddr;
}
int TLB::CacheLine::get_frame()
{
    return frame;
}
int TLB::CacheLine::get_LRU()
{
    return LRU;
}
TLB::TLB()
{
    int i;
    for(i=0; i<CACHESIZE; i++)
    {
        main_cache[i].set_LRU(i);
    }
}
int TLB::get_frame(int i)
{
    return main_cache[i].get_frame();
}
int TLB::cache_hit_miss(VirtualMem Vmem)
{
    int addr = Vmem.get_segement_address() + Vmem.get_pagetable_address();
    int i;
    for(i=0; i<CACHESIZE; i++)
    {
        if(main_cache[i].get_addr() == addr)
        {    
            return HIT;
        }
    }
    return MISS;
}
int TLB::search_cache_line(VirtualMem Vmem)
{
    int addr = Vmem.get_segement_address() + Vmem.get_pagetable_address();
    int i;
    for(i=0; i<CACHESIZE; i++)
    {
        if(main_cache[i].get_addr() == addr)
        {    
            return i;
        }
    }
    return NOT_FOUND;
}
int TLB::find_lowest_LRU()
{
    int ret_index = NOT_FOUND;
    int i;
    for(i=0; i<CACHESIZE; i++)
    {
        if(main_cache[i].get_LRU() == 0)
        {    
            return i;
        }
    }
    return ret_index;

}
void TLB::update_LRU_hit(int i)
{
    int x = main_cache[i].get_LRU();
    int j;
    for(j=0; j< CACHESIZE; j++)
    {
        if(main_cache[j].get_LRU() > x)
        {
            main_cache[j].set_LRU(main_cache[j].get_LRU()-1);
        }
    }
    main_cache[i].set_LRU(RESET);
}
void TLB::update_LRU_miss()
{
    int x = find_lowest_LRU();
    int j;
    for(j=0; j< CACHESIZE; j++)
    {
        main_cache[j].set_LRU(main_cache[j].get_LRU()-1);
    }
    main_cache[x].set_LRU(RESET);
}
void TLB::set_cache_line(int i, VirtualMem Vmem, int * pmem)
{
    update_LRU_miss();
    main_cache[i].set_addr(Vmem.get_segement_address() + Vmem.get_pagetable_address());
    main_cache[i].set_frame(pmem[pmem[Vmem.get_segement_address()]+Vmem.get_pagetable_address()]);
}
#endif /* TLB_CPP */