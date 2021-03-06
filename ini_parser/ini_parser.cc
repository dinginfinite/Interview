#include "ini_parser.h"
#include "buffer.h"
#include "ini_utility.h"
#include <fstream>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>

namespace qh
{
    const size_t INIParser::MaxLineLenght = 1024;

    bool INIParser::Parse(const std::string& ini_file_path) {
        bool isValid = true;
        std::ifstream input(ini_file_path);
        if (!input.is_open())
            isValid = false;
        else {
            while(input) {
                std::string line;
                std::getline(input, line);
                processLine(line);
            }
        }
        return isValid;
    }

    bool INIParser::Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator, const std::string& key_value_seperator) {
        bool isValid = true;
        Buffer buf(std::string(ini_data, ini_data_len));
        std::string line;
        std::string key, value;
        while (buf.hasMoreLine()) {
            line = buf.getNextLine(line_seperator);

            if (processLine(line, key_value_seperator) == false) {
                isValid = false;
                break;
            }
        }
        return isValid;
    }

    const std::string& INIParser::Get(const std::string& key, bool* found) {
        std::string section = "default";
        return Get(section, key, found);
    }

    const std::string& INIParser::Get(const std::string& section, const std::string& key, bool* found) {
        if (data_.find(section) != data_.end() && data_[section].find(key) != data_[section].end()) {
            if (found)
                *found = true;
            result = data_[section][key];
        } else {
            if (found)
                *found = false;
            result = "";
        }
        return result;
    }

    bool INIParser::processLine(std::string &line, const std::string &key_value_seperator) {
        std::string key, value;
        if (line.empty() || line[0] == ';') // empty line or comment line
            return true;
        else if (line[0] == '[') {          // section line
            size_t pos = line.find_first_of("]");
            if (pos == std::string::npos) {
                // bad input
                return false;
            }
            curSection = line.substr(1, pos - 1);
            trim(curSection);
        } else {                            // key-value pair
            size_t posKey = line.find(key_value_seperator);
            if (posKey == std::string::npos) {
                // bad input
                return false;
            }
            key = line.substr(0, posKey);
            trim(key);

            value = line.substr(posKey + 1);
            trim(value);

            if ( (value[0] == '\'' || value[0] == '"') && std::count(value.begin(), value.end(), value[0]) != 1) {
                size_t  posValue = value.find_last_of(value[0]);
				value = value.substr(1, posValue - 1);
            } else {
                size_t posValue = value.find_first_of(";");
                if (posValue != std::string::npos)
                    value = value.substr(0, posValue);
                trim(value);
            }

            data_[curSection][key] = value;
        }
        return true;
    }
}
