#!/bin/bash

#-------------------------------------------------------------------------------
#
# Script to configure the building folder for CMake
#
# Author: Jesus Ortiz
# email : jortizsl@gmail.com
# Date  : 18-05-2014
#
#-------------------------------------------------------------------------------

# Set color script
SCRIPT_FOLDER=$(dirname $0)
source $SCRIPT_FOLDER/colors.sh


# Function to display the help
function display_help
{
  color_reset
  echo -e "${COLOR_BOLD}NAME${COLOR_RESET}"
  echo -e "       configure.sh - Script to configure the building folder for CMake"
  echo -e ""
  echo -e "${COLOR_BOLD}SYNOPSIS${COLOR_RESET}"
  echo -e "       ${COLOR_BOLD}configure.sh${COLOR_RESET} [${COLOR_UNDE}OPTIONS${COLOR_RESET}]..."
  echo -e ""
  echo -e "${COLOR_BOLD}DESCRIPTION${COLOR_RESET}"
  echo -e "       This script configures the building folder for CMake. The script has to"
  echo -e "       be called from the build folder."
  echo -e ""
  echo -e "       You can add the following options when calling the script:"
  echo -e ""
  echo -e "       ${COLOR_BOLD}--help${COLOR_RESET}, ${COLOR_BOLD}-h${COLOR_RESET}"
  echo -e "              Display this help message"
  echo -e ""
  echo -e "       ${COLOR_BOLD}--debug${COLOR_RESET}, ${COLOR_BOLD}-g${COLOR_RESET}"
  echo -e "              Compiles in debug mode."
  echo -e "              If not compiling mode is set, CMake is called without flags."
  echo -e ""
  echo -e "       ${COLOR_BOLD}--release${COLOR_RESET}"
  echo -e "              Compiles in release mode"
  echo -e "              If not compiling mode is set, CMake is called without flags."
  echo -e ""
  echo -e "       ${COLOR_BOLD}-D${COLOR_RESET}${COLOR_UNDE}CMAKEVARIABLE${COLOR_RESET}"
  echo -e "              Specifies a CMake option. CMake will be invoked with the argument"
  echo -e "              -DCMAKEVARIABLE"
  echo -e ""
  echo -e "       ${COLOR_BOLD}--reset${COLOR_RESET}, ${COLOR_BOLD}-r${COLOR_RESET}"
  echo -e "              Deletes everything in the folder before configuring it"
  echo -e ""
  echo -e "${COLOR_BOLD}AUTHOR${COLOR_RESET}"
  echo -e "       Written by Jesus Ortiz."
  echo -e ""
  echo -e "${COLOR_BOLD}REPORTING BUGS${COLOR_RESET}"
  echo -e "       Report bugs to <jortizsl@gmail.com>"
  echo -e ""
  echo -e "${COLOR_BOLD}COPYRIGHT${COLOR_RESET}"
  echo -e "       This software is not for public distribution."
  echo -e ""
  color_reset
}


# Calculate the root folder and pass it as an option to CMake
ROOT_DIR=$(pwd)/$(dirname $0)/..

# Clean root path
OLDIFS="$IFS"
IFS='/'
END=false
while ! $END; do
  FOUND_BACK=false
  AUX=""
  ROOT_DIR_AUX=""
  for TOKEN in $ROOT_DIR; do
    if $FOUND_BACK; then
      ROOT_DIR_AUX=${ROOT_DIR_AUX}/${TOKEN}
    else
      if [ "$TOKEN" == ".." ]; then
        FOUND_BACK=true
      else
        if [ -n "$ROOT_DIR_AUX" ]; then
          ROOT_DIR_AUX=${ROOT_DIR_AUX}/${AUX}
        else
          ROOT_DIR_AUX=${AUX}
        fi
        AUX=$TOKEN
      fi
    fi
  done
  if ! $FOUND_BACK; then
    END=true
  else
    ROOT_DIR="/${ROOT_DIR_AUX}"
  fi
done
IFS="$OLDIFS"
OPTIONS="-DROOT_DIR=$ROOT_DIR"


# Reset terminal color
color_reset
echo ""


# Check arguments
for ARG in "$@"; do
  if [ $ARG == "--help" ] || [ $ARG == "-h" ]; then     # Display help
    display_help
    exit
  elif [ $ARG == "--debug" ] || [ $ARG == "-g" ]; then  # Compiles with the debug flag
    echo -e "${COLOR_INFO} + Debug mode${COLOR_RESET}"
    OPTIONS="$OPTIONS -DCMAKE_BUILD_TYPE=Debug"
  elif [ $ARG == "--release" ]; then                    # Compiles with the release flag
    echo -e "${COLOR_INFO} + Release mode${COLOR_RESET}"
    OPTIONS="$OPTIONS -DCMAKE_BUILD_TYPE=Release"
  elif [ ${ARG:0:2} == "-D" ]; then                     # cmake definitions
    OPTIONS="$OPTIONS -D${ARG:2}"
  elif [ $ARG == "--reset" ] || [ $ARG == "-r" ]; then  # Cleans the current folder before configuration
    echo -e "${COLOR_INFO} + Cleaning folder...${COLOR_RESET}"
    rm -rf *
  else
    echo "Unrecognized parameter. Please read the documentation with the --help parameter"
    exit
  fi
done


# Launch cmake with the automatic options
echo -e "${COLOR_INFO} + Launching CMake...${COLOR_RESET}"
echo -e "cmake $ROOT_DIR $OPTIONS"
echo ""
color_reset
cmake $ROOT_DIR $OPTIONS

