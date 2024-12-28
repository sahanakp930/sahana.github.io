#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <memory>
using namespace std;
// Structure to hold employee data
struct Employee {
    char name[20];
    int age;
    int experience;
};

struct Node {
    Employee data;
    Node* left;
    Node* right;
};
//structure for passenger management
struct Passenger {
    char name[50];
    int coachNumber;
};

typedef struct Passenger P;
P details[200];

//structure for Waste management
struct Waste {
    int id;              // Unique ID for waste
    string wasteType;    // "Wet" or "Dry"
    string degradable;   // "Degradable" or "Non-Degradable" (for Dry only)
    string chemical;     // "Chemical" or "Non-Chemical" (for Degradable Dry only)
};

// Function prototypes
int insert(Node* &root, Employee* e);
void displayEmployee(Node* root);
int deleteEmployee(Node* &root, int exp);
Employee max(Node* root);
Employee min(Node* root);
void load_from_file7(Node* &root);

// Global variable for counting entries
int count_4 = 0;
int global_count1 = 0;

// Function to load employee data from a file
void load_from_file7(Node* &root) {
    ifstream fp("employee.txt");
    Employee employee[100];

    if (!fp) {
        cout << "File not found" << endl;
        return;
    }

    while (fp >> employee[count_4].name >> employee[count_4].age >> employee[count_4].experience) {
        insert(root, &employee[count_4]);
        cout << employee[count_4].name << " " << employee[count_4].age << " " << employee[count_4].experience << endl;
        count_4++;
    }

    cout << "Initial employee count = " << count_4 << endl;
    fp.close();
}

// Function to insert an employee into the Binary Search Tree
int insert(Node* &root, Employee* e) {
    Node* newNode = new Node;
    newNode->data = *e;
    newNode->left = newNode->right = nullptr;

    if (root == nullptr) {
        root = newNode;
        return 1;
    }

    Node* parent = nullptr;
    Node* current = root;
    while (current) {
        parent = current;
        if (e->experience <= current->data.experience)
            current = current->left;
        else
            current = current->right;
    }

    if (e->experience > parent->data.experience)
        parent->right = newNode;
    else
        parent->left = newNode;

    return 1;
}

// Function to display all employees in the tree
void displayEmployee(Node* root) {
    if (root == nullptr)
        return;

    cout << root->data.name << " " << root->data.age << " " << root->data.experience << endl;
    displayEmployee(root->left);
    displayEmployee(root->right);
}

// Function to count the number of employees with a specific experience
int count(Node* root, int exp) {
    if (root == nullptr)
        return 0;

    int count1 = (root->data.experience == exp) ? 1 : 0;
    count1 += count(root->left, exp);
    count1 += count(root->right, exp);

    return count1;
}

// Function to delete an employee based on experience
int deleteEmployee(Node* &root, int exp) {
    int c = count(root, exp);
    cout << "Number of employees with experience " << exp << ": " << c << endl;

    while (c) {
        Node* current = root;
        Node* parent = nullptr;
        while (current && current->data.experience != exp) {
            parent = current;
            if (exp < current->data.experience)
                current = current->left;
            else
                current = current->right;
        }

        if (current == nullptr) {
            cout << "No employee with experience " << exp << " found.\n";
            return 0;
        }

        // Case 1: Deleting leaf node
        if (current->left == nullptr && current->right == nullptr) {
            if (current == root)
                root = nullptr;
            else if (parent->left == current)
                parent->left = nullptr;
            else
                parent->right = nullptr;
            delete current;
            cout << "Deleted employee with experience " << exp << ".\n";
            return 1;
        }

        // Case 2: Deleting a node with one child
        if (current->left != nullptr && current->right == nullptr) {
            if (current == root)
                root = current->left;
            else if (parent->left == current)
                parent->left = current->left;
            else
                parent->right = current->left;
            delete current;
            cout << "Deleted employee with experience " << exp << ".\n";
            return 1;
        }

        if (current->right != nullptr && current->left == nullptr) {
            if (current == root)
                root = current->right;
            else if (parent->left == current)
                parent->left = current->right;
            else
                parent->right = current->right;
            delete current;
            cout << "Deleted employee with experience " << exp << ".\n";
            return 1;
        }

        // Case 3: Deleting node with two children
        if (current->left && current->right) {
            Node* inOrderSuccessor = current->right;
            while (inOrderSuccessor->left)
                inOrderSuccessor = inOrderSuccessor->left;

            current->data = inOrderSuccessor->data;
            return deleteEmployee(current->right, inOrderSuccessor->data.experience);
        }

        c--;
    }
    return 0;
}

// Function to find the employee with the maximum experience
Employee max(Node* root) {
    Node* current = root;
    while (current->right)
        current = current->right;
    return current->data;
}

// Function to find the employee with the minimum experience
Employee min(Node* root) {
    Node* current = root;
    while (current->left)
        current = current->left;
    return current->data;
}

