#include "Container.h"


/**
 * Metodi pubblici di Container
 */
bool Container::isEmpty() const {
    return first == nullptr;
}

void Container::pushFront(const T &x) {
    first = new Node(x, first);
}

void Container::remove(const T &t) {
    DeepPtr p = first, prev, q;
    DeepPtr original = first;
    first = nullptr;
    while (p != nullptr && !(p->value == t)) {
        q = new Node(p->value, p->next);
        if (prev == nullptr) first = q;
        else prev->next = q;
        prev = q;
        p = p->next;
    }
    if (p == nullptr) first = original;
    else if (prev == nullptr) first = p->next;
    else prev->next = p->next;
}

T Container::popFirst() {
    if (this->isEmpty()) {
        throw;
    }
    T aux = first->value;
    first = first->next;
    return aux;
}

std::ostream &operator<<(std::ostream &os, const Container &c) {
    os << "[";
    Container::DeepPtr p = c.first;
    int i = 1;
    while (p != nullptr) {
        os << p->value;
        p = p->next;
        if (p != nullptr) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}


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
    if (pointer != nullptr) {
        pointer = pointer->next;
    }
    return aux;
}


/**
 * Metodi di Node
 */
Container::Node::Node() : references(0) {}

Container::Node::Node(const T &x, const DeepPtr &p) : value(x), next(p), references(0) {}


/**
 * Metodi di DeepPtr
 */
Container::DeepPtr::DeepPtr(Container::Node *p) : pointer(p) {
    if (pointer) pointer->references++;
}

Container::DeepPtr::DeepPtr(const Container::DeepPtr &p) : pointer(p.pointer) {
    if (pointer) pointer->references++;
}

Container::DeepPtr::~DeepPtr() {
    if (pointer) {
        pointer->references--;
        if (pointer->references == 0) delete pointer;
    }
}

Container::DeepPtr &Container::DeepPtr::operator=(const Container::DeepPtr &p) {
    if (this != &p) {
        Node *t = pointer;
        pointer = p.pointer;
        if (pointer) pointer->references++;
        if (t) {
            t->references--;
            if (t->references == 0) delete t;
        }
    }
    return *this;
}

Container::Node &Container::DeepPtr::operator*() const {
    return *pointer;
}

Container::Node *Container::DeepPtr::operator->() const {
    return pointer;
}

bool Container::DeepPtr::operator==(const Container::DeepPtr &p) const {
    return pointer == p.pointer;
}

bool Container::DeepPtr::operator!=(const Container::DeepPtr &p) const {
    return pointer != p.pointer;
}
