// 队列抽象类的定义
#pragma once

template <typename T>
class queue {
public:
    virtual void enQueue(const T &x) = 0;  // 入队
    virtual T deQueue() = 0;               // 出队
    virtual T getHead() const = 0;         // 读取队首元素
    virtual bool isEmpty() const = 0;      // 判断队列是否为空
    virtual ~queue() {}
};


