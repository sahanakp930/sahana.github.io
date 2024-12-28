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
/**structure for recording student information(array implementation)**/
struct school
{
    char name[20];
    int roll_no;
    double percentage;
};
/**structure for recording school data(list implementation);**/
struct node_school
{
    struct node_school *left;
    struct school data;
    struct node_school *right;
    int height;
};
int count_4 = 0;
/**structure for storing source and destination vertices and their weights(array implementation)**/
struct graph {
    int u[50];
    int v[50];
    int w[50];
};
/**structure for minimum spanning tree(kruskals implementation)**/
struct Edge {
    int src, dest, weight;
};

/**Structure to represent a location (delivery point)**/
struct delivery {
    char location[100];
    int parcels;
};
/**Funtion prototypes**/
node_school* newNode(school key);
int height(node_school* node);
int max_school(int a, int b);
node_school* rightRotate(node_school* y);
node_school* leftRotate(node_school* x);
int getBalance(node_school* node);
node_school* insertAVL(node_school* root, school key);
node_school* minValueNode(node_school* node);
node_school* deleteNodeAVL(node_school* root, int key);
void load_from_file7(node_school** root2);
void display_school(node_school* root2);
void display_class(node_school* root2, int roll);
void executeSchoolFunctionality();

void read(struct graph &g, int E);
void heapify(struct graph &g, int n, int i);
void Sort(struct graph &g, int E);
int Find(int arr[], int p);
void Union(int arr[], int p, int q, int V);

void executeDeliveryFunctionality();
int find(int arr[], int u);
void unionfind(int arr[], int n, int u, int v);
void quicksort(Edge edges[], int low, int high);
int partition(Edge edges[], int low, int high);

