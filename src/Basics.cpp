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
#include "Basics.h"

using namespace std;

Basics::Basics()
{
    //ctor
    table = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,!?:;-=<>+*/\"'{} ";
}

Basics::~Basics()
{
    //dtor
}



string Basics::getDir(string s) {
    if (s.find_last_of('\\') != string::npos) {
       int i = s.find_last_of('\\');
       return s.substr(0,i);
    } else {
        return s;
    }
}

string Basics::readFile(string name) {
   fstream fs;
   string content = "";
   fs.open(name,ios::in); //open a file to perform read operation using file object
   if (fs.is_open()){   //checking whether the file is open
      string tp;
      while(getline(fs, tp)){ //read data from file object and put it into string.
         if ((tp.size() > 0)) {
            content += tp;
         }
      }
      fs.close(); //close the file object.
   }
   return content;
}

string Basics::getAFile(string dir) {
    string result = "";
    for (const auto & file : filesystem::directory_iterator(dir)) {
        string path = file.path().string();
        int i = path.size()-5;
        string ext = path.substr(i);
        if ((ext != ".norg") && (ext != ".NORG")&& (ext != ".Norg")) {result = path; break;}
     }
     return result;
}

void Basics::deleteFile(string name) {
    int v = remove(name.c_str()); // 0=ok
    if (v != 0) {exit(EXIT_FAILURE);}
}

int Basics::charToInt(char c) {
    size_t found = table.find(c);
    if (found!=string::npos) {
        return (int) found;
    } else {
        return -1;
    }
}

int Basics::digitToInt(char c) {
    return xToInt(c, "0123456789");
}

int Basics::xToInt(char c, string s) {
    size_t found = s.find(c);
    if (found!=string::npos) {
        return (int) found;
    } else {
        return -1;
    }
}

string Basics::intToStr(long long int i, int outmode) {
    if (outmode == 0) {return to_string(i);}
    if ((i<0) || (i>79)) {return "";}
    if ((outmode==2) && (i<10)) {return "";}; // alpha-only
    string t = "";
    char c =table[i];
    t.push_back(c);
    return t;
}

void Basics::checkDirection(char c) {
    string s = "lrudfb";
    size_t found = s.find(c);
    if (found==string::npos) {exit(EXIT_FAILURE);}
}

bool Basics::isDigit(char c) {
    return (c=='0') || (c=='1') || (c=='2') || (c=='3') || (c=='4') || (c=='5') || (c=='6') || (c=='7') || (c=='8') || (c=='9');
}

