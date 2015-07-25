g++ -g -o stitch_detail stitching_detailed.cpp `pkg-config --cflags --libs opencv`
./stitch_detail `ls *.JPG`
