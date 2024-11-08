#include "DoublyCircularLinkedList.h"
#include <iostream>
#include <utility>

#define LOG(x) std::cout << (x) << std::endl
#define LOG_BOOL(x) std::cout << std::boolalpha << (x) << std::endl

int main()
{
    DoublyCircularLinkedList<int> ls;

    LOG("\n> Pushing three");
    ls.push(1);
    ls.push(2);
    ls.push(3);
    ls.print();

    LOG("\n> Popping two");
    LOG_BOOL(ls.pop());
    LOG_BOOL(ls.pop());
    ls.print();

    LOG("\n> Popping two more");
    LOG_BOOL(ls.pop());
    LOG_BOOL(ls.pop());
    ls.print();

    LOG("\n> Pushing four");
    ls.push(1);
    ls.push(2);
    ls.push(3);
    ls.push(4);
    ls.print();

    LOG("\n> Clearing");
    ls.clear();
    ls.print();
}
