// CS2255_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Algorithm {
	private:
		vector<int> arr;
		int sizeOfArr;
		double duration;
	public:
		Algorithm() {
			
		}
		
		Algorithm(vector<int>& arr, int sizeOfArr) {
			this->arr = arr;
			sizeOfArr = arr.size();
		}
		
		vector<int>& getArr() {
			return arr;
		}
		
		void setArr(vector<int>& arr) {
			this->arr = arr;
		}
		
		int getSizeOfArr() {
			return sizeOfArr;
		}
		
		void setSizeOfArr() {
			sizeOfArr = arr.size();
		}
		
		double getDuration() {
			return duration;
		}
		
		void setDuration(double duration) {
			this->duration = duration;
		}
		
		void selectionSort() {
			setSizeOfArr();
		    for (int i = 0; i < sizeOfArr - 1; ++i) {
		        int minIndex = i;
		        for (int j = i + 1; j < sizeOfArr; ++j) {
		            if (arr[j] < arr[minIndex]) {
		                minIndex = j;
		            }
		        }
		        swap(arr[i], arr[minIndex]);
		    }
		}
		
		void mergeSort(int left, int right) {
		    if (left < right) {
		        int mid = left + (right - left) / 2;
		        mergeSort(left, mid);
		        mergeSort(mid + 1, right);
		        merge(left, mid, right);
		    }
		}
		
		void merge(int left, int mid, int right) {
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
		
		void bubbleSort() {
			setSizeOfArr();
		    for (int i = 0; i < sizeOfArr - 1; ++i) {
		        for (int j = 0; j < sizeOfArr - i - 1; ++j) {
		            if (arr[j] > arr[j + 1]) {
		                swap(arr[j], arr[j + 1]);
		            }
		        }
		    }
		}
		
		void handleChooseAlgorithm() {
		    int sortingAlgorithm;
		    cout << "Choose sorting algorithm (1 - Selection Sort, 2 - Merge Sort, 3 - Bubble Sort): ";
		    cin >> sortingAlgorithm;
		
		    runAlgorithm(sortingAlgorithm);
		}
		
		void handleCompareAlgorithms() {
		    int inputSizes[] = { 10000, 100000, 1000000 };
		
		    for (int size : inputSizes) {
		        // Generate random input
		        arr.clear();
		        shuffleArray(size);
		
		        // Compare execution time for each algorithm
		        cout << "Input size: " << size << endl;
		        for (int i = 1; i <= 3; ++i) {
		            runAlgorithm(i);
		        }
		        cout << "------------------------" << endl;
		    }
		}
		
		void runAlgorithm(int choice) {
		    clock_t start = clock();
		
		    switch (choice) {
		    case 1:
		        selectionSort();
		        cout << "Selection Sort executed." << endl;
		        break;
		    case 2:
		        mergeSort(0, arr.size() - 1);
		        cout << "Merge Sort executed." << endl;
		        break;
		    case 3:
		        bubbleSort();
		        cout << "Bubble Sort executed." << endl;
		        break;
		    default:
		        cout << "Invalid algorithm choice." << endl;
		        break;
		    }
		
		    clock_t stop = clock();
		    duration = static_cast<double>(stop - start) / CLOCKS_PER_SEC;
		    cout << "Execution time: " << duration * 1000 << " milliseconds." << endl;
		}
		
		void shuffleArray(int size) {
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
};

class File : public Algorithm{
	private: 
		string fileName;
	public:
		File() : Algorithm (){
			
		}
		
		File(string fileName, vector<int> arr, int sizeOfArr) : Algorithm(arr, sizeOfArr) {
			this->fileName = fileName;
		}
		string getFileName() {
			return fileName;
		}
		
		void setFileName(string fileName) {
			this->fileName = fileName;
		}
		
		void handleGenerateFile() {
		    // Number of elements
//		    int num_elements = 15000;
			int num_elements;
			cout << "Enter elements of .txt file: ";
			
			cin >> num_elements;
			
			if (num_elements < 10000) {
				cout << "Number of elements of .txt file must greater than 10,000!" << endl; 
				return;
			}
		
		    // Set seed to generate random numbers
		    srand(time(0));
		
		    // Generate random number sequence
		    vector<int> random_numbers;
		    for (int i = 0; i < num_elements; ++i) {
		        random_numbers.push_back(std::rand() % 1000000 + 1);
		    }
		
		    // Save to .txt file
		    cout << "Enter filename: ";
		    cin >> fileName;
		    
		    ofstream file(fileName);
		    if (file.is_open()) {
		        for (int number : random_numbers) {
		            file << number << " ";
		        }
		        file.close();
		        cout << "The .txt file has been created successfully." << endl;
		    }
		    else {
		        cerr << "Cannot open file for recording." << endl;
		        exit(0);
		    }
		}
		
		void handleImportFile() {
//		    string filename;
		    cout << "Enter filename: ";
		    cin >> fileName;
		
		    ifstream inputFile(fileName);
		    if (!inputFile.is_open()) {
		        cout << "Error opening file." << endl;
		        return;
		    }
		
		    int num;
		    while (inputFile >> num) {
		        getArr().push_back(num);
		    }
		    
			setSizeOfArr();
			
			if (getSizeOfArr() < 10000) {
				cout << "Number of elements of input_data.txt must greater than 10,000!" << endl; 
				getArr().clear();
				return;
			}
		
		    cout << "File imported successfully." << endl;
		}
		
		void handleSaveToFile() {
		    if (getArr().empty()) {
		        cout << "Please import a file first." << endl;
		        return;
		    }
		
//		    string outputFilename;
		    cout << "Enter output filename: ";
		    cin >> fileName;
		
//		    clock_t start = clock();
		
		    saveToFile();
		
//		    clock_t stop = clock();
//		    double duration = static_cast<double>(stop - start) / CLOCKS_PER_SEC;
		    cout << "Execution time: " << getDuration() * 1000 << " milliseconds." << endl;
		}
		
		
		void saveToFile() {
		    ofstream outputFile(fileName);
		    if (outputFile.is_open()) {
		        for (int num : getArr()) {
		            outputFile << num << " ";
		        }
		        cout << "Sorted data saved to " << fileName << endl;
		    }
		    else {
		        cout << "Error saving to file." << endl;
		    }
		}
};

// Function prototypes
//void selectionSort(vector<int>& arr);
//void mergeSort(vector<int>& arr, int left, int right);
//void merge(vector<int>& arr, int left, int mid, int right);
//void bubbleSort(vector<int>& arr);
//void printArray(const vector<int>& arr);
//void saveToFile(const vector<int>& arr, const string& filename);
//void runAlgorithm(vector<int>& arr, int choice);
//void shuffleArray(vector<int>& arr, int size);
//void handleImportFile(vector<int>& arr);
//void handleChooseAlgorithm(vector<int>& arr);
//void handleSaveToFile(vector<int>& arr);
//void handleCompareAlgorithms(vector<int>& arr);
//void handleGenerateFile();

void menu() {
    cout << "Menu:" << endl;
    cout << "4. Generate file .txt with a sequence of numbers (minimum 10,000 elements)." << endl;
    cout << "5. Import a .txt file with a sequence of numbers (minimum 10,000 elements)." << endl;
    cout << "6. Choose a sorting algorithm (1 - Selection Sort, 2 - Merge Sort, 3 - Bubble Sort)." << endl;
    cout << "7. Save sorted result to a file and display execution time." << endl;
    cout << "8. Compare execution time of all three algorithms with different input sizes." << endl;
    cout << "9. Exit" << endl;
}

int main() {
    int option;
	File file;
	
//	vector<int> arr = file.getArr();

    // Display menu
    menu();

    while (true) {
        cout << "Enter option: ";
        cin >> option;

        switch (option) {
        case 4:
//            handleGenerateFile();
			file.handleGenerateFile();
            break;
        case 5:
//            handleImportFile(arr);
			file.handleImportFile();
//			algorithm.setArr(file.getArr());
            break;
        case 6:
        	file.handleChooseAlgorithm();
//        	file.setArr(algorithm.getArr());
//            handleChooseAlgorithm(arr);
            break;
        case 7:
            file.handleSaveToFile();
            break;
        case 8:
            file.handleCompareAlgorithms();
            break;
        case 9: 
            cout << "Goodbye" << endl;
            exit(0);
        default:
            cout << "Invalid option. Try again." << endl;
            break;
        }
    }

    return 0;
}

//void handleGenerateFile() {
//    // Number of elements
//    int num_elements = 15000;
//
//    // Set seed to generate random numbers
//    std::srand(std::time(0));
//
//    // Generate random number sequence
//    std::vector<int> random_numbers;
//    for (int i = 0; i < num_elements; ++i) {
//        random_numbers.push_back(std::rand() % 1000000 + 1);
//    }
//
//    // Save to .txt file
//    std::ofstream file("input_data.txt");
//    if (file.is_open()) {
//        for (int number : random_numbers) {
//            file << number << " ";
//        }
//        file.close();
//        cout << "The input_data.txt file has been created successfully." << endl;
//    }
//    else {
//        cerr << "Cannot open file for recording." << endl;
//        exit(0);
//    }
//}
//
//void handleImportFile(vector<int>& arr) {
//    string filename;
//    cout << "Enter filename: ";
//    cin >> filename;
//
//    ifstream inputFile(filename);
//    if (!inputFile.is_open()) {
//        cout << "Error opening file." << endl;
//        return;
//    }
//
//    int num;
//    while (inputFile >> num) {
//        arr.push_back(num);
//    }
//
//    cout << "File imported successfully." << endl;
//}
//
//void handleChooseAlgorithm(vector<int>& arr) {
//    int sortingAlgorithm;
//    cout << "Choose sorting algorithm (1 - Selection Sort, 2 - Merge Sort, 3 - Bubble Sort): ";
//    cin >> sortingAlgorithm;
//
//    runAlgorithm(arr, sortingAlgorithm);
//}
//
//void handleSaveToFile(vector<int>& arr) {
//    if (arr.empty()) {
//        cout << "Please import a file first." << endl;
//        return;
//    }
//
//    string outputFilename;
//    cout << "Enter output filename: ";
//    cin >> outputFilename;
//
//    clock_t start = clock();
//
//    saveToFile(arr, outputFilename);
//
//    clock_t stop = clock();
//    double duration = static_cast<double>(stop - start) / CLOCKS_PER_SEC;
//    cout << "Execution time: " << duration * 1000 << " milliseconds." << endl;
//}
//
//void handleCompareAlgorithms(vector<int>& arr) {
//    int inputSizes[] = { 10000, 100000, 1000000 };
//
//    for (int size : inputSizes) {
//        // Generate random input
//        arr.clear();
//        shuffleArray(arr, size);
//
//        // Compare execution time for each algorithm
//        cout << "Input size: " << size << endl;
//        for (int i = 1; i <= 3; ++i) {
//            runAlgorithm(arr, i);
//        }
//        cout << "------------------------" << endl;
//    }
//}
//
//void shuffleArray(vector<int>& arr, int size) {
//    arr.clear();
//    for (int i = 1; i <= size; ++i) {
//        arr.push_back(i);
//    }
//
//    // Fisher-Yates shuffle algorithm
//    for (int i = size - 1; i > 0; --i) {
//        int j = rand() % (i + 1);
//        swap(arr[i], arr[j]);
//    }
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

