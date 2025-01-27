/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/*
 * Copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 * This file is part of UPOalglib.
 *
 * UPOalglib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * UPOalglib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "bst_private.h"
#include <stdio.h>
#include <stdlib.h>


/**** EXERCISE #1 - BEGIN of FUNDAMENTAL OPERATIONS ****/


upo_bst_t upo_bst_create(upo_bst_comparator_t key_cmp)
{
    upo_bst_t tree = malloc(sizeof(struct upo_bst_s));
    if (tree == NULL)
    {
        perror("Unable to create a binary search tree");
        abort();
    }

    tree->root = NULL;
    tree->key_cmp = key_cmp;

    return tree;
}

void upo_bst_destroy(upo_bst_t tree, int destroy_data)
{
    if (tree != NULL)
    {
        upo_bst_clear(tree, destroy_data);
        free(tree);
    }
}

void upo_bst_clear_impl(upo_bst_node_t *node, int destroy_data)
{
    if (node != NULL)
    {
        upo_bst_clear_impl(node->left, destroy_data);
        upo_bst_clear_impl(node->right, destroy_data);

        if (destroy_data)
        {
            free(node->key);
            free(node->value);
        }

        free(node);
    }
}

void upo_bst_clear(upo_bst_t tree, int destroy_data)
{
    if (tree != NULL)
    {
        upo_bst_clear_impl(tree->root, destroy_data);
        tree->root = NULL;
    }
}

