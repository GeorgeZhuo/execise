g++ -g -o genNegImages genNegImages.cpp `pkg-config --cflags --libs opencv`
./genNegImages
cd ./images
rm *.bmp
cd ..
rm negative.txt

mv *.bmp ./images/
ls ./images > negative.txt

