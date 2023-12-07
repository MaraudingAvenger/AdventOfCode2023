# pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <map>
#include "Utils.hpp"
#include "Day.hpp"

class Day1 : public Day {
private:
	std::string path;
	std::map<std::string, std::string> digits {
		{"one", "1"}, {"two", "2"}, {"three", "3"},
		{"four", "4"}, {"five", "5"}, {"six", "6"},
		{"seven", "7"}, {"eight", "8"}, {"nine", "9"}, 
		{"zero", "0"}
	};

public:
	Day1(std::string path) : path(path) {}
	std::string run () override
	{
		std::string part1 = this->part1();
		std::string part2 = this->part2();
		return utils::join({part1, part2}, "\n");
	}
	std::string part1()
	{
		std::ifstream file(path);
		if (!file.is_open())
		{
			return "ERROR: file did not open";
		}
		std::vector<int> values;
		std::string line;
		while (std::getline(file, line)) 
		{
			std::string str = "";
			for(char c : line)
			{
				if (isdigit(c)) 
				{
					str += c;
					break;
				}
			}
			for (int i = line.length()-1; i >= 0; --i)
			{
				if (isdigit(line[i]))
				{
					str += line[i];
					break;
				}
			}
			if (str.length() < 2) {
				return "Bad read";
			}
			int num = std::stoi(str);
			values.push_back(num);
		}
		file.close();
		return "Part 1: " + std::to_string(std::accumulate(values.begin(), values.end(), 0, std::plus<int>()));
	}

	std::string part2()
	{
		std::ifstream file(path);
		if (!file.is_open())
		{
			return "ERROR: file did not open";
		}
		std::vector<int> values;
		std::string line;
		while (std::getline(file, line))
		{
			std::string str = "";
			// go forwards through line
			for (int i=0; i<line.length(); ++i)
			{
				// check if current character is a digit
				if (isdigit(line[i]))
				{
					str += line[i];
					break;
				}
				// check if current character is start of a key in nums
				bool found = false;
				for (auto& [key, value] : digits)
				{
					if (line.substr(i, key.length()) == key)
					{
						str += value;
						found = true;
						break;
					}
				}
				if (found) break;
			}

			// go backwards through line
			for (int i=line.length(); i >= 0; --i)
			{
				// check if current character is a digit
				if (isdigit(line[i]))
				{
					str += line[i];
					break;
				}
				// check if current character is start of a key in nums
				bool found = false;
				for (auto& [key, value] : digits)
				{
					if (line.substr(i, key.length()) == key)
					{
						str += value;
						found = true;
						break;
					}
				}
				if (found) break;
			}
			if (str.length() < 2) {
				return "Bad read";
			}
			int num = std::stoi(str);
			values.push_back(num);
		}
		file.close();
		return "Part 2: " + std::to_string(std::accumulate(values.begin(), values.end(), 0, std::plus<int>()));
	}
};