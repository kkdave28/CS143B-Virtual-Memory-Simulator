#ifndef MAINMEM_CPP
#define MAINMEM_CPP
#include "MainMem.hpp"
#include "Helper.cpp"
#include <string>
#include <iostream>
#include <cstring>
#define FRAMESZ 512
#define MEMORYSZ 1024
#define READ 0
#define WRITE 1
#define INVALID -1
#define ERROR "err "
#define PAGEFAULT "pf "
#define HIT "h "
#define MISS "m "
MainMem::MainMem()
{
    pmem = new int[FRAMESZ*MEMORYSZ];
}
MainMem::~MainMem()
{
    delete [] (pmem);
}
void MainMem::init_main_mem()
{
    int i;
    for(i=0; i< FRAMESZ*MEMORYSZ; i++)
    {
        pmem[i] =-1;
    }
    for(i=0; i<FRAMESZ; i++)
    {
        pmem[i] = 0;
    }
    //helper::custom_memset<int>(pmem, 0, FRAMESZ);
    bmap.set_bit(0);
}
int MainMem::is_addr_valid(int addr)
{
    return addr != INVALID;
}
int MainMem::get_bit_for_segement(int addr)
{
    return addr/FRAMESZ;
}
void MainMem::set_segement(int segment_addr, int addr)
{
    pmem[segment_addr] = addr;
    if(addr != -1)
    {
        int i;
        for(i=addr; i< addr + (2*FRAMESZ); i++)
        {
            pmem[i] = 0;
        }
        //helper::custom_memset<int>(pmem+addr, 0, addr + 2*FRAMESZ);
        bmap.set_bit(addr/FRAMESZ);
        bmap.set_bit((addr/FRAMESZ) +1);
    }
}
int MainMem::get_page_table_addr(int segment_addr)
{
    return pmem[segment_addr];
}
void MainMem::set_page_table(int page_index, int segment_index, int page_number)
{
    int start = get_page_table_addr(segment_index);
    if(start !=-1 && start !=0)
    {
        pmem[start+page_index] = page_number;
        if(page_number != -1)
        {
            int i;
            for(i=page_number; i<page_number + FRAMESZ; i++)
            {
                pmem[i] = 0;
            }
            //helper::custom_memset<int>(pmem+page_number, 0, page_number+FRAMESZ);
            bmap.set_bit(page_number/FRAMESZ);
        }
    }

}
int MainMem::get_read_write_choice(unsigned char read_write)
{
    if(read_write == READ)
    {
        return READ;
    }
    else if(read_write == WRITE)
    {
        return WRITE;
    }
    return -1;
}
std::string MainMem::addr_command_processing(unsigned char read_write, int Vaddr, int tlb_enabled)
{
    if(!get_read_write_choice(read_write))
    {
        if(tlb_enabled)
        {
            return read_from_mem_TLB(Vaddr);
        }
        else
        {
            return read_from_mem(Vaddr);
        }
    }
    else
    {
        if(tlb_enabled)
        {
            return write_to_mem_TLB(Vaddr);
        }
        else
        {
            return write_to_mem(Vaddr);
        }
    }
 
}
int MainMem::get_PT_entry(int page_table_addr, int page_index)
{
    
    return pmem[page_table_addr+page_index];
}
int MainMem::get_segment_entry(int segment_addr)
{
    return pmem[segment_addr];
}
void MainMem::set_segement_entry(int segment_addr, int page_table_addr)
{
    pmem[segment_addr] = page_table_addr;
}
void MainMem::set_page_table_entry(int page_table_addr, int page_addr, int new_page_addr)
{
    pmem[page_table_addr+page_addr] = new_page_addr;
}
void MainMem::create_page(VirtualMem Vmem)
{
    int page = bmap.get_first_unallocated_bit();
    bmap.set_bit(page);
    set_page_table_entry(pmem[Vmem.get_segement_address()], Vmem.get_pagetable_address(), page*FRAMESZ);
    int * temp = pmem;
    int i;
    for(i= page*FRAMESZ; i< page*FRAMESZ + FRAMESZ; i++)
    {
        pmem[i] = 0;
    }
    //helper::custom_memset<int>((pmem + page*FRAMESZ), 0, page*FRAMESZ + FRAMESZ);

}
std::string MainMem::write_to_mem(int va)
{
    VirtualMem v(va);
    int ptaddr = get_segment_entry(v.get_segement_address());
    if(ptaddr == -1)
    {
        return PAGEFAULT;
    }
    int paddr = get_PT_entry(ptaddr, v.get_pagetable_address());
    if(paddr == -1)
    {
        return PAGEFAULT;
    }
    if(ptaddr ==0)
    {
        int index_open_bmap_pair = bmap.get_first_unallocated_pair();
        bmap.set_bit(index_open_bmap_pair);
        bmap.set_bit(index_open_bmap_pair+1);
        set_segement_entry(v.get_segement_address(),index_open_bmap_pair*FRAMESZ);
        int *temp = pmem;
        int i;
        int total = index_open_bmap_pair*FRAMESZ + 2* FRAMESZ;
        for(i=index_open_bmap_pair*FRAMESZ; i< total; i++)
        {
            pmem[i] = 0;
        }
        //helper::custom_memset<int>(pmem+(index_open_bmap_pair*FRAMESZ),0,(index_open_bmap_pair*FRAMESZ + 2*FRAMESZ));
        create_page(v);
        std::string ret = std::to_string(get_PT_entry(pmem[v.get_segement_address()], v.get_pagetable_address())+ v.get_pagenumber_address());
        ret+=" ";
        return ret;
        
    }
    else if(paddr ==0)
    {
        create_page(v);
        std::string ret = std::to_string(get_PT_entry(pmem[v.get_segement_address()], v.get_pagetable_address())+ v.get_pagenumber_address());
        ret+=" ";
        return ret;
    }
    else
    {
        std::string ret = std::to_string(get_PT_entry(pmem[v.get_segement_address()], v.get_pagetable_address())+ v.get_pagenumber_address());
        ret+=" ";
        return ret;
    }

}
std::string MainMem::read_from_mem(int va)
{
    VirtualMem v(va);
    int ptaddr = get_segment_entry(v.get_segement_address());
    if(ptaddr == -1)
    {
        return PAGEFAULT;
    }
    if(ptaddr == 0)
    {
        return ERROR;
    }
    int paddr = get_PT_entry(ptaddr, v.get_pagetable_address());
    if(paddr == -1)
    {

        return PAGEFAULT;
    }
    if(paddr == 0)
    {
        return ERROR;
    }
    std::string ret =  std::to_string(paddr+v.get_pagenumber_address());
    ret+= " ";
    return ret;
}
std::string MainMem::write_to_mem_TLB(int va)
{
    VirtualMem v(va);
    if(cline.cache_hit_miss(v))
    {
        int index = cline.search_cache_line(v);
        cline.update_LRU_hit(index);
        return std::string(HIT + std::to_string(v.get_pagenumber_address()+ cline.get_frame(index)) + " ");
    }
    else
    {
        std::string ret = write_to_mem(va);
        if(ret == PAGEFAULT)
        {
            std::string temp = ret;
            ret = MISS;
            ret+=temp;
            return ret;
        }
        int index = cline.find_lowest_LRU();
        cline.set_cache_line(index, v,pmem);
        std::string temp = ret;
        ret = MISS;
        ret+=temp;
        return ret;

    }
}
std::string MainMem::read_from_mem_TLB(int va)
{
    VirtualMem v(va);
    if(cline.cache_hit_miss(v))
    {
        int index = cline.search_cache_line(v);
        cline.update_LRU_hit(index);
        return std::string(HIT + std::to_string(v.get_pagenumber_address()+ cline.get_frame(index))+ " ");
    }
    else
    {
        std::string ret = read_from_mem(va);
        if(ret == PAGEFAULT || ret == ERROR)
        {
            std::string temp = ret;
            ret = MISS;
            ret+=temp;
            return ret;
        }
        int index = cline.find_lowest_LRU();
        cline.set_cache_line(index, v, pmem);
        std::string temp = ret;
        ret = MISS;
        ret+=temp;
        return ret;
        
    }
}
#endif /* MAINMEM_CPP */