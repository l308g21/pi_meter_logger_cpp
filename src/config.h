#pragma once

#include <vector>
#include <string>

struct SParameter
{
    std::string name;
    std::string value;
};

class CConfig
{
    public:
        void load_config( std::string config_path);
        std::string get( std::string parameter);
        void set_delimiter (const char delimiter);
 
    public:
        CConfig( void );
       ~CConfig( void );

    private:
        std::vector<SParameter> v_parameters;

        // default: ':'
        char delimiter;
};