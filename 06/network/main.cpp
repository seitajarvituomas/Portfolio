#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::string HELP_TEXT = "S = store id1 id2\n"
                              "C = count id\n"
                              "D = depth id\n";


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

std::vector <std::map <std::string, std::string>> save(std::string id1, std::string id2, std::vector <std::map <std::string, std::string>>& savings) {
    std::map <std::string, std::string> link;
    link.insert({id1, id2});
    savings.push_back(link);
    return savings;
}

void print(const std::vector<std::map<std::string, std::string>>& savings, const std::string& id, int current_depth = 0) {
    std::string indentation(current_depth * 2, '.');
    std::cout << indentation << id << std::endl;
    for (const auto& link : savings) {
        auto it = link.find(id);
        if (it != link.end()) {
            std::string employed_id = it->second;
            print(savings, employed_id, current_depth + 1);
        }
    }
}

int count(std::vector <std::map <std::string, std::string>>& savings, std::string id) {
    int total_count = 0;
    for (const auto& link : savings) {
        auto it = link.find(id);
        if (it != link.end()) {
            std::string employed_id = it->second;
            total_count += 1 + count(savings, employed_id);
        }
    }
    return total_count;
}

int depth_counter(const std::vector<std::map<std::string, std::string>>& savings, const std::string& id, int current_depth = 0) {
    int depth = current_depth;
    for (const auto& link : savings) {
        auto it = link.find(id);
        if (it != link.end()) {
            std::string employedId = it->second;
            depth = std::max(depth, depth_counter(savings, employedId, current_depth + 1));
        }
    }
    return depth;
}

int main()
{
    // TODO: Implement the data structure here
    std::vector <std::map <std::string, std::string>> savings;

    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            save(id1, id2, savings);

        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            print(savings, id);


        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            int total_count = count(savings, id);
            std::cout << total_count << std::endl;

        }

        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            int total_depth = depth_counter(savings, id);
            std::cout << total_depth+1 << std::endl;

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
