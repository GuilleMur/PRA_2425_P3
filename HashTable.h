#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2425_P1/ListLinked.h"  
template <typename V>
class HashTable: public Dict<V> {
private:
    int n;
    int max;
    ListLinked<TableEntry<V>>* table;
    //Transforma la clave en un número entero dentro del HashTable
    int h(const std::string& key) {
        int sum = 0;
        for (char c : key) {
            sum += static_cast<int>(c);
        }
        return (sum % max + max) % max;
    }

public:
    //Crea una tabla de hash con tamaño size
    HashTable(int size) {
        if (size <= 0) throw std::invalid_argument("Tamaño no válido");
        table = new ListLinked<TableEntry<V>>[size];
        max = size;
        n = 0;
    }

    ~HashTable() {
        delete[] table;
    }

    int capacity() {
        return max;
    }
    //Sobrecarga de << para imprimir la tabla
    friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& th) {
        for (int i = 0; i < th.max; i++) {
            out << i << ": " << th.table[i] << std::endl;
        }
        return out;
    }
    //Sobrecarga de [] para acceder a un valor dado una clave
    V operator[](std::string key) {
        int aux = h(key);
        for (int i = 0; i < table[aux].size(); i++) {
            if (table[aux][i].key == key) {
                return table[aux][i].value;
            }
        }
        throw std::runtime_error("Clave no encontrada");
    }


    void insert(const std::string key, const V val) {
        int aux = h(key);

        for (int i = 0; i < table[aux].size(); i++) {
            if (table[aux][i].key == key) {
                throw std::runtime_error("Clave ya en uso");
            }
        }
        //Si la lista en la posición aux está vacía, inserta el valor en la primera posición
        TableEntry<V> entry(key, val);
        //agrega el valor al inicio de la lista
        table[aux].insert(0, entry);
        n++;
    }


    V search(const std::string& key) {
        int aux = h(key);
        if (table[aux].empty()) {
            throw std::runtime_error("Clave no encontrada");
        }

        for (int i = 0; i < table[aux].size(); i++) {
            if (table[aux][i].key == key) {
                return table[aux][i].value;
            }
        }
        throw std::runtime_error("Clave no encontrada");
    }

    V remove(const std::string& key) {
        int aux = h(key);
        if (table[aux].empty()) {
            throw std::runtime_error("Clave no encontrada");
        }

        for (int i = 0; i < table[aux].size(); i++) {
            if (table[aux][i].key == key) {
                V val = table[aux][i].value;
                table[aux].remove(i);
                n--;
                return val;
            }
        }
        throw std::runtime_error("Clave no encontrada");
    }

    int entries() {
        return n;
    }
};

#endif // HASHTABLE_H
