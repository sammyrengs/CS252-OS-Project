#include <iostream>
#include <stdlib.h>
#include <pthread.h>
using namespace std;

#define N 12 //size of array to be sorted

int unsorted_arr[] = {78, 3, 6, 91, 1, 43, 26, 54, 12, 39, 81, 66};
int sorted_arr[N];

//sorting params
typedef struct{
    int start_idx;
    int end_idx;
} sorting_parameters;

//merging params
typedef struct{
    int first_start;
    int first_end;
    int second_start;
    int second_end;
} merging_parameters;

//bubble sort algorithm
void *sorting(void *params){
    sorting_parameters *sorting_worker = (sorting_parameters *) params;
    int start_idx = sorting_worker->start_idx;
    int end_idx = sorting_worker->end_idx;
    for(int i=0; i<(end_idx-start_idx); i++){
        for(int j=start_idx; j<end_idx-i-1;j++){
            if(unsorted_arr[j]>unsorted_arr[j+1]){
                swap(unsorted_arr[j],unsorted_arr[j+1]);
            }
        }
    }
    pthread_exit(0);
}

//function to merge the two sorted halves
void *merging(void *params){
    merging_parameters *merging_worker = (merging_parameters *)params;
    int first_start = merging_worker->first_start;
    int first_end = merging_worker->first_end;
    int second_start = merging_worker->second_start;
    int second_end = merging_worker->second_end;
    int i = first_start, j = second_start, k = 0;
    while(i<first_end && j<second_end){
        if(unsorted_arr[i]<unsorted_arr[j]){
            sorted_arr[k++] = unsorted_arr[i++];
        } else {
            sorted_arr[k++] = unsorted_arr[j++];
        }
    }
    if(i>=first_end && j<second_end){
        while(j<second_end)
            sorted_arr[k++] = unsorted_arr[j++];
    } else{
        while(i<first_end)
            sorted_arr[k++] = unsorted_arr[i++];
    }
    pthread_exit(0);
}


int main()
{
    
    cout<<"Unsorted Array: ";
    for(int i=0;i<N;i++)
        cout<<unsorted_arr[i]<<" ";
    cout<<"\n";
    //creating the threads
    pthread_t first_thread, second_thread, merging_thread;
    
    //passing params to sorting thread 1
    sorting_parameters *first_half = (sorting_parameters *)malloc(sizeof(sorting_parameters));
    first_half->start_idx = 0;
    first_half->end_idx = N/2;

    //passing params to sorting thread 2
    sorting_parameters *second_half = (sorting_parameters *)malloc(sizeof(sorting_parameters));
    second_half->start_idx = N/2;
    second_half->end_idx = N;

    //passing params to merging thread
    merging_parameters *merge = (merging_parameters *)malloc(sizeof(merging_parameters));
    merge->first_start = 0;
    merge->first_end = N/2;
    merge->second_start = N/2;
    merge->second_end = N;

    //creating the pthreads pthread_create(pthread_t, pthread_attr(NULL, pthread function, copy of struct for pthread))
    pthread_create(&first_thread, NULL, sorting, (void *)first_half);
    pthread_create(&second_thread, NULL, sorting, (void *)second_half);
    pthread_create(&merging_thread,NULL, merging, (void *)merge);
    
    //wating for threads to exit
    pthread_join(first_thread,NULL);
    pthread_join(second_thread,NULL);
    pthread_join(merging_thread,NULL);
    

    
    cout<<"Sorted Array: ";
    for(int i=0; i<N;i++)
        cout<<sorted_arr[i]<<" ";
    cout<<"\n";

    return 0;
}