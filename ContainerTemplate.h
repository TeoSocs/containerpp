//
// Created by socs on 08/02/19.
//

#ifndef CONTAINERPP_CONTAINERTEMPLATE_H
#define CONTAINERPP_CONTAINERTEMPLATE_H

template<class T>
class Container {
    friend class Iterator;

    friend std::ostream &operator<<(std::ostream &, const Container &);

private:
    class Node;

    class DeepPtr {
    public:
        Node *pointer;

        DeepPtr(Node *p = nullptr);

        DeepPtr(const DeepPtr &);

        ~DeepPtr();

        DeepPtr &operator=(const DeepPtr &);

        Node &operator*() const;

        Node *operator->() const;

        bool operator==(const DeepPtr &) const;

        bool operator!=(const DeepPtr &) const;
    };

    class Node {
    public:
        Node();

        Node(const T &, const DeepPtr &);

        T value;
        DeepPtr next;
        int references;
    };

    DeepPtr first;

public:
    class Iterator {
        friend class Container;

    private:
        DeepPtr pointer;
    public:
        bool operator==(Iterator) const;

        bool operator!=(Iterator) const;

        const Container::Iterator operator++(int);
    };

    Container() : first(nullptr) {}

    // Metodi di accesso
    Iterator begin() const;

    Iterator end() const;

    T &operator[](Iterator) const;

    bool isEmpty() const;

    void pushFront(const T &);

    void remove(const T &);

    T popFirst();
};


/**
 * Metodi pubblici di Container
 */
template<class T>
bool Container<T>::isEmpty() const {
    return first == nullptr;
}

template<class T>
void Container<T>::pushFront(const T &x) {
    first = new Node(x, first);
}

template<class T>
void Container<T>::remove(const T &t) {
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

template<class T>
T Container<T>::popFirst() {
    if (this->isEmpty()) {
        throw;
    }
    T aux = first->value;
    first = first->next;
    return aux;
}

template<class T>
std::ostream &operator<<(std::ostream &os, const Container<T> &c) {
    os << "[";
    typename Container<T>::DeepPtr p = c.first;
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
 * Metodi di accesso di Container<T>
 */
template<class T>
typename Container<T>::Iterator Container<T>::begin() const {
    Iterator aux;
    aux.pointer = first;
    return aux;
}

template<class T>
typename Container<T>::Iterator Container<T>::end() const {
    Iterator aux;
    aux.pointer = nullptr;
    return aux;
}

template<class T>
T &Container<T>::operator[](Container<T>::Iterator it) const {
    return it.pointer->value;
}

template<class T>
// ...Non proprio metodi di accesso ma stessa area semantica
bool Container<T>::Iterator::operator==(Container<T>::Iterator it) const {
    return pointer == it.pointer;
}

template<class T>
bool Container<T>::Iterator::operator!=(Container<T>::Iterator it) const {
    return pointer != it.pointer;
}

template<class T>
const typename Container<T>::Iterator Container<T>::Iterator::operator++(int) {
    Iterator aux = *this;
    if (pointer != nullptr) {
        pointer = pointer->next;
    }
    return aux;
}


/**
 * Metodi di Node
 */
template<class T>
Container<T>::Node::Node() : references(0) {}

template<class T>
Container<T>::Node::Node(const T &x, const DeepPtr &p) : value(x), next(p), references(0) {}


/**
 * Metodi di DeepPtr
 */
template<class T>
Container<T>::DeepPtr::DeepPtr(Container<T>::Node *p) : pointer(p) {
    if (pointer) pointer->references++;
}

template<class T>
Container<T>::DeepPtr::DeepPtr(const Container<T>::DeepPtr &p) : pointer(p.pointer) {
    if (pointer) pointer->references++;
}

template<class T>
Container<T>::DeepPtr::~DeepPtr() {
    if (pointer) {
        pointer->references--;
        if (pointer->references == 0) delete pointer;
    }
}

template<class T>
typename Container<T>::DeepPtr &Container<T>::DeepPtr::operator=(const Container<T>::DeepPtr &p) {
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

template<class T>
typename Container<T>::Node &Container<T>::DeepPtr::operator*() const {
    return *pointer;
}

template<class T>
typename Container<T>::Node *Container<T>::DeepPtr::operator->() const {
    return pointer;
}

template<class T>
bool Container<T>::DeepPtr::operator==(const Container<T>::DeepPtr &p) const {
    return pointer == p.pointer;
}

template<class T>
bool Container<T>::DeepPtr::operator!=(const Container<T>::DeepPtr &p) const {
    return pointer != p.pointer;
}


#endif //CONTAINERPP_CONTAINERTEMPLATE_H
