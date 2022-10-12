#include "json.hpp"

Json::Json(){};
Json::~Json(){};

bool Json::parse_file(std::string file_path) {
    file.open(file_path, std::ios::in);
    if (!file.good()) {
        std::cerr << "Error opening file " << file_path << std::endl;
        return false;
    }

    char c;

    while(file.get(c)) {
        switch (c) {
            // if the next character is white space just keep going
            case ' ' || '\n' || '\t' || '\r': continue;  break;
            // this would be the start of our file, meaning the next part should be an object name
            // so just keep reading and load the following characters into a string objects[object_name]
            // and possibly just go to a seperate function
            case '{' : 
                if(!parse_object()) {
                    std::cerr << "error reading file " << file_path << std::endl;
                    return false;
                }
            break;
        }
    }



    file.close();
    return true;
}

bool Json::parse_object() {
    std::string object_name;
    char c;
    while(file.get(c)) {
        if (c == ':') {
            if(!parse_component(object_name)) return false;
        } else if (c == '\"' || c == ' ' || c == '\n' || c == '\t' || c == '\r') {
            continue;
        } else {
            object_name.push_back(c);
        }
    }
    return true;
}

bool Json::parse_component(std::string &parent_object) {
    if (parent_object.empty()) {
        std::cerr << "object name is empty" << std::endl;
        return false;
    }

    if (objects.count(parent_object)>0) {
        std::cerr << "object duplicate: " << parent_object << std::endl;
        return false;
    }

    char c;
    while(file.get(c)) {
        switch(c) {

        }
    }

    return true;
}