#!/bin/env bash

# sudo previleges required by command in line 13

mkdir /tmp/pigpio
cd /tmp/pigpio
wget "https://github.com/joan2937/pigpio/archive/master.zip"
unzip master.zip
cd pigpio-master
make

# this one needs sudo privileges
(make install && cd /tmp && rm -rf pigpio) || echo "run command < cd /tmp/pigpio/pigpio-master && sudo make install > to finalize pigpio installation"

