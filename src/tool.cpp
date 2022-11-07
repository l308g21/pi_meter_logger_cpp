#include "tool.h"

#include <algorithm>


void trim_left( std::string& _string )
{
    _string.erase( _string.begin(), std::find_if( _string.begin(), _string.end(), [](const char _char){
        return !std::isspace(_char);
    }));
    return;
}

void trim_right( std::string& _string)
{
    _string.erase( std::find_if( _string.rbegin(), _string.rend(), [](const char _char){
        return !std::isspace(_char);
    }).base(), _string.end());
    return;
}

void trim ( std::string & _string)
{
    trim_left(_string);
    trim_right(_string);
    return;
}