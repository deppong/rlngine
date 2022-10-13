#include "json.hpp"

Json::Json(){};
Json::~Json(){};

bool Json::is_whitespace(char c) {
    return (c == ' ' || c == '\n' || c == '\t' || c == '\r');
}

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
            default: break;
        }
    }



    file.close();
    return true;
}

bool Json::parse_object() {
    std::string object_name;
    char c;
    while(file.get(c)) {
        if (c == ':' ) {
            std:: cout << "Found object " << object_name << std::endl;
            if(!parse_component(object_name)) return false;
        } else if (c == '\"' || c == '}' || c == ' ' || c == '\n' || c == '\t' || c == '\r') {
            continue;
        } else if (c == '}') {
            break;
        } else if (c == ',') {
            object_name.clear();
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

    std::string component_name;
    char c;
    while(file.get(c)) {
        if (c == ':') {
            std::cout << "found component " << component_name << std::endl;
            parse_data(parent_object, component_name);
            component_name.clear();
        } else if (c == '}' ) {
            break;
        } else if (c == '\"' || c == '{' || is_whitespace(c)) {
            continue;
        } else if (c == ',') {
            component_name.clear();
        } else {
            component_name.push_back(c);
        }
    }

    return true;
}

bool Json::parse_data(std::string &object_id, std::string &component_id) {
    if (component_id.empty()) {
        std::cerr << "component name is empty" << std::endl;
        return false;
    }

    if (objects[object_id].count(component_id)>0) {
        std::cerr << "component duplicate: " << component_id << std::endl;
        return false;
    }


    std::string data_id, data_value;
    bool parsing_key = true;
    char c;
    while(file.get(c)) {
        // done with the component
        if ( c == '}') {
            objects[object_id][component_id][data_id] = data_value;
            parsing_key = true;
            data_value.clear();
            data_id.clear();
            break;
        // ignore whitespace
        } else if (c == '\"' || c == '{' || is_whitespace(c)) {
            continue;
        // if we've reached the value to the key, value pair
        }  else if (c == ':') {
            if (data_id.empty()) {
                std::cerr << "data_id is empty" << std::endl;
                return false;
            }
            parsing_key = false;
        // we've reached the end of one of the data values
        } else if (c == ',') {
            /**
             * this is where the *magic* happens!
             * because of how awesome maps are it will automatically add
             * all of these values to the map if they don't exist 
             * (which they shouldn't)
            */
            objects[object_id][component_id][data_id] = data_value;
            parsing_key = true;
            data_value.clear();
            data_id.clear();
        } else {
            if (parsing_key) {
                data_id.push_back(c);
            } else {
                data_value.push_back(c);
            }

        }
    }

    return true;
}

