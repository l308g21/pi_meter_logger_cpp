#include "db.h"

#include <mariadb/mysql.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


// helper functions
enum CONFIG_PARAMETERS {OTHER, HOSTNAME, DATABASE, USERNAME, PASSWORD, PORT};

CONFIG_PARAMETERS hash_parameter( std::string _parameter)
{
    if (_parameter == "hostname") return CONFIG_PARAMETERS::HOSTNAME;
    if (_parameter == "database") return CONFIG_PARAMETERS::DATABASE;
    if (_parameter == "username") return CONFIG_PARAMETERS::USERNAME;
    if (_parameter == "password") return CONFIG_PARAMETERS::PASSWORD;
    if (_parameter == "port")     return CONFIG_PARAMETERS::PORT;
    return CONFIG_PARAMETERS::OTHER;
}









void CDatabase::load_config(const char* _config_file)
{
    // open file
    // read lines
    //      end if read all parameter
    // split line
    // match line[0] -> hostname | database | user | password
    // trim whitespaces from line[1]
    // save line[1] to matched variable

    std::ifstream config_file;
    config_file.open("../config/db.config");

    if ( ! config_file.is_open() )
    {
        std::cerr << "file failed to open" << std::endl;
        exit(1);
    }

   
    
    std::string       line, parameter, value;
    char delimiter = ':';
    while (config_file)
    {
        std::getline( config_file, line);

        std::stringstream sline(line);
        std::getline( sline, parameter, delimiter);
        // if already at end of line, it missed a delimiter and is probably an empty line thus continue
        if(!sline) continue;
        std::getline( sline, value);

        switch (hash_parameter(parameter))
        {
            case CONFIG_PARAMETERS::HOSTNAME : hostname = value; break;
            case CONFIG_PARAMETERS::DATABASE : database = value; break;
            case CONFIG_PARAMETERS::USERNAME : username = value; break;
            case CONFIG_PARAMETERS::PASSWORD : password = value; break;
            case CONFIG_PARAMETERS::PORT     : port     = std::stoi(value); break;
            default: ;
        }
    }

    std::cout << "hostname: " << hostname << std::endl;
    std::cout << "database: " << database << std::endl;
    std::cout << "username: " << username << std::endl;
    std::cout << "password: " << password << std::endl;
    std::cout << "port:     " << port     << std::endl;


    return;
}







void CDatabase::run(const char* _query)
{
    // open mysql connection
    // run query
    // close connection

    MYSQL* connection;

    // only inserting data - no need for listening to responses
    // MYSQL_RES* response;
    // MYSQL_ROW  row;

    connection = mysql_init(NULL);


    // hostname, username, password, database, port, unix_socket, client_flag

    if (!mysql_real_connect( connection, hostname.c_str(), username.c_str(), password.c_str(), database.c_str(), port, NULL, 0))
    {
        // connection failed -> print issue and exit
        std::cerr << "connection failed: " << mysql_error(connection) << std::endl;
        exit(1);
    }

    if (mysql_query(connection, _query))
    {
        std::cerr << "query caused error: " << mysql_error(connection) << std::endl;
        exit(1);
    }
    // incomplete but currently i'm not interested in returning data
    // response = mysql_use_result( connection );
    return;
}
