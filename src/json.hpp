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
 * Usage:
 *
 * Json json;
 * json.parse_file("objects/walls.json");
 *
 * for ( const auto&[object, component] : json.objects) {
 *      std::cout << object << " : " << std::endl;
 *      for (const auto&[comp_id, data] : component) {
 *          std::cout << "    " << comp_id << " : " << std::endl;
 *          for (const auto&[key, value] : data) {
 *              std::cout << "        " << key << " : " << value << std::endl;
 *          }
 *      }
 *  }
 *
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
        bool parse_data(std::string &object_id, std::string &component_id);

        // basically just return objects[name]; we'll see how right I am when 
        // I try to implement it haha
        std::map<std::string, std::map<std::string, std::string>> get_object_data(std::string name);

        std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> objects;

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

        bool is_whitespace(char c);
        std::fstream file;

};

#endif
