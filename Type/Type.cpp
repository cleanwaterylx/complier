//
// Created by Westie on 2022/7/31.
//

#include "Type.h"

ProductType::ProductType(Type *T1, Type *T2) {
    nameOfClass = string("ProductType");
    if (T1->is_ProductType()) {
        auto &t1 = static_cast<ProductType *>(T1)->eles;
        eles.insert(eles.end(), t1.begin(), t1.end());
        value = "<" + T2->getValue().substr(1, T2->getValue().size() - 2);
    } else {
        eles.push_back(T2);
        value = "<" + T2->getValue();
    }
    if (T2->is_ProductType()) {
        auto &t2 = static_cast<ProductType *>(T2)->eles;
        eles.insert(eles.end(), t2.begin(), t2.end());
        value = "," + T2->getValue().substr(1, T2->getValue().size() - 2);
    } else {
        eles.push_back(T2);
        value += "," + T2->getValue();
    }
    value += ">";
}

ProductType::ProductType(Type *T1, Type *T2, int n) {
    nameOfClass = string("ProductType");
    if (T1->is_ProductType()) {
        auto &t1 = static_cast<ProductType *>(T1)->eles;
        eles.insert(eles.end(), t1.begin(), t1.end());
        value = "<" + T1->getValue().substr(1, T1->getValue().size() - 2);
    } else {
        eles.push_back(T1);
        value = "<" + T1->getValue();
    }
    while (--n) {
        if (T2->is_ProductType()) {
            auto &t2 = static_cast<ProductType *>(T2)->eles;
            eles.insert(eles.end(), t2.begin(), t2.end());
            value = "," + T2->getValue().substr(1, T2->getValue().size() - 2);
        } else {
            eles.push_back(T2);
            value += "," + T2->getValue();
        }
    }
    value += ">";
}

bool ProductType::sameas(vector<Type *> &t) {
    if (t.size() != eles.size())
        return false;
    for (int i = 0; i < eles.size(); i++) {
        if (eles[i]->getValue().compare(t[i]->getValue()) != 0) {
            return false;
        }
    }
    return true;
}


ArrayType::ArrayType(int i, BasicType &t) {
    nameOfClass = string("ArrayType");
    value = t.getValue() + "[" + to_string(i) + "]";
    level = 1;
    elements_nums.push_back(i);
    basicType = t;
}

ArrayType::ArrayType(int i, ArrayType &t) {
    nameOfClass = string("ArrayType");
    value = t.getValue() + "[" + to_string(i) + "]";
    level = t.level + 1;
    elements_nums = t.elements_nums;
    elements_nums.push_back(i);
    basicType = t.basicType;
}

void ArrayType::setBasicType(BasicType &t) {
    value.replace(0, basicType.getValue().size(), t.getValue());
    basicType = t;
}

Type *ArrayType::lowerOneLevel() {
    if (level == 1) {
        return new BasicType(basicType);
    } else {
        auto ptr = new ArrayType();
        ptr->basicType = basicType;
        ptr->elements_nums = elements_nums;
        ptr->elements_nums.pop_back();
        ptr->level = level - 1;
        ptr->value = basicType.getValue();
        for (int i = 0; i < ptr->level; i++) {
            ptr->value += "[" + to_string(ptr->elements_nums[i]) + "]";
        }
        return ptr;
    }
}


FunType::FunType(BasicType &R, vector<Type *> T) {
    nameOfClass = string("FunType");
    args.assign(T.begin(), T.end());
    basicType = R;
    value = R.getValue() + "(";
    for (auto &ptr: T) {
        num_args++;
        value += ptr->getValue() + ",";
    }
    if (value[value.size() - 1] == ',')
        value.pop_back();
    value += ",";
}
