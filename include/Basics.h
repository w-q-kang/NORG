/*
Copyright 2023 W. Q. Kang

This file is part of the NORG Interpreter.

    The NORG Interpreter is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The NORG Interpreter is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the NORG Interpreter.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef BASICS_H
#define BASICS_H
#include <string>
#include <fstream>
#include <filesystem>

using namespace std;

class Basics
{
    public:
        Basics();
        virtual ~Basics();
        string getDir(string s);
        string readFile(string name);
        string getAFile(string dir);
        void deleteFile(string name);
        int charToInt(char c);
        int digitToInt(char c);
        string intToStr(long long int i, int outmode);
        void checkDirection(char c);
        bool isDigit(char c);
    protected:
        int xToInt(char c, string s);
    private:
        string table;
};

#endif // BASICS_H
