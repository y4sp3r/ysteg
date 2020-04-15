#!/bin/bash

#Compile
echo "[COMPILING]"
cd src
make
cd ..

echo "[TESTING INSERTION]"
#Test insertion
./bin/ysteg -hide "test/test.txt" "test/key.otp" "test/image.ppm" "out.image.ppm"

echo "[TESTING EXTRACTION]"
#Test extraction
./bin/ysteg -extract "out.image.ppm" "test/key.otp" "out.test.txt"

#Test if output is valid
cmp "out.test.txt" "test/test.txt"

#Checking the return value of cmp
if [ $? -ne 0 ]
then
    echo "[TEST FAILED]"
    exit 1
else
    echo "[TEST PASSED]"

    #Remove outputs
    rm "out.test.txt" "out.image.ppm"

    #Exit with no errors
    exit 0
fi
