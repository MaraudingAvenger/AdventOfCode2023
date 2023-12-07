#pragma once

#include "Day.hpp"
#include "Utils.hpp"
#include <string>
#include <vector>
#include <map>
#include <numeric>
#include <fstream>

class Grid
{
private:
    std::vector<std::string> grid;
    std::vector<std::pair<int, int>> symbols;

public:
    Grid() {}
    Grid(std::vector<std::string> grid) : grid(grid)
    {
        for (size_t y = 0; y < grid.size(); ++y)
        {
            for (size_t x = 0; x < grid[y].size(); ++x)
            {
                if (grid[y][x] != '.' && !std::isdigit(grid[y][x]))
                {
                    symbols.push_back(std::make_pair(x, y));
                }
            }
        }
    }

    size_t width() { return grid[0].size(); }

    size_t height() { return grid.size(); }

    char get(std::pair<int, int> pos)
    {
        return grid[pos.second][pos.first];
    }

    char at(int x, int y)
    {
        return grid[y][x];
    }

    bool check_position_against_symbols(const std::pair<int, int> &pos)
    {
        for (const auto &[symbol_x, symbol_y] : symbols)
        {
            if (std::abs(pos.first - symbol_x) <= 1 || std::abs(pos.second - symbol_y) <= 1)
            {
                return true;
            }
        }
        return false;
    }
};

class Day3 : public Day
{
private:
    std::string path;
    Grid grid;

public:
    Day3(std::string path) : path(path) {}
    std::string run() override
    {
        std::string part1 = this->part1();
        return part1;
        // std::string part2 = this->part2();
        // return utils::join({part1, part2}, "\n");
    }

    std::string part1()
    {
        std::ifstream file(path);
        if (!file.is_open())
            return "ERROR: file did not open";

        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();

        grid = Grid(lines); // actually instantiate the grid

        // find numbers in grid
        std::vector<int> valid_numbers;

        for (int y = 0; y < grid.height(); ++y)
        {
            for (int x = 0; x < grid.width(); ++x)
            {
                // if the character we're on is a digit
                if (std::isdigit(grid.at(x, y)))
                {
                    // create a string of all the digits in a row and their positions
                    std::string number = "";
                    std::vector<std::pair<int, int>> pos_to_check;
                    while (std::isdigit(grid.at(x, y)))
                    {
                        number += grid.at(x, y);
                        pos_to_check.push_back(std::make_pair(x, y));
                        x += 1;
                    }
                    for (const auto &pos : pos_to_check)
                    {
                        if (grid.check_position_against_symbols(pos))
                        {
                            valid_numbers.push_back(std::stoi(number));
                            break;
                        }
                    }
                }
            }
        }

        return "Part 1: " + std::to_string(
                                std::accumulate(valid_numbers.begin(), valid_numbers.end(), 0, std::plus<int>()));
    }
};