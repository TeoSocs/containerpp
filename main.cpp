#include <iostream>
#include "Container.h"
using namespace std;

int main()
{
    cout << "Creo un Container" << endl;
    Container c1 = Container();
    c1.pushFront(1);
    c1.pushFront(2);
    c1.pushFront(3);
    c1.pushFront(4);
    c1.pushFront(5);

    cout << "Testo assegnazione profonda" << endl;
    Container c2 = c1;
    c2.remove(2);

    cout << "Testo la modifica di un elemento" << endl;
    auto it = c2.begin();
    it++;
    c2[it] = 420;

    cout << "Testo metodi di accesso" << endl;
    for (it = c1.begin(); it != c1.end(); it++) {
        cout << c1[it] << " ";
    }
    cout << endl;
    for (it = c2.begin(); it != c2.end(); it++) {
        cout << c2[it] << " ";
    }
}
