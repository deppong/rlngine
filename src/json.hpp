#pragma once
#ifndef JSON_HPP
#define JSON_HPP

/**
 * This is by no means a fully functional or complete json parser
 * as it will really only support std::string inside. On top of this
 * the actual data structure is mainly only for support a "object" id
 * which points to a dictionary of components where the id would be a string
 * and the value is yet another dictionary of strings key value pairs.
 * For a better understanding look in the objects directory of this project
 * as it will make much more sense for the objects member of this class.
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
        bool parse_object();
        bool parse_component(std::string &parent_object);

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

};

#endif
