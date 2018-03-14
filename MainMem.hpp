#ifndef MAINMEM_HPP
#define MAINMEM_HPP
#include <iostream>
#include "BitMap.hpp"
#include "TLB.hpp"
#include "VirtualMem.hpp"
#include <string>
#define FRAMESZ 512
#define MEMORYSZ 1024
#define READ 0
#define WRITE 1

class VirtualMemSimException{

    public:
        VirtualMemSimException(const char * message)
        {
            std::cout<<"Virtual Memory Simulator Exception: "<<message<<std::endl;
        }
        VirtualMemSimException()
        {
            std::cout<<"Unknown Virtual Memory Simulator Exception Thrown"<<std::endl;
        }
};
class MainMem
{
    public:
        MainMem();
        ~MainMem();
        void init_main_mem();
        void set_segement(int segment_index, int addr);
        int get_page_table_addr(int segment_addr);
        void set_page_table(int page_index, int segment_index, int page_number);
        std::string addr_command_processing(unsigned char read_write, int Vaddr, int tlb_enabled);
        int get_PT_entry(int page_table_addr, int page_index);
        int get_segment_entry(int segment_addr);
        int get_bit_for_segement(int addr);
        void set_segement_entry(int segment_addr, int page_table_addr);
        void set_page_table_entry(int page_table_addr, int page_addr, int new_page_addr);
        void create_page(VirtualMem Vmem);
        int is_addr_valid(int addr);
        int get_read_write_choice(unsigned char read_write);
        std::string write_to_mem(int va);
        std::string read_from_mem(int va);
        std::string write_to_mem_TLB(int va);
        std::string read_from_mem_TLB(int va);



    private:
        int * pmem;
        BitMap bmap;
        TLB cline;
    
};
#endif /* MAINMEM_HPP */