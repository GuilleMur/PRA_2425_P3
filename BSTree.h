#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include <stdexcept>
#include "BSNode.h" // Asegúrate de que este archivo contiene la definición de BSNode<T>

template <typename T>
class BSTree {
private:
    int nelem; // Número de elementos en el árbol
    BSNode<T>* root; // Nodo raíz

    // Métodos privados
    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (!n) throw std::runtime_error("Elemento no encontrado");
        if (e == n->data) return n;
        if (e < n->data) return search(n->left, e);
        return search(n->right, e);
    }

    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (!n) {
            nelem++;
            return new BSNode<T>(e);
        }
        if (e == n->data) throw std::runtime_error("Elemento ya existente");
        if (e < n->data) n->left = insert(n->left, e);
        else n->right = insert(n->right, e);
        return n;
    }

    void print_inorder(std::ostream& out, BSNode<T>* n) const {
        if (!n) return;
        print_inorder(out, n->left);
        out << n->data << " ";
        print_inorder(out, n->right);
    }

    BSNode<T>* remove(BSNode<T>* n, T e) {
        if (!n) throw std::runtime_error("Elemento no encontrado");
        if (e < n->data) n->left = remove(n->left, e);
        else if (e > n->data) n->right = remove(n->right, e);
        else {
            if (!n->left) {
                BSNode<T>* temp = n->right;
                delete n;
                nelem--;
                return temp;
            }
            if (!n->right) {
                BSNode<T>* temp = n->left;
                delete n;
                nelem--;
                return temp;
            }
            T maxVal = max(n->left);
            n->data = maxVal;
            n->left = remove_max(n->left);
        }
        return n;
    }

    T max(BSNode<T>* n) const {
        while (n->right) n = n->right;
        return n->data;
    }

    BSNode<T>* remove_max(BSNode<T>* n) {
        if (!n->right) {
            BSNode<T>* temp = n->left;
            delete n;
            return temp;
        }
        n->right = remove_max(n->right);
        return n;
    }

    void delete_cascade(BSNode<T>* n) {
        if (!n) return;
        delete_cascade(n->left);
        delete_cascade(n->right);
        delete n;
    }

public:
    // Constructor
    BSTree() : nelem(0), root(nullptr) {}

    // Destructor
    ~BSTree() {
        delete_cascade(root);
    }

    // Tamaño del árbol
    int size() const {
        return nelem;
    }

    // Búsqueda de elementos
    T search(T e) const {
        BSNode<T>* result = search(root, e);
        return result->data;
    }

    T operator[](T e) const {
        return search(e);
    }

    // Inserción de elementos
    void insert(T e) {
        root = insert(root, e);
    }

    // Eliminación de elementos
    void remove(T e) {
        root = remove(root, e);
    }

    // Recorrido e impresión
    friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst) {
        bst.print_inorder(out, bst.root);
        return out;
    }
};

#endif

