


#include <iostream>
#include "../dynamicSearchTable/set.h"
using namespace std;

template <class KEY, class OTHER>
void quickSort(SET<KEY, OTHER> a[], int low, int high) {
    int mid;
    if (low >= high) return;
    mid = divide(a, low, high);
    quickSort(a, low, mid-1);
    quickSort(a, mid+1, high);

}

template <class KEY, class OTHER>
int divide(SET<KEY,OTHER> a[], int low, int high) {
    SET<KEY, OTHER> k = a[low];
    
    do {
        while (low < high && a[high].key > k.key) --high;
        if (low < high) {a[low++] = a[high];}
        while (low < high && a[low].key < k.key) ++low;
        if (low < high) {a[high--] = a[low];}

    } while (low != high);

    a[low] = k;
    return low;
}


template <class KEY, class OTHER>
void quickSort(SET<KEY, OTHER> a[], int size) {
    quickSort(a, 0, size - 1);
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
    quickSort(a, n);
    cout << "\n插入排序后的数组元素为：\n";
    for (int i = 0; i < n; i++)
    {
        cout << a[i].key << ' ' << a[i].other << endl;
    }
}