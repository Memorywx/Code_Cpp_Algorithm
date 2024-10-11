#pragma once

template <class KEY, class OTHER>
struct SET {
    KEY key = 0;
    OTHER other = 0;
    SET(KEY k, OTHER o) {
        key = k;
        other = o;
    }
    SET() = default;
};

template <class KEY, class OTHER>
bool compareByKey(const SET<KEY, OTHER> &s1, const SET<KEY, OTHER> &s2) {
    return s1.key < s2.key;
}

template <class KEY, class OTHER>
void sort(SET<KEY, OTHER> data[], int size) {
    // 冒泡排序     升序排序
    for (int i=0; i<size-1; i++) {
        for (int j=0; j<size-i-1; j++) {
            if (data[j].key > data[j+1].key) {
                SET<KEY,OTHER> temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }
        }
    }
}


