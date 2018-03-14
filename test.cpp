#include <iostream>
#include <fstream>
#include "MainMem.hpp"
#include <unistd.h>
#include <vector>
#include <sys/wait.h>
class point
{
    public:
        point(){ x = 9; y = 5;}
        void set(){x = 10; y = 20;}
        void print_point(){std::cout<<x<<std::endl; std::cout<<y<<std::endl;}
    private:
        int x;
        int y;
};
void set_p(point & p)
{
    p.set();
}
int main()
{
    point z;
    z.print_point();
    set_p(z);
    z.print_point();

}