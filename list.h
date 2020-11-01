#ifndef LIST_H
#define LIST_H

#include <stddef.h>

/*
    Для реализации двусвязного списка нам понадобится структура узел. 
    Указатель prev хранит адрес предыдущего узла, если его нет (значит, это первый узел), 
    то переменная равна NULL. Аналогично, указатель next хранит адрес следующего узла.
*/
typedef struct _Node {
    int value;
    struct _Node* next;
    struct _Node* prev;
} Node;

/*
    Структура двусвязного списка будет хранить свой размер (чтобы не пересчитывать количество 
    элементов каждый раз), а также указатель head, ссылающийся на первый элемент, и указатель tail, 
    ссылающийся на последний элемент.
*/
typedef struct _DblLinkedList {
    size_t size;
    Node* head;
    Node* tail;
} DblLinkedList;

// Создание экземпляра структуры DblLinkedList
DblLinkedList* createDblLinkedList();

// Удаление двусвязного списка
void deleteDblLinkedList(DblLinkedList** list);

// Добавление элемента в начало списка
void pushFront(DblLinkedList* list, int data);

// Удаление элемента из начала списка
int popFront(DblLinkedList* list);

// Добавление элемента в конец списка
void pushBack(DblLinkedList* list, int value);

// Удаление элемента с конца списка
int popBack(DblLinkedList* list);

/*
    Получение элемента по определенному индексу. 
    Eсли список длинный, то в зависимости от индекса можно проходить либо с начала в конец, 
    либо с конца в начало. Это позволяет всегда использовать не более size/2 шагов.
*/
Node* getNth(DblLinkedList* list, size_t index);

// Вставка элемента в список по определенному индексу
void insert(DblLinkedList* list, size_t index, int value);

// Удаление элемента с позиции, определенной входным индексом
int deleteNth(DblLinkedList* list, size_t index);

// Печать списка
void printDblLinkedList(DblLinkedList* list, void (*fun)(int));
void printInt(int value);

// Инициализация count элементов списка случайными значениями
void initListByRand(DblLinkedList* list, size_t count);

#endif // !LIST_H