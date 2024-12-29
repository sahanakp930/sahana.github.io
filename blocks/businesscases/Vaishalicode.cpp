#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <queue>
#include <tuple>

using namespace std;
#define MAX_CRIME_TYPES 100

// Structs for Library and Crime Data
struct Book
{
    string name;
    string authorname;
    int edition;
};

struct Criminal
{
    string name;
    int crimeCount;
    unique_ptr<Criminal> next;
};

struct CrimeType
{
    string type;
    unique_ptr<Criminal> criminals;
};

// Global Variables
vector<Book> list;
vector<CrimeType> crimeArray(MAX_CRIME_TYPES);

// Function Declarations
void executeLibraryFunctionality();
void load_from_file4();
void search_books(const string& search_term);
int bfss(const string& P, const string& T);
void executeCrimeFunctionality();
void addCriminal(const string& crimeType, const string& name);
void displayCriminals(const string& crimeType);
void freeCrimeArrays();
void executeTimeCalculation();

// Sorting Algorithms
void mergeSort(vector<Book>& books, int left, int right);
void heapSort(vector<Book>& books);
void quickSort(vector<Book>& books, int low, int high);
int partition(vector<Book>& books, int low, int high);
void heapify(vector<Book>& books, int n, int i);

// BFS Algorithm
void bfs(const vector<vector<int>>& adjList, int startNode);

// Kruskal's Algorithm
struct Edge
{
    int u, v, weight;
    bool operator<(const Edge& other) const
    {
        return weight < other.weight;
    }
};

int findParent(int u, vector<int>& parent);
void kruskal(int numVertices, vector<Edge>& edges);

// Dijkstra's Algorithm
void dijkstra(const vector<vector<pair<int, int>>>& adjList, int startNode);

// KMP Search Algorithm
int KMP_search(const string& text, const string& pattern);

void executeLibraryFunctionality()
{
    load_from_file4();
    string search_term;
    cout << "Enter the search pattern: ";
    cin >> search_term;
    search_books(search_term);
}

void load_from_file4()
{
    ifstream file("book.txt");

    if (!file)
    {
        cout << "File not found" << endl;
        return;
    }

    Book book;
    while (file >> book.name >> book.authorname >> book.edition)
    {
        list.push_back(book);
        cout << book.name << " " << book.authorname << " " << book.edition << endl;
    }

    cout << "Count = " << list.size() << endl;
    file.close();
}

void search_books(const string& search_term)
{
    int found = 0;
    for (int i = 0; i < list.size(); i++)
    {
        if (bfss(search_term, list[i].name) != -1)
        {
            cout << "Book found at index " << i << ":\n";
            cout << "Name: " << list[i].name << "\nAuthor: " << list[i].authorname << "\nEdition: " << list[i].edition << endl;
            found = 1;
        }
    }

    if (!found)
    {
        cout << "No books found with the specified pattern.\n";
    }
}

int bfss(const string& P, const string& T)
{
    int m = P.length();
    int n = T.length();

    for (int i = 0; i <= n - m; i++)
    {
        int j = 0;
        while (j < m && P[j] == T[i + j])
        {
            j++;
            if (j == m)
            {
                return i; // Found match
            }
        }
    }

    return -1; // No match found
}

void executeCrimeFunctionality()
{
    ifstream file("crime.txt");

    if (!file)
    {
        cerr << "Error opening file" << endl;
        return;
    }

    string crimeType, name;
    while (file >> crimeType >> name)
    {
        addCriminal(crimeType, name);
    }

    cout << "\nAll Crimes Information:" << endl;
    for (int i = 0; i < MAX_CRIME_TYPES; i++)
    {
        if (!crimeArray[i].type.empty())
        {
            displayCriminals(crimeArray[i].type);
        }
    }

    freeCrimeArrays();
}

void addCriminal(const string& crimeType, const string& name)
{
    int crimeIndex = -1;

    for (int i = 0; i < MAX_CRIME_TYPES; i++)
    {
        if (crimeArray[i].type == crimeType)
        {
            crimeIndex = i;
            break;
        }
        if (crimeArray[i].type.empty())
        {
            crimeArray[i].type = crimeType;
            crimeIndex = i;
            break;
        }
    }

    if (crimeIndex == -1)
    {
        cout << "Exceeded the maximum number of crime types." << endl;
        return;
    }

    auto newCriminal = make_unique<Criminal>();
    newCriminal->name = name;
    newCriminal->crimeCount = 1;
    newCriminal->next = move(crimeArray[crimeIndex].criminals);
    crimeArray[crimeIndex].criminals = move(newCriminal);
}

