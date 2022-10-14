#pragma once

#include <string>

class CDatabase
{
    public:

        void load_config(const char* config_file);
        void run(        const char* query);

    private:

        std::string hostname;
        std::string database;
        std::string username;
        std::string password;
        int port;
};