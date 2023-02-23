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
#include "Cell.h"

using namespace std;

Cell::Cell()
{
    //ctor
    val = 0;
    reg = "";
}

Cell::~Cell()
{
    //dtor
}

long long int Cell::get() {
    return val;
}

void Cell::set(long long int i) {
     val = i;
}

void Cell::setMin(long long int i) {
     if (i < val) {val = i;}
}

void Cell::add(long long int i) {
     val += i;
}

void Cell::minus() {
     val = -val;
}

void Cell::mult(long long int i) {
     val *= i;
}

bool Cell::divide(long long int i) {
     if (i==0) {return true;}
     val /= i;
     return false;
}


bool Cell::compEq(long long int i) {
    int comp = 0;
    if (val==i) {
        comp = 1;
    } else {
        comp = -1;
    }
    return comp==1;
}

bool Cell::compGe(long long int i) {
    int comp = 0;
    if (val>=i) {
       comp = 1;
    } else {
       comp = -1;
    }
    return comp==1;
}


void Cell::clearReg() {
     reg = "";
}

string Cell::getReg() {
    return reg;
}

bool Cell::setReg(string s) {
    if (s.size() > 20) {return false;}
    reg=s;
    return true;
}
