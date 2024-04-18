#include <iostream>

struct Link {
    int value;
    Link* next = nullptr;
    
    Link(int val) : value(val), next(nullptr) {}
};

Link* reverse(Link* head) {
    Link* prev = nullptr;
    Link* current = head;
    Link* next = nullptr;
    
    while (current != nullptr) {
        next = current->next;  
        current->next = prev;  
        prev = current;       
        current = next;    
    }
    return prev;
}

void printList(Link* head) {
    Link* current = head;
    while (current != nullptr) {
        std::cout << current->value;
        if (current->next != nullptr) {
            std::cout << "->";
        }
        current = current->next;
    }
    std::cout << std::endl;
}

int main() {
    Link* head = nullptr;
    int n;
    std::cout << "Podaj liczbe elementow w liscie: ";
    std::cin >> n;
    
    if (n > 0) {
        std::cout << "Podaj elementy listy:\n";
        Link* prev = nullptr;
        for (int i = 0; i < n; ++i) {
            int val;
            std::cin >> val;
            Link* newNode = new Link(val);
            if (prev == nullptr) {
                head = newNode;
            } else {
                prev->next = newNode;
            }
            prev = newNode;
        }
    }
    
    std::cout << "Lista przed odwroceniem: ";
    printList(head);
    
    head = reverse(head);
    
    std::cout << "Lista po odwroceniu: ";
    printList(head);

    Link* current = head;
    while (current != nullptr) {
        Link* temp = current;
        current = current->next;
        delete temp;
    }
    
    return 0;
}
