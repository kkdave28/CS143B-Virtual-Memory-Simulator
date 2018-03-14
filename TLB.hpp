#ifndef TLB_HPP
#define TLB_HPP
#include "VirtualMem.hpp"
#define CACHESIZE 4

class TLB
{
    public:
        TLB();
        int get_frame(int i);
        int cache_hit_miss(VirtualMem Vmem);
        int search_cache_line(VirtualMem Vmem);
        int find_lowest_LRU();
        void set_cache_line(int i, VirtualMem Vmem, int * pmem);
        void update_LRU_hit(int i);
        void update_LRU_miss();
        void print_cache();
    private:
        struct CacheLine
        {
            public:
                CacheLine();
                void set_LRU(int i);
                void set_addr(int addr);
                void set_frame(int f);
                int get_LRU();
                int get_addr();
                int get_frame();
            private:
                int LRU;
                int segmetaddr;
                int frame;
        };
        CacheLine main_cache[CACHESIZE];
};
#endif /* TLB_HPP */