node_school* newNode(school key) {
    node_school* node = new node_school;
    node->data = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int height(node_school* node) {
    if (node == NULL) return 0;
    return node->height;
}

int max_school(int a, int b) {
    return (a > b) ? a : b;
}

node_school* rightRotate(node_school* y) {
    node_school* x = y->left;
    node_school* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max_school(height(y->left), height(y->right)) + 1;
    x->height = max_school(height(x->left), height(x->right)) + 1;

    return x;
}

node_school* leftRotate(node_school* x) {
    node_school* y = x->right;
    node_school* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max_school(height(x->left), height(x->right)) + 1;
    y->height = max_school(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(node_school* node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}

node_school* insertAVL(node_school* root, school key) {
    if (root == NULL) return newNode(key);

    if (key.roll_no <= root->data.roll_no)
        root->left = insertAVL(root->left, key);
    else if (key.roll_no > root->data.roll_no)
        root->right = insertAVL(root->right, key);
    else return root;

    root->height = 1 + max_school(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && key.roll_no < root->left->data.roll_no)
        return rightRotate(root);

    if (balance < -1 && key.roll_no > root->right->data.roll_no)
        return leftRotate(root);

    if (balance > 1 && key.roll_no > root->left->data.roll_no) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && key.roll_no < root->right->data.roll_no) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

node_school* minValueNode(node_school* node) {
    node_school* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

node_school* deleteNodeAVL(node_school* root, int key) {
    if (root == NULL) return root;

    if (key < root->data.roll_no)
        root->left = deleteNodeAVL(root->left, key);
    else if (key > root->data.roll_no)
        root->right = deleteNodeAVL(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            node_school* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }

            delete temp;
        } else {
            node_school* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNodeAVL(root->right, temp->data.roll_no);
        }
    }

    if (root == NULL) return root;

    root->height = 1 + max_school(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
/**Function Name: load_from_file
Input Params: NILL
Return Type: void
Description: loads all the data available with details into appropriate data structure**/
void load_from_file7(node_school** root2) {
    ifstream fp("school.txt");
    school school[100];

    if (!fp) {
        cout << "File Not found" << endl;
        return;
    }

    while (fp >> school[count_4].name >> school[count_4].roll_no >> school[count_4].percentage) {
        *root2 = insertAVL(*root2, school[count_4]);
        cout << school[count_4].name << " " << school[count_4].roll_no << " " << school[count_4].percentage << endl;
        count_4++;
    }
    cout << "Initial student count = " << count_4 << endl;

    fp.close();
}
/**Function Name:display_school
Input params:NILL
return type:Void
Description:Display all the students information of a school.**/
void display_school(node_school* root2) {
    if (root2 == NULL) return;

    display_school(root2->left);
    cout << root2->data.name << " " << root2->data.roll_no << " " << root2->data.percentage << endl;
    display_school(root2->right);
}

void display_class(node_school* root2, int roll) {
    if (root2 == NULL) return;

    if (root2->data.roll_no >= roll && root2->data.roll_no < roll + 100)
        cout << root2->data.name << " " << root2->data.roll_no << " " << root2->data.percentage << endl;

    display_class(root2->left, roll);
    display_class(root2->right, roll);
}

void executeSchoolFunctionality() {
    node_school* root2 = NULL;
    load_from_file7(&root2);
    int Class;
    int choice;

    cout << "\\\\ Menu \\\\" << endl;
    cout << "1. Insert new student record into AVL tree" << endl;
    cout << "2. Delete student record" << endl;
    cout << "3. Display all students in school" << endl;
    cout << "4. Display student in particular class" << endl;
    cout << "5. Exit" << endl;

    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            school new_student;
            cout << "Enter student details: " << endl;
            cout << "Enter student name: ";
            cin >> new_student.name;
            cout << "Enter roll_no: ";
            cin >> new_student.roll_no;
            cout << "Enter percentage of student in academics: ";
            cin >> new_student.percentage;

            if (new_student.roll_no > 100 && new_student.roll_no < 1099 && new_student.percentage > 0.0 && new_student.percentage < 100.0)
                root2 = insertAVL(root2, new_student);
            else
                cout << "Invalid student details" << endl;

            break;
        }
        case 2: {
            int key;
            cout << "Enter roll number to delete: ";
            cin >> key;
            root2 = deleteNodeAVL(root2, key);
            break;
        }
        case 3: {
            cout << "Updated AVL tree after deletion:" << endl;
            display_school(root2);
            break;
        }
        case 4: {
            cout << "Enter the class to be displayed: ";
            cin >> Class;
            if (Class >= 1 && Class <= 10)
                display_class(root2, Class * 100);
            break;
        }
        case 5: {
            cout << "Exiting program." << endl;
            return;
        }
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
        }
    }
}
void read(struct graph &g, int E) {
    cout << "Enter the edges (u, v, w):\n";
    for (int i = 1; i <= E; i++) {
        cin >> g.u[i] >> g.v[i] >> g.w[i];
    }
}

void heapify(struct graph &g, int n, int i) {
    int largest = i;
    int left = 2 * i;
    int right = 2 * i + 1;

    if (left <= n && g.w[left] > g.w[largest])
        largest = left;
    if (right <= n && g.w[right] > g.w[largest])
        largest = right;

    if (largest != i) {
        swap(g.u[i], g.u[largest]);
        swap(g.v[i], g.v[largest]);
        swap(g.w[i], g.w[largest]);
        heapify(g, n, largest);
    }
}

void Sort(struct graph &g, int E) {
    for (int i = E / 2; i >= 1; i--) heapify(g, E, i);
    for (int i = E; i > 1; i--) {
        swap(g.u[1], g.u[i]);
        swap(g.v[1], g.v[i]);
        swap(g.w[1], g.w[i]);
        heapify(g, i - 1, 1);
    }
}

int Find(int arr[], int p) {
    if (arr[p] == p)
        return p;
    return arr[p] = Find(arr, arr[p]); 
}
/**function name :Union
input:Array of defined elements,vertex V,indices p and q
output:Replace arr[p] by arr[q]
return type:void**/
void Union(int arr[], int p, int q, int V) {
    int rootP = Find(arr, p);
    int rootQ = Find(arr, q);
    if (rootP != rootQ) {
        arr[rootP] = rootQ;
    }
}
/**
function name :kruskals algorithm
input:struct edges,no of vertices,no of edges ,struct location
output:returns the minimum distance to cover all vertices
return type:int
*/
int deliveryKruskal(Edge edges[], int V, int E, delivery locations[]) {
    quicksort(edges, 0, E - 1);

    int *arr = (int *)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) {
        arr[i] = i; // Initialize parent of each vertex to itself
    }

    int ecounter = 0;
    int k = 0;
    int sum = 0;

    while (ecounter < V - 1 && k < E) {
        if (find(arr, edges[k].src) != find(arr, edges[k].dest)) {  // If no cycle
            unionfind(arr, V, edges[k].src, edges[k].dest);  // Union the sets

            printf("Delivering from %s to %s, Distance: %d\n", locations[edges[k].src].location,
                   locations[edges[k].dest].location, edges[k].weight);
            sum += edges[k].weight;
            ecounter++;
        }
        k++;
    }

    free(arr);  // Free allocated memory
    return sum;
}
/**
function name :Find
input:Array of defined elements and index u
output:Finds whether the index elements are same or different
return type:int
*/
int find(int arr[], int u) {
    if (arr[u] != u) {
        arr[u] = find(arr, arr[u]); // Path compression
    }
    return arr[u];
}

