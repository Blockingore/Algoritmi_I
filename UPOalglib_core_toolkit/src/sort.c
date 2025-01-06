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

#include <assert.h>
#include "sort_private.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/utility.h>


void upo_insertion_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    unsigned char* pc_base = (unsigned char*) base;

    size_t j;


    for(size_t i = 1; i < n; i++){
          j = i;
       while( j > 0 ){
       if( cmp( (void*) (pc_base + (j-1) * size ), (void*) (pc_base + j* size )) <= 0) {
            break;
       }
           upo_swap( (void*) (pc_base + (j-1) * size ) , (void*) (pc_base + j * size), size  );
            j--;
        
       }
    }
}


void upo_merge(void* base, size_t low, size_t mid, size_t high, size_t size, upo_sort_comparator_t cmp){
            
            size_t i = low;
            size_t j = mid + 1; 

            size_t k = 0;

            void* aux = malloc((high + 1) * size ); 

            memcpy((unsigned char*) aux, (unsigned char*)base + (low * size), (high - low + 1) * size); 

            while(i <= mid && j <= high){
                if(cmp((unsigned char*) aux + ( i - low) * size, (unsigned char*) aux + (j - low) * size ) <= 0  ){
                    memcpy( (unsigned char*) base + (k + low) * size  , (unsigned char*) aux + (i - low) * size , size );
                    i++;
                }else{
                    memcpy( (unsigned char*) base + ((k + low) * size), (unsigned char*) aux + ((j - low) * size), size );
                    j++;
                }
                k++;
            }

            while(i <= mid){
                memcpy( (unsigned char*) base + (k + low) * size , (unsigned char*) aux + (i - low) * size , size );
                i++;
                k++;
            }

            while(j <= high){
                memcpy( (unsigned char*) base + (k + low) * size, (unsigned char*) aux + (j - low) * size, size );
                j++;
                k++;
            }

    free(aux);
        }


    void upo_merge_sort_Rec(void* base, size_t low, size_t high, size_t size, upo_sort_comparator_t cmp){
        if(low >= high) return;

        size_t mid = (low + high) / 2;

        upo_merge_sort_Rec(base, low, mid, size, cmp);
        upo_merge_sort_Rec(base, mid + 1, high, size, cmp);
        upo_merge(base, low, mid, high, size, cmp);
    }

void upo_merge_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp) {
    
    if (n < 2) return;

    upo_merge_sort_Rec(base, 0, n-1, size, cmp);

    /*
    unsigned char* stampa = base;
    for(size_t k = 0; k < n-1; k++ ){
        printf("%ld ", *(int*) stampa + (k*size));
    }
        printf("\n\nHO FINITO IL MERGE\n\n");
    */

}


void upo_quick_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
      // da fare 
}



/*
// Funzione ausiliaria per la fusione
void upo_merge(void *base, size_t lo, size_t mid, size_t hi, size_t size, void *temp, upo_sort_comparator_t cmp) {

    // lo = 0
    // mid = 0
    // hi = 1

    size_t i = lo; // i punta alla parte sinistra dell'array 
    size_t j = mid + 1; // j punta alla parte destra dell'array 
    size_t k = 0; //indice dell'array finale

    // Copia temporanea dei dati nell'array temp
    memcpy(temp, (unsigned char *)base + lo * size, (hi - lo + 1) * size); 
    //memcpy(array_temporaneo,
      //          puntatore al primo carattere di array_da_copiare,
         //       numero di elementi dell'array);
    


    // ciclo finchè ho elementi da guardare
    while (i <= mid && j <= hi) { 
        
        //controllo il primo elemento di sinistra (i)  con il primo elemento di destra (j);
        if (cmp((unsigned char *)temp + (i - lo) * size, (unsigned char *)temp + (j - lo) * size) <= 0) { 

            // se è piu piccolo allora lo copio come elemento in base[k]
            memcpy((unsigned char *)base + (k + lo) * size, (unsigned char *)temp + (i - lo) * size, size);
            i++;

        } else {
            
            // altrimenti copio l'elemento di destra come elemento in base[k]
            memcpy((unsigned char *)base + (k + lo) * size, (unsigned char *)temp + (j - lo) * size, size);
            j++;
        }
        k++;
    }

    // Copia elementi rimanenti
    while (i <= mid) {
        memcpy((unsigned char *)base + (k + lo) * size, (unsigned char *)temp + (i - lo) * size, size);
        i++;
        k++;
    }

    while (j <= hi) {
        memcpy((unsigned char *)base + (k + lo) * size, (unsigned char *)temp + (j - lo) * size, size);
        j++;
        k++;
    }
}

// Funzione ricorsiva per Merge Sort
void upo_merge_sort_rec(void *base, size_t lo, size_t hi, size_t size, void *temp, upo_sort_comparator_t cmp) { 
    if (lo >= hi)
        return;

    size_t mid = (lo + hi) / 2;

    // Chiamate ricorsive per le due metà
    upo_merge_sort_rec(base, lo, mid, size, temp, cmp);
    upo_merge_sort_rec(base, mid + 1, hi, size, temp, cmp);

    // Fusione delle due metà
    upo_merge(base, lo, mid, hi, size, temp, cmp);
}

// Funzione principale
void upo_merge_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp) {
    if (n < 2) return; // Nessun elemento da ordinare o un solo elemento

    // Array temporaneo per la fusione
    void *temp = malloc(n * size);
    if (temp == NULL) return; // Controllo allocazione memoria

    // Chiamata alla funzione ricorsiva
    upo_merge_sort_rec(base, 0, n - 1, size, temp, cmp);

    // Libera la memoria temporanea
    free(temp);


    for(size_t k = 0; k < n-1; k++ ){
        printf("%ld ", *(int*) stampa + (k*size));
    }
        printf("\n\nHO FINITO IL MERGE\n\n");

}

*/


