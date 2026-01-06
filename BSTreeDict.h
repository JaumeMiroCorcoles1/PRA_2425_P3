#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {

private:
    BSTree<TableEntry<V>>* tree;

public:
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();
    }

    ~BSTreeDict() {
        delete tree;
    }

    void insert(std::string key, V value) {
        tree->insert(TableEntry<V>(key, value));
    }

    V search(std::string key) {
        return tree->search(TableEntry<V>(key)).value;
    }

    V remove(std::string key) {
        V value = tree->search(TableEntry<V>(key)).value;
        tree->remove(TableEntry<V>(key));
        return value;
    }

    int entries() {
        return tree->size();
    }

    V operator[](std::string key) {
        return search(key);
    }

    friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs) {
        out << *(bs.tree);
        return out;
    }
};

#endif

