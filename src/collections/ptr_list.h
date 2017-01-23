#ifndef LIST_PTR_H
#define LIST_PTR_H

namespace sentinel {
    namespace collections {
        template <typename T>
        class ptr_list {
        public:
            ptr_list();
            ~ptr_list();

            void push_front(T* x);
            T* pop_front();

        private:
            struct ListEntry {
                T* data;
                ListEntry* next;
            };
            ListEntry* head;
        };        
    }
}

template <typename T>
sentinel::collections::ptr_list<T>::ptr_list() : head(nullptr) { }

template <typename T>
sentinel::collections::ptr_list<T>::~ptr_list() {
    auto current = head;

    while (current != nullptr) {
        auto next = current->next;
        delete current->data;
        delete current;
        current = next;
    }    
}

template <typename T>
void sentinel::collections::ptr_list<T>::push_front(T* x) {
    auto newEntry = new ListEntry { x, head };
    head = newEntry;
}

template <typename T>
T* sentinel::collections::ptr_list<T>::pop_front() {
    if (head == nullptr)
        return nullptr;
    
    auto old_head = head;
    head = head->next;
    T* result = old_head->data;
    delete old_head;
    return result;
}
#endif /* LIST_PTR_H */

