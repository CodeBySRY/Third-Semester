#include <iostream>
using namespace std;

void DisplayArr(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }

    cout << endl;
}

void SelectionSort(int arr[], int size) {
    // SELECT a minimum index element, and sort
    int min;

    for (int i = 0; i < size; i++) {
        min = i;

        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }

        if (min != i) {
            int temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
}

void InsertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;

    }
}

void BubbleSort(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}



int main() {

    int arr[7] = {7, 6, 5, 4, 3, 2, 1};

    cout << "BEFORE: ";
    DisplayArr(arr, 7);
    cout << endl;

    BubbleSort(arr, 7);

    cout << "AFTER: ";
    DisplayArr(arr, 7);


    return 0;
}