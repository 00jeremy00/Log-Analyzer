#ifndef LOG_PARSE_H
#define LOG_PARSE_H
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

enum class Method {
    GET,
    POST,
    PUT,
    DELETE_,
    UNKNOWN
};

enum class Level {
    INFO,
    ERROR,
    WARN,
    UNKNOWN
};

struct LogEntry {
    std::tm timestamp;
    Level level;
    std::string service;
    std::string event;
    std::string endpoint;
    int transaction_num = -1;
    int product_num = -1;
    double quantity_change = 0.0;
    std::string product_name;
    std::string error;
    Method method = Method::UNKNOWN;
};

Level stringToLevel(const std::string& level_str);
std::string levelToString(Level level);
Method stringToMethod(const std::string& method_str);
std::string methodToString(const Method& method);
bool parseTimestamp(const std::string& ts, std::tm& parsed_time);


#endif