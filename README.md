# NORG

## Introduction
This project originally started out as a small homage to the most beloved species ;-) in the galaxy. It however adapted somewhat to humans so I felt it needed a different name.

NORG is an esolang that doesn't try to be as hard as BF or even Malbolge but rather restricts programming in a different way. See the documentation in pdf format. 

I provide an interpreter written in C++, currently source code and windows executable.


## Code

You should compile the source code with C++11 or later. To avoid crashes on programs that define a 'large' cube (see docs), set linker option -Wl,--stack,25000000.

## Motivation
Why write an esolang?  
Inventing a programming language is some form of creativity - at least if you go beyond turing tarpits. The real work is not implementing a compiler/interpreter/transpiler/… but rather inventing a design and thinking about it: is it really possible to do anything useful with your initial design? How do you have to change it for solving some basic problems? Can this be done without compromising your initial ideas? It is of course always possible to tweak the initial design in a way that allows many problems to be solved. You are tempted to make a 'quick fix' by inventing new features.  
But is the language still close to what you originally had in mind? Do the new features 'fit in' or do they rather change the nature of your language too much? 
These are the questions that come up when you try out your design. The way you answer them is always your choice. You want to have the feeling that somehow the features of your language 'play together' and are 'consistent' in some way.

In short: designing languages is a kind of brain teaser and it's fun.
