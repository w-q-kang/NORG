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
#ifndef CELL_H
#define CELL_H
#include <string>

using namespace std;

class Cell
{
    public:
        Cell();
        virtual ~Cell();
        // value
        long long int get();
        void set(long long int i);
        void add(long long int i);
        void mult(long long int i);
        bool divide(long long int i);
        void minus();
        void setMin(long long int i);
        // compare
        bool compEq(long long int i);
        bool compGe(long long int i);
        // exec register
        void clearReg();
        string getReg();
        bool setReg(string s);
    protected:

    private:
        long long int val;
        string reg;
};

#endif // CELL_H
