#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>

class Container {
    friend class Iterator;

    friend std::ostream &operator<<(std::ostream &, const Container &);

private:
    class Node {
    public:
        Node();

        Node(const int &, Node *);

        int value;
        Node *next;
    };

    Node *first;

    // Metodi di utilità per la manipolazione profonda di liste
    static Node *cloneListStartingBy(Node *);

    static void destroyListStartingBy(Node *);

public:
    class Iterator {
        friend class Container;

    private:
        Node *pointer;
    };

    Container() : first(nullptr) {}

    // Gestione della memoria "profonda"
    Container &operator=(const Container &);

    Container(const Container &);

    ~Container();

    // Metodi di accesso
    Iterator begin() const;

    Iterator end() const;

    int &operator[](Iterator) const;

    bool isEmpty() const;

    void pushFront(int);

    void remove(int);

    int popFirst();
};

#endif // BOLLETTA_H
