#pragma once


class CDatabase;

class CDatalogger
{
    public:

        CDatalogger();
       ~CDatalogger();

       static void gpio_init();

    public:

        void set_db( CDatabase& _db);
        void set_period( const int seconds);
        void set_gpio(   const int gpio);
        void set_id  (   const int id);
        
        unsigned int get_pulse_count();
        int          get_period();

        void start_logging();
        void log_period();


    private:
        
        CDatabase*      db;
        int             id;
        int             period;    
        int             gpio;
        unsigned int    pulse_count;

};