// Function to execute the main employee functionality
void executeEmployeeFunctionality() {
    Node* root = nullptr;
    load_from_file7(root);

    int choice, new_exp;
    int status_2;
    Employee max_employee;
    Employee min_employee;

    cout << "\nMenu:\n";
    cout << "1. Insert new employee details\n";
    cout << "2. Delete employee based on experience\n";
    cout << "3. Display employees\n";
    cout << "4. Display most experienced employee\n";
    cout << "5. Display recently joined employee\n";
    cout << "6. Exit\n";

    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            Employee new_employee;

            cout << "Enter new details of the employee:\n";
            cout << "Name: ";
            cin >> new_employee.name;

            cout << "Age: ";
            cin >> new_employee.age;

            cout << "Experience: ";
            cin >> new_employee.experience;

            if (new_employee.age <= new_employee.experience)
                cout << "Invalid input\n";
            else {
                status_2 = insert(root, &new_employee);
                if (status_2 == 1)
                    cout << "Inserted successfully\n";
            }
            break;
        }

        case 2: {
            cout << "Enter the experience threshold: ";
            cin >> new_exp;

            int deleted = deleteEmployee(root, new_exp);
            if (deleted == 0)
                cout << "No employees with the specified experience found.\n";
            break;
        }

        case 3:
            cout << "Displaying employees:\n";
            displayEmployee(root);
            break;

        case 4:
            cout << "Displaying most experienced employee:\n";
            max_employee = max(root);
            cout << max_employee.name << " " << max_employee.age << " " << max_employee.experience << endl;
            break;

        case 5:
            cout << "Displaying most recently joined employee:\n";
            min_employee = min(root);
            cout << min_employee.name << " " << min_employee.age << " " << min_employee.experience << endl;
            break;

        case 6:
            cout << "Exiting program.\n";
            return;

        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    }
}
//Function to search for a passenger by name
void searchPassenger(const char searchName[]) {
    bool found = false;
    for (int i = 0; i < global_count1; i++) {
        if (strcmp(details[i].name, searchName) == 0) {
            cout << "Passenger found!" << endl;
            cout << "Name\t\tCoach Number" << endl;
            cout << details[i].name << "\t\t" << details[i].coachNumber << endl;
            found = true;
            break;  // Break out of the loop since the passenger is found
        }
    }
    if (!found) {
        cout << "Passenger not found." << endl;
    }
}

// Heapify the struct passenger array based on coach number
void heapify(P passengers[], int n, int i) {
    int max = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && passengers[max].coachNumber < passengers[left].coachNumber)
        max = left;
    if (right < n && passengers[max].coachNumber < passengers[right].coachNumber)
        max = right;

    if (max != i) {

        // Swap passengers if they are in the wrong order

        swap(passengers[i], passengers[max]);
        heapify(passengers, n, max);
    }
}

// Heap sort function to sort the passengers based on coach number
void heapSort(P passengers[], int n) {

    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(passengers, n, i);

    // Extract elements from the heap
    for (int i = n - 1; i >= 0; i--) {
        // Swap the root (max element) with the last element
        swap(passengers[0], passengers[i]);

        // Heapify the reduced heap
        heapify(passengers, i, 0);
    }
}

// Load passenger data from file
void load_from_file_1() {
    ifstream file("railwaymanagement.txt");

    // Check if the file was successfully opened
    if (!file) {
        cout << "File not found." << endl;
        return;
    }

    // Read data from the file
    while (file >> details[global_count1].name >> details[global_count1].coachNumber) {
        cout << details[global_count1].name << " " << details[global_count1].coachNumber << endl;
        global_count1++;
    }

    cout << "Total passengers: " << global_count1 << endl;
    file.close();
}

// Function to display passenger details sorted by coach number
void executePassengerFunctionality() {
    // Load data from file
    load_from_file_1();

    // Sort the passengers based on coach numbers
    heapSort(details, global_count1);

    // Display the sorted passenger details
    cout << "\nPassenger details sorted by coach number:\n";
    cout << "Name\t\tCoach Number" << endl;
    for (int i = 0; i < global_count1; i++) {
        cout << details[i].name << "\t\t" << details[i].coachNumber << endl;
    }

    // Example of using the search function
    char searchName[50];
    cout << "\nEnter the name of the passenger to search: ";
    cin >> searchName;
    searchPassenger(searchName);
}
// To identify the moisture content in waste
string detectType(double moisture) {
    return (moisture > 50.0) ? "Wet" : "Dry";
}

// To identify the type of material in waste
string detectDegradability(string material) {
    if (material == "Paper" || material == "Food" || material == "Wood")
        return "Degradable";
    return "Non-Degradable";
}

string detectChemicalPresence(string material) {
    if (material == "Battery" || material == "Cleaning Agent")
        return "Chemical";
    return "Non-Chemical";
}

// Heapify function for Heap Sort (sorting by ID for clarity)
void heapify(vector<Waste> &waste, int n, int i) {
    int largest = i;          // Initialize largest as root
    int left = 2 * i + 1;     // Left child
    int right = 2 * i + 2;    // Right child

    // Compare with left child
    if (left < n && waste[left].id < waste[largest].id)
        largest = left;

    // Compare with right child
    if (right < n && waste[right].id < waste[largest].id)
        largest = right;

    // Swap and continue heapifying if root is not largest
    if (largest != i) {
        swap(waste[i], waste[largest]);
        heapify(waste, n, largest);
    }
}

