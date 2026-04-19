#include "log_parse.h"

bool parseTimestamp(const std::string& ts, std::tm& parsed_time){
    std::istringstream ss(ts);
    ss >> std::get_time(&parsed_time, "%Y-%m-%dT%H:%M:%S");
    return !ss.fail();
}

Level stringToLevel(const std::string& level_str) {
    if (level_str == "INFO") {
        return Level::INFO;
    } else if (level_str == "ERROR") {
        return Level::ERROR;
    } else if (level_str == "WARN") {
        return Level::WARN;
    } else {
        return Level::UNKNOWN;
    }
}

std::string methodToString(const Method& method) {
    switch(method) {
        case Method::GET:
            return "GET";
        case Method::POST:
            return "POST";
        case Method::PUT:
            return "PUT";
        case Method::DELETE_:
            return "DELETE";
        default:
            return "UNKNOWN";
    }
};

Method stringToMethod(const std::string& method_str) {
    if (method_str == "GET") {
        return Method::GET;
    } else if (method_str == "POST") {
        return Method::POST;
    } else if (method_str == "PUT") {
        return Method::PUT;
    } else if (method_str == "DELETE") {
        return Method::DELETE_;
    } else {
        return Method::UNKNOWN;
    }
}

std::string levelToString(Level level) {
    switch(level){
        case Level::INFO:
            return "INFO";
        case Level::ERROR:
            return "ERROR";
        case Level::WARN:
            return "WARN";
        default:
            return "UNKNOWN";
    }
};