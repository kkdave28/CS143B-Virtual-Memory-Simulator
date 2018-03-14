#ifndef BITMAP_HPP
#define BITMAP_HPP
#define MASKSZ 32
#define MAPSZ 32
class BitMap
{
    public:
        BitMap();
        void clear_bitmap();
        int * get_bitmap();
        void set_bit(int i);
        void clr_bit(int i);
        int get_first_unallocated_bit();
        int get_first_unallocated_pair();
        int get_index(int i);
        ~BitMap();
    private:
        int map[32];
        int mask[32];
};
#endif /* BITMAP_HPP */