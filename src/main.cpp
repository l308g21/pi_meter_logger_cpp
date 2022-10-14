
#include "datalogger.h"
#include "db.h"


#include <iostream>

int main(){

    // create db instance
    // load db config
    
    // every 10 min 

    // delete db instance

    const CDatabase db = CDatabase();
    const CDatalogger logger = CDatalogger();
    
    logger.set_db(db);
    logger.set_gpio(4);
    logger.set_period(10);

    logger.start_logging();

    while (true)
    {
        sleep(10);
    }

}


// #include <iostream>
// #include <unistd.h>
// #include <pigpio.h>
// #include <mariadb/mysql.h>

// #define FLASH_GPIO 4
// #define READING_PERIOD_S 10

// void state_change_detected( int _gpio, int _level, uint32_t _tick, void* _p_flash_count)
// {
//    // check if rising edge
//    if (_level != 1) return;

//    *(int *) _p_flash_count += 1;

//    return;
// }


// int main(int argc, char *argv[])
// {

//    int flash_count = 0;

//    if (gpioInitialise() < 0) return 1;
//    gpioSetMode(        FLASH_GPIO, PI_INPUT);
//    gpioSetPullUpDown(  FLASH_GPIO, PI_PUD_DOWN);    // enable internal pull-down
//    gpioSetAlertFuncEx( FLASH_GPIO, state_change_detected, (void *) &flash_count);

//    // keep program running
//    while (true)
//    {
//       sleep(READING_PERIOD_S);

//       int reading = flash_count;
//       flash_count = 0;

//       std::cout << "saving to db: " << reading <<  std::endl;
      

//    }


//    gpioTerminate();
//    return 0;
// }