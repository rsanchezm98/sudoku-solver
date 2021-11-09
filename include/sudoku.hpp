#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>

namespace game
{

    class Sudoku
    {
        public:
            Sudoku(size_t size, const std::string& filename);
            ~Sudoku();
            bool InitializeSudoku();
            void DisplaySudokuStates();
            void DisplaySudokuStates(const std::vector<std::vector<size_t>>& table);
            bool SolveSudoku();
            bool Backtracking(std::vector<std::vector<size_t>>& table);
            bool GetNextMove(size_t& row, size_t& col, const std::vector<std::vector<size_t>>& table);
            bool IsValidSolution(size_t value, size_t row, size_t col, const std::vector<std::vector<size_t>>& table);
 
        private:
            std::vector<std::vector<size_t>> m_table; // table
            size_t m_size; // size of the table
            std::string m_sudoku_file; // file of the sudoku to be solved
            double m_elapsed_time = 0.0; // elapsed time of the sudoku solving algorithm
    };
    
}

#endif