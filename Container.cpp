#include "Container.h"

/**
 * Gestione della memoria di Container
 */
Container &Container::operator=(const Container &c) {
    if (this != &c) {
        if (first) delete first;
        first = c.first;
        if (first) first->references++;
    }
    return *this;
}

Container::Container(const Container &c) : first(c.first) {
    if (first) {
        first->references++;
    }
}

Container::~Container() {
    if (first) delete first;
}


/**
 * Metodi pubblici di Container
 */
bool Container::isEmpty() const {
    return first == nullptr;
}

void Container::pushFront(const T &x) {
    if (first) {
        first->references--;
    }
    first = new Node(x, first);
    first->references++;
}

// TODO: facile che sia da modificare più avanti
void Container::remove(const T &t) {
    Node *p = first, *prev = nullptr, *q = nullptr;
    first = nullptr;
    while (p && !(p->value == t)) {
        if (q) delete q;
        q = new Node(p->value, p->next);
        q->references++;
        if (prev == nullptr) {
            first = q;
            first->references++;
        } else {
            if (prev->next) delete prev->next;
            prev->next = q;
            prev->next->references++;
        }
        if (prev) delete prev;
        prev = q;
        prev->references++;
        if (p) delete p;
        p = q->next;
        if (p) p->references++;
    }
    if (p) {
        if (prev == nullptr) {
            first = p->next;
            if (first) first->references++;
        } else {
            if (prev->next) delete prev->next;
            prev->next = p->next;
            if (prev->next) prev->next->references++;
        }
    }
    if (p) delete p;
    if (prev) delete prev;
    if (q) delete q;
}

T Container::popFirst() {
    if (this->isEmpty()) {
        throw;
    }
    T aux = first->value;
    Node *p = first;
    if (p) p->references++;
    if (first) delete first;
    first = p->next;
    if (first) first->references++;
}

std::ostream &operator<<(std::ostream &os, const Container &c) {
    os << "[";
    Container::Node *p = c.first;
    int i = 1;
    while (p) {
        os << p->value;
        p = p->next;
        if (p) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}


/**
 * Metodi di utilità di Container
 */
//Container::Node *Container::cloneListStartingBy(Container::Node *p) {
//    if (!p) return nullptr;
//    return new Node(p->value, cloneListStartingBy(p->next));
//}
//
//void Container::destroyListStartingBy(Container::Node *p) {
//    if (p) {
//        destroyListStartingBy(p->next);
//        delete p;
//    }
//}

/**
 * Metodi di accesso di Container
 */
Container::Iterator Container::begin() const {
    Iterator aux;
    aux.pointer = first;
    return aux;
}

Container::Iterator Container::end() const {
    Iterator aux;
    aux.pointer = nullptr;
    return aux;
}

T &Container::operator[](Container::Iterator it) const {
    return it.pointer->value;
}

// ...Non proprio metodi di accesso ma stessa area semantica
bool Container::Iterator::operator==(Container::Iterator it) const {
    return pointer == it.pointer;
}

bool Container::Iterator::operator!=(Container::Iterator it) const {
    return pointer != it.pointer;
}

const Container::Iterator Container::Iterator::operator++(int) {
    Iterator aux = *this;
    if (pointer) {
        pointer = pointer->next;
    }
    return aux;
}


/**
 * Metodi di Node
 */
Container::Node::Node() : next(nullptr), references(0) {}

Container::Node::Node(const T &x, Container::Node *n) : value(x), next(n), references(0) {
    if (next) {
        next->references++;
    }
}

// Necessario per implementazione condivisione di memoria controllata
void Container::Node::operator delete(void *pVoid) {
    if (pVoid) {
        Node *q = static_cast<Node *>(pVoid);
        q->references--;
        if (q->references == 0) {
            delete q->next;
            ::delete q;
        }
    }
}
