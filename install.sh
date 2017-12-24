#!/bin/bash

LOCAL_INCLUDE_DIRECTORY="/usr/local/include/"
SENSUM_LIB_DIRECTORY="/usr/local/include/sensum"
SENSUM_EXAMPLES_PATH="/usr/src/sensum-library-examples"

if [ -d "$LOCAL_INCLUDE_DIRECTORY" ]; then
	echo "Local include directory exist, starting installation..."  
	
	if [ -d "$SENSUM_LIB_DIRECTORY" ]; then
		echo "Old library folders exist. Deleting..."
		rm -rf $SENSUM_LIB_DIRECTORY
	fi
	
	if [ -d "$SENSUM_EXAMPLES_PATH" ]; then
                echo "Old library examples folders exist. Deleting..."
                rm -rf $SENSUM_LIB_DIRECTORY
	fi
	
	echo "Creating library folder..."
	mkdir "$SENSUM_LIB_DIRECTORY"

	echo "Copy library files..."
	cp -v ./lib/* "$SENSUM_LIB_DIRECTORY"

	echo "Creating library examples folder..."
	mkdir "$SENSUM_EXAMPLES_PATH"

	echo "Copy library examples files..."
	cp -v ./examples/* "$SENSUM_EXAMPLES_PATH"
	chmod +x "$SENSUM_EXAMPLES_PATH/compile.sh"
fi

if [ ! -d "LOCAL_INCLUDE_DIRECTORY" ]; then
	echo "Local include directory does not exist, starting installation..."
fi



echo "The library was copied to the folder $SENSUM_LIB_DIRECTORY"
echo "Examples of using the library copied to a folder $SENSUM_EXAMPLES_PATH"