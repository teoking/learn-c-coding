#!/bin/sh

make clean

make

devpkg=./devpkg

$devpkg -S
$devpkg -I https://github.com/teoking/learn-c-coding.git
$devpkg -L
