//
// Created by Westie on 2022/8/2.
//

#include "./SymbolTable.h"


/*  Symbol类    */

Symbol::Symbol(string name)
{
    this->name=name;
    level=0;
    flag='V';
    type=0;
    types="int";
    paramnum=0;
    offset=0x00;
}

Symbol::~Symbol() {}
bool Symbol::Clone(const Symbol &symbol)//复制函数
{
    this->name=symbol.name;
    this->alias=symbol.alias;
    this->flag=symbol.flag;
    this->type=symbol.type;
     this->types=symbol.types;
    this->paramnum=symbol.paramnum;
    this->offset=symbol.offset;
    this->level=symbol.level;
    this->pretype=symbol.pretype;
    return true;
}

/*  Symboltable类   */

Symboltable::Symboltable()
{
    this->index=0;
}

Symboltable::~Symboltable() {}

//根据index得到对应符号的引用,没有则返回空指针
Symbol* Symboltable::getSymbol(int index)
{
    if(this->index<index || index<0)
        return nullptr;
    else return &symbols[index];
}

//插入符号，返回当前栈中已有的符号数
int Symboltable::Push(Symbol& symbol)
{
    symbols.push_back(symbol);
    index++;
    print();
    return symbols.size();
}

//删除符号，返回当前栈中已有的符号数
int Symboltable::Pop() 
{
    if(symbols.size()<=0) exit(1);  
    symbols.pop_back();
    index--;
    return symbols.size();
}

//从删除符号符号，直到剩余符号数=index
int Symboltable::Pop_until(int index)  
{
    if(index==this->index) return this->index;
    while(Pop()!=index);
    print();
    return this->index;

}

int Symboltable::Search(string name)   
{
    for(int i=index-1;i>=0;i--)
        if(!name.compare(symbols[i].name)) return i;
    return -1;
}

bool Symboltable::Replace(int index,Symbol& newsymbol)    
{
    return symbols[index].Clone(newsymbol);
}
string name;  
int level;      
int type;       
int paramnum;  
string alias; 
char offset;    

void Symboltable::print()//打印符号表
{
    #ifdef DEBUG
    printf("index\tname\talias\tlevel\ttypes\tflag\tparam\toffset\t\n");
    for(int i=0;i<index;i++){
        printf("%d\t",i);
        printf("%s\t",symbols[i].name.c_str());
        printf("%s\t",symbols[i].alias.c_str());
        printf("%d\t",symbols[i].level);
        // printf("%d\t",symbols[i].type);
        printf("%s\t",symbols[i].types.c_str());
        printf("%c\t",symbols[i].flag);
        printf("%d\t",symbols[i].paramnum);
        printf("%d\t",symbols[i].offset);
        printf("\n");
    }
    #endif
}

void Symboltable::reset()
{
    Pop_until(0);
}
