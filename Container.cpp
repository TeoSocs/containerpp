#include "Container.h"

/**
 * Gestione della memoria di Container
 */
Container &Container::operator=(const Container &c) {
    if (this != &c) {
        destroyListStartingBy(first);
        first = cloneListStartingBy(c.first);
    }
    return *this;
}

Container::Container(const Container &c) : first(cloneListStartingBy(c.first)) {}

Container::~Container() {
    destroyListStartingBy(first);
}


/**
 * Metodi pubblici di Container
 */
bool Container::isEmpty() const {
    return first == nullptr;
}

void Container::pushFront(int x) {
    first = new Node(x, first);
}

// TODO: facile che sia da modificare più avanti
void Container::remove(int x) {
    Node *p = first, *prev = nullptr;
    // Scorro fino a che non trovo il value che voglio. Da modificare per classi più complesse
    while (p && p->value != x) {
        prev = p;
        p = p->next;
    }
    // a questo punto o ho trovato il nodo da rimuovere o sono uscito
    if (p) {
        if (!prev) {
            // se sono al primo nodo devo far partire il container dal secondo perché sto per cancellare
            first = p->next;
        } else {
            prev->next = p->next;
        }
        delete p;
    }
}

int Container::popFirst() {
    if (this->isEmpty()) {
        throw;
    }
    Node *p = first;
    first = first->next;
    int aux = p->value; // viene invocato il costruttore di copia
    delete p;
    return aux;
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
Container::Node *Container::cloneListStartingBy(Container::Node *p) {
    if (!p) return nullptr;
    return new Node(p->value, cloneListStartingBy(p->next));
}

void Container::destroyListStartingBy(Container::Node *p) {
    if (p) {
        destroyListStartingBy(p->next);
        delete p;
    }
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

int &Container::operator[](Container::Iterator it) const {
    return it.pointer->value;
}


/**
 * Metodi di Node
 */
Container::Node::Node() : next(nullptr) {}

Container::Node::Node(const int &x, Container::Node *n) : value(x), next(n) {}
