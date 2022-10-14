#include "datalogger.h"
#include "db.h"

#include <pigpio.h>

#include <unistd.h>
#include <iostream>
#include <string>





void *write_data(void * _arg)
{
    CDatalogger & logger = *(CDatalogger *) _arg;
    while (true)
    {
        // sleep over the course of period length
        // -> write pulse_count to db
        sleep(logger.get_period());
        
        logger.log_period();
    }
    // returning nullptr to inhibit warning
    return nullptr;
}





CDatalogger::CDatalogger()
{
    period   = 10;
    db       = nullptr;
    return;
}


CDatalogger::~CDatalogger()
{
    gpioStopThread(p_thread_logger);

    db              = nullptr;
    p_thread_logger = nullptr;
    return;
}



unsigned int CDatalogger::get_pulse_count()
{
    return pulse_count;
}

int CDatalogger::get_period()
{
    return period;
}

void CDatalogger::set_db( CDatabase& _db)
{
    db = &_db;
    return;
}


void CDatalogger::set_period( const int _seconds)
{
    period = _seconds;
    return;
}

void CDatalogger::set_gpio( const int _gpio)
{
    if (_gpio < 2 || _gpio > 27)
    {
        std::cout << "gpio number !: 2 < gpio < 27" << std::endl;
        exit(0);
    }
    gpio = _gpio;
    return;
}


void CDatalogger::set_id( const int _id)
{
    id = _id;
    return;
}


void CDatalogger::start_logging()
{
    // split off new thread
    //      sleep over the course of period length
    //      write current value to db
    // remember to close thread if logger determinated
    
    if (p_thread_logger != nullptr) return;

    p_thread_logger = gpioStartThread(write_data, (void *) this );
    return;
}

void CDatalogger::log_period()
{
    std::string reading_time = "NULL";  // NULL defaults back to NOW() db sides
    int reading = pulse_count;
    pulse_count = 0;

    std::string query = "INSERT INTO SENSOR_DATA (reading, reading_time, sensor_id) VALUES (";
    query += std::to_string(reading) + ',' 
           + reading_time + ',' 
           + std::to_string(id) + ");";


    db->run(query.c_str());
    return;
}
