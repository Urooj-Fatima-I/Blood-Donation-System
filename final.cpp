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

//global variables and constants for summary for summary
int blood_donated;
int blood_requested;
int no_of_donors=0;
int donor_index=0;
string blood_types[8] = { "A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-" };
int donatedByType[8] = {0};
int requestedByType[8] = {0};
const int low_stock = 5;


//global array for donors added
Donor new_donors[100];


// function delaration
void displayMenu();
bool checkEligibility();
bool isValidname(char[]);
bool isValidblood(char[]);
bool isValidphone(string);
void addDonor();
void viewDonor();
void donate_request(bool);
void searchDonor();
void summary();

// main function
int main() {

    cout << "\033[31m";
    cout << "\t\t\t--------------------------------------\n";
    cout << "\t\t\tWELCOME TO ASAAN BLOOD DONATION SYSTEM\n";
    cout << "\t\t\t--------------------------------------\n";
    cout << "\033[0m";
    int choice;
    do {
        bool test = 0;
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
            searchDonor(); //to search donor by blood group
            break;
        case 4:
            summary();
            break;
        case 5:
           int request;
            while(true)
            {
            cout << "Enter 0 if you want do donate\nEnter 1 if you want do Request" << endl;
            cin >> request;
            if(request==1||request==0)
                break;
            else
            cout<<"Invalid Input Try Agian\n";}
            donate_request(request);
            break;
        case 6:
            cout << "Asaan Blood Donation Management System is designed to simplify and streamline the process of blood donation and distribution.\n";
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
    {
        cout << "Invalid Blood type Enter again" << endl;
        return false;
    }
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
    //increment for summary
    no_of_donors++;
    //saving in array for summary
    new_donors[donor_index++] = D;

    cout << "\033[31m";
    cout << "\t\t\t--------------------------------------\n";
    cout << "\033[0m";
    cout << "If you want to donate blood now, Press \033[31m0\033[0m\n";
    cout << "If you only want to get registered as a donor, press \033[31m1\033[0m\n";
    do {
        cout << "Enter your choice: ";
        cin >> donate;
        if (donate == 0) {
            //calling function and bool variable will tell weather to donate or request
            donate_request(donate);
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
//view donor
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

void searchDonor() {
    ifstream file("Donor_data.txt");
    if (!file) {
        cout << "No donor records found.\n";
        return;
    }

    string blood;
    cout << "Enter blood group to search: ";
    cin >> blood;

    while (!isValidblood(&blood[0])) { // validate blood group
        cout << "Enter valid blood group: ";
        cin >> blood;
    }

    string line;
    bool found = false;
    cout << "\033[31m";
    cout << "\t\t\t--------------------------------DONORS FOUND--------------------------------\n";
    cout << "\033[0m";
    while (getline(file, line)) {           // read each line fully
        if (line.find(blood) != string::npos) {  // check if blood group exists in line
            cout << line << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No donors found with blood group " << blood << ".\n";
    }
    cout << "\033[31m";
    cout << "\t\t\t---------------------------------------------------------------------------\n";
    cout << "\033[0m";
    file.close();
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
    do {
        cout << "Enter valid blood type: ";
        cin >> t_type;
    } while (!isValidblood(&t_type[0]));
    cout << "Enter amount(ml): ";
    cin >> t_amount;

    //Search usong loop
    bool found = false;
    int i,j;
    for ( i = 0; i < n; i++)
    {

        if (t_inv[i].type == t_type)
        {
            found = true;
            if (!choose) 
            {
                t_inv[i].amount += t_amount;
                blood_donated+=t_amount; // Donation
            }
            else {
                if (t_inv[i].amount >= t_amount)
                    {t_inv[i].amount -= t_amount;
                    //increament for summary    
                    blood_requested+=t_amount;}
                     // Request
                else {
                    cout << "Not enough blood in stock!" << endl;
                    return;
                }
            }
            //to report how much blood of each type has been added or deleted
        for (j = 0; j < 8; j++) {
        if (blood_types[j] == t_type) {
        if (!choose)
            donatedByType[j] += t_amount;
        else
            requestedByType[j] += t_amount;
        break;
    }
            
        }
        
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

//summary function
void summary()
{
    cout << "\033[31m";
    cout << "\n\t\t\t----------- REPORT -----------\n";
    cout << "\033[0m";
    //stats
    cout << "Total donors added today: " << no_of_donors << endl;
    cout << "Total blood donated today: " << blood_donated << " ml"<<endl;
    cout << "Total blood requested today: " << blood_requested <<" ml"<< endl;
    cout << "\nBlood Donated by Type:\n";
    //according to blood type
    for (int i = 0; i < 8; i++) {
    if (donatedByType[i] > 0)
        cout << blood_types[i] << " : " << donatedByType[i]<<" ml" << endl;
    }

    cout << "\nBlood Requested by Type:\n";
    for (int i = 0; i < 8; i++) {
    if (requestedByType[i] > 0)
        cout << blood_types[i] << " : " << requestedByType[i]<<" ml" << endl;
    }

    //info of new donor added
    cout << "\nDonors added today:\n";

    if (no_of_donors == 0) {
        cout << "No donors added today.\n";
    }
    else {
        //for alignment
        cout << left
             << setw(25) << "Name"
             << setw(10) << "Blood"
             << setw(15) << "Phone" << endl;

        for (int i=0; i<donor_index; i++) 
        {
            cout << setw(25) << new_donors[i].name
                 << setw(10) << new_donors[i].blood_group
                 << setw(15) << new_donors[i].phone
                 << endl;
        }
    }
    //notification for low blodd stock by readind the inventory again in variable invFile
    //opening to read    
    ifstream invFile("inventory.txt");
    bool lowFound = false;

    cout << "\nLOW BLOOD STOCK ALERT:\n";
    //checking if file is opne
    if (invFile.is_open()) 
    {
        string type;
        int units;
        //reading into type and unit
        while (invFile >> type >> units) 
        {
            if (units <= low_stock) 
            {
                cout << type << " : " << units << " ml remaining\n";
                lowFound = true;
            }
        }
        invFile.close();
    }

    if (!lowFound) {
        cout << "All blood types are in stock.\n";
    }


    cout << "\033[31m";
    cout << "\t\t\t-------------------------------------\n";
    cout << "\033[0m";
}
