// 样例输入：
// 请输入待排序数组的元素个数： 4
// 请依次输入待排序数组元素(按照key，other的形式)：
// 1 1
// 4 4
// 7 2
// 3 6
// 样例输出：
// 插入排序后的数组元素为：
// 1 1
// 3 6
// 4 4
// 7 2

#include <iostream>
#include "../dynamicSearchTable/set.h"
using namespace std;


template <class KEY, class OTHER>
void simpleInsertSort(SET<KEY, OTHER> a[], int size)
{
    int j;
    SET<KEY, OTHER> tmp;

    for (int i = 1; i < size; ++i)
    {
        tmp = a[i];
        for (j = i - 1; j >= 0 && tmp.key < a[j].key; --j)
        {
            a[j + 1] = a[j];
        }
        a[j + 1] = tmp;
    }
}

SET<int, int> a[100000];
int main()
{
    cout << "请输入待排序数组的元素个数：";
    int n;
    cin >> n;

    cout << "\n请依次输入待排序数组元素(按照key，other的形式)：\n";
    for (int i = 0; i < n; i++)
    {
        cin >> a[i].key >> a[i].other;
    }
    simpleInsertSort(a, n);
    cout << "\n插入排序后的数组元素为：\n";
    for (int i = 0; i < n; i++)
    {
        cout << a[i].key << ' ' << a[i].other << endl;
    }
}