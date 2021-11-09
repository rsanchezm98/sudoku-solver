#include "sudoku.hpp"

namespace game
{
    Sudoku::Sudoku(size_t size, const std::string& filename)
    :   m_size(size), 
        m_sudoku_file(filename)
    {
        if(!InitializeSudoku())
        {
            std::cout << "Invalid Sudoku. Please restart the game with another file...\n";
        }else
        {
            DisplaySudokuStates();
            if(!SolveSudoku())
            {
                std::cout << "Unable to solve the sudoku...\n";
            }else
            {
                std::cout << "***************************\n";
                std::cout << "Sudoku solved!\n";
                DisplaySudokuStates();
                std::cout << "Elapsed time to solve the sudoku: " << m_elapsed_time << "ms\n";
            }
        }
    }

    Sudoku::~Sudoku()
    {

    }

    bool
    Sudoku::InitializeSudoku()
    {
        if (m_sudoku_file.empty())
        {   
            std::cout << "No filename provided...\n";
            return false;
        }

        std::ifstream source;
        source.open(m_sudoku_file);
        
        
        if(source.is_open())
        {
            std::string line;

            while(std::getline(source, line))
            {
                std::istringstream string_stream(line);
                size_t value;
                std::vector<size_t> row;

                while (string_stream >> value)
                {
                    row.push_back(value);
                }   
                if(row.size() != m_size)
                {
                    source.close();
                    return false;
                }

                m_table.push_back(row);         
            }

            if(m_table.size() != m_size)
            {
                source.close();
                return false;
            }else
            {
                source.close();
                return true;
            }
        }else
        {
            return false;
        }
    }

    void
    Sudoku::DisplaySudokuStates()
    {

        std::cout << "Rows: " << m_table.size() << " -- Cols: " << m_table[0].size() << "\n";
        for (size_t i = 0; i < m_size; i++)
        {
            for (size_t j = 0; j < m_size; j++)
            {
                std::cout << m_table[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    void
    Sudoku::DisplaySudokuStates(const std::vector<std::vector<size_t>>& table)
    {

        std::cout << "Rows: " << table.size() << " -- Cols: " << table[0].size() << "\n";
        for (size_t i = 0; i < m_size; i++)
        {
            for (size_t j = 0; j < m_size; j++)
            {
                std::cout << table[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    bool
    Sudoku::SolveSudoku()
    {
        auto init_timestamp = std::chrono::steady_clock::now();

        std::vector<std::vector<size_t>> table = m_table;
        if(!Backtracking(table))
        {
            return false;
        }

        m_table = table;

        auto end_timestamp = std::chrono::steady_clock::now();
        

        m_elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end_timestamp - init_timestamp).count()/1e6;
        return true;

    }

    bool
    Sudoku::Backtracking(std::vector<std::vector<size_t>>& table)
    {   
        size_t row, col;

        if(!GetNextMove(row, col, table))
        {
            // the sudoku is solved
            return true;
        }

        for (size_t i = 1; i < 10; i++)
        {
            
            if(IsValidSolution(i, row, col, table))
            {
                table[row][col] = i;

                if(Backtracking(table))
                {
                    return true;
                }

                table[row][col] = 0;
            }
        }

        return false;
    }

    bool 
    Sudoku::GetNextMove(size_t& row, size_t& col, const std::vector<std::vector<size_t>>& table)
    {
        for (size_t i = 0; i < m_size; i++)
        {
            for(size_t j = 0; j < m_size; j++)
            {
                if(table[i][j] == 0)
                {
                    row = i;
                    col = j;
                    return true;
                }
            }
        }

        return false;
    }

    bool
    Sudoku::IsValidSolution(size_t value, size_t row, size_t col, const std::vector<std::vector<size_t>>& table)
    {
        bool valid_solution = true;

        /* check the row */
        if(std::find(std::begin(table[row]), std::end(table[row]), value) != std::end(table[row]))
        {
            valid_solution = false;

        }
        /* check the column */
        for(size_t i = 0; i < m_size; i++)
        {
            if(table[row][col] == value)
            {
                valid_solution = false;
            }
        }

        size_t number_of_box;


        /* check the box */
        for(size_t i = 0; i < 3; i++)
        {
            for (size_t j = 0; j < 3; j++)
            {
                if(table[i + row - row%3][j + col - col%3] == value)
                {
                    valid_solution = false;
                }
            }
        }

        return valid_solution;
    }
}