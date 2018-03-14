#include <iostream>
#include <fstream>
#include "MainMem.hpp"
#include <unistd.h>
#include <vector>
std::vector<std::string> split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}
static void shell()
{
    MainMem m;
    m.init_main_mem();
    std::ifstream input_init;
    std::ifstream input_command;
    std::ofstream output_without_TLB;
    std::ofstream output_with_TLB;

    input_init.open("file1.txt", std::ifstream::in);
    input_command.open("file2.txt",std::ifstream::in);
    output_with_TLB.open("61699159_tlb.txt",std::ofstream::out);
    output_without_TLB.open("61699159.txt",std::ofstream::out);

    std::string init_segment;
    std::string init_page_tables;
    std::string processing_commands;

    std::getline(input_init, init_segment);
    std::getline(input_init, init_page_tables);
    std::getline(input_command,processing_commands);

    std::vector<std::string> list_of_segment_commands = split(init_segment, " ");
    std::vector<std::string> list_of_page_table_commands = split(init_page_tables, " ");
    std::vector<std::string> list_of_processing_commands = split(processing_commands, " ");
    int i;
    for(i=0; i< list_of_segment_commands.size(); i+=2)
    {
        m.set_segement(std::stoi(list_of_segment_commands[i]), std::stoi(list_of_segment_commands[i+1]));
    }
    for(i=0; i<list_of_page_table_commands.size(); i+=3)
    {
        m.set_page_table(std::stoi(list_of_page_table_commands[i]), std::stoi(list_of_page_table_commands[i+1]), std::stoi(list_of_page_table_commands[i+2]));
    }
    for(i=0; i<list_of_processing_commands.size(); i+=2)
    {
       output_with_TLB<<m.addr_command_processing(std::stoi(list_of_processing_commands[i]), std::stoi(list_of_processing_commands[i+1]), true);
       output_without_TLB<<m.addr_command_processing(std::stoi(list_of_processing_commands[i]), std::stoi(list_of_processing_commands[i+1]), false);
    }
    
}
int main(int argc, char * argv[])
{
    shell();
    return 0;
}