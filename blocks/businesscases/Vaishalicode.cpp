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

    // Check if the file was successfully opened
    if (!file)
    {
        cout << "File not found" << endl;
        return;
    }

    // Until the end of the file, read all the file data
    while (file >> list[global_count4].name >> list[global_count4].authorname >> list[global_count4].edition)
    {
        cout << list[global_count4].name << " " << list[global_count4].authorname << " " << list[global_count4].edition << endl;
        global_count4++;
    }
    cout << "Count = " << global_count4 << endl;

    file.close();
}

/**
 * Function name: search_books
 * Input: Specific subtitle of the book
 * Output: Displays all book details which contain that subtitle
 * Return type: void
 */
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

/**
 * Function name: bfss (brute force string matching algorithm)
 * Input: Book title name and pattern to be searched in book title
 * Output: Return index of the book on matching the text with pattern else -1
 * Return type: void
 */
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

    // Read the file and add criminals
    cout << "File contents:" << endl;
    string crimeType, name;
    while (file >> crimeType >> name) 
    {
        cout << crimeType << " " << name << endl;
        addCriminal(crimeType, name);
    }

    // Display all crimes and their associated criminals
    cout << "\nAll Crimes Information:" << endl;
    for (int i = 0; i < MAX_CRIME_TYPES; i++) 
        {
        if (!crimeArray[i].type.empty()) 
        {
            displayCriminals(crimeArray[i].type);
        }
    }

    // Free the memory before exiting
    freeCrimeArrays();
}

/**
 * Function name: addCriminal
 * Input: crimeType (string) and name (string)
 * Output: Adds the criminal name to the specific crime type
 * Return type: void
 */
void addCriminal(const string& crimeType, const string& name) 
{
    int crimeIndex = -1;

    // Find the index of the crime type in the array
    for (int i = 0; i < MAX_CRIME_TYPES; i++)
        {
        if (crimeArray[i].type == crimeType) 
        {
            crimeIndex = i;
            break;
        }
        if (crimeArray[i].type.empty())
         {
            // Empty slot found, store the new crime type
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

    // Create a new criminal node
    auto newCriminal = make_unique<Criminal>();
    newCriminal->name = name;
    newCriminal->crimeCount = 1;
    newCriminal->next = move(crimeArray[crimeIndex].criminals);
    crimeArray[crimeIndex].criminals = move(newCriminal);
}

/**
 * Function name: displayCriminals
 * Input: crimeType (string)
 * Output: Displays the criminals' names for the specific crime
 * Return type: void
 */
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

/**
 * Function name: freeCrimeArrays
 * Input: None
 * Output: Frees the memory allocated for the linked lists
 * Return type: void
 */
void freeCrimeArrays() 
{
    // Using smart pointers, memory will be automatically freed
}

/**
 * Function name: executeTimeCalculation
 * Input: None
 * Output: Computes and displays time difference between two places
 * Return type: void
 */
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

/**Function name:KMP search
Input parameters:pattern and text(security pin:text) (input string:patterns)
Return type:int
Description:Return the sum of indices(if the text and pattern match)
**/
void compute_LPS_array(const string& pattern, int M, vector<int>& lps)
 {
    int len = 0;  // length of the previous longest prefix suffix
    lps[0] = 0;  // lps[0] is always 0
    int i = 1;

    // Calculate the LPS array
    while (i < M)
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
}

// Function to perform KMP string search
int KMP_search(const string& pattern, const string& text)
 {
    int M = pattern.length();
    int N = text.length();

    if (M == 0 || N == 0) 
    {
        return -1;
    }

    vector<int> lps(M);  // LPS array for pattern
    int j = 0;  // index for pattern

    // Preprocess the pattern (compute the LPS array)
    compute_LPS_array(pattern, M, lps);

    int i = 0;  // index for text
    while (i < N)
        {
        if (pattern[j] == text[i]) 
        {
            j++;
            i++;
        }

        if (j == M)
        {
            return i - j;  // Match found, return starting index
        } 
        else if(i < N && pattern[j] != text[i]) 
        {
            if (j != 0) 
            {
                j = lps[j - 1];  // Use LPS to skip characters in the pattern
            } 
        else 
            {
                i++;
            }
        }
    }

    return -1;  // No match found
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