// Heap Sort function
void heapSort(vector<Waste> &waste) {
    int n = waste.size();

    // Build heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(waste, n, i);

    // Extract elements from heap one by one
    for (int i = n - 1; i >= 0; i--) {
        swap(waste[0], waste[i]);
        heapify(waste, i, 0);
    }
}

// Function to simulate actuators sorting waste into bins
void placeInBins(const vector<Waste> &waste) {
    cout << "\nPlacing waste into bins:\n";
    for (const auto &wasteItem : waste) { // Renamed w to wasteItem for clarity
        cout << "Waste ID: " << wasteItem.id << " -> ";
        if (wasteItem.wasteType == "Wet") {
            cout << "Bin: Wet Waste\n";
        } else if (wasteItem.wasteType == "Dry" && wasteItem.degradable == "Degradable") {
            if (wasteItem.chemical == "Chemical") {
                cout << "Bin: Dry Degradable Chemical Waste\n";
            } else {
                cout << "Bin: Dry Degradable Non-Chemical Waste\n";
            }
        } else {
            cout << "Bin: Dry Non-Degradable Waste\n";
        }
    }
}
void compute_LPS_array(const string& pattern, int M, vector<int>& lps) {
    int len = 0;  // length of the previous longest prefix suffix
    lps[0] = 0;  // lps[0] is always 0
    int i = 1;

    // Calculate the LPS array
    while (i < M) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}
/**Funcction name:KMP SEARCH
Input Params:Pattern and text(Security pin:text)(input string:pattern)
Return type:int
Description:Return the sum of indices(if the text and pattern match)
**/
// Function to perform KMP string search
int KMP_search(const string& pattern, const string& text) {
    int M = pattern.length();
    int N = text.length();

    if (M == 0 || N == 0) {
        return -1;
    }

    vector<int> lps(M);  // LPS array for pattern
    int j = 0;  // index for pattern

    // Preprocess the pattern (compute the LPS array)
    compute_LPS_array(pattern, M, lps);

    int i = 0;  // index for text
    while (i < N) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == M) {
            return i - j;  // Match found, return starting index
        } else if (i < N && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];  // Use LPS to skip characters in the pattern
            } else {
                i++;
            }
        }
    }

    return -1;  // No match found
}
int main() {
    int choice;
    //Security to the program
    string security="Sahanakp@332";
    string pin;
    cout<<"Enter the security key to use the program\n";
    cout<<"Name@roll_no\n";
    cin>>pin;
    int found=KMP_search(pin,security);
    if(found!=-1)
    {
        cout<<"Security key matched.Access granted!\n";
    while(1) {
        cout << "Menu\n";
        cout << "1-Employee record\n";
        cout << "2-Passenger management\n";
        cout<< "3-Waste management\n";
        cout << "Any other option to exit\n";
        cout << "Enter choice\n";
        cin >> choice;
        switch(choice) {
            case 1: executeEmployeeFunctionality();
                  break;
            case 2: {
                 executePassengerFunctionality();
                break;
            }
               case 3: {
                // Initialize waste data
                vector<Waste> wasteData = {
                    {1, detectType(30.0), detectDegradability("Plastic"), ""},  // Non-Degradable
                    {2, detectType(70.0), "", ""},                             // Wet Waste
                    {3, detectType(20.0), detectDegradability("Paper"), detectChemicalPresence("Paper")},  // Degradable, Non-Chemical
                    {4, detectType(60.0), "", ""},                             // Wet Waste
                    {5, detectType(10.0), detectDegradability("Battery"), detectChemicalPresence("Battery")} // Non-Degradable, Chemical
                };

                cout << "Raw Waste Data:\n";
                for (const auto &w : wasteData) {
                    cout << "ID: " << w.id
                         << ", Type: " << w.wasteType
                         << ", Degradable: " << (w.degradable.empty() ? "N/A" : w.degradable)
                         << ", Chemical: " << (w.chemical.empty() ? "N/A" : w.chemical)
                         << endl;
                }

                // Sort waste using Heap Sort based on waste ID (for clarity)
                heapSort(wasteData);

                // Display sorted waste and place into bins
                cout << "\nSorted Waste Data:\n";
                for (const auto &w : wasteData) {
                    cout << "ID: " << w.id
                         << ", Type: " << w.wasteType
                         << ", Degradable: " << (w.degradable.empty() ? "N/A" : w.degradable)
                         << ", Chemical: " << (w.chemical.empty() ? "N/A" : w.chemical)
                         << endl;
                }

                placeInBins(wasteData);
                break;
            }


            default:
                cout << "Exiting...\n";
                return 0; // Exit the program
        }
    }
}
else
{
    cout<<"Security key not matched.You cannot continue with the program\n";
}
}
