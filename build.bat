@echo off
echo Compiling...
cd o
g++ -c ../src/*.cpp
cd ../
echo Linking...
g++ -o main.exe -mconsole o/*.o
echo DONE.