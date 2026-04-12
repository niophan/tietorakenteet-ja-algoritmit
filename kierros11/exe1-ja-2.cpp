enum Error_code { success, overflow, range_error };

template <class Node_entry>
struct Node {
//  data members
   Node_entry entry;
   Node<Node_entry> *next;
//  constructors
   Node();
   Node(Node_entry, Node<Node_entry> *link = NULL);
};

template <class List_entry>
class List {
public:
//  Specifications for the methods of the list ADT go here.
//  The following methods replace compiler-generated defaults.
   List();
   int size() const;
   bool full() const;
   bool empty() const;
   void clear();
   void traverse(void (*visit)(List_entry &));
   Error_code retrieve(int position, List_entry &x) const;
   Error_code replace(int position, const List_entry &x);
   Error_code remove(int position,  List_entry &x);
   ~List();
   List(const List<List_entry> &copy);
   List<List_entry> &operator =(const List<List_entry> &copy);
protected:
//  Data members for the linked list implementation now follow.
   int count;
   mutable int current_position;
   Node<List_entry> *head;
   mutable Node<List_entry> *current;

//  The following auxiliary function is used to locate list positions
   void set_position(int position) const;
};


template <class List_entry>
void List<List_entry>::set_position(int position) const
/*
Pre:  position is a valid position in the List: 0 <= position < count.
Post: The current Node pointer references the Node at position.
*/
{
   if (position < current_position) {  //  must start over at head of list
      current_position = 0;
      current = head;
   }
   for ( ; current_position != position; current_position++)
      current = current->next;
}

template <class List_entry>
List<List_entry>::List()
   : count(0), current_position(0), head(nullptr), current(nullptr)
{
}

template <class List_entry>
int List<List_entry>::size() const
{
   return count;
}

template <class List_entry>
bool List<List_entry>::full() const
{
    return false;
}

template <class List_entry>
bool List<List_entry>::empty() const
{
    return count == 0;
}


template <class List_entry>
void List<List_entry>::clear()
{
   while (head != nullptr) {
      Node<List_entry> *old_head = head;
      head = head->next;
      delete old_head;
   }
   count = 0;
}


template <class List_entry>
List<List_entry>::~List()
{
   clear();
}


template <class List_entry>
List<List_entry>::List(const List<List_entry> &copy)
   : count(0), head(nullptr)
{
   Node<List_entry> *source = copy.head;
   Node<List_entry> *tail = nullptr;
  
   while (source != nullptr) {
      Node<List_entry> *new_node = new Node<List_entry>(source->entry, nullptr); // access value
      if (head == nullptr) {
         head = new_node;
      } else {
         tail->next = new_node; //append
      }
      tail = new_node;
      source = source->next;
      ++count;
   }
}

template <class List_entry>
List<List_entry> &List<List_entry>::operator =(const List<List_entry> &copy)
{
   if (this == &copy) {
      return *this;
   }

   List<List_entry> temporary(copy);

   Node<List_entry> *old_head = head;
   int old_count = count;

   head = temporary.head;
   count = temporary.count;

   temporary.head = old_head;
   temporary.count = old_count;

   return *this;
}

template <class List_entry>
void List<List_entry>::traverse(void (*visit)(List_entry &))
{  
   Node<List_entry> *old_head = head;
   while (old_head != nullptr) {
      (*visit)(old_head->entry);
      old_head = old_head->next;
   }
}


template <class List_entry>
Error_code List<List_entry>::replace(int position, const List_entry &x)
{
   if (position < 0 || position >= count)
      return range_error;

   Node<List_entry> *target = set_position(position);
   target->entry = x; // (*target).entry access the entry member of the node that target point to
   return success;
}

template <class List_entry>
Error_code List<List_entry>::retrieve(int position, List_entry &x) const
{
   if (position < 0 || position >= count)
      return range_error;

   Node<List_entry> *target = set_position(position);
   x = target->entry;
   return success;
}


template <class List_entry>
Error_code List<List_entry>::remove(int position, List_entry &x)
{
   if (position < 0 || position >= count)
      return range_error;

   Node<List_entry> *old_head;

   if (position == 0) {
      old_head = head;
      head = head->next;
      current = head;
      current_position = 0;
   } else {
      set_position(position - 1);
      old_head = current->next;
      current->next = old_head->next;
      current_position = position - 1;
      current = current->next;
   }

   x = old_head->entry;
   delete old_head;
   --count;

   return success;
}