#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Day.hpp"
#include "Utils.hpp"

class Day2 : public Day
{
private:
    std::string path;
    std::map<int, std::map<std::string, int>> scores;
    bool part1_done = false;
public:
    Day2(std::string path) : path(path) {}
    std::string run() override
    {
        std::string part1 = this->part1();
        std::string part2 = this->part2();
        return utils::join({part1, part2}, "\n");
    }

    std::string part1() 
    {
        std::ifstream file(path);
        if (!file.is_open())
            return "ERROR: file did not open";

        // "Game 1: 1 red, 3 blue, 11 green; 1 blue, 5 red; ..."
        std::string line;
        while (std::getline(file, line))
        {
            // "Game 123: ..."
            //      ^---^
            int game = std::stoi(line.substr(5, line.find(":")-5));
            
            scores[game] = std::map<std::string, int>{
                {"red", 0}, {"blue", 0}, {"green", 0}
            };
            
            // "1 red, 3 blue, 11 green; 1 blue, 5 red; ..."
            std::string show_string = utils::split(line, ": ")[1];

            // ["1 red, 3 blue, 11 green", "1 blue, 5 red", "...]
            std::vector<std::string> shows = utils::split(show_string, "; ");

            // iterate over shows, update scores to highest
            for (std::string show : shows)
            {
                // ["1 red", "3 blue", "11 green"]
                std::vector<std::string> colors = utils::split(show, ", ");

                // iterate over colors, update scores to highest
                for (std::string color : colors)
                {
                    // "123 red"
                    //  ___^
                    int count = std::stoi(color.substr(0, color.find(" ")));

                    // "123 red"
                    //      ^--^
                    std::string color_name = color.substr(color.find(" ")+1);

                    scores[game][color_name] = std::max(scores[game][color_name], count);
                }
            }
        } // end while getline

        // the actual number of stones
        std::map<std::string, int> check {
            {"red", 12}, {"blue", 14}, {"green", 13}
        };

        // iterate over games, find out which ones are possible with the number of stones in check
        int id_sum = 0;
        for (const auto& game_pair : scores)
        {
            bool game_possible = true;
            for (const auto& color_pair : game_pair.second)
            {
                if (check[color_pair.first] < color_pair.second)
                {
                    game_possible = false;
                    break;
                }
            }
            if (game_possible)
                id_sum += game_pair.first;
        }
        part1_done = true;
        return "Part 1: " + std::to_string(id_sum);

    }

    std::string part2()
    {
        if (!part1_done)
            this->part1();
        
        unsigned long long int stone_score = 0;
        // iterate over scores, find minimum number of stones needed of each color
        for (const auto& game_pair : scores)
        {
            unsigned long long int game_score = 1;
            for (const auto& color_pair : game_pair.second)
            {
                game_score *= color_pair.second;
            }
            stone_score += game_score;
        }

        return "Part 2: " + std::to_string(stone_score);
    }
};