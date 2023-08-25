if [ ! -d "bin" ]; then mkdir "bin"; fi
if [ ! -d "obj/src" ]; then mkdir -p "obj/src"; fi
clang++ -Wall -fexceptions -g -std=c++17 -Og -Iinclude -c main.cpp -o obj/main.o
clang++ -Wall -fexceptions -g -std=c++17 -Og -Iinclude -c src/Basics.cpp -o obj/src/Basics.o
clang++ -Wall -fexceptions -g -std=c++17 -Og -Iinclude -c src/Cell.cpp -o obj/src/Cell.o
clang++ -o bin/norg obj/main.o obj/src/Basics.o obj/src/Cell.o -Wl,-stack_size -Wl,0x1000000 
