#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"
#include "../../P1/PRA_2526_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {

private:
    int n;
    int max;
    ListLinked<TableEntry<V>>* table;

    int h(std::string key) {
        int sum = 0;
        for (int i = 0; i < (int)key.size(); i++)
            sum += int(key.at(i));
        return sum % max;
    }

    int findPos(int bucket, std::string key) {
        for (int i = 0; i < table[bucket].size(); i++)
            if (table[bucket].get(i).key == key)
                return i;
        return -1;
    }

public:
    HashTable(int size) : n(0), max(size) {
        table = new ListLinked<TableEntry<V>>[max];
    }

    ~HashTable() {
        delete[] table;
    }

    void insert(std::string key, V value) {
        int pos = h(key);
        if (findPos(pos, key) != -1)
            throw std::runtime_error("Key '" + key + "' already exists!");
        table[pos].insert(0, TableEntry<V>(key, value));
        n++;
    }

    V search(std::string key) {
        int pos = h(key);
        int i = findPos(pos, key);
        if (i == -1)
            throw std::runtime_error("Key '" + key + "' not found!");
        return table[pos].get(i).value;
    }

    V remove(std::string key) {
        int pos = h(key);
        int i = findPos(pos, key);
        if (i == -1)
            throw std::runtime_error("Key '" + key + "' not found!");
        V value = table[pos].get(i).value;
        table[pos].remove(i);
        n--;
        return value;
    }

    int entries() {
        return n;
    }

    int capacity() {
        return max;
    }

    V operator[](std::string key) {
        return search(key);
    }

    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
        out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]\n";
        out << "==============\n\n";
        for (int i = 0; i < th.max; i++) {
            out << "== Cubeta " << i << " ==\n\n";
            out << "List => " << th.table[i] << "\n\n";
        }
        out << "==============\n";
        return out;
    }
};

#endif

