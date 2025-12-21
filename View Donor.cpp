#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
// structure for data of donor 
struct Donor {
    char name[30];
    char blood_group[6];
    string phone;
};

// function delaration
void displayMenu();
bool checkEligibility();
bool isValidname(char[]);
bool isValidblood(char[]);
bool isValidphone(string);
void addDonor();
void viewDonor();

// main function
int main() {
    cout << "\033[31m";
    cout << "\t\t\t--------------------------------------\n";
    cout << "\t\t\tWELCOME TO ASAAN BLOOD DONATION SYSTEM\n";
    cout << "\t\t\t--------------------------------------\n";
    cout << "\033[0m";
    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        // switch statement to choose from menu
        switch (choice) {
        case 1:
          addDonor(); //to add new donor data
            break;
        case 2:
            viewDonor(); // to view all saved data
            break;
        case 3:
            //search

            break;
        case 4:
            //view summary
            break;
        case 5:
            //request blood
            break;
        case 6:
            cout << "\033[31mAsaan Blood Donation Management \033[0mSystem is designed to simplify and streamline the process of blood donation and distribution.\n";
            cout << "Our goal is to connect donors, blood banks, and recipients through a secure and efficient platform, ensuring timely availability of safe blood.\n";
            cout << "We aim to save lives by improving coordination, reducing delays, and promoting voluntary blood donation.\n";
            cout << "\033[31m";
            cout << "\t\t\t--------------------------------------\n";
            cout << "\033[0m";
            break;
        case 7:
            cout << "\033[31m";
            cout << "You have successfully exited the program.";
            cout << "\033[0m";
            break;
        default:
            cout << "Invalid Input!";
        }
    } while (choice != 7);
    return 0;
}
// function definition
void displayMenu() {
    cout << "\n1. Press \033[31m1\033[0m to add a donor.\n2. Press \033[31m2\033[0m to view donor list.\n3. Press \033[31m3\033[0m to search donor.\n4. Press \033[31m4\033[0m to view summary.\n5. Press \033[31m5\033[0m to request blood.\n6. About us.\n7. Exit program.\n";
    cout << "\033[31m";
    cout << "\t\t\t--------------------------------------\n";
    cout << "\033[0m";
}
bool checkEligibility() {
    int age, valid;
    cout << "Enter your age: ";
    cin >> age;
    if (age < 18 || age > 60) {
        cout << "\033[31m";
        cout << "Sorry! you are not eligible to donate blood. Age must be between 18 and 60.\n";
        cout << "\033[0m";
        return false;
    }
    cout << "Have you donated blood in last three months?\n";
    cout << "If yes, press \033[31m1 \033[0m \nIf no, press \033[31m0 \033[0m \n";
    do {
        cout << "Enter your choice: ";
        cin >> valid;
        if (valid == 1) {
            cout << "\033[31m";
            cout << "Sorry! you are not eligible to donate blood.\n";
            cout << "\033[0m";
            return false;
        }
        else if (valid == 0) {
            cout << "You are eligible to donate blood!\n";
            return true;
        }
        else {
            cout << "Invalid input!";
        }
    } while (valid != 1 && valid != 0);
}
bool isValidname(char Name[]) {
    int i = 0;
    // checking condition for name to be valid and not empty
    while (Name[i] != '\0') {
        if (Name[i] != ' ') {
            return true; //valid
        }
        i++;
    }
    return false;
}
bool isValidblood(char blood[]) {
    // checking all possible condition for valid entry
    if ((blood[0] == 'A' && blood[1] == 'B' && (blood[2] == '+' || blood[2] == '-') && blood[3] == '\0') ||
        ((blood[0] == 'A' || blood[0] == 'B' || blood[0] == 'O') &&
            (blood[1] == '+' || blood[1] == '-') && blood[2] == '\0')) {
        return true; //valid
    }
    else
        return false;
}
bool isValidphone(string phone) {
    {
        // Check length
        if (phone.length() != 11)
            return false;

        // Check all characters are digits
        for (int i = 0; i < phone.length(); i++)  // initialization; condition; increment
        {
            if (!isdigit(phone[i])) // check if the character is not a digit
                return false;
        }

        return true; // valid
    }
}
void addDonor() {
    if (!checkEligibility()) {
        return;
    }
    // if eligible
    bool donate;
    Donor D;
    ofstream file;
    file.open("Donor_data.txt", ios::app); //opening a text file
    if (!file) {
        cout << "Unable to open file for writing!\n";
        return;
    }
    cin.ignore();
    // asks for input unless it is entered correctly
    do {
        cout << "Enter your name: ";
        cin.getline(D.name, 30);
    } while (!isValidname(D.name));
    do {
        cout << "Enter your Blood group(A+,A-,B+,B-,AB+,AB-,O+,O-): ";
        cin.getline(D.blood_group, 6);
    } while (!isValidblood(D.blood_group));
    do {
        cout << "Enter your phone number(11 digits): ";
        getline(cin, D.phone);
    } while (!isValidphone(D.phone));
    // saving data in a file
    file << left << setw(30) << D.name << setw(6) << D.blood_group << setw(12) << D.phone << endl;
    file.close();
    cout << "Donor added successfully!\n";
    cout << "\033[31m";
    cout << "\t\t\t--------------------------------------\n";
    cout << "\033[0m";
    cout << "If you want to donate blood now, Press 0\n";
    cout << "If you only want to get registered as a donor, press 1\n";
    do {
        cout << "Enter your choice: ";
        cin >> donate;
        if (donate == 0) {
            // continue Urooj

        }
        else if (donate == 1) {
            cout << "Your record has been saved, Thank You!\n";
            cout << "\033[31m";
            cout << "\t\t\t--------------------------------------\n";
            cout << "\033[0m";
            return;
        }
        else {
            cout << "Invalid input!";
        }
    } while (donate != 1 && donate != 0);
}
void viewDonor() {
    ifstream file("Donor_data.txt");
    if (!file) {
        cout << "No donor records found.\n";
        return;
    }
    string list;
    cout << "\033[31m";
    cout << "\t\t\t--------------------------------DONOR LIST--------------------------------\n";
    cout << "\033[0m";
    while (getline(file, list)) {
        cout << list << endl;
    }
    cout << "\033[31m";
    cout << "\t\t\t---------------------------------------------------------------------------\n";
    cout << "\033[0m";
    file.close(); // closing the file
}