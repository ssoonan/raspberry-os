#include "lib.h"
#include "process.h"
#include "stddef.h"
#include "debug.h"

void append_list_tail(struct LinkedList *list, struct Node *item)
{
    item->next = NULL; // 혹시나를 위한 초기화

    if (is_list_empty(list))
    {
        list->head = item;
        list->tail = item;
    }
    else
    {
        list->tail->next = item;
        list->tail = item;
    }
}

struct Node *remove_list_head(struct LinkedList *list)
{
    if (is_list_empty(list))
    {
        return NULL;
    }

    struct Node *head = list->head;
    list->head = head->next;

    if (list->head == NULL)
    {
        list->tail = NULL;
    }

    return head;
}

bool is_list_empty(struct LinkedList *list)
{
    return (list->head == NULL);
}

// 해당 함수는 wakeup, wait에서 쓰임. 보류
// struct Node *remove_list(struct LinkedList *list, int wait)
// {
//     struct Node *current = list->head;
//     struct Node *prev = (struct Node *)list;
//     struct Node *item = NULL;

//     while (current != NULL)
//     {
//         if (((struct Process *)current)->wait == wait)
//         {
//             prev->head = current->head;
//             item = current;

//             if (list->head == NULL)
//             {
//                 list->tail = NULL;
//             }
//             else if (current->head == NULL)
//             {
//                 list->tail = prev;
//             }

//             break;
//         }

//         prev = current;
//         current = current->head;
//     }

//     return item;
// }
