// list_ref.h

#if ! defined (LIST_REF_H)
#define LIST_REF_H 1

 /*
  * The struct list type can be used to represent chained lists with tail pointer.
  * - The ref field contains the unique key (int) of the website (char).
  * - The nbelem field contains the hub score of the hub site, i.e. the size of the target vector.
  * The empty list is encoded by head = tail = NIL and nbelem = 0.
  * Nodes are allocated dynamically.
  * The next field of the last node is NIL.
  */

struct node {
    char* ref;
    struct node* next;
};

#define NIL (struct node*)0

struct list {
    struct node* head;
    struct node* tail;
    int nbelem;
};

extern void init_list (struct list*);

extern void clear_list (struct list*);

extern void add_to_head_list (struct list*, char*);

extern void add_sorted_list (struct list*, char*) ;

extern void add_to_tail_list (struct list*, char*);

extern void print_list (struct list*);

extern int search_in_list (struct list*, char*) ;

#endif
