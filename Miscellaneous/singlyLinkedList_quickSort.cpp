#include <iostream>

struct Node {
    int data;
    Node* next = nullptr;

    Node(int value, Node* ptr = nullptr)
        : data(value), next(ptr) {}
};

struct PartitionResult {
    Node* trueHead;
    Node* falseHead;
};

struct ListSegment {
    Node* head;
    Node* tail;
};

void push_back(Node*& begin, Node*& end, Node* toAdd)
{
    if (begin == nullptr)
    {
        begin = end = toAdd;
    }
    else
    {
        end->next = toAdd;
        end = toAdd;
    }
}

template <class PredicateType>
PartitionResult partition(Node* list, const PredicateType& pred)
{
    Node* trueBegin = nullptr;
    Node* trueEnd   = nullptr;

    Node* falseBegin = nullptr;
    Node* falseEnd   = nullptr;

    while (list != nullptr)
    {
        if (pred(list->data))
            push_back(trueBegin, trueEnd, list);
        else
            push_back(falseBegin, falseEnd, list);

        list = list->next;
    }

    if (trueEnd)
        trueEnd->next = nullptr;

    if (falseEnd)
        falseEnd->next = nullptr;

    return { trueBegin, falseBegin };
}

std::pair<Node*, Node*> concatLists(Node* leftBegin, Node* leftEnd,
                                    Node* rightBegin, Node* rightEnd)
{
    if (leftBegin == nullptr)
        return std::make_pair(rightBegin, rightEnd);

    if (rightBegin == nullptr)
        return std::make_pair(leftBegin, leftEnd);

    leftEnd->next = rightBegin;
    return std::make_pair(leftBegin, rightEnd);
}

ListSegment quickSort(Node* list)
{
    if (!list || !list->next)
        return { list, list };

    int pivot = list->data;

    PartitionResult parts =
        partition(list, [pivot](int el) { return el < pivot; });

    Node* pivotPtr = parts.falseHead;

    ListSegment left  = quickSort(parts.trueHead);
    ListSegment right = quickSort(pivotPtr->next);

    pivotPtr->next = right.head;
    right.head = pivotPtr;
    if (!right.tail)
        right.tail = pivotPtr;

    auto merged = concatLists(left.head, left.tail,
                              right.head, right.tail);

    return { merged.first, merged.second };
}

void printList(Node* iter)
{
    while (iter != nullptr)
    {
        std::cout << iter->data;
        if (iter->next)
            std::cout << " -> ";
        iter = iter->next;
    }
}

void freeList(Node* iter)
{
    while (iter != nullptr)
    {
        Node* toDelete = iter;
        iter = iter->next;
        delete toDelete;
    }
}

int main()
{
    Node* list = new Node{ 31,
                    new Node{ 4,
                    new Node{ 53,
                    new Node{ 2 }}}};

    ListSegment sorted = quickSort(list);
    printList(sorted.head);
    freeList(sorted.head);
}
