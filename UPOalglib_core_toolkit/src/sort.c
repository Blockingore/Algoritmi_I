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

size_t upo_partition(void* base,size_t size,size_t lo,size_t hi,upo_sort_comparator_t cmp){
    unsigned char* ptb = base;
    size_t p = lo, i=lo, j=hi+1;

    while(1){
        do{
            i++;
        }while((i<hi) && (cmp(ptb + i * size,ptb + p * size) < 0) );
    
        do{
            j--;
        }while((j>lo) && (cmp(ptb + j * size,ptb + p * size) > 0) );
    
        if(i >= j){
            break;
        }
        upo_swap(ptb + i * size, ptb + j * size, size);
    }
    upo_swap(ptb + p * size, ptb + j * size, size);
    return j;
}


void upo_quick_sortRec(void* base, size_t size, size_t lo, size_t hi, upo_sort_comparator_t cmp){
    //caso base
    if (lo >= hi) return;

    size_t j = upo_partition(base, size, lo, hi, cmp);

    if(j > 0){
        upo_quick_sortRec(base, size, lo, j-1, cmp);
    }
    upo_quick_sortRec(base, size, j+1, hi, cmp);
}





void upo_quick_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    if(base != NULL)
        upo_quick_sortRec(base, size, 0, n-1, cmp);      
}

