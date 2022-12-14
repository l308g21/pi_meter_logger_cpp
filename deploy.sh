#!/bin/bash

USER=$1
MACHINE=$2
TARGET=$3
REMOTE_LOCATION=$4

ssh $USER@$MACHINE "mkdir -p $REMOTE_LOCATION"
scp $TARGET.zip $USER@$MACHINE:$REMOTE_LOCATION/$TARGET.zip
ssh $USER@$MACHINE "cd $REMOTE_LOCATION && unzip $TARGET.zip && make"