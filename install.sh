#!/bin/bash

$DIRECTORY = /usr/local/include/

if [ -d "$DIRECTORY" ]; then

	echo "Local include folder exist, starting installation."  
	mkdir $DIRECTORY/sensum
	cp -v ./lib/* $DIRECTORY/sensum/
fi