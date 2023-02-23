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
#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include "Cell.h"
#include <vector>
#include <filesystem>
#include "Basics.h"

using namespace std;

struct Pos {
    int x;
    int y;
    int z;
};

string parcmds = "aghimqsy";

int flagci = 0; // global comparison indicator
int flagfs = 0; // global file status indicator (1=all files read and deleted)

int cmdLength(string s, int pos) {
    int i = 1;
    if (parcmds.find(s[pos])!=string::npos) {
        return 2;
    } else if (s[pos] == 't') {
        while (i+pos < (int) s.size()) {
           if (s[i+pos] == '.') {break;}
           i++;
        }
        return i;
    }

    return 1;

}

void moveCursor(char direction, int& cx, int& cy, int& cz, int dmax, bool pageMode) {
    if (direction == 'b') {
       // back
       cy++;
       if (cy > dmax) {
          cy=0;
          if (pageMode) {exit(EXIT_FAILURE);}
       };

    } else if (direction == 'd') {
       // down
       cz--;
       if (cz<0) {
           cz=dmax;
           if (pageMode) {moveCursor('b', cx, cy, cz, dmax, pageMode);}
       }
    } else if (direction == 'f') {
       // forward
       cy--;
       if (cy<0) {
            cy=dmax;
            if(pageMode) {exit(EXIT_FAILURE);}
       }
    } else if (direction == 'l') {
       // left
       cx--;
       if (cx<0) {
            cx=dmax;
            if (pageMode) {moveCursor('u', cx, cy, cz, dmax, pageMode);}
       }

    } else if (direction == 'r') {
      // right
      cx++;
      if (cx > dmax) {
            cx=0;
            if (pageMode) {moveCursor('d', cx, cy, cz, dmax, pageMode);}

      };

    } else if (direction == 'u') {
      // up
      cz++;
      if (cz > dmax) {
            cz=0;
            if (pageMode) {moveCursor('f', cx, cy, cz, dmax, pageMode);}
      };

    }
}

