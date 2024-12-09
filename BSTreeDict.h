#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

#include <vector>

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


    V operator[](std::string key) override {
        return tree->search(TableEntry<V>(key, V())).getValue();
    }


    void insert(std::string key, V value) override {
        TableEntry<V> entry(key, value);
        tree->insert(entry);
    }

    //Busca un valor asociado a una clave en el diccionario
    V search(std::string key) override {
        return tree->search(TableEntry<V>(key, V())).getValue();
    }

    //Elimina una entrada clave->valor del diccionario
    void remove(std::string key) override {
        tree->remove(TableEntry<V>(key, V()));
    }

    //Devuelve todas las entradas clave->valor del diccionario
    friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &dict) {
    // Utilizamos la sobrecarga del operador << de BSTree.
 	if (dict.tree) {
   	    out << *(dict.tree);
    	} else {
	    out << "El diccionario está vacío.";
    	}
    	return out;
	}

    //Sobrecarga del operador << para imprimir el contenido del diccionario
    friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs) {
        out << *(bs.tree);
        return out;
    }
};

#endif

