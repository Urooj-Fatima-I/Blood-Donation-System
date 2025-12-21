#include <iostream>
using namespace std;
// function delaration
void displayMenu();
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
           //to add new donor data
            break;
        case 2:
          // to view all saved data
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