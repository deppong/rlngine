#pragma once
#ifndef JSON_HPP
#define JSON_HPP

/**
 * This is by no means a fully functional or complete json parser
 * as it will really only support std::string inside; however, 
 * this really meets my use case as I can simply cast the std::string
 * to any 
*/

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class Json {
    public:
        Json();
        ~Json();
        
        bool parse_file(std::string file_path);

        // basically just return objects[name]; we'll see how right I am when 
        // I try to implement it haha
        std::map<std::string, std::map<std::string, std::string>> get_object_data(std::string name);

    private:
        /**
         * Each object will be it's own string which just holds a list (vector)
         * of dictionaries. each component has a list of key value pairs. I 
         * think I could even have the component just be a list of std::any or
         * something but I'm not too sure at the moment
         * 
         *  std::map<
         *      std::string, std::map<
         *          std::string, std::map<std::string, std::string>
         *      >
         *  >
         * or could be read as:
         * walls.json
         */
        std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> objects;

        std::fstream file;

}

#endif
