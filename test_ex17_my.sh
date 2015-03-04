#!/bin/sh

rm a.bin
make

echo
echo
echo "##### Test beging #####"

./ex17_my a.bin c 1024 1000
./ex17_my a.bin s 1 Joe joe@aaa.com 
./ex17_my a.bin g 1
./ex17_my a.bin s 2 Ken ken@bbb.com
./ex17_my a.bin s 2 Han han@ccc.com
./ex17_my a.bin d 2
./ex17_my a.bin s 2 Han han@ccc.com

./ex17_my a.bin s 3 Lin lin@ccc.com
./ex17_my a.bin s 4 Yan yan@ccc.com
./ex17_my a.bin s 999 Nan nan@ccc.com
./ex17_my a.bin s 6 Man man@ccc.com
./ex17_my a.bin s 5 Wan wan@ccc.com

./ex17_my a.bin l