#ifndef BSTREE_H
#define BSTREE_H

#include <stdexcept>
#include <ostream>
#include "BSNode.h"

template <typename T>
class BSTree {
private:
    BSNode<T>* root;
    int nelem;

    
    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (!n) throw std::runtime_error("Elemento no encontrado");
        if (e == n->elem) return n;               
        if (e < n->elem) return search(n->left, e); 
        return search(n->right, e);                 
    }

    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (!n) {
            nelem++;
            return new BSNode<T>(e);
        }
        if (e == n->elem) throw std::runtime_error("Elemento ya existente");
        if (e < n->elem) n->left = insert(n->left, e);
        else n->right = insert(n->right, e);   
        return n;
    }

    void print_inorder(std::ostream &out, BSNode<T>* n) const {
        if (n) {
            print_inorder(out, n->left);
            out << n->elem << " ";
            print_inorder(out, n->right);
        }
    }

    BSNode<T>* remove(BSNode<T>* n, T e) {
        if (!n) throw std::runtime_error("Elemento no encontrado");
        if (e < n->elem) n->left = remove(n->left, e);
        else if (e > n->elem) n->right = remove(n->right, e);
        else {
            if (!n->left) {
                BSNode<T>* temp = n->right;
                delete n;
                nelem--;
                return temp;
            } else if (!n->right) {
                BSNode<T>* temp = n->left;
                delete n;
                nelem--;
                return temp;
            }
            T maxVal = max(n->left);
            n->elem = maxVal;
            n->left = remove_max(n->left);
        }
        return n;
    }

    T max(BSNode<T>* n) const {
        while (n->right) n = n->right;
        return n->elem; 
    }

    BSNode<T>* remove_max(BSNode<T>* n) {
        if (!n->right) {
            BSNode<T>* temp = n->left;
            delete n;
            nelem--;
            return temp;
        }
        n->right = remove_max(n->right);
        return n;
    }

    void delete_cascade(BSNode<T>* n) {
        if (n) {
            delete_cascade(n->left);
            delete_cascade(n->right);
            delete n;
        }
    }

public:
    BSTree(){
    	root = nullptr;
	nelem = 0;
    
    }

    ~BSTree() {
        delete_cascade(root);
    }


    int size() const {
        return nelem;
    }

    T search(T e) const {
        BSNode<T>* result = search(root, e);
        return result->elem;
    }

    //Sobrecarga del operador []
    T operator[](T e) const {
        return search(e);
    }

   
    void insert(T e) {
        root = insert(root, e);
    }

    
    void remove(T e) {
        root = remove(root, e);
    }

    //Sobrecarga del operador <<
    friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
        bst.print_inorder(out, bst.root);
        return out;
    }
};

#endif

