
#include "config.h"
#include "tool.h"

#include <fstream>
#include <sstream>
#include <iostream>




CConfig::CConfig( void )
{
    delimiter = ':';
}


void CConfig::load_config( std::string& _config_path)
{
    // open file
    // exit if error while opening
    // iterate over each line
    // splice line in parameter-name & -value

    std::ifstream config_file;
    config_file.open( _config_path, std::ios_base::in);

    if( ! config_file.is_open() )
    {
        std::cerr << "ERROR, failed to open " << _config_path << std::endl;
        exit(1);
        // are there cause specific exit codes
    }

    std::string line, word;
    int line_counter = 0;
    while (config_file) // loop till end reached
    {
        line_counter++;

        std::getline(config_file, line);
        trim_left( line );
        // allow comments
        if (line[0] == '#') continue;

        std::stringstream stream_line(line);
        std::getline(stream_line, word, delimiter);


        if ( line.length() - word.length() == 0 )
        {
            // word == line -> there was no delimiter
            // cannot split into name and value
            std::cerr << "ERROR, in line " << line_counter << 
                ": there seems to be no " << delimiter << 
                " in '" << line << "'" << std::endl;
            exit(1);
            // are there cause specific exit codes?   
        }

        trim_right(word);

        SParameter param;
        param.name = word;
        
        // second half, i.e. value 
        std::getline(stream_line, word);

        trim(word);
        if (word.length() == 0 )
        {
            std::cerr << "ERROR, in line " << line_counter
            << ": no value to parameter" << std::endl;
            exit(1);
            // are there cause specific exit codes?
        }
        param.value = word;

        v_parameters.push_back(param);

    }
    return;
}


void CConfig::set_delimiter( const char _delimiter )
{
    delimiter = _delimiter;
    return;
}


std::string* CConfig::get( std::string& _parameter)
{
    for ( int i = 0; i < (int) v_parameters.size(); i++ )
    {
        if (v_parameters[i].name == _parameter) return &v_parameters[i].value;
    }
    return nullptr;
}