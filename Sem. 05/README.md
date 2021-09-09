
# Стек (Stack)
**Добавяне и премахване от една и съща страна.**

*1 вариант: pushBack + popBack*
|                  | pushBack | popBack |   |
|------------------|----------|---------|---|
| Vector           |  O(1)*   |  O(1)*  |   |
| SinglyLinkedList |  O(1)    |  O(n)   |   |
| DoublyLinkedList |  O(1)    |  O(1)   |   |


*2 вариант: pushFront + popFront*
|                  | pushFront | popFront |   |
|------------------|----------|-----------|---|
| Vector           |  O(n)    |  O(n)     |   |
| SinglyLinkedList |  O(1)    |  O(1)     |   |
| DoublyLinkedList |  O(1)    |  O(1)     |   |

# Опашка (Queue)
**Добавяне и премахване от двете противоположни страни**

*1 вариант: pushBack + popFront*

|                  | pushBack | popFront |   |
|------------------|----------|----------|---|
| Vector           |  O(1)*   |  O(n)    |   |
| SinglyLinkedList |  O(1)    |  O(1)    |   |
| DoublyLinkedList |  O(1)    |  O(1)    |   |

*2 вариант: pushFront + popBack*

|                  | pushFront | popBack |   |
|------------------|----------|----------|---|
| Vector           |  O(n)    |  O(1)*   |   |
| SinglyLinkedList |  O(1)    |  O(n)    |   |
| DoublyLinkedList |  O(1)    |  O(1)    |   |

3 вариант: циркуларна опашка
