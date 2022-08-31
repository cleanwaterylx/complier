//
// Created by Westie on 2022/7/31.
//

#ifndef COMPLIER_AST_H
#define COMPLIER_AST_H

#include "../Type/Type.h"


enum node_kind {
    Root, CompUnit, Decl, ConstDecl, BType, BlockItems, ConstDef, VarDecl, VarDef, FuncCall,
    InitVal, FuncDef, FuncFParams, FuncFParam, Block, Stmt, Cond, LVal,
    PrimaryExp, Number, UnaryExp, UnaryOp, FuncRParams, Idents, FuncFParamArray,
    MulExp, AddExp, RelExp, EqExp, LAndExp, LOrExp

};

struct node {
    enum node_kind kind;
    union {
        char type_id[32];
        int type;
        float type_float;
    };
    struct node *ptr[3];    //子树指针
    int level;
    int place;


};


class AST {
private:
    char last[50];
    struct node *root;
public:
    int level = 0;

    void printAST(struct node *T, int indent, int deep);

    void ASTtoSymbolTable(struct node *T);

    struct node *setRoot(struct node *root);

    struct node *getRoot() {return root;}

    void calAttribute(struct node *T);

};


#endif //COMPLIER_AST_H
