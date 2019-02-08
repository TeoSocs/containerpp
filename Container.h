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

#endif // BOLLETTA_H
