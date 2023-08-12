if not exist "bin\" mkdir bin
if not exist "obj\" mkdir obj
if not exist "obj\src\" mkdir obj\src
g++.exe -Wall -fexceptions -g -O2 -std=c++17 -Og -Iinclude -c main.cpp -o obj\main.o
g++.exe -Wall -fexceptions -g -O2 -std=c++17 -Og -Iinclude -c src\Basics.cpp -o obj\src\Basics.o
g++.exe -Wall -fexceptions -g -O2 -std=c++17 -Og -Iinclude -c src\Cell.cpp -o obj\src\Cell.o
g++.exe  -o bin\NORG.exe obj\main.o obj\src\Basics.o obj\src\Cell.o  -Wl,--stack,25000000 
