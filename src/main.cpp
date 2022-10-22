
#include "datalogger.h"
#include "db.h"
#include "unistd.h"


#include <iostream>

int main(){

    // create db instance
    // load db config
    
    // add individual instances
    // log every 10 min

    // delete db instance


    // exits if init fails
    CDatalogger::gpio_init();

    CDatabase db = CDatabase();
    CDatalogger logger = CDatalogger();

    // run program from project root directory
    // or modify following line
    db.load_config("config/db.conf");
    
    logger.set_db(db);
    logger.set_gpio(4);
    logger.set_period(10);
    logger.start_logging();

    // add another logger here


    //keep program running while logger runs in background
    while (true) sleep(60);

    return 0;
}
