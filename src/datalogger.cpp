#include "datalogger.h"
#include "db.h"

#include <pigpio.h>

#include <unistd.h>
#include <iostream>
#include <string>




// some helper functions

void increment_pulse_counter(int _gpio, int _level, uint32_t _tick, void* _p_pulse_count)
{
    // only trigger on rising edge
    if (_level != 1) return;

    * (unsigned int*) _p_pulse_count += 1;

    // returning nullptr to inhibit warning
    return;
}


void *CDatalogger::logging_data( void* logger )
{
    
    while (true)
    {
        sleep( ((CDatalogger*) logger)->get_period() );
        ((CDatalogger*) logger)->log_period();
    }
}





void CDatalogger::gpio_init(){
    if ( gpioInitialise() < 0 )
    {            //  ^-- this seems to be a library level typo
        std::cerr << "ERROR: gpio initialization failed" << std::endl;
        exit(1);
    }
    return;
}


CDatalogger::CDatalogger()
{
    gpio   = -1;
    period = 10;
    db     = nullptr;
    p_logger_thread = nullptr;
    return;
}


CDatalogger::~CDatalogger()
{
    db = nullptr;
    gpioStopThread(p_logger_thread);
    p_logger_thread = nullptr;
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
    
    if ( db == nullptr )
    {
        std::cerr << "ERROR: logger.database not set" << std::endl;
        exit(1);
    }
    if ( gpio < 0 )
    {
        std::cerr << "ERROR: logger.gpio not set" << std::endl;
    }else if ( gpio > 53 )
    {
        std::cerr << "ERROR: logger.gpio value exceeds viable gpio range: " << gpio << " < 53" << std::endl;
        exit(1);
    }

    // one small notice:
    // don't be stupid, don't use gpios already in use
    gpioSetMode(gpio, PI_INPUT);
    gpioSetPullUpDown(gpio, PI_PUD_DOWN);

    gpioSetAlertFuncEx(gpio, increment_pulse_counter, &pulse_count);
    p_logger_thread = gpioStartThread(logging_data, this);

    return;
}

void CDatalogger::log_period()
{
    std::string reading_time = "NOW()";  // NULL defaults back to NOW() db sides // defaulting did not work 
    int reading = pulse_count;
    pulse_count = 0;

    std::string query = "INSERT INTO LOGGER_DATA (reading, reading_time, logger_id) VALUES (";
    query += std::to_string(reading) + ',' 
           + reading_time + ',' 
           + std::to_string(id) + ");";


    db->run(query.c_str());
    return;
}
