#ifndef VIRTUALMEM_HPP
#define VIRTUALMEM_HPP
class VirtualMem
{
    public:
        VirtualMem(int VA);
        void get_individual_addresses();
        int get_segement_address();
        int get_pagetable_address();
        int get_pagenumber_address();

    private:
        int virtual_address;
        int segemetaddr;
        int pagetableaddr;
        int pageaddr;
};

#endif /* VIRTUALMEM_HPP */