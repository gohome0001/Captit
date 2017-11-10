#include "data_types.h"

int add_node(int index, p_llist* list, pnode* to_add)
{
    if(index < 0) // to the last
    {
        list->top_node->next = to_add;
        to_add->priv = list->top_node
        return 0;
    }else{
        pnode* priv = get_node(index, list->m_node);
        if(priv->next != NULL)
        {
            priv->next->priv = to_add;
            to_add->next
        }
        priv->next = to_add;
        to_add->priv = priv;
    }
    return 0;
}

pnode* create_node(const pnode* data, int size)
{
    pnode* rval = (pnode*)malloc(size);
    rval->priv = NULL;
    rval->next = NULL;
    rval = pnode;
    return rval;
}

int delete_node(pnode* to_del)
{
    pnode *priv = to_del->priv;
    pnode *next = tp_del->next;
    
    free(to_del->data);
    
    if(next != NULL)
    {
        priv->next = next;
        next->priv = priv;
    }else{
        priv->next = NULL;
    }

    return 0;
}

int get_node(int index, pnode* m_node)
{
    node* next = node->next;
    if(next == NULL)
    {
        return next;
    }
    if(index == 1)
    {
        return next;
    }
    return get_node(index-1, next);
}