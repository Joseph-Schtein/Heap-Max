#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define SIZEARR 32


typedef struct maxHeap{

    int *arr;
    int size;
    int capacity;
    void (*addHeap)(struct maxHeap *mh, int data);
    void (*extractHeap)(struct maxHeap *mh);
    void (*tostring)(struct maxHeap *mh);

}maxHeap;


void swap(int *x, int *y){
    *x = *x + *y;
    *y = *x - *y;
    *x = *x - *y;
}

void add(maxHeap *mh, int data){
    if(mh->size == -1){
        mh->arr[0] = data;
        mh->size++;
    }

    else{
        if(mh->capacity - 1 == mh->size){
            mh->arr = realloc(mh->arr, mh->capacity*2);
            mh->capacity *= 2;
        }
        
        int index = mh->size+1;
        mh->arr[index] = data;
        mh->size++;

        while(index != 0 && mh->arr[(index-1)/2] < mh->arr[index]){
            swap(&mh->arr[(index-1)/2], &mh->arr[index]);
            index = (index-1)/2;
        }
        
    }

}

void extractMax(maxHeap *mh){
    if(mh->size >= 0){    
        swap(&mh->arr[0], &mh->arr[mh->size]);
        mh->arr[mh->size] = 0;
        mh->size--;  

        int indexChange = 0;   
        int bool = TRUE;
        while(bool){    
            int right = 2*indexChange+2;
            int left = 2*indexChange+1;
            if(left < mh->size && right <= mh->size){
                if(mh->arr[left] > mh->arr[right]){
                    if(mh->arr[left] > mh->arr[indexChange]){
                        swap(&mh->arr[left], &mh->arr[indexChange]);
                        indexChange = left;
                    }
                    else{
                        bool = FALSE;
                    }    
                }

                else{
                    if(mh->arr[right] > mh->arr[indexChange]){
                        swap(&mh->arr[right], &mh->arr[indexChange]);
                        indexChange = right;
                    }
                    else{
                        bool = FALSE;
                    }    
                }    
            }

            else if(left <= mh->size){
                if(mh->arr[left] > mh->arr[indexChange]){
                    swap(&mh->arr[left], &mh->arr[indexChange]);
                    indexChange = left;
                }
                
                else{
                    bool = FALSE;
                }        
            }
            else{
                bool = FALSE;
            }   


        }

    } 
}

void toString(maxHeap *mh){
    for(int i = 0; i < mh->size; i++){
        printf("%d, ", mh->arr[i]);
    }
    printf("%d\n", mh->arr[mh->size]);
    
}


maxHeap initilize(){

    maxHeap output;
    output.size = -1;
    output.addHeap = add;
    output.extractHeap = extractMax;
    output.tostring = toString;
    output.capacity = SIZEARR;
    output.arr = (int*)malloc(SIZEARR*4);
    for(int i = 0; i < SIZEARR; i++){
        output.arr[i] = -10000000;
    }
    return output;
}


int main(){
    maxHeap max = initilize();
    max.addHeap(&max, 7);
    max.addHeap(&max, -9);
    max.addHeap(&max, 1);
    max.addHeap(&max, -8);
    max.tostring(&max);
    max.extractHeap(&max);
    max.tostring(&max);
    return 0;
}

