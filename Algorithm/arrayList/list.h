#pragma once

template <class T>
class list {
 public:
  virtual void clear() = 0;  // 清空线性表
  virtual int length() const = 0;  // 获取线性表的长度，即元素个数
  // 在第i个位置插入一个元素x
  virtual void insert(int i, const T &x) = 0;
  virtual void remove(int i) = 0;  // 删除第i个元素
  // 搜索元素x是否在线性表中出现
  virtual int search(const T &x) const = 0;
  virtual T visit(int i) const = 0;  // 访问线性表第i个元素
  virtual void traverse() const = 0;        // 遍历线性表
  virtual void add(T e) = 0;      // 添加元素 
  virtual void setElem(int i, T e) = 0;    // 设置第i个元素
  virtual ~list() {};
};