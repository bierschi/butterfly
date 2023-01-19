#!/bin/bash

main()
{

  if [[ $# -eq 0 ]]
  then
    print_usage
  fi

  STD=false
  XML=false
  HTML=false

  while [[ $# -gt 0 ]]
  do
    case "$1" in
      "--std" )   STD=true; shift;;
      "--xml" )   XML=true; shift;;
      "--html" )  HTML=true; shift;;

      "-h" | "--help" ) print_usage;;
      "--" ) shift; break;;
      *) print_usage;;
    esac
  done

  set_directories
  set_options
  mkdir -p ../reports

  if [[ "$STD" = true ]]
  then
    cppcheck $DIR_INCLUDE $DIR_SRC $OPTIONS
    exit 1

  fi

  if [[ "$XML" = true ]]
  then
    cppcheck $DIR_INCLUDE $DIR_SRC $OPTIONS 2>../reports/cppcheck.xml

    if [[ "$HTML" = true ]]
    then

      cppcheck-htmlreport --file ../reports/cppcheck.xml --report-dir=../reports/html/ --title=butterfly

    fi
  fi

}

print_usage()
{
  echo "Usage:    cppcheck.sh [--std] or [ [--xml] & [--html] ]"
  echo ""
  echo "--std     Prints the cppcheck to the standard output"
  echo ""
  echo "--xml     Creates a cppcheck xml file"
  echo ""
  echo "--html    Creates the cppcheck html files"
  exit 1
}

set_directories()
{
  DIR_INCLUDE="-I../include -I../include/crypto"
  DIR_SRC="../src ../src/crypto"
}

set_options()
{
  if [[ "$STD" = true ]]
  then
    OPTIONS="--enable=all --suppress=missingIncludeSystem --suppressions-list=suppressions.txt --std=c++11 --inline-suppr --verbose"
  else
    OPTIONS="--enable=all --suppress=missingIncludeSystem --suppressions-list=suppressions.txt --std=c++11 --inline-suppr --verbose --xml --xml-version=2"
  fi
}

main "$@"
