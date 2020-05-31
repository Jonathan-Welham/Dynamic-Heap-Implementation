/*
 * HackerRank link: https://www.hackerrank.com/contests/cst370-s20-hw9/challenges/max-heap-1-2/submissions/code/1322917448
 * Title: hw9_1.cpp
 * Abstract: This program is a template for heap operations
 * Author: Jonathan Welham
 * ID: 6781
 * Date: 04/20/2020
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Function declarations
void commands();
void heapify(int* arr, int n, int i);
void buildHeap(int* arr, int n);
void display(int* arr, int n);
void insert(int newVal);
void deleteMax();
void deleteValue(int deleteVal);

//GLOBALS
int* arr = NULL;
int size = 0;

int main()
{
    if(arr){
        //I put this here for repeatability. If the program crashes without reaching the delete[] at the end
        //then there will be a problem with the memory, causing the program to crash.
        delete[] arr;
        arr = NULL;
    }

    int n;
    cin >> n;

    size = n;
    arr = new int[n];

    int temp;
    int largest;
    bool isMaxHeap = true;

    for(int i = 0; i < n; i++){
        cin >> temp;
        if(i == 0){
            largest = temp;
        }
        else if(temp > largest){
            isMaxHeap = false;
        }
        arr[i] = temp;
    }

    if(!isMaxHeap){
        cout << "This is NOT a heap.\n";
        buildHeap(arr, n);
    }
    else{
        cout << "This is a heap.\n";
    }

    int numCommands;
    cin >> numCommands;

    for(int i = 0; i < numCommands; i++){
        commands();
    }

    delete[] arr;
    return 0;
}

void commands(){
    string temp;
    cin >> temp;

    if(temp == "displayMax"){
        if (size != 0) {
            cout << arr[0] << endl;
        }
    }

    else if(temp == "deleteMax"){
        if (size != 0) {
            deleteMax();
        }
    }

    else if(temp == "insert"){
        int newVal;
        cin >> newVal;
        if (size != 0) {
            insert(newVal);
        } else {
            //size will == 0 so we need to update the size and append the new value
            size++;
            arr[0] = newVal;
        }
    }

    else if(temp =="display"){
        if (size != 0) {
            display(arr, size);
        }
    }

    else if(temp == "update"){
        if (size != 0) {
            int index;
            int val;
            cin >> index >> val;
            arr[index - 1] = val;
            buildHeap(arr, size);
        }
    }

    else if(temp == "delete"){
        if (size != 0) {
            int deleteVal;
            cin >> deleteVal;
            deleteValue(deleteVal);
        }
    }

}

//From: https://www.geeksforgeeks.org/building-heap-from-array/

// To heapify a subtree rooted with node i which is
// an index in arr[]. N is size of heap
void heapify(int* arr, int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Function to build a Max-Heap from the given array
void buildHeap(int* arr, int n)
{
    // Index of last non-leaf node
    int startIdx = (n / 2) - 1;

    // Perform reverse level order traversal
    // from last non-leaf node and heapify
    // each node
    for (int i = startIdx; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

void display(int* arr, int n){
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

void insert(int newVal){
    int temp[size];

    //Copy the current contents of the dynamic array into a temporary array
    for(int i = 0; i < size; i++){
        temp[i] = arr[i];
    }

    //Delete the dynamic array and increase the size by 1
    //new dynamic array assigned with a size of 1 bigger
    delete[] arr;
    arr = NULL;
    size++;
    arr = new int[size];

    //Copy the temporary array values into the new dynamic array up to the new size - 1
    for(int i = 0; i < size-1; i++){
        arr[i] = temp[i];
    }

    //Append the new value at the end of the dynamic array and build the heap
    arr[size-1] = newVal;
    buildHeap(arr, size);
}

void deleteMax(){
    //value of last index is held in a temp variable
    int temp = arr[size-1];
    //last index is overwritten with root value
    arr[size-1] = arr[0];
    //root value is now the value of the last index
    arr[0] = temp;

    //declare a temp array with 1 less of previous size
    size--;
    int tempArr[size];

    //Copy the current contents of the dynamic array into a temporary array up to but not including the last index
    for(int i = 0; i < size; i++){
        tempArr[i] = arr[i];
    }

    //delete the dynamic memory and create a new dynamic array with size of 1 less than previous.
    delete[] arr;
    arr = NULL;
    arr = new int[size];

    //Copy the temporary array values into the new dynamic array up to the new size - 1
    for(int i = 0; i < size; i++){
        arr[i] = tempArr[i];
    }

    //construct the new heap
    buildHeap(arr, size);
}

void deleteValue(int deleteVal){

    //Scan the array to find the value we are looking for
    for(int i = 0; i < size; i++){
        if(arr[i] == deleteVal){
            int temp = arr[size-1];
            arr[size-1] = arr[i];
            arr[i] = temp;
            continue;
        }
    }

    //declare a temp array with 1 less of previous size
    size--;
    int tempArr[size];

    //Copy the current contents of the dynamic array into a temporary array up to but not including the last index
    for(int i = 0; i < size; i++){
        tempArr[i] = arr[i];
    }

    //delete the dynamic memory and create a new dynamic array with size of 1 less than previous.
    delete[] arr;
    arr = NULL;
    arr = new int[size];

    //Copy the temporary array values into the new dynamic array up to the new size - 1
    for(int i = 0; i < size; i++){
        arr[i] = tempArr[i];
    }

    //construct the new heap
    buildHeap(arr, size);


}