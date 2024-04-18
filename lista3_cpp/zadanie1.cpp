#include <iostream>

struct Link
{
    int value;     
    Link* next = nullptr;  
};

// a) funkcja zwraca liczbe elementow listy
size_t size(const Link* head) {
    size_t count = 0;       
    const Link* current = head; 
    while (current != nullptr) {  
        count++;        
        current = current->next;    
    }
    return count;   
}

// b) funkcja zwraca sumę wartości przechowywanych na liście
size_t sum(const Link* head) {
    size_t total = 0;      
    const Link* current = head;   
    while (current != nullptr) {  
        total += current->value;    
        current = current->next;    
    }
    return total;  
}

int main() {

    //lista 
    Link* head = new Link{1};
    head->next = new Link{2};
    head->next->next = new Link{3};
    head->next->next->next = new Link{4};
    head->next->next->next->next = new Link{5};

    //wywołanie
    std::cout << "a) Rozmiar listy: " << size(head) << std::endl;
    std::cout << "b) Suma wartosci na liscie: " << sum(head) << std::endl;

    while (head != nullptr) {
        Link* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