void interpreter(string cmds, bool printcmd, int dim, string workDir) {
    Cell cube[dim][dim][dim];
    Basics b;
    string commands = cmds;
    bool fatal = false;

    Pos execs[10]; // positions of first ten t-commands
    int ex = 0; // pos.

    int ctr = dim / 2; // center
    int cx = ctr; // currentx
    int cy = ctr; // currenty
    int cz = ctr; // currentz
    int newcx = 0;
    int newcy = 0;
    int newcz = 0;
    int dmax = dim - 1;
    int jump = cmds.size()-1;

    long long int queen[3] = {0,0,0};
    int q = 0;
    bool pageMode = false;
    int outmode = 0;
    long long int curr = 0; // curr value
    char c1 = '?'; // curr cmd
    char c2 = '?'; // curr cmd par
    int v = 0; // help
    int h = 0; // help
    char c = '?'; // help
    string help = ""; // help

    fstream fs;
    string fassim = "";

    if (printcmd) {cout << "initial cmd size: "  << commands.size() << endl;}
    if (printcmd) {cout << "center set to: " << ctr << endl;}

    bool goon = true;
    int i = 0;
    while (i < (int) commands.size()) {
        c1 = commands[i];
        c2 = '?';
        if (parcmds.find(c1)!=string::npos) {
            i++;
            if (i >= (int) commands.size()) {exit(EXIT_FAILURE);}
            c2 = commands[i];
            if (printcmd) {cout << "command: "  << c1 << c2 << endl;}
        } else if (printcmd){
            cout << "command: "  << c1 << endl;
        }

        switch(c1) {
        case 'a':
            goon = true;
            if (fassim.size() == 0) {
                fassim = b.getAFile(workDir);
                if (fassim.size() == 0) {
                    // nothing more to assimilate
                     flagfs = 1;
                     goon = false;
                } else {
                    fs.open(fassim,ios::in);
                    if (printcmd) {cout << "assim:"  << fassim << endl;}
                }
            }
            if (goon) {
                if (!fs.is_open()) {exit(EXIT_FAILURE);}
                if (c2=='l') {
                    getline(fs, help);
                } else {
                    c = fs.get();
                }
                if (fs.eof()) {
                    fs.close();
                    b.deleteFile(fassim);
                    if (printcmd) {cout << fassim << " assimilated."  << endl;}
                    fassim = "";
                } else if (c2 == 'l') {
                    v = 0;
                    for (int i = 0; i < (int) help.size(); ++i) {
                        v = 10 * v;
                        h = b.digitToInt(help[i]);
                        if (h<0) {break;}
                        v += h;
                    }
                    if (printcmd) {cout << " set cell to: " << v << endl;}
                    (cube[cx][cy][cz]).set(v);
                } else {
                    h = b.charToInt(c);
                    if (printcmd) {cout << "input:" << c << " set cell to: " << h << endl;}
                    (cube[cx][cy][cz]).set(h);
                 }
            }
            break;
        case 'b':
        case 'f':
        case 'l':
        case 'r':
        case 'u':
        case 'd':
            moveCursor(c1, cx, cy, cz, dmax, pageMode);
            if (printcmd) {cout << cx << "," << cy << "," << cz << endl;}
            break;
        case 'c':
            if (flagci!=1) {
                i++;
                if (i >= (int) commands.size()) {exit(EXIT_FAILURE);}
                if (parcmds.find(commands[i])!=string::npos) {
                    i++;
                    if (i >= (int) commands.size()) {exit(EXIT_FAILURE);}
                // command e has variable length
                } else if (commands[i] == 'e') {
                    if (i+1 < (int) commands.size()) {
                        c2 = commands[i+1];
                        if (b.isDigit(c2)) {i++;}
                    }
                }
            }
            break;
        case 'e':
            help = (cube[cx][cy][cz]).getReg();
            if (i + 1 < (int) commands.size()) {
                c2 = commands[i+1];
                if (b.isDigit(c2)) {
                    int ix = b.digitToInt(c2);
                    if (printcmd) {cout << "exec e" << ix << endl;}
                    help = (cube[execs[ix].x][execs[ix].y][execs[ix].z]).getReg();
                    i++;
                }
            }

            if (printcmd) {cout << "execution string: " << help << endl;}
            jump = i + help.size();
            help = commands.substr(0,i+1) + help + commands.substr(i+1, string::npos);
            commands = help;
            break;

        case 'g':
            // get
            b.checkDirection(c2);
            newcx=cx;newcy=cy;newcz=cz;
            moveCursor(c2, newcx, newcy, newcz, dmax, pageMode);
            (cube[cx][cy][cz]).set((cube[newcx][newcy][newcz]).get());
            if (printcmd) {cout << cx << "," << cy << "," << cz << " set to " << (cube[cx][cy][cz]).get() << endl;}
            break;
        case 'h':
            // get
            b.checkDirection(c2);
            newcx=cx;newcy=cy;newcz=cz;
            moveCursor(c2, newcx, newcy, newcz, dmax, pageMode);
            (cube[cx][cy][cz]).setReg((cube[newcx][newcy][newcz]).getReg());
            break;
        case 'i':
            if (c2 == 'i') {
                flagci = -flagci;
            } else if (c2 =='v') {
                (cube[cx][cy][cz]).minus();
                if (printcmd) {cout << cx << "," << cy << "," << cz << " set to " << (cube[cx][cy][cz]).get() << endl;}
            } else if (c2 =='q') {
                queen[q]=-queen[q];
            } else {
                exit(EXIT_FAILURE);
            }
            break;
        case 'j':
            i = jump;
            break;
        case 'm':
            if (c2 == 'm') {
                pageMode = !pageMode;
            } else if (c2 =='o') {
                cx=0;cy=0;cz=0;
                if (printcmd) {cout << cx << "," << cy << "," << cz << endl;}
            } else if (c2 =='c') {
                cx=ctr;cy=ctr;cz=ctr;
                if (printcmd) {cout << cx << "," << cy << "," << cz << endl;}
            } else {
                exit(EXIT_FAILURE);
            }
            break;

        case 'o':
            // change output mode
            outmode++;
            if (outmode > 2) {outmode=0;}
            break;
        case 'q':
            switch (c2) {
            case 'l':
                break;
            case 'r':
                (cube[cx][cy][cz]).add(queen[q]);
                break;
            case 'u':
                (cube[cx][cy][cz]).mult(queen[q]);
                break;
            case 'd':
                fatal = (cube[cx][cy][cz]).divide(queen[q]);
                if (fatal) {
                    if (printcmd) {cout << "divided by 0" << endl;}
                    exit(EXIT_FAILURE);
                }
                break;
            case 'f':
                if  ((cube[cx][cy][cz]).compEq(queen[q])) {
                    flagci = 1;
                } else {
                    flagci = -1;
                }
                if (printcmd) {cout << "gci(eq)=" << flagci << endl;}
                break;
            case 'b':
                if ((cube[cx][cy][cz]).compGe(queen[q])) {
                    flagci = 1;
                } else {
                    flagci = -1;
                }
                if (printcmd) {cout << "gci(ge)=" << flagci << endl;}
                break;
            case 'n':
                q = (q+1) % 3;
                if (printcmd) {cout << "select g.r.[" << q << "]" << endl;}
                break;
            case 'p':
                q = (q+2) % 3;
                if (printcmd) {cout << "select g.r.[" << q << "]" << endl;}
                break;
            case 'g':
                queen[q] = (cube[cx][cy][cz]).get();
                if (printcmd) {cout << "g.r.[" << q << "]=" << queen[q] << endl;}
                break;
            };
            break;


            break;
        case 's':
            // send
            b.checkDirection(c2);
            curr = (cube[cx][cy][cz]).get();
            newcx=cx;newcy=cy;newcz=cz;
            moveCursor(c2, newcx, newcy, newcz, dmax, pageMode);
            switch (c2) {
            case 'l':
                (cube[newcx][newcy][newcz]).setMin(curr);
                if (printcmd) {cout << newcx << "," << newcy << "," << newcz << " set to " << (cube[newcx][newcy][newcz]).get() << endl;}
                break;
            case 'r':
                (cube[newcx][newcy][newcz]).add(curr);
                if (printcmd) {cout << newcx << "," << newcy << "," << newcz << " set to " << (cube[newcx][newcy][newcz]).get() << endl;}
                break;
            case 'u':
                (cube[newcx][newcy][newcz]).mult(curr);
                if (printcmd) {cout << newcx << "," << newcy << "," << newcz << " set to " << (cube[newcx][newcy][newcz]).get() << endl;}
                break;
            case 'd':
                fatal = (cube[newcx][newcy][newcz]).divide(curr);
                if (fatal) {
                    if (printcmd) {cout << "divided by 0" << endl;}
                    exit(EXIT_FAILURE);
                }
                if (printcmd) {cout << newcx << "," << newcy << "," << newcz << " set to " << (cube[newcx][newcy][newcz]).get() << endl;}
                break;
            case 'f':
                if  ((cube[newcx][newcy][newcz]).compEq(curr)) {
                    flagci = 1;
                } else {
                    flagci = -1;
                }
                if (printcmd) {cout << "gci(eq)=" << flagci << endl;}
                break;
            case 'b':
                if ((cube[newcx][newcy][newcz]).compGe(curr)) {
                    flagci = 1;
                } else {
                    flagci = -1;
                }
                if (printcmd) {cout << "gci(ge)=" << flagci << endl;}
                break;
            };
            break;
        case 't':
            (cube[cx][cy][cz]).clearReg();
            i++;
            help = "";
            while (i < (int) commands.size()) {
                c2 = commands[i];
                if (c2 == '.') {
                    break;
                } else {
                    help.push_back(c2);
                }
                i++;
            }
            (cube[cx][cy][cz]).setReg(help);

            if (ex < 10) {
                execs[ex].x = cx;
                execs[ex].y = cy;
                execs[ex].z = cz;
                ex++;
            }
            if (printcmd) {
                cout << "set exec string: " << (cube[cx][cy][cz]).getReg() << endl;
            }

            break;
        case 'x':
            // end program
            if (printcmd) {cout << "final cmd size: "  << commands.size() << endl;}
            exit(EXIT_SUCCESS);
        case 'y':
            // output current cursor
            if (c2 == 's') {
                cout << b.intToStr((cube[cx][cy][cz]).get(), outmode) << endl;
            } else if (c2 == 'o') {
                cout << b.intToStr((cube[cx][cy][cz]).get(), outmode);
            // output current plane
            } else if (c2 == 'p') {
                for (int m = dmax; m >=0; --m) {
                    for (int n = 0; n < dim; ++n) {
                        if ((n>0) && (outmode == 0)) {cout << ',';}
                        cout << b.intToStr((cube[n][cy][m]).get(), outmode);
                    }
                    if (outmode == 0) {cout << endl;}
                }
                cout << endl;
            } else if (b.isDigit(c2)) {
                v = b.charToInt(c2);
                for (int m = dmax; m >=0; --m) {
                    for (int n = 0; n < dim; ++n) {
                        if ((n>0) && (outmode == 0)) {cout << ',';}
                        cout << b.intToStr((cube[n][v][m]).get(), outmode);
                    }
                    if (outmode == 0) {cout << endl;}
                }
                cout << endl;

            } else {
                exit(EXIT_FAILURE);
            }
            break;
        case 'z':
            if (flagfs!=1) {
                i++;
                if (i >= (int) commands.size()) {exit(EXIT_FAILURE);}
                if (parcmds.find(commands[i])!=string::npos) {
                    i++;
                    if (i >= (int) commands.size()) {exit(EXIT_FAILURE);}
                // command e has variable length
                } else if (commands[i] == 'e') {
                    if (i+1 < (int) commands.size()) {
                        c2 = commands[i+1];
                        if (b.isDigit(c2)) {i++;}
                    }
                }
            }

            break;

        default:
            int v = b.charToInt(c1);
            if (v< 0) {
                exit(EXIT_FAILURE);
            } else {
                (cube[cx][cy][cz]).set(v);
                if (printcmd) {cout << cx << "," << cy << "," << cz << " set to " << v << endl;}
            }
            break;
        }
        i++;
        goon = true;
    }

    if (printcmd) {cout << "final cmd size: "  << commands.size() << endl;}
}
int main(int argc, char *argv[])
{
    Basics b;
    bool printcmd = false;
    string workDirectory = "";
    string filename = "";
    for (int i = 1; i < argc; ++i) {
        string sargv = argv[i];
        if (sargv == "-p") {
            printcmd = true;
        } else {
            filename = sargv;
            workDirectory = b.getDir(sargv);
        }
    }
    if (printcmd) {cout << "workDir: " << workDirectory << endl;}

    string content = b.readFile(filename);
    int dim = b.charToInt(content[0]);
    content.erase(0,1);
    if (printcmd) {cout << "dim: " << dim << endl;}
    interpreter(content, printcmd, dim, workDirectory);

    return 0;
}


