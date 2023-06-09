#ifndef DA_TP_CLASSES_MUTABLEPRIORITYQUEUE
#define DA_TP_CLASSES_MUTABLEPRIORITYQUEUE

#include <vector>

template <class T>
class MutablePriorityQueue {
    std::vector<T *> H;

    ///@note Auxilir function for priority queue used in prim algorithm
    void heapifyUp(unsigned i);

    ///@note Auxilir function for priority queue used in prim algorithm
    void heapifyDown(unsigned i);

    ///@note Auxilir function for priority queue used in prim algorithm
    inline void set(unsigned i, T * x);
public:
    ///@note Auxilir function for priority queue used in prim algorithm
    MutablePriorityQueue();

    ///@note Auxilir function for priority queue used in prim algorithm
    void insert(T * x);

    ///@note Auxilir function for priority queue used in prim algorithm
    T * extractMin();

    ///@note Auxilir function for priority queue used in prim algorithm
    void decreaseKey(T * x);

    ///@note Auxilir function for priority queue used in prim algorithm
    bool empty();
};

// Index calculations
#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)

///@note Auxilir function for priority queue used in prim algorithm
template <class T>
MutablePriorityQueue<T>::MutablePriorityQueue() {
    H.push_back(nullptr);
    // indices will be used starting in 1
    // to facilitate parent/child calculations
}

template <class T>
bool MutablePriorityQueue<T>::empty() {
    return H.size() == 1;
}

template <class T>
T* MutablePriorityQueue<T>::extractMin() {
    auto x = H[1];
    H[1] = H.back();
    H.pop_back();
    if(H.size() > 1) heapifyDown(1);
    x->queueIndex = 0;
    return x;
}

template <class T>
void MutablePriorityQueue<T>::insert(T *x) {
    H.push_back(x);
    heapifyUp(H.size()-1);
}

template <class T>
void MutablePriorityQueue<T>::decreaseKey(T *x) {
    heapifyUp(x->queueIndex);
}

template <class T>
void MutablePriorityQueue<T>::heapifyUp(unsigned i) {
    auto x = H[i];
    while (i > 1 && *x < *H[parent(i)]) {
        set(i, H[parent(i)]);
        i = parent(i);
    }
    set(i, x);
}

template <class T>
void MutablePriorityQueue<T>::heapifyDown(unsigned i) {
    auto x = H[i];
    while (true) {
        unsigned k = leftChild(i);
        if (k >= H.size())
            break;
        if (k+1 < H.size() && *H[k+1] < *H[k])
            ++k; // right child of i
        if ( ! (*H[k] < *x) )
            break;
        set(i, H[k]);
        i = k;
    }
    set(i, x);
}

template <class T>
void MutablePriorityQueue<T>::set(unsigned i, T * x) {
    H[i] = x;
    x->queueIndex = i;
}

#endif
