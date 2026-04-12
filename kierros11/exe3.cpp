enum Error_code { success, overflow, range_error };

template <class Node_entry>
struct Node {
//  data members
   Node_entry entry;
   Node<Node_entry> *next;
   Node<Node_entry> *back;
//  constructors
   Node();
   Node(Node_entry, Node<Node_entry> *link_back = NULL,
                    Node<Node_entry> *link_next = NULL);
};

template <class List_entry>
class List {
public:
//  Add specifications for methods of the list ADT.
//  Add methods to replace compiler generated defaults.
   List();
   int size() const;
   bool full() const;
   bool empty() const;
   void clear();
   void traverse(void (*visit)(List_entry &));
   Error_code retrieve(int position, List_entry &x) const;
   Error_code replace(int position, const List_entry &x);
   Error_code remove(int position,  List_entry &x);
   Error_code insert(int position,  const List_entry &x);
   ~List();
   List(const List<List_entry> &copy);
protected:
//  Data members for the doubly-linked list implementation follow:
   int count;
   mutable int current_position;
   mutable Node<List_entry> *current;

//  The auxiliary function to locate list positions follows:
   void set_position(int position) const;
};


template <class List_entry>
void List<List_entry>::set_position(int position) const
/*
Pre:  position is a valid position in the List: 0 <= position < count.
Post: The current Node pointer references the Node at position.
*/
{
   if (current_position <= position)
      for ( ; current_position != position; current_position++)
         current = current->next;
   else
      for ( ; current_position != position; current_position--)
         current = current->back;
}


template <class List_entry>
List<List_entry>::List()
   : count(0), current_position(0), current(nullptr)
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
   if (count == 0)
      return;

   set_position(0);
   while (current != nullptr) {
      Node<List_entry> *old_node = current;
      current = current->next;
      delete old_node;
   }
   count = 0;
   current = nullptr;
   current_position = 0;
}


template <class List_entry>
List<List_entry>::~List()
{
   clear();
}


template <class List_entry>
List<List_entry>::List(const List<List_entry> &copy)
   : count(0), current_position(0), current(nullptr)
{
   if (copy.count == 0)
      return;

   List<List_entry> &source_list = const_cast<List<List_entry> &>(copy);
   int saved_source_position = source_list.current_position;
   Node<List_entry> *saved_source_current = source_list.current;
   source_list.set_position(0);

   Node<List_entry> *source = source_list.current;
   Node<List_entry> *previous = nullptr;

   while (source != nullptr) {
      Node<List_entry> *new_node = new Node<List_entry>(source->entry, previous, nullptr);
      if (previous != nullptr)
         previous->next = new_node;
      else
         current = new_node;

      previous = new_node;
      source = source->next;
      ++count;
   }

   source_list.current = saved_source_current;
   source_list.current_position = saved_source_position;

   current_position = 0;
}

template <class List_entry>
void List<List_entry>::traverse(void (*visit)(List_entry &))
{
   if (count == 0)
      return;

   int saved_position = current_position;
   Node<List_entry> *saved_current = current;

   set_position(0);
   Node<List_entry> *node = current;
   while (node != nullptr) {
      (*visit)(node->entry);
      node = node->next;
   }

   current = saved_current;
   current_position = saved_position;
}


template <class List_entry>
Error_code List<List_entry>::replace(int position, const List_entry &x)
{
   if (position < 0 || position >= count)
      return range_error;

   set_position(position);
   current->entry = x;
   return success;
}

template <class List_entry>
Error_code List<List_entry>::retrieve(int position, List_entry &x) const
{
   if (position < 0 || position >= count)
      return range_error;

   set_position(position);
   x = current->entry;
   return success;
}


template <class List_entry>
Error_code List<List_entry>::remove(int position, List_entry &x)
{
   if (position < 0 || position >= count)
      return range_error;

   set_position(position);
   Node<List_entry> *old_node = current;

   if (old_node->back != nullptr)
      old_node->back->next = old_node->next;
   if (old_node->next != nullptr)
      old_node->next->back = old_node->back;

   x = old_node->entry;

   if (count == 1) {
      current = nullptr;
      current_position = 0;
   } else if (old_node->next != nullptr) {
      current = old_node->next;
      current_position = position;
   } else {
      current = old_node->back;
      current_position = position - 1;
   }

   delete old_node;
   --count;

   return success;
}


template <class List_entry>
Error_code List<List_entry>::insert(int position, const List_entry &x)
/*
Post: If the List is not full and 0 <= position <= n,
      where n is the number of entries in the List, the function succeeds:
      Any entry formerly at position and all later entries have their
      position numbers increased by 1 and x is inserted at position of the List.
      Else: the function fails with a diagnostic error code.
*/
{
   Node<List_entry> *new_node, *following, *preceding;
   if (position < 0 || position > count) return range_error;
   if (position == 0) {
      if (count == 0) following = NULL;
      else {
         set_position(0);
         following = current;
      }
      preceding = NULL;
   }
   else {
      set_position(position - 1);
      preceding = current;
      following = preceding->next;
   }
   new_node = new Node<List_entry>(x, preceding, following);

   if (new_node == NULL) return overflow;
   if (preceding != NULL) preceding->next = new_node;
   if (following != NULL) following->back = new_node;
   current = new_node;
   current_position = position;
   count++;
   return success;
}