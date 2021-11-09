#include <iostream>
#include <string>
#include "sudoku.hpp"

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cout << "Please, rerun the program with a filename...\n";
        return 0;
    }

    std::string filename = argv[1];
    filename = "../sudoku_files/" + filename;
    size_t table_size = 9;

    std::cout << "Sudoku filename: " << filename << "\n"; 
    game::Sudoku sudoku(table_size, filename);
    return 0;
}