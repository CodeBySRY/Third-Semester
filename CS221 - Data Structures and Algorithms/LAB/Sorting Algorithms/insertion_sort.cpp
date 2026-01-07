#include <iostream>
using namespace std;



void InsertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i-1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        
        arr[j+1] = key;
    }
}

void DisplayArr(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
}




int main() {
    
    int myArr[5] = {37, 5, 6, 9, 2};
    cout << "BEFORE Sorting: ";
    DisplayArr(myArr, 5);
    InsertionSort(myArr, 5);
    
    
    cout << endl;
    
    cout << "Displaying the sorted arr: ";
    DisplayArr(myArr, 5);
    
    return 0;
}
