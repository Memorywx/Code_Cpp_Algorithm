#pragma once

template <typename T>
class stack {
public:
    virtual bool isEmpty() const = 0;    // 判断是否为空
    virtual void push(const T &x) = 0;   // 入栈
    virtual T pop() = 0;                 // 出栈
    virtual T top() const = 0;           // 读取栈顶元素
    virtual ~stack() {} 

};