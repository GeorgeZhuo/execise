./opencv_createsamples -vec positive.vec -info positive/positive.txt -bg negative/negative.txt -w 28 -h 28 -num 10000
./opencv_haartraining -data classifier -vec positive.vec  -npos 200 -nneg 800 -bg negative/negative.txt -w 28 -h 28 -mem 500 -mode all