upo_bst_node_t* nodeCreate(void* key,void* value){
    upo_bst_node_t* node = malloc(sizeof(struct upo_bst_node_s));
    node->key = key;
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

upo_bst_node_t* putImpl(upo_bst_t tree,void* key, void* value,void* vOld,upo_bst_node_t* node){

    if(node == NULL){
        return nodeCreate(key, value);
    }else if(  tree->key_cmp(key, node->key) < 0 ){
        node->left = putImpl (tree, key, value, vOld, node->left );
    }else if(  tree->key_cmp(key, node->key) > 0 ){
        node->right = putImpl (tree, key, value, vOld, node->right );
    }else{
        vOld = node->value;
        node->value = value;
    }
    return node;
}

void* upo_bst_put(upo_bst_t tree, void *key, void *value){

    void* vOld = NULL;
    tree->root = putImpl(tree, key, value, vOld, tree->root);

    return vOld;

}

/*

void* upo_bst_put(upo_bst_t tree, void *key, void *value)
{
    if(tree == NULL){
        return NULL;
    }

    if(tree->root == NULL){
        upo_bst_node_t* newNode = malloc(sizeof(struct upo_bst_node_s));
        tree->root = newNode;
        newNode->key = key;
        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
        return NULL;
    }

    upo_bst_node_t* nodoValutato = tree->root; 
     
    upo_bst_node_t* parent = NULL;

   
    //ciclo finche non trovo un valore null e quindi sono arrivato ad una foglia
    while(nodoValutato != NULL ){

        //tengo traccia del genitore
        parent = nodoValutato; 


        // se trovo la chiave nell'albero allora vado a sovrascrivere il valore
        if(tree->key_cmp(nodoValutato->key, key) == 0 ){
            void* datoDaRitornare = nodoValutato->value;
            nodoValutato->value = value;
            return datoDaRitornare;
        }

        if(tree->key_cmp(nodoValutato->key, key) > 0 ){
            
            nodoValutato = nodoValutato->left;
        
        }
        else if(tree->key_cmp(nodoValutato->key, key) < 0 ){

            nodoValutato = nodoValutato->right;
        }

    }    

    
    upo_bst_node_t* newNode = malloc(sizeof(struct upo_bst_node_s));
    if(newNode == NULL) return NULL; //errore allocazione memoria

    newNode->key = key;
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;

    if(tree->key_cmp(parent->key, newNode->key) > 0){
        parent->left = newNode;
    }else{
        parent->right = newNode;
    }

    return NULL;

}

*/
//inserisce il valore v identificato da k in t solo se non è un duplicato
void upo_bst_insert(upo_bst_t tree, void *key, void *value)
{
    if(tree == NULL){
        return;
    }

    if(tree->root == NULL){
            upo_bst_node_t* newNode = malloc(sizeof(struct upo_bst_node_s));
            tree->root = newNode;
            newNode->key = key;
            newNode->value = value;
            newNode->left = NULL;
            newNode->right = NULL;
            return;
        }

    upo_bst_node_t* nodoValutato = tree->root; 
     
    upo_bst_node_t* parent = NULL;
    //ciclo finche non trovo un valore null e quindi sono arrivato ad una foglia
    while( nodoValutato != NULL ){

        if(nodoValutato != NULL)

        parent = nodoValutato; 

        if(tree->key_cmp(nodoValutato->key, key) > 0 ){
            nodoValutato = nodoValutato->left;
        }
        else if(tree->key_cmp(nodoValutato->key, key) < 0 ){
            nodoValutato = nodoValutato->right;
        }
        else
        // se trovo la chiave nell'albero allora ritorno dato che il valore è duplicato
        if(tree->key_cmp(nodoValutato->key, key) == 0 ){
            return;
        }
    }    

upo_bst_node_t* newNode = malloc(sizeof(struct upo_bst_node_s));
    if(newNode == NULL) return; //errore allocazione memoria

    newNode->key = key;
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;

    if(tree->key_cmp(parent->key, newNode->key) > 0){
        parent->left = newNode;
    }else{
        parent->right = newNode;
    }
    return;
}

void* upo_bst_get(const upo_bst_t tree, const void *key)
{

    if(tree == NULL){
        return NULL;
    }


    upo_bst_node_t* nodoValutato = tree->root; 


     while( nodoValutato != NULL ){

        if(tree->key_cmp(nodoValutato->key, key) > 0 )
            nodoValutato = nodoValutato->left;
        
        else if(tree->key_cmp(nodoValutato->key, key) < 0 )
            nodoValutato = nodoValutato->right;

        // se trovo la chiave nell'albero allora vado a sovrascrivere il valore
        if(tree->key_cmp(nodoValutato->key, key) == 0 ){
                return nodoValutato->value;
        }
    }    

    return NULL;

}

int upo_bst_contains(const upo_bst_t tree, const void *key)
{
 
   if(tree == NULL){
        return 0;
    }


    upo_bst_node_t* nodoValutato = tree->root; 


     while( nodoValutato != NULL ){

        if(tree->key_cmp(nodoValutato->key, key) > 0 )
            nodoValutato = nodoValutato->left;
        
        else if(tree->key_cmp(nodoValutato->key, key) < 0 )
            nodoValutato = nodoValutato->right;

        // se trovo la chiave nell'albero allora vado a sovrascrivere il valore
        if(tree->key_cmp(nodoValutato->key, key) == 0 ){
                return 1;
        }

    }    

    return 0;

}

upo_bst_node_t* upo_delete_impl(upo_bst_t tree, const void *key, int destroy_data, upo_bst_node_t* nodoValutato);

upo_bst_node_t* delete1_impl( upo_bst_node_t* nodoValutato){

    upo_bst_node_t* x = nodoValutato;

    if(nodoValutato->left != NULL){
        nodoValutato = nodoValutato->left;
    }else{
        nodoValutato = nodoValutato->right;
    }

    free(x);

    return nodoValutato;

}

upo_bst_node_t* max_impl(upo_bst_node_t* nodoValutato){
    

    if(nodoValutato == NULL){
        return NULL;
    }
    else if(nodoValutato->right != NULL){
        return max_impl(nodoValutato->right);
    }else{
        return nodoValutato;
    }
}

upo_bst_node_t* delete2_impl(upo_bst_t tree, int destroy_data, upo_bst_node_t* nodoValutato){

    upo_bst_node_t* max = max_impl(nodoValutato->left);

    nodoValutato->key = max->key;
    nodoValutato->value = max->value;

    nodoValutato->left = upo_delete_impl(tree, max->key, destroy_data, nodoValutato->left );

    return nodoValutato;
}

upo_bst_node_t* upo_delete_impl(upo_bst_t tree, const void *key, int destroy_data, upo_bst_node_t* nodoValutato){

    if(nodoValutato == NULL){
        return NULL;
    }

    if(tree->key_cmp(key, nodoValutato->key) < 0){
        nodoValutato->left = upo_delete_impl(tree, key, destroy_data, nodoValutato->left);
    }

    else if(tree->key_cmp(key, nodoValutato->key) > 0){
   
        nodoValutato->right = upo_delete_impl(tree, key, destroy_data, nodoValutato->right);

    }
    else if(nodoValutato->left != NULL && nodoValutato->right != NULL){
        nodoValutato = delete2_impl(tree, destroy_data, nodoValutato);
    }else{
        nodoValutato = delete1_impl(nodoValutato);
    }
        
    return nodoValutato;
 }

void upo_bst_delete(upo_bst_t tree, const void *key, int destroy_data)
{
    /*
    if(tree == NULL){
        printf("\n\nLA ROOT E' NULL E RITORNO NULL\n\n");
        return NULL;
    }

        printf("\n\n------------------------sono nella delete---------------------\n\n");

    // setto un puntatore per scorrere l'albero
    upo_bst_node_t* nodoValutato = tree->root; 
    //setto un puntatore per tenere in memoria il nodo genitore    
    upo_bst_node_t* parent = NULL;
    
    //ciclo finche non trovo un valore null e quindi sono arrivato ad una foglia
    while( nodoValutato != NULL ){

        printf("\n\n ENTRO NEL WHILE DELLA DELETE  \n\n");
        parent = nodoValutato; 
            printf("\n\nsono in: %d key: %d  left : %d , right; %d \n\n",
            *(unsigned char*) nodoValutato->key,
            *(unsigned char*) key,
            *(unsigned char*) nodoValutato->left->key,
            *(unsigned char*) nodoValutato->right->key);


        if(tree->key_cmp(nodoValutato->key, key) > 0 ){
            printf("\n\n VADO A SINISTRA  \n\n");
            nodoValutato = nodoValutato->left;
        }
        else if(tree->key_cmp(nodoValutato->key, key) < 0 ){
            printf("\n\n VADO A DESTRA  \n\n");
            nodoValutato = nodoValutato->right;
        }
        // se trovo la chiave nell'albero controllo il nodo da eliminare
        else if(tree->key_cmp(nodoValutato->key, key) == 0 ){

            
            printf("\n\n nodo trovato\n\n");
            //se il nodo che trovo da eliminare è una FOGLIA
            
            if( nodoValutato->left == NULL && nodoValutato->right == NULL ){
                printf("\n\n il nodo è una foglia\n\n");
                //controllo se il nodo da eliminare è un figlio destro o sinistro
                if(tree->key_cmp(parent->key, nodoValutato->key) > 0){
                    printf("\n\n il nodo è una foglia e figlio DESTRO\n\n");
                    free(nodoValutato);
                    parent->right = NULL;
                }else{
                    printf("\n\n il nodo è una foglia e figlio SINISTRO\n\n");
                    free(nodoValutato);
                    parent->left = NULL;
                }

                // se il nodo da eliminare ha un figlio DESTRO    
            }else if( nodoValutato->left == NULL && nodoValutato->right != NULL){
                printf("\n\n il nodo Ha un figlio destro\n\n");
                upo_bst_node_t* tmp = nodoValutato;
                parent->right = nodoValutato->right;
                free(tmp);
            }
                // se il nodo da eliminare ha un figlio SINISTRO    
            else if( nodoValutato->left != NULL && nodoValutato->right == NULL){
                printf("\n\n il nodo Ha un figlio sinitro\n\n");
                upo_bst_node_t* tmp = nodoValutato;
                parent->left = nodoValutato->left;
                free(tmp);
                //se il nodo da eliminare ha DUE FIGLI


            }else if(nodoValutato->left != NULL && nodoValutato->right != NULL){
                printf("\n\nkey: %d nodovalutato: %d nodovalutato.left: %d e nodovalutato right %d\n\n",*(unsigned char*) key, *(unsigned char*)nodoValutato->key, *(unsigned char*)nodoValutato->left->key,*(unsigned char*) nodoValutato->right->key );

                printf("\n\n il nodo Ha un DUE FIGLI\n\n");

                //tengo in memoria i figli del nodo da eliminare
                upo_bst_node_t* sonLeft = nodoValutato->left;
                upo_bst_node_t* sonRight = nodoValutato->right;

                //tengo in memoria il genitore del nodo da eliminare
                upo_bst_node_t* minParent = nodoValutato;

                //vado a prendere il nodo minimo SUCCESSORE che trovo
                upo_bst_node_t* min;
                //scendo una volta a destra per poi andare solo a sinistra per trovare il minimo
                    min = nodoValutato->right;
                while(min->left != NULL){
                    minParent = min;
                    min = min->left;
                }    
                printf("\n\n ho trovato il minimo successore: %d\n\n", *(unsigned char*) min->key ) ;

                //se il nodo da eliminare è un figlio sinistro
                if(tree->key_cmp(minParent->key, min->key) > 0){
                    minParent->left = NULL;
                    min->left = sonLeft;
                    min->right = sonRight;     
                    free(nodoValutato);
                    break;
                    
                // se il nodo da eliminare è un figlio destro
                }else{
                    minParent->right = NULL;
                    min->left = sonLeft;
                    min->right = sonRight;     
                    free(nodoValutato);
                    break;
                }
            }
        }

    }
    */
   if(tree == NULL || tree->root == NULL){
 
    printf("\nL'albero è vuoto o non esiste!\n");
    return;
   }


   tree->root = upo_delete_impl(tree, key, destroy_data, tree->root);
    return;

}
    
void count_right(upo_bst_node_t* nodo, size_t* size){
    if(nodo == NULL){
        return;
    }
    size++;
    count_right(nodo->right, size);
}

void count_left(upo_bst_node_t* nodo, size_t* size){
        if(nodo == NULL){
            return;
        }
        size++;
        count_left(nodo->left, size);
    }

size_t size_impl(upo_bst_node_t* nodo){

    if(nodo == NULL){
        return 0;
    }
    
    return 1 + size_impl(nodo->left) + size_impl(nodo->right);

}

size_t upo_bst_size(const upo_bst_t tree)
{
    if(upo_bst_is_empty(tree)){
        return 0;
    }

    return size_impl(tree->root);
}

int isLeaf(upo_bst_node_t* node){
    
    if(node->left == NULL && node->right == NULL){
        return 1;
    }
    else{
     return 0;
    }
}

size_t max(size_t a, size_t b) {
    return (a > b) ? a : b;
}

size_t height_imlp(upo_bst_node_t* node){
    
    if(node == NULL || isLeaf(node)){
        return 0;
    }

    return 1 + max(height_imlp(node->left), height_imlp(node->right));

}

size_t upo_bst_height(const upo_bst_t tree)
{
    size_t height = 0;
    height = height_imlp(tree->root);

    return height;

}

void traverse(upo_bst_node_t* node, upo_bst_visitor_t visit, void* visit_context){
    
    if(node == NULL)
        return;

    traverse(node->left, visit, visit_context);
        visit(node->key, node->value, visit_context);
    traverse(node->right, visit, visit_context);

}

void upo_bst_traverse_in_order(const upo_bst_t tree, upo_bst_visitor_t visit, void *visit_context)
{
    if (tree == NULL){
        return;
    }
    traverse(tree->root, visit, visit_context);
}

int upo_bst_is_empty(const upo_bst_t tree)
{
    if(tree == NULL || tree->root == NULL){
        return 1;
    }
    return 0;
}


/**** EXERCISE #1 - END of FUNDAMENTAL OPERATIONS ****/


/**** EXERCISE #2 - BEGIN of EXTRA OPERATIONS ****/

upo_bst_node_t* bst_min_impl(upo_bst_node_t* node){
    
    if(node->left == NULL){
        return node;
    }else{
        node = bst_min_impl(node->left);
    }
    return node;
}

void* upo_bst_min(const upo_bst_t tree)
{

    if(upo_bst_is_empty(tree)){
        return NULL;
    }else return bst_min_impl(tree->root)->key;
}

upo_bst_node_t* bst_max_impl(upo_bst_node_t* node){
    
    if(node->right == NULL){
        return node;
    }else{
        node = bst_max_impl(node->right);
    }
    return node;
}

void* upo_bst_max(const upo_bst_t tree)
{
    if(upo_bst_is_empty(tree)) return NULL;
    else return bst_max_impl(tree->root)->key;
}

void upo_bst_delete_min(upo_bst_t tree, int destroy_data)
{
    if(upo_bst_is_empty(tree)) return;
    upo_bst_delete(tree, upo_bst_min(tree) , destroy_data);
    return;
}

void upo_bst_delete_max(upo_bst_t tree, int destroy_data)
{
    if(upo_bst_is_empty(tree)) return;
    upo_bst_delete(tree, upo_bst_max(tree) , destroy_data);    
    return;
}

upo_bst_node_t* floor(upo_bst_t tree, void* key, upo_bst_node_t* node) {
    
    if (node == NULL) {
        return NULL; 
    }

    if (tree->key_cmp(key, node->key) < 0) {
        // Cerca a sinistra
        return floor(tree, key, node->left);
    } else if (tree->key_cmp(key, node->key) > 0) {
        // Cerca nel sottoalbero destro
        upo_bst_node_t* t = floor(tree, key, node->right);
        if (t != NULL) {
            return t; // Nodo trovato nel sottoalbero destro
        }
        return node; // Nessun nodo migliore trovato, ritorna il nodo corrente
    } else {
        return node; // La chiave è esattamente uguale
    }

}

// Restituisce la più grande chiave <= k
void* upo_bst_floor(const upo_bst_t tree, const void* key) {

    if (upo_bst_is_empty(tree)) {
        return NULL; // Albero vuoto, ritorna NULL
    }

    upo_bst_node_t* result = floor(tree, key, tree->root);
    return (result != NULL) ? result->key : NULL; // Ritorna la chiave trovata o NULL
}

upo_bst_node_t* ceiling(upo_bst_t tree, void* key, upo_bst_node_t* node) {
    if (node == NULL) {
        return NULL; // Nessun nodo valido trovato
    }

    if (tree->key_cmp(key, node->key) > 0) {
        // Cerca nel sottoalbero destro
        return ceiling(tree, key, node->right);
    } else if (tree->key_cmp(key, node->key) < 0) {
        // Cerca nel sottoalbero sinistro
        upo_bst_node_t* t = ceiling(tree, key, node->left);
        if (t != NULL) {
            return t; // Nodo trovato nel sottoalbero sinistro
        }
        return node; // Nessun nodo migliore trovato, ritorna il nodo corrente
    } else {
        return node; // La chiave è esattamente uguale
    }
}

// Restituisce la più piccola chiave >= k
void* upo_bst_ceiling(const upo_bst_t tree, const void* key) {
    if (upo_bst_is_empty(tree)) {
        return NULL; // Albero vuoto, ritorna NULL
    }

    upo_bst_node_t* result = ceiling(tree, key, tree->root);
    return (result != NULL) ? result->key : NULL; // Ritorna la chiave trovata o NULL
}

void range(upo_bst_t tree, upo_bst_key_list_t* node_list, void* low_key, void* high_key, upo_bst_node_t* node){
    
    if(node == NULL ) return;

    if (tree->key_cmp(low_key, node->key) < 0){
        range(tree, node_list, low_key, high_key, node->left);
    }
    
    if(tree->key_cmp(low_key, node->key) <= 0 && tree->key_cmp(high_key, node->key) >= 0 ){
        upo_bst_key_list_t newNodeList = malloc(sizeof(upo_bst_key_list_t));
        newNodeList->key = node->key;
        newNodeList->next = *node_list;
        *node_list = newNodeList;
    }

    if(tree->key_cmp(high_key, node->key) > 0 ){
       range(tree, node_list, low_key, high_key, node->right);
    }
}

upo_bst_key_list_t upo_bst_keys_range(const upo_bst_t tree, const void *low_key, const void *high_key)
{
    if(upo_bst_is_empty(tree)) return NULL;
    if(low_key == NULL || high_key == NULL) return NULL;

    //creo la testa della lista
    upo_bst_key_list_t head = NULL;
    range(tree, &head, low_key, high_key, tree->root);

    return head;
}



void keys_impl(upo_bst_t tree, upo_bst_key_list_t* list, upo_bst_node_t* node){

    if (node == NULL) return;

    keys_impl(tree, list, node->left);

    upo_bst_key_list_t nodeList = malloc(sizeof(upo_bst_key_list_t));

    nodeList->key = node->key;

    nodeList->next = *list;

    *list = nodeList;

    keys_impl(tree, list, node->right);

}


upo_bst_key_list_t upo_bst_keys(const upo_bst_t tree)
{
    if(upo_bst_is_empty(tree)) return NULL;

    upo_bst_key_list_t head = NULL;

    keys_impl( tree, &head, tree->root );
    
    return head; 

}


int bst_impl(const upo_bst_t tree, const void *min_key, const void *max_key, upo_bst_node_t* node){
   
    if(node == NULL) return 1;

    if(tree->key_cmp(node->key, min_key) <= 0 || tree->key_cmp(node->key, max_key) >= 0 ){
       return 0; 
    }

    return bst_impl(tree, min_key, node->key, node->left) && bst_impl(tree, node->key, max_key, node->right);
}


int upo_bst_is_bst(const upo_bst_t tree, const void *min_key, const void *max_key)
{
    if(upo_bst_is_empty(tree)) return 1;

    return bst_impl(tree, min_key, max_key, tree->root);
}


/**** EXERCISE #2 - END of EXTRA OPERATIONS ****/


upo_bst_comparator_t upo_bst_get_comparator(const upo_bst_t tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    return tree->key_cmp;
}
