#include "sorts.h"

//GRADING: INSERTION
void insertionSort(vector<int> &a, int x, int y)
{
    vector<int>::iterator it;
    for (it = a.begin() + x + 1; it != a.begin() + y; ++it) {
        int key = *it;
        vector<int>::reverse_iterator jit(it);
        while (jit != a.rend() - x && *(jit) > key) {
            *(jit - 1) = *jit;
            jit += 1;
        }
        *(jit - 1) = key;
    }
}

//GRADING: MERGE
void mergeSort(vector<int>& a, int x, int y, int n)
{
    if (y - x <= n) {
        return insertionSort(a, x, y);
    }
    int q = (x + y) / 2;
    mergeSort(a, x, q, n);
    mergeSort(a, q, y, n);

    //merge
    vector<int>::iterator it, jit, kit = a.begin() + x;
    vector<int> L, R;
    L.assign(a.begin() + x, a.begin() + q);
    R.assign(a.begin() + q, a.begin() + y);

    for (it = L.begin(), jit = R.begin(); it != L.end() && jit < R.end(); ++kit) {
        if (*it <= *jit) {
            *kit = *(it++);
        }
        else {
            *kit = *(jit++);
        }
    }

    while (it != L.end()) {
        *(kit++) = *(it++);
    }
    while (jit != R.end()) {
        *(kit++) = *(jit++);
    }


}
