#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP

#include <cstddef>
#include <iterator>
#include <iostream>

template <typename T>
struct List;

template <typename T>
struct ListNode
{
  ListNode() : m_value(), m_prev(nullptr), m_next(nullptr) {}

  ListNode(T const& v, ListNode* prev, ListNode* next)
    : m_value(v), m_prev(prev), m_next(next)
  {}

  T m_value;
  ListNode* m_prev;
  ListNode* m_next;
};

/*-------------------*/
/* -- ITERATOR -- */
/*-------------------*/
template <typename T>
struct ListIterator
{
  typedef ListIterator<T> Self;
  typedef ListNode<T> Node;
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
  typedef ptrdiff_t difference_type;
  typedef std::forward_iterator_tag iterator_category;

  friend class List<T>;

// Aufgabe 5.4
  ListIterator() : m_node{nullptr} {}
  ListIterator(ListNode<T>* n) : m_node{n} {}

  reference operator*() const { return m_node->m_value; }

  pointer operator->() const { return &(m_node->m_value); }

  Self& operator++() { // prefix increment
    if (m_node) m_node = m_node->m_next;
    return *this;
  }

  Self operator++(int) { // postfix increment
    Self tmp = *this;
    if (m_node) m_node = m_node->m_next;
    return tmp;
  }

  bool operator==(const Self& x) const {
    return m_node == x.m_node;
  }

  bool operator!=(const Self& x) const { return !(*this == x); }
  
  Self next() const {
    if (m_node)
      return ListIterator{m_node->m_next};
    else
      return ListIterator{nullptr};
  }

	private:
  	ListNode<T>* m_node;
};

/*-------------------*/
/* -- CONST ITERATOR -- */
/*-------------------*/
template <typename T>
struct ListConstIterator
{
	public: 
		//implement
	private:
  	ListNode<T>* m_node;
};

/*-------------------*/
/* -- LIST CLASS -- */
/*-------------------*/
template <typename T>
class List
{
public:
	List() : m_size{}, m_first{nullptr}, m_last{nullptr} {}
	~List() { clear(); }

// Aufgabe 5.7
// Copy Constructor
	List(List<T> const& other)											
    : m_size{}, m_first{nullptr}, m_last{nullptr}
  {
    // auto ist vom Typ const T&
    for (auto i : other) push_back(i);
  }

// Move Constructor
	List(List<T>&& other) 
    : m_size{}, m_first{nullptr}, m_last{nullptr}
  {
    std::swap(m_size, other.m_size);
    std::swap(m_first, other.m_first);
    std::swap(m_last, other.m_last);
  }


// methoden //
// Aufgabe 5.1 
	bool empty() const {
  	return m_size == 0;
  }

std::size_t size() const {
  return m_size;
  }

// Aufgabe 5.2
	void push_front(T const& value) {
    if (empty()) {
      m_first = new ListNode<T>{value, nullptr, nullptr};
      m_last = m_first;
    } else {
      ListNode<T>* tmp = new ListNode<T>{value, nullptr, m_first};
      m_first->m_prev = tmp;
      m_first = tmp;
    }
    m_size++;
  }

	void push_back(T const& value) {
    if (empty()) {
      m_last = new ListNode<T>{value, nullptr, nullptr};
      m_first = m_last;
    } else {
      ListNode<T>* tmp = new ListNode<T>{value, m_last, nullptr};
      m_last->m_next = tmp;
      m_last = tmp;
    }
    m_size++;
  }

	void pop_front() {
    if (m_size == 1) {
      ListNode<T>* temp = m_first;
      m_first = nullptr;
      m_last = nullptr;
      delete temp;
      m_size--;
    } else if (m_size > 1) {
      ListNode<T>* temp = m_first->m_next;
      temp->m_prev = nullptr;
      delete m_first;
      m_first = temp;
      m_size--;
    }
  }

  void pop_back() {
    if (m_size == 1) {
      ListNode<T>* temp = m_last;
      m_last = nullptr;
      m_first = nullptr;
      delete temp;
      m_size--;
    } else if (m_size > 1) {
      ListNode<T>* temp = m_last->m_prev;
      temp->m_next = nullptr;
      delete m_last;
      m_last = temp;
      m_size--;
    }
  }

  T front() const {
    return m_first->m_value;
  }

  T back() const {
    return m_last->m_value;
  }

// Aufgabe 5.3
  void clear() {
    while (!empty()) pop_back();
  }

// Aufgabe 5.5
  ListIterator<T> begin() const {
    return ListIterator<T>{m_first};
  }

  ListIterator<T> end() const {
    return ListIterator<T>{nullptr};
  }

// Aufgabe 5.8 (leeren Operator einfügen)
  void insert(ListIterator<T> const& it, T const& v) {
    if (empty()) {
      push_front(v);
    } else {
      if (it.m_node == m_first) {
        push_front(v);
      } else {
        ListNode<T>* tmp = new ListNode<T>{v, it.m_node->m_prev, it.m_node};
        it.m_node->m_prev = tmp;
        tmp->m_prev->m_next = tmp;
        m_size++;
      }
    }
  }

// Aufgabe 5.9
  void reverse() {
    ListNode<T>* current = m_first;
    ListNode<T>* next = nullptr;

    std::swap(m_last, m_first);

    while (current != nullptr) {
      next = current->m_next;
      std::swap(current->m_next, current->m_prev);
      current = next;
    }
  }



// ZusatzMethode

  void print() const {
    std::cout << "List = [ ";
    for (auto i : *this)
      std::cout << i << " ";
    std::cout << "]" << std::endl;
  }

private:
  std::size_t m_size;
  ListNode<T>* m_first;
  ListNode<T>* m_last;
};


// Aufgabe 5.6
template <typename T>
bool operator==(List<T> const& xs, List<T> const& ys) {
  ListIterator<T> it = ys.begin();

  if (xs.size() != ys.size()) return false;

  for (auto i : xs) {
    if (i != *it) return false;
    ++it;
  }

  return true;
}

template <typename T>
bool operator!=(List<T> const& xs, List<T> const& ys) {
  return !(xs == ys);
}


#endif // BUW_LIST_HPP
