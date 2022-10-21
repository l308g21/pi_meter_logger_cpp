# Pi Meter Logger

sense and log meter data to database

## setup

### required libraries

* **mariadb**
* **pigpio**
since ligpigpio via apt did not work (at least for me)
try https://github.com/joan2937/pigpio, install via command
> sudo ./get_pigpio.sh


### create config files

* from *db.config.template* create **db.config**
contains data required to connect to database

* from *deploy.config.template* create **deploy.config**
contains data required to deploy data to pi

## build
on remote pi run command
> make

to build from remote pi while on local machine run command
> make deploy

## database
expects db structure to match query
> insert into < db >.LOGGER values (reading, reading_time, logger_id)