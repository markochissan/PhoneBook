#include <iostream>
#include <fstream>
#include <algorithm> // for std::all_of
using namespace std;

// Global variables
string fname, lname, phone_num;

// Functions
void addContact();
void searchContact();
void removeContact();
bool isValidPhoneNumber(const string&);

int main() {
    int choice;
    do {
        system("cls"); // Clear the screen 
        system("color 0A"); // Change text color 
        cout << "\n\n\t\tContact Management.";
        cout << "\n\n\t1. Add Contact\n\t2. Search Contact\n\t3. Remove Contact\n\t4. Exit\n\t> ";
        cin >> choice;

        switch (choice) {
        case 1: addContact(); break;
        case 2: searchContact(); break;
        case 3: removeContact(); break;
        case 4: cout << "\n\tThank you for using!\n"; exit(0);
        default: cout << "\n\tInvalid Input! Press any key to continue."; cin.ignore(); cin.get();
        }
    } while (choice != 4);

    return 0;
}

// Add contact function
void addContact() {
    ofstream phoneFile("number.txt", ios::app);
    system("cls");
    cout << "\nEnter First Name: "; cin >> fname;
    cout << "Enter Last Name: "; cin >> lname;
    cout << "Enter 10-Digit Phone Number: "; cin >> phone_num;

    if (isValidPhoneNumber(phone_num)) {
        phoneFile << fname << " " << lname << " " << phone_num << endl;
        cout << "\nContact Saved Successfully!";
    }
    else {
        cout << "\nInvalid phone number. Please enter a 10-digit number containing only digits.";
    }
    phoneFile.close();
    cout << "\nPress any key to continue."; cin.ignore(); cin.get();
}

// Search contact function
void searchContact() {
    ifstream phoneFile("number.txt");
    string keyword;
    bool found = false;

    cout << "\nEnter Name to Search: "; cin >> keyword;
    while (phoneFile >> fname >> lname >> phone_num) {
        if (keyword == fname || keyword == lname) {
            cout << "\nContact Found:\nFirst Name: " << fname << "\nLast Name: " << lname << "\nPhone Number: " << phone_num;
            found = true;
            break;
        }
    }
    if (!found) cout << "\nNo contact found.";
    phoneFile.close();
    cout << "\nPress any key to continue."; cin.ignore(); cin.get();
}

// Remove contact function
void removeContact() {
    ifstream phoneFile("number.txt");
    ofstream tempFile("temp.txt");
    string keyword;
    bool found = false;

    cout << "\nEnter Name to Remove: "; cin >> keyword;
    while (phoneFile >> fname >> lname >> phone_num) {
        if (keyword == fname || keyword == lname) {
            cout << "\nContact Removed:\nFirst Name: " << fname << "\nLast Name: " << lname << "\nPhone Number: " << phone_num;
            found = true;
        }
        else {
            tempFile << fname << " " << lname << " " << phone_num << endl;
        }
    }
    phoneFile.close();
    tempFile.close();
    remove("number.txt");
    rename("temp.txt", "number.txt");

    if (!found) cout << "\nNo contact found.";
    cout << "\nPress any key to continue."; cin.ignore(); cin.get();
}

// Function to validate if the phone number is 10 digits long and contains only digits
bool isValidPhoneNumber(const string& number) {
    return number.length() == 10 && all_of(number.begin(), number.end(), ::isdigit);
}
