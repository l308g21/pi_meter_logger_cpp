CREATE DATABASE IF NOT EXISTS SOME_DB;
USE SOME_DB;


-- DROP TABLE  IF EXISTS LOGGER_PERIODS;
CREATE TABLE IF NOT EXISTS LOGGER_PERIODS
(
    period_id       INTEGER     NOT NULL    PRIMARY KEY     AUTO_INCREMENT
    ,duration       INTEGER     NOT NULL    
    ,since          DATETIME    NOT NULL    DEFAULT NOW()
    ,logger_id      INTEGER     NOT NULL
);


-- DROP TABLE IF EXISTS LOGGER;
CREATE TABLE IF NOT EXISTS LOGGER_DATA
(
     reading_id     INTEGER     NOT NULL    PRIMARY KEY     AUTO_INCREMENT
    ,reading        INTEGER     NOT NULL
    ,reading_time   DATETIME    NOT NULL    DEFAULT NOW()
    ,logger_id      INTEGER     NOT NULL
);


--DROP TABLE IF EXISTS SENSOR
CREATE TABLE IF NOT EXISTS SENSOR
(
    sensor_id       INTEGER     NOT NULL    PRIMARY KEY     AUTO_INCREMENT
    ,sensor_name    VARCHAR(50) NOT NULL
    ,since          DATETIME    NULL
    ,logger_scale   INTEGER     NULL
);


ALTER TABLE LOGGER_PERIODS
    ADD CONSTRAINT fk_logger_periods_sensor FOREIGN KEY (logger_id) REFERENCES SENSOR (sensor_id)
;

ALTER TABLE LOGGER_DATA
    ADD CONSTRAINT fk_logger_data_sensor FOREIGN KEY (logger_id) REFERENCES SENSOR (sensor_id)
;
