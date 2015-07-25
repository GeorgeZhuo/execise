g++ -g -o houghlines houghlines.cpp `pkg-config --cflags --libs opencv`
for i in $(seq 1 15)
do
    ./houghlines $i.jpg
done
#./houghlines 1.jpg 
#./houghlines 2.jpg 
#./houghlines 3.jpg 
./houghlines 4.jpg
#./houghlines 5.jpg 
#./houghlines 6.jpg
