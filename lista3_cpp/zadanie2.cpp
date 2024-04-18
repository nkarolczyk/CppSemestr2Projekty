#include <iostream>

struct Link {
    int value;
    Link* next = nullptr;
};

void release(Link** phead) {
    Link* head = *phead;
    while (head != nullptr) {
        Link* tmp = head;
        head = head->next;
        delete tmp;
    }
    *phead = nullptr;
}

void release_2(Link** phead) {
    if (*phead == nullptr) {
        return;
    }
    Link* tmp = *phead;
    *phead = (*phead)->next;
    delete tmp;
    release_2(phead);
}

int main() {
    Link* head = new Link{1};
    head->next = new Link{2};
    head->next->next = new Link{3};

    std::cout << "Przed zwolnieniem za pomoca petli:" << std::endl;
    Link* current = head;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
    release(&head);
    std::cout << "Po zwolnieniu za pomoca petli:" << std::endl;
    if (head == nullptr) {
        std::cout << "lista jest pusta" << std::endl;
    }

    head = new Link{1};
    head->next = new Link{2};
    head->next->next = new Link{3};

    std::cout << "\nPrzed zwolnieniem za pomoca rekurencji:" << std::endl;
    current = head;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
    release_2(&head);
    std::cout << "Po zwolnieniu za pomoca rekurencji:" << std::endl;
    if (head == nullptr) {
        std::cout << "lista jest pusta" << std::endl;
    }

    return 0;
}
