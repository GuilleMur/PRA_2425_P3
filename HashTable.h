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
        ListLinked<TableEntry<V>> *table;

        int h(std::string key){
            int sum = 0;
            for(int i = 0; i<key.size(); i++){
                sum += int(key.at(i));
            }
            return sum%max;
        }

    public:

        HashTable(int size){
            table = new ListLinked<TableEntry<V>>[size];
            max = size;
            n = 0;
        }


        ~HashTable(){
            delete[] table;
        }

        int capacity(){
            return max;
        }   

        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
            for (int i = 0; i < th.max; i++){
                out << i << ": " << th.table[i] << std::endl;
            }
            return out;
        }

	
        V operator[](std::string key){
            int temp = h(key);
            for(int i = 0; i < table[temp].size(); i++){
                if(table[temp][i].key == key){
                    return table[temp][i].value;
                }
            }
            throw std::runtime_error("no existe la llave");
        }

       void insert(const std::string key, const V val){
            int temp = h(key);
            try {
                search(key);
            } catch (const std::runtime_error&) {
                TableEntry<V> entry(key, val);
                table[temp].insert(0, entry);
                n++;
            }
       }

        V search(std::string key){
            int temp = h(key);
            for(int i = 0; i < table[temp].size(); i++){
                if(table[temp][i].key == key){
                    return table[temp][i].value;
                }
            }
            throw std::runtime_error("No se encontro la llave");
        }

        V remove(std::string key){
            int temp = h(key);
            for(int i = 0; i < table[temp].size(); i++){
                if(table[temp][i].key == key){
                    V temp = table[temp][i].value;
                    table[temp].remove(i);
                    n--;
                    return temp;
                }
            }
            throw std::runtime_error("No se encontro la llave");
        }

        int entries(){
            return n;
        }
        
};

#endif
