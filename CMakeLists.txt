cmake_minimum_required(VERSION 3.14)
project(complier)

add_executable(complier main.cpp Type/Type.cpp Type/Type.h AST/AST.cpp AST/AST.h SymbolTable/SymbolTable.cpp SymbolTable/SymbolTable.h)