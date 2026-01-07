#include <iostream>
using namespace std;

void DisplayArr(int arr[], int size) {
    cout << "Array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int SmallestNum(int arr[], int size) {
    int tempSmallest = arr[0];
    for (int i = 1; i < size; i++) {
        if (tempSmallest > arr[i]) {
            tempSmallest = arr[i];
        }
      
    }

    return tempSmallest; // Return AFTER checking all elements;
    
}

int main() {

    int arr1[5] = {95, 10, 15, 20, 25};
    int arr2[5] = {99, 12, 9, 5, 2};
    int arr3[5] = {97, 3, 18, 4, 22};
    int smallest1 = SmallestNum(arr1, 5);
    int smallest2 = SmallestNum(arr2, 5);
    int smallest3 = SmallestNum(arr3, 5);

    DisplayArr(arr1, 5);
    cout << "The smallest number in the array is: " << smallest1 << endl;
    
    DisplayArr(arr2, 5);
    cout << "The smallest number in the array is: " << smallest2 << endl;

    DisplayArr(arr3, 5);
    cout << "The smallest number in the array is: " << smallest3 << endl;

    return 0;

}