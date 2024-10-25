/*
图的抽象类定义
*/

#pragma once

template <class TypeOfVer, class TypeOfEdge>
class graph {
public:
    virtual void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) = 0;
    virtual void remove(TypeOfVer x, TypeOfVer y) = 0;
    virtual bool exist(TypeOfVer x, TypeOfVer y) const = 0;
    virtual ~graph() {};
    int numOfVer() const {return Vers;}
    int numOfEdge() const {return Edges;}

protected:
    int Vers, Edges;
};