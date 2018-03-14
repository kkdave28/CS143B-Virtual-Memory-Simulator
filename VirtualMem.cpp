#ifndef VIRTUALMEM_CPP
#define VIRTUALMEM_CPP
#include "VirtualMem.hpp"
#include <iostream>

VirtualMem::VirtualMem(int VA)
{
    virtual_address = VA;
    get_individual_addresses();

}
void VirtualMem::get_individual_addresses()
{
   // little endian formatting...
    segemetaddr = virtual_address & 0b00001111111110000000000000000000;
    segemetaddr = segemetaddr >> 19;

    pagetableaddr = virtual_address &0b00000000000001111111111000000000;
    pagetableaddr = pagetableaddr >> 9;

    pageaddr = virtual_address & 0b00000000000000000000000111111111;

}


int VirtualMem::get_segement_address()
{
    return segemetaddr;
}
int VirtualMem::get_pagetable_address()
{
    return pagetableaddr;
}
int VirtualMem::get_pagenumber_address()
{
    return pageaddr;
}


#endif /* VIRTUALMEM_CPP */