#include "Utils.hpp"
#include <filesystem>
#include <algorithm>
#include <sstream>
#include <string>

std::vector<std::string> utils::split(const std::string& str, const std::string& delim) {
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

std::vector<std::string> utils::split(const std::string& str, const char delim) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        if (!token.empty()) tokens.push_back(token);
    }
    return tokens;
}

std::string utils::trim(const std::string& str) {
    std::string s = str;
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
    return s;
}

std::string utils::trim(const std::string& str, const std::string& chars) {
    std::string s = str;
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [&chars](int ch) {
        return chars.find(ch) == std::string::npos;
    }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [&chars](int ch) {
        return chars.find(ch) == std::string::npos;
    }).base(), s.end());
    return s;
}

std::string utils::join(const std::vector<std::string>& vec, const std::string& delim) {
    std::stringstream ss;
    for (size_t i = 0; i < vec.size(); ++i) {
        ss << vec[i];
        if (i != vec.size() - 1) ss << delim;
    }
    return ss.str();
}

std::string utils::join(const std::vector<std::string>& vec, const char delim) {
    std::stringstream ss;
    for (size_t i = 0; i < vec.size(); ++i) {
        ss << vec[i];
        if (i != vec.size() - 1) ss << delim;
    }
    return ss.str();
}

std::string utils::replace(const std::string& str, const std::string& from, const std::string& to) {
    std::string s = str;
    size_t start_pos = 0;
    while ((start_pos = s.find(from, start_pos)) != std::string::npos) {
        s.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return s;
}

std::string utils::replace(const std::string& str, const char from, const char to) {
    std::string s = str;
    size_t start_pos = 0;
    while ((start_pos = s.find(from, start_pos)) != std::string::npos) {
        s.replace(start_pos, 1, 1, to);
        start_pos += 1;
    }
    return s;
}

std::vector<std::string> utils::get_files(const std::string& dir, const std::string& ext) {
    std::vector<std::string> files;
    for (const auto& entry : std::filesystem::directory_iterator(dir)) {
        if (entry.path().extension() == ext) {
            files.push_back(entry.path().string());
        }
    }
    return files;
}