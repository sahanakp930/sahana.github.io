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
#define MAX 100
#define MAX_CRIME_TYPES 100

struct Book
{
    string name;
    string authorname;
    int edition;
};

Book list[200];
int global_count4 = 0;

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

void executeLibraryFunctionality();
void load_from_file4();
void search_books(const string& search_term);
int bfss(const string& P, const string& T);
vector<CrimeType> crimeArray(MAX_CRIME_TYPES);
void executeCrimeFunctionality();
void addCriminal(const string& crimeType, const string& name);
void displayCriminals(const string& crimeType);
void freeCrimeArrays();
void executeTimeCalculation();

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

    while (file >> list[global_count4].name >> list[global_count4].authorname >> list[global_count4].edition)
    {
        cout << list[global_count4].name << " " << list[global_count4].authorname << " " << list[global_count4].edition << endl;
        global_count4++;
    }
    cout << "Count = " << global_count4 << endl;

    file.close();
}

void search_books(const string& search_term)
{
    int found = 0;
    for (int i = 0; i < global_count4; i++)
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
        cout << crimeType << " " << name << endl;
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
    // Using smart pointers, memory will be automatically freed
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
void merge(vector<Book>& books, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        merge(books, left, mid);
        merge(books, mid + 1, right);

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
    int i = low - 1;

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

void bfs(const vector<vector<int>>& adjList, int startNode)
{
    vector<bool> visited(adjList.size(), false);
    queue<int> q;

    visited[startNode] = true;
    q.push(startNode);

    while (!q.empty())
    {
        int current = q.front();
        q.pop();
        cout << "Visited node: " << current << endl;

        for (int neighbor : adjList[current])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int findParent(int u, vector<int>& parent)
{
    if (parent[u] != u)
        parent[u] = findParent(parent[u], parent);
    return parent[u];
}

void kruskal(int numVertices, vector<Edge>& edges)
{
    sort(edges.begin(), edges.end());

    vector<int> parent(numVertices);
    for (int i = 0; i < numVertices; i++)
        parent[i] = i;

    vector<Edge> mst;
    for (const Edge& edge : edges)
    {
        int parentU = findParent(edge.u, parent);
        int parentV = findParent(edge.v, parent);

        if (parentU != parentV)
        {
            mst.push_back(edge);
            parent[parentU] = parentV;
        }
    }

    cout << "Minimum Spanning Tree edges:" << endl;
    for (const Edge& edge : mst)
    {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
    }
}

void dijkstra(const vector<vector<pair<int, int>>>& adjList, int startNode)
{
    int n = adjList.size();
    vector<int> dist(n, INT_MAX);
    dist[startNode] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, startNode});

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        for (const auto& neighbor : adjList[u])
        {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Shortest distances from node " << startNode << ":" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i << " : " << dist[i] << endl;
    }
}

int main()
{
    string security = "Vaishali@305";
    string pin;
    cout << "Enter the security key to use the program\n";
    cout << "Name@roll_no\n";
    cin >> pin;
    int found = KMP_search(pin, security);
    if (found != -1)
    {
        cout << "Security key matched. Access granted!\n";

        int choice;
        while (1)
        {
            cout << "Menu\n";
            cout << "1 - Library management\n";
            cout << "2 - Public safety management\n";
            cout << "3 - Time calculation between two places\n";
            cout << "4 - Sort books\n";
            cout << "5 - Graph Algorithms\n";
            cout << "Any other option to exit\n";
            cout << "Enter choice\n";
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
                    cout << "Choose sorting algorithm:\n";
                    cout << "1 - Merge Sort\n";
                    cout << "2 - Heap Sort\n";
                    cout << "3 - Quick Sort\n";
                    int sortChoice;
                    cin >> sortChoice;
                    switch (sortChoice)
                    {
                        case 1:
                            merge(list, 0, global_count4 - 1);
                            break;
                        case 2:
                            heapSort(list);
                            break;
                        case 3:
                            quickSort(list, 0, global_count4 - 1);
                            break;
                        default:
                            cout << "Invalid choice.\n";
                            break;
                    }
                    cout << "Books sorted!\n";
                    break;
                case 5:
                    cout << "Choose graph algorithm:\n";
                    cout << "1 - BFS\n";
                    cout << "2 - Kruskal\n";
                    cout << "3 - Dijkstra\n";
                    int graphChoice;
                    cin >> graphChoice;
                    switch (graphChoice)
                    {
                        case 1:
                            {
                                vector<vector<int>> adjList = {{1, 2}, {0, 3}, {0, 3}, {1, 2}};
                                bfs(adjList, 0);
                            }
                            break;
                        case 2:
                            {
                                vector<Edge> edges = {{0, 1, 10}, {0, 2, 6}, {1, 2, 5}, {2, 3, 4}};
                                kruskal(4, edges);
                            }
                            break;
                        case 3:
                            {
                                vector<vector<pair<int, int>>> adjList = {
                                    {{1, 10}, {2, 5}},
                                    {{0, 10}, {2, 2}, {3, 1}},
                                    {{0, 5}, {1, 2}, {3, 9}},
                                    {{1, 1}, {2, 9}}
                                };
                                dijkstra(adjList, 0);
                            }
                            break;
                        default:
                            cout << "Invalid choice.\n";
                            break;
                    }
                    break;
                default:
                    cout << "Exiting...\n";
                    return 0; // Exit the program
            }
        }
    }
    else
    {
        cout << "Security key not matched. You cannot continue with the program\n";
    }
}
