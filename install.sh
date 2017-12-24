#!/bin/bash

LOCAL_INCLUDE_DIRECTORY="/usr/local/include/"

if [ ! -d "$LOCAL_INCLUDE_DIRECTORY" ]; then
	echo "Local include directory does not exist..."
	read -e -p "Please enter the absolute path to the correct directory for installing the library ( /usr/local/include ): " SENSUM_LIB_DIRECTORY
	read -e -p "Please enter the absolute path to the correct directory for installing the library examples ( /usr/src ): " SENSUM_EXAMPLES_PATH
fi

# Проверяем, существует ли папка /usr/local/include/
if [ -d "$LOCAL_INCLUDE_DIRECTORY" ]; then

	SENSUM_LIB_DIRECTORY="/usr/local/include/"
	SENSUM_EXAMPLES_PATH="/usr/src/"	

	echo "Local include directory exist, starting installation..."  
	
fi

# Проверяем была ли ранее установленна библиотека. Если да то удаляем старую версию
if [ -d "$SENSUM_LIB_DIRECTORY/sensum" ]; then
        echo "Old library folders exist. Deleting..."
        rm -rf "$SENSUM_LIB_DIRECTORY/sensum"
fi

if [ -d "$SENSUM_EXAMPLES_PATH/sensum" ]; then
        echo "Old library examples folders exist. Deleting..."
        rm -rf "$SENSUM_EXAMPLES_PATH/sensum"
fi

# Собственно установка
echo "Creating library folder..."
mkdir "$SENSUM_LIB_DIRECTORY/sensum"

echo "Copy library files..."
cp -v ./lib/* "$SENSUM_LIB_DIRECTORY/sensum"

echo "Creating library examples folder..."
mkdir "$SENSUM_EXAMPLES_PATH/sensum"

echo "Copy library examples files..."
cp -v ./examples/* "$SENSUM_EXAMPLES_PATH/sensum"
chmod +x "$SENSUM_EXAMPLES_PATH/sensum/compile.sh"

echo "The library was copied to the folder $SENSUM_LIB_DIRECTORY"
echo "Examples of using the library copied to a folder $SENSUM_EXAMPLES_PATH"
