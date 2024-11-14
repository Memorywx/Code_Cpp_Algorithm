// 代码清单7-4至7-5 堆排序
// 样例输入：
// 请输入待排序数组的元素个数： 4
// 请依次输入待排序数组元素(按照key，other的形式)：
// 1 1
// 4 4
// 7 2
// 3 6
// 样例输出：
// 堆排序后的数组元素为：
// 1 1
// 3 6
// 4 4
// 7 2

#include <iostream>
#include "../dynamicSearchTable/set.h"
using namespace std;

template <class KEY, class OTHER>
void heapSort(SET<KEY, OTHER> a[], int size) {
    int i;
    SET<KEY, OTHER> tmp;

    // 创建初始最大堆
    // 从第一个非叶子节点开始，一个一个判断是否下沉
    for (i = size / 2 - 1; i >= 0; --i) percolateDown(a, i, size);

    // 利用最大堆进行原地排序，减少空间复杂度
    // 最后能够排序成递增序列，靠的是每次出队！
    // 将最大放在最后，最小的放在前面，最小的下沉，新的最大的上来，然后又放在最后面
    
    // 出队 n - 1次
    for (i = size - 1; i > 0; --i) {
        tmp = a[i];
        a[i] = a[0];
        a[0] = tmp;
        percolateDown(a, 0, i);
    }

}

template <class KEY, class OTHER>
void percolateDown(SET<KEY, OTHER> a[], int hole, int size) {
    int child;
    SET<KEY, OTHER> tmp = a[hole];

    // hole * 2 + 1 为左儿子, hole * 2 + 2 为右儿子
    for (; hole * 2 + 1 < size; hole = child) {
        child = hole * 2 + 1;
        if (child != size - 1 && a[child + 1 ].key > a[child].key)  // 让更大的来
            child++;
        if (a[child].key > tmp.key) {
            a[hole] = a[child];
        } else break;
    } 
    a[hole] = tmp;
}

SET<int, int> a[100000];
int main() {
  cout << "请输入待排序数组的元素个数：";
  int n;
  cin >> n;

  cout << "\n请依次输入待排序数组元素(按照key，other的形式)：\n";
  for (int i = 0; i < n; i++) { cin >> a[i].key >> a[i].other; }
  heapSort(a, n);
  cout << "\n堆排序后的数组元素为：\n";
  for (int i = 0; i < n; i++) {
    cout << a[i].key << ' ' << a[i].other << endl;
  }
}