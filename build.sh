# This script only runs on POSIX sistems.

#!/bin/bash

echo "Start building."
mkdir build
g++ manager/main.cpp -o build/manager
if [[ $? == 0 ]]
then
  echo "Build SUCCEDED."
  echo "You can ignore warnings."
  echo "Execute the prgram by runing: build/manager"
else
  echo "Build FAILED."
  echo "See the logs to review the error."
fi