// Union function for Union-Find
void unionfind(int arr[], int n, int u, int v) {
    int rootU = find(arr, u);
    int rootV = find(arr, v);

    if (rootU != rootV) {
        arr[rootU] = rootV; // Union the sets
    }
}
/**Function name:quicksort
Input:Edges,right and left end of array
Output:Sort the array based on weights
Return type:void**/
void quicksort(Edge edges[], int low, int high) {
    if (low < high) {
        int pi = partition(edges, low, high);
        quicksort(edges, low, pi - 1);
        quicksort(edges, pi + 1, high);
    }
}

// Partition function for quicksort based on weight
int partition(Edge edges[], int low, int high) {
    Edge pivot = edges[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (edges[j].weight < pivot.weight) {
            i++;
            swap(edges[i], edges[j]);
        }
    }

    swap(edges[i + 1], edges[high]);
    return i + 1;
}

// Function to execute the delivery process
void executeDeliveryFunctionality() {
    int V, E;
    FILE *fp = fopen("parcels.txt", "r");

    if (fp == NULL) {
        printf("FILE not found\n");
        return;
    }

    fscanf(fp, "%d", &V);  // Read number of locations
    printf("Number of locations: %d\n", V);

    fscanf(fp, "%d", &E);  // Read number of edges
    printf("Number of edges: %d\n", E);

    Edge edges[E];
    delivery locations[V];

    // Read the locations
    printf("Enter the names of locations:\n");
    for (int i = 0; i < V; i++) {
        fscanf(fp, "%s", locations[i].location);
        locations[i].parcels = 1;  // Assume each location has 1 parcel initially
        printf("%s\n", locations[i].location);
    }

    // Read the edges
    printf("Enter the connections and their distances:\n");
    for (int i = 0; i < E; i++) {
        fscanf(fp, "%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
        printf("%d %d %d\n", edges[i].src, edges[i].dest, edges[i].weight);
    }

    int sum = deliveryKruskal(edges, V, E, locations);
    if (sum == 0) {
        printf("There is no chance to cover all locations in minimum distance\n");
    } else {
        printf("%d is the sum of minimum distances to cover all parcel locations\n", sum);
    }

    fclose(fp);  // Close the file
}
/**Funcction name:KMP SEARCH
Input Params:Pattern and text(Security pin:text)(input string:pattern)
Return type:int
Description:Return the sum of indices(if the text and pattern match)
**/
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
    //security to the program(KMP implementation)
    string security="Pooja@331";
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
        cout << "1-students record in school\n";
        cout << "2-24\7 water supply\n";
        cout<< "3-Delivery management\n";
        cout << "Any other option to exit\n";
        cout << "Enter choice\n";
        cin >> choice;
        switch(choice) {
            case 1: executeSchoolFunctionality();
                  break;
            case 2: {
                graph g;
                int V, E;

                cout << "Enter the total number of vertices\n";
                cin >> V;
                cout << "Enter the total number of edges\n";
                cin >> E;

                read(g, E);
                Sort(g, E);

                cout << "Edges sorted by weight (descending):\n";
                for (int i = 1; i <= E; i++) {
                    cout << g.u[i] << " " << g.v[i] << " " << g.w[i] << endl;
                }

                int arr[50];
                for (int i = 0; i < V; i++) {
                    arr[i] = i; // Each vertex is its own "parent"
                }

                cout << "Maximum Spanning Tree Edges:\n";
                int mst_weight = 0;

                for (int i = 1; i <= E; i++) {
                    int connected = Find(arr, g.u[i]);
                    if (connected == 0) { // Add edge if it doesn't form a cycle
                        cout << g.u[i] << " " << g.v[i] << " " << g.w[i] << endl;
                        mst_weight += g.w[i];
                        Union(arr, g.u[i], g.v[i], V);
                    }
                }

                cout << "Total weight of Maximum Spanning Tree: " << mst_weight << endl;
                break;
            }
            case 3:executeDeliveryFunctionality();
            break;

            default:
                cout << "Exiting...\n";
                return 0; // Exit the program
        }
    }}else{
        cout<<"Security key not matched.You cannot continue with the program\n";
    }}
