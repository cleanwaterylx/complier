//
// Created by Westie on 2022/7/31.
//

#ifndef COMPLIER_TYPE_H
#define COMPLIER_TYPE_H

#include "vector"
#include "iostream"

using namespace std;

class Type {
protected:
    string nameOfClass;
    string value;
public:
    Type() {}

    ~Type() {}

    string getNameOfClass() { return nameOfClass; }

    string getValue() { return value; }

    bool is_BasicType() { return nameOfClass.compare("BasicType") == 0 ? true : false; }

    bool is_ProductType() { return nameOfClass.compare("ProductType") == 0 ? true : false; }

    bool is_ArrayType() { return nameOfClass.compare("ArrayType") == 0 ? true : false; }

    bool is_FunType() { return nameOfClass.compare("FunType") == 0 ? true : false; }

};

class BasicType : public Type {
public:
    BasicType() { nameOfClass = string("BasicType"); }

    ~BasicType() {}

    BasicType(string type) {
        nameOfClass = string("BasicType");
        value = type;
    }

    void setValue(string val) { value = val; }
};

class ProductType : public Type {
public:
    ProductType() { nameOfClass = string("ProductType"); }

    ProductType(Type *T1, Type *T2);

    ProductType(Type *T1, Type *T2, int n);

    ~ProductType() {}

    bool sameas(vector<Type *> &t);

    vector<Type *> eles;

};

class ArrayType : public Type {
public:
    ArrayType() {nameOfClass = string("ArrayType");}
    ArrayType(int i, BasicType &t);
    ArrayType(int i, ArrayType &t);
    ~ArrayType() {}
    void setBasicType(BasicType &t);
    Type *lowerOneLevel();
    int level = 0;
    vector<int> elements_nums;
    BasicType basicType;
};

class FunType:public Type{
public:
    FunType() {nameOfClass = string("FunType");}
    FunType(BasicType &R, vector<Type *> T);
    ~FunType() {}
    int num_args = 0;
    BasicType basicType;
    vector<Type *> args;
};


#endif //COMPLIER_TYPE_H
