#ifndef CAPTIT_DATA_TYPES_H // 다른거랑 이름 안겹치게끔 길게 함

#define CAPTIT_DATA_TYPES_H

typedef struct
{
    void* priv;
    void* data;
    void* next;
}node, *pnode;

typdef struct
{
    pnode *m_node;
    pnode *top_node;
}llist, *p_llist;

int add_node(int index, p_llist* list, pnode* to_add);

pnode* create_node(const pnode* data, int size);

int delete_node(pnode* to_del);

int get_node(int index, pnode* m_node);

#endif