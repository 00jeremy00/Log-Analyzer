#include "log_parse.h"
using json = nlohmann::json;


int main(){
    int menu_choice = 1;
    std::vector<LogEntry> log_entries;

    while(menu_choice != 0){
        std::cout << "Log Analyzer Menu:\n";
        std::cout << "1. Load log file\n";
        std::cout << "2. Display log entries\n";
        std::cout << "3. Delete log entries\n";
        std::cout << "0. Exit\n";

        std::cout << "Enter your choice: ";
        std::cin >> menu_choice;
        
        switch(menu_choice){
            case 1: {
                std::string filename;
                std::cout << "Enter log filename: ";
                std::cin >> filename;
                std::ifstream log_file(filename);
                if (!log_file.is_open()) {
                    std::cerr << "Could not open the file!" << std::endl;
                    return 1;
                }
                std::string line;

                while(std::getline(log_file, line)){
                    if (line.empty()){
                        continue;
                    }

                    try {
                    json log = json::parse(line);
            
                    std::string level = log.value("level", "UNKNOWN");
                    Level log_level = stringToLevel(level);
                    std::string event = log.value("event", "UNKOWN");
                    std::string service = log.value("service", "UNKNOWN");
                    std::string timestamp = log.value("timestamp", "UNKNOWN");
                    std::tm parsed_time = {};
                    if(!parseTimestamp(timestamp, parsed_time)){
                        std::cerr << "Invalid timestamp \n";
                        continue; 
                    }
                    std::string endpoint = log.value("endpoint", "UNKNOWN");
                    int transaction_num = log.value("transaction_num", -1);
                    int product_num = log.value("product_num", -1);
                    double quantity_change = log.value("quantity_change", 0.0);
                    std::string product_name = log.value("product_name", "UNKNOWN");
                    std::string error = log.value("error", "UNKNOWN");
                    std::string method_str = log.value("method", "UNKNOWN");
                    Method method = stringToMethod(method_str);
                    LogEntry entry{parsed_time, log_level, service, event, endpoint, transaction_num, product_num, quantity_change, product_name, error, method};
                    log_entries.push_back(entry);
                }
                catch (json::parse_error& e) {
                    std::cerr << "JSON parse error: " << e.what() << std::endl;
                }

            } 
                break;
        }
            case 2: {
                for(auto &entry: log_entries){
                    std::cout << "Timestamp: " << std::put_time(&entry.timestamp, "%Y-%m-%d %H:%M:%S") << '\n';
                    std::cout << "Level: " << levelToString(entry.level) << '\n';
                    std::cout << "Service: " << entry.service << '\n';
                    std::cout << "Event: " << entry.event << '\n';
                    std::cout << "Endpoint: " << entry.endpoint << '\n';
                    std::cout << "Method: " << methodToString(entry.method) << '\n';
                    if (entry.transaction_num != -1) {
                        std::cout << "Transaction Number: " << entry.transaction_num << '\n';
                    }
                    if (entry.product_num != -1) {
                        std::cout << "Product Number: " << entry.product_num << '\n';
                    }
                    if (entry.quantity_change != 0.0) {
                        std::cout << "Quantity Change: " << entry.quantity_change << '\n';
                    }
                    if (entry.product_name != "UNKNOWN") {
                        std::cout << "Product Name: " << entry.product_name << '\n';
                    }
                    if (entry.error != "UNKNOWN") {
                        std::cout << "Error: " << entry.error << '\n';
                    }
                    std::cout << "-----------------------------" << '\n';
                }
                std::cout << "Total Entries: " << log_entries.size() << '\n';
                break;
            }
            case 3:
                break;
            case 0:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

    }
    return 0;
}
