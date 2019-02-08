#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>

class T {
    friend std::ostream &operator<<(std::ostream &os, const T &t) {
        os << t.i;
        return os;
    };

private:
    int i;

public:
    T() {};

    T(int x) : i(x) {};

    bool operator==(const T &t) const { return i == t.i; };
};

class Container {
    friend class Iterator;

    friend std::ostream &operator<<(std::ostream &, const Container &);

private:
    class Node {
    public:
        Node();

        Node(const T &, Node *);

        void operator delete(void *);

        T value;
        Node *next;
        int references;
    };

    Node *first;

//    // Metodi di utilità per la manipolazione profonda di liste
//    static Node *cloneListStartingBy(Node *);
//
//    static void destroyListStartingBy(Node *);

public:
    class Iterator {
        friend class Container;

    private:
        Node *pointer;
    public:
        bool operator==(Iterator) const;

        bool operator!=(Iterator) const;

        const Container::Iterator operator++(int);
    };

    Container() : first(nullptr) {}

    // Gestione della memoria "profonda"
    Container &operator=(const Container &);

    Container(const Container &);

    ~Container();

    // Metodi di accesso
    Iterator begin() const;

    Iterator end() const;

    T &operator[](Iterator) const;

    bool isEmpty() const;

    void pushFront(const T &);

    void remove(const T &);

    T popFirst();
};

#endif // BOLLETTA_H
