// CS2255_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

// Function prototypes
void selectionSort(vector<int>& arr);
void mergeSort(vector<int>& arr, int left, int right);
void merge(vector<int>& arr, int left, int mid, int right);
void bubbleSort(vector<int>& arr);
void printArray(const vector<int>& arr);
void saveToFile(const vector<int>& arr, const string& filename);
void runAlgorithm(vector<int>& arr, int choice);
void shuffleArray(vector<int>& arr, int size);
void handleImportFile(vector<int>& arr);
void handleChooseAlgorithm(vector<int>& arr);
void handleSaveToFile(vector<int>& arr);
void handleCompareAlgorithms(vector<int>& arr);

int main() {
    int option;
    vector<int> arr;

    // Display menu
    cout << "Menu:" << endl;
    cout << "5. Import a .txt file with a sequence of numbers (minimum 10,000 elements)." << endl;
    cout << "6. Choose a sorting algorithm (1 - Selection Sort, 2 - Merge Sort, 3 - Bubble Sort)." << endl;
    cout << "7. Save sorted result to a file and display execution time." << endl;
    cout << "8. Compare execution time of all three algorithms with different input sizes." << endl;

    while (true) {
        cout << "Enter option: ";
        cin >> option;

        switch (option) {
        case 5:
            handleImportFile(arr);
            break;
        case 6:
            handleChooseAlgorithm(arr);
            break;
        case 7:
            handleSaveToFile(arr);
            break;
        case 8:
            handleCompareAlgorithms(arr);
            break;
        default:
            cout << "Invalid option. Try again." << endl;
            break;
        }
    }

    return 0;
}

void handleImportFile(vector<int>& arr) {
    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    int num;
    while (inputFile >> num) {
        arr.push_back(num);
    }

    cout << "File imported successfully." << endl;
}

void handleChooseAlgorithm(vector<int>& arr) {
    int sortingAlgorithm;
    cout << "Choose sorting algorithm (1 - Selection Sort, 2 - Merge Sort, 3 - Bubble Sort): ";
    cin >> sortingAlgorithm;

    runAlgorithm(arr, sortingAlgorithm);
}

void handleSaveToFile(vector<int>& arr) {
    if (arr.empty()) {
        cout << "Please import a file first." << endl;
        return;
    }

    string outputFilename;
    cout << "Enter output filename: ";
    cin >> outputFilename;

    clock_t start = clock();

    saveToFile(arr, outputFilename);

    clock_t stop = clock();
    double duration = static_cast<double>(stop - start) / CLOCKS_PER_SEC;
    cout << "Execution time: " << duration * 1000 << " milliseconds." << endl;
}

void handleCompareAlgorithms(vector<int>& arr) {
    int inputSizes[] = { 10000, 100000, 1000000 };

    for (int size : inputSizes) {
        // Generate random input
        arr.clear();
        shuffleArray(arr, size);

        // Compare execution time for each algorithm
        cout << "Input size: " << size << endl;
        for (int i = 1; i <= 3; ++i) {
            runAlgorithm(arr, i);
        }
        cout << "------------------------" << endl;
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        }
        else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }
}

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

void saveToFile(const vector<int>& arr, const string& filename) {
    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        for (int num : arr) {
            outputFile << num << " ";
        }
        cout << "Sorted data saved to " << filename << endl;
    }
    else {
        cout << "Error saving to file." << endl;
    }
}

void runAlgorithm(vector<int>& arr, int choice) {
    clock_t start = clock();

    switch (choice) {
    case 1:
        selectionSort(arr);
        cout << "Selection Sort executed." << endl;
        break;
    case 2:
        mergeSort(arr, 0, arr.size() - 1);
        cout << "Merge Sort executed." << endl;
        break;
    case 3:
        bubbleSort(arr);
        cout << "Bubble Sort executed." << endl;
        break;
    default:
        cout << "Invalid algorithm choice." << endl;
        break;
    }

    clock_t stop = clock();
    double duration = static_cast<double>(stop - start) / CLOCKS_PER_SEC;
    cout << "Execution time: " << duration * 1000 << " milliseconds." << endl;
}

void shuffleArray(vector<int>& arr, int size) {
    arr.clear();
    for (int i = 1; i <= size; ++i) {
        arr.push_back(i);
    }

    // Fisher-Yates shuffle algorithm
    for (int i = size - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(arr[i], arr[j]);
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
