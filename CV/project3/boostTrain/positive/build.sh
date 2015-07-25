#! /bin/bash

g++ -g -o genPosImages genPosImages.cpp `pkg-config --cflags --libs opencv`
./genPosImages
cd ./images
rm *.bmp
cd ..
rm positive.txt

mv *.bmp ./images/
ls ./images > positive.txt
sed -i 's/bmp/bmp 1 0 0 28 28/' positive.txt