void displayCriminals(const string& crimeType)
{
    for (int i = 0; i < MAX_CRIME_TYPES; i++)
    {
        if (crimeArray[i].type == crimeType)
        {
            cout << "Criminals for " << crimeType << ":" << endl;

            Criminal* currentCriminal = crimeArray[i].criminals.get();
            while (currentCriminal != nullptr)
            {
                cout << "- " << currentCriminal->name << ": " << currentCriminal->crimeCount << " crimes" << endl;
                currentCriminal = currentCriminal->next.get();
            }

            return;
        }
    }

    cout << "Crime type not found: " << crimeType << endl;
}

void freeCrimeArrays()
{
    // Smart pointers automatically handle cleanup
}

void executeTimeCalculation()
{
    string place1, place2;
    double offset1, offset2;

    cout << "Enter the name of the first place: ";
    cin >> place1;
    cout << "Enter the UTC offset for " << place1 << " (e.g., -5.5 for EST, 1 for CET): ";
    cin >> offset1;

    cout << "Enter the name of the second place: ";
    cin >> place2;
    cout << "Enter the UTC offset for " << place2 << " (e.g., -8 for PST, 9 for JST): ";
    cin >> offset2;

    double timeDifference = offset1 - offset2;
    cout << "The time difference between " << place1 << " and " << place2 << " is ";
    cout << (timeDifference >= 0 ? "+" : "") << timeDifference << " hours.\n";
}

// Merge Sort
void mergeSort(vector<Book>& books, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(books, left, mid);
        mergeSort(books, mid + 1, right);

        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<Book> leftBooks(n1), rightBooks(n2);
        for (int i = 0; i < n1; i++)
            leftBooks[i] = books[left + i];
        for (int i = 0; i < n2; i++)
            rightBooks[i] = books[mid + 1 + i];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2)
        {
            if (leftBooks[i].name < rightBooks[j].name)
                books[k++] = leftBooks[i++];
            else
                books[k++] = rightBooks[j++];
        }

        while (i < n1)
            books[k++] = leftBooks[i++];
        while (j < n2)
            books[k++] = rightBooks[j++];
    }
}

// Heap Sort
void heapify(vector<Book>& books, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && books[left].name > books[largest].name)
        largest = left;
    if (right < n && books[right].name > books[largest].name)
        largest = right;

    if (largest != i)
    {
        swap(books[i], books[largest]);
        heapify(books, n, largest);
    }
}

void heapSort(vector<Book>& books)
{
    int n = books.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(books, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        swap(books[0], books[i]);
        heapify(books, i, 0);
    }
}

// Quick Sort
int partition(vector<Book>& books, int low, int high)
{
    string pivot = books[high].name;
    int i = (low - 1);

    for (int j = low; j < high; j++)
    {
        if (books[j].name < pivot)
        {
            i++;
            swap(books[i], books[j]);
        }
    }
    swap(books[i + 1], books[high]);
    return i + 1;
}

void quickSort(vector<Book>& books, int low, int high)
{
    if (low < high)
    {
        int pi = partition(books, low, high);
        quickSort(books, low, pi - 1);
        quickSort(books, pi + 1, high);
    }
}

// KMP Algorithm
int KMP_search(const string& text, const string& pattern)
{
    int n = text.length();
    int m = pattern.length();

    vector<int> lps(m, 0);
    int len = 0;
    int i = 1;

    while (i < m)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }

    int j = 0;
    i = 0;
    while (i < n)
    {
        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }

        if (j == m)
        {
            return i - j;
        }
        else if (i < n && pattern[j] != text[i])
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }

    return -1;
}

int main()
{
    int choice;
     string security="Vaishali@305";
    string pin;
    cout<<"Enter the security key to use the program\n";
    cout<<"Name@roll_no\n";
    cin>>pin;
    int found=KMP_search(pin,security);
    if(found!=-1)
    {
        cout<<"Security key matched.Access granted!\n";
    do
    {
        cout << "\nMain Menu:\n";
        cout << "1. Library Functionality\n";
        cout << "2. Crime Functionality\n";
        cout << "3. Time Calculation\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            executeLibraryFunctionality();
            break;
        case 2:
            executeCrimeFunctionality();
            break;
        case 3:
            executeTimeCalculation();
            break;
        case 4:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
            break;
        }
    } while (choice != 4);

    return 0;
}
else
{
    cout<<"Security key not matched.You cannot continue with the program\n";
}
}
