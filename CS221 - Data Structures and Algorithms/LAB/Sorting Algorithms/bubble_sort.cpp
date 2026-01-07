#include <iostream>
using namespace std;



void BubbleSort(int arr[], int size) {
    int temp;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
            temp = arr[j];
            arr[j] = arr[j+1];
            arr[j+1] = temp;
            }
        
        } // corresponds to the inner for loop
    } // corresponds to the outer for loop
}

void DisplayArr(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
}




int main() {
    
    int myArr[5] = {12, 5, 6, 9, 2};
    cout << "BEFORE Sorting: ";
    DisplayArr(myArr, 5);
    BubbleSort(myArr, 5);
    
    
    cout << endl;
    
    cout << "Displaying the sorted arr: ";
    DisplayArr(myArr, 5);
    
    return 0;
}
