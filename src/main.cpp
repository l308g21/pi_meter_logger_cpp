
#include "datalogger.h"
#include "db.h"
#include "unistd.h"


#include <iostream>

int main(){

    // create db instance
    // load db config
    
    // every 10 min 

    // delete db instance

    CDatabase db = CDatabase();
    CDatalogger logger = CDatalogger();
    
    logger.set_db(db);
    logger.set_gpio(4);
    logger.set_period(10);

    logger.start_logging();

    // this part is never executed
    return 0;
}
