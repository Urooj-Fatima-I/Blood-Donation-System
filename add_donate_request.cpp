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

//strucrure for blood inventiry
struct Blood {
    string type;
    int amount;
};




// function delaration
void displayMenu();
bool checkEligibility();
bool isValidname(char[]);
bool isValidblood(char[]);
bool isValidphone(string);
void addDonor();
void viewDonor();
void donate_request(bool);

// main function
int main() {
    cout << "\t\t\t--------------------------------------\n";
    cout << "\t\t\tWELCOME TO ASAAN BLOOD DONATION SYSTEM\n";
    cout << "\t\t\t--------------------------------------\n";
    int choice;
    do { bool test = 0;
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
    
            break;
        case 4:
            //view summary
            break;
        case 5:
            //request blood
            break;
        case 6:
            cout << "Asaan Blood Donation Management System is designed to simplify and streamline the process of blood donation and distribution.\n";
            cout << "Our goal is to connect donors, blood banks, and recipients through a secure and efficient platform, ensuring timely availability of safe blood.\n";
            cout << "We aim to save lives by improving coordination, reducing delays, and promoting voluntary blood donation.\n";
            cout << "\t\t\t--------------------------------------\n";
            break;
        case 7:
            cout << "You have successfully exited the program.";
            break;
        default:
            cout << "Invalid Input!";
        }
    } while (choice != 7);
    return 0;
}
// function definition
void displayMenu() {
    cout << "\n1. Press 1 to add a donor.\n2. Press 2 to view donor list.\n3. Press 3 to search donor.\n4. Press 4 to view summary.\n5. Press 5 to request blood.\n6. About us.\n7. Exit program.\n";
    cout << "\t\t\t--------------------------------------\n";
}
bool checkEligibility() {
    int age, valid;
    cout << "Enter your age: ";
    cin >> age;
    if (age < 18 || age > 60) {
        cout << "Sorry! you are not eligible to donate blood. Age must be between 18 and 60.\n";
        return false;
    }
    cout << "Have you donated blood in last three months?\n";
    cout << "If yes, press 1\nIf no, press 0\n";
    do {
        cout << "Enter your choice: ";
        cin >> valid;
        if (valid == 1) {
            cout << "Sorry! you are not eligible to donate blood.\n";
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
          getline(cin,D.phone);
        } while (!isValidphone(D.phone));
        // saving data in a file
        file << left << setw(30) << D.name << setw(6) << D.blood_group << setw(12) << D.phone << endl;
        file.close();
        cout << "Donor added successfully!\n";
        cout << "\t\t\t--------------------------------------\n";
        cout << "If you want to donate blood now, Press 0\n";
        cout << "If you only want to get registered as a donor, press 1\n";
        do {
            cout << "Enter your choice: ";
            cin >> donate;
            if (donate == 0) {
                //calling function and bool variable will tell weather to donate or request
                donate_request(donate);
            }
            else if (donate == 1) {
                cout << "Your record has been saved, Thank You!\n";
                 cout << "\t\t\t--------------------------------------\n";
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
    cout << "\t\t\t--------------------------------DONOR LIST--------------------------------\n";
    while (getline(file, list)) {
        cout << list << endl;
    }
    cout << "\t\t\t----------------------------------------------------------------------------\n";
    file.close(); // closing the file
}

 

void donate_request(bool choose)
{
    int n = 0;
    Blood t_inv[100];
    string t_type;
    int t_amount;

    // reading file to make copy into array
    ifstream readFile("inventory.txt");
    if (readFile.is_open()) {
        while (n < 100 && readFile >> t_inv[n].type >> t_inv[n].amount) 
        {
            n++;
        }
        readFile.close();
    }

    //Take Input into temporary variables
    cout << "Enter blood type: ";
    cin >> t_type;
    cout << "Enter amount: ";
    cin >> t_amount;

    //Search usong loop
    bool found = false;
    for (int i = 0; i < n; i++) 
    {

        if (t_inv[i].type == t_type) 
        { 
            found = true;
            if (!choose) {
                t_inv[i].amount += t_amount; // Donation
            } else {
                if (t_inv[i].amount >= t_amount)
                    t_inv[i].amount -= t_amount; // Request
                else {
                    cout << "Not enough blood in stock!" << endl;
                    return;
                }
            }
            break;
        }
    }

   

    //Saveing to File using
    ofstream writeFile("inventory.txt");
    for (int i = 0; i < n; i++) 
    {
        writeFile << t_inv[i].type << " " << t_inv[i].amount << endl;
    }
    writeFile.close();

    cout << (choose ? "Request processed" : "Donation successful") << endl;
}






    


