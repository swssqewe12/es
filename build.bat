@echo off
echo Compiling...
cd o
g++ -c -std=c++11 ../src/*.cpp
cd ../
echo Linking...
g++ -o main.exe -mconsole o/*.o
echo DONE.