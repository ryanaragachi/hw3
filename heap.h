#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> data;
  int arity;
  PComparator comp;

  void upHeap(size_t idx);
  void downHeap(size_t idx);

};

// Add implementation of member functions here




template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c)
    : arity(m), comp(c) {}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() {}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item) {
    data.push_back(item);
    upHeap(data.size() - 1);
}




// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Cannot access top. Heap is empty.");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data.front();


}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Cannot pop. Heap is empty.");

  }
  std::swap(data[0], data.back());
    data.pop_back();
    downHeap(0);


}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const {
    return data.empty();
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const {
    return data.size();
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::upHeap(size_t idx) {
    while (idx > 0) {
        size_t parent = (idx - 1) / arity;
        if (comp(data[idx], data[parent])) {
            std::swap(data[idx], data[parent]);
            idx = parent;
        } else {
            break;
        }
    }
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::downHeap(size_t idx) {
    size_t child = idx * arity + 1;
    while (child < data.size()) {
        size_t minChild = child;
        for (size_t next = child + 1; next < child + arity && next < data.size(); ++next) {
            if (comp(data[next], data[minChild])) {
                minChild = next;
            }
        }
        if (comp(data[minChild], data[idx])) {
            std::swap(data[minChild], data[idx]);
            idx = minChild;
            child = idx * arity + 1;
        } else {
            break;
        }
    }
}




#endif

