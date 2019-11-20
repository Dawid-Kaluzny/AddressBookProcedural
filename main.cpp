#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>

using namespace std;

struct UserData {
    int id;
    string firstName, lastName, phoneNumber, email, address;
};

int addNewContact(vector <UserData>& addressBook, int numberOfContacts) {
    string firstName, lastName, phoneNumber, email, address;
    int id = 1;
    fstream addressBookFile;

    cin.sync();
    cout << "Enter first name: ";
    getline(cin, firstName, '\n');
    cout << "Enter last name: ";
    getline(cin, lastName, '\n');
    cout << "Enter phone number: ";
    getline(cin, phoneNumber, '\n');
    cout << "Enter email: ";
    getline(cin, email, '\n');
    cout << "Enter adress: ";
    getline(cin, address, '\n');

    for (int i = 0; i < numberOfContacts; i++) {
        if (addressBook[i].firstName == firstName && addressBook[i].lastName == lastName && addressBook[i].phoneNumber == phoneNumber && addressBook[i].email == email && addressBook[i].address == address) {
            cout << "Such contact already exists! Return to the main menu\n";
            Sleep(1000);
            return numberOfContacts;
        }
    }

    if (numberOfContacts != 0) {
        id = addressBook[numberOfContacts - 1].id + 1;
    }

    addressBook.push_back(UserData {id, firstName, lastName, phoneNumber, email, address});
    addressBookFile.open("Adress_Book.txt", ios::out | ios::app);
    addressBookFile << id << "|";
    addressBookFile << firstName << "|";
    addressBookFile << lastName << "|";
    addressBookFile << phoneNumber << "|";
    addressBookFile << email << "|";
    addressBookFile << address << "|" << endl;
    addressBookFile.close();
    cout << "Contact added correctly!\n";
    Sleep(1000);

    return numberOfContacts + 1;
}

void viewContact(vector <UserData>& addressBook, int i) {
    cout << addressBook[i].id << "|";
    cout << addressBook[i].firstName << "|" << addressBook[i].lastName << "|";
    cout << addressBook[i].phoneNumber << "|";
    cout << addressBook[i].email << "|";
    cout << addressBook[i].address << "|" << '\n';
}

void searchFirstName(vector <UserData>& addressBook, int numberOfContacts) {
    string firstName;

    cin.ignore();
    cout << "Enter first name: ";
    getline(cin, firstName, '\n');
    cout << endl;

    for (int i = 0; i < numberOfContacts; i++) {
        if (addressBook[i].firstName == firstName) {
            viewContact(addressBook, i);
        }
    }
    system("pause");
}

void searchLastName(vector <UserData>& addressBook, int numberOfContacts) {
    string lastName;

    cin.ignore();
    cout << "Enter last name: ";
    getline(cin, lastName, '\n');
    cout << endl;

    for (int i = 0; i < numberOfContacts; i++) {
        if (addressBook[i].lastName == lastName) {
            viewContact(addressBook, i);
        }
    }
    system("pause");
}

void viewAllContacts(vector <UserData>& addressBook, int numberOfContacts) {
    for (int i = 0; i < numberOfContacts; i++) {
        viewContact(addressBook, i);
    }
    system("pause");
}

int loadDataFileAddressBook (vector <UserData>& addressBook, int numberOfContacts) {
    fstream addressBookFile;
    int id;
    string firstName, lastName, phoneNumber, email, address, dataLineAddressBookFile;
    int lineNumberAddressBookFile = 1;

    if (addressBookFile.good()) {
        addressBookFile.open("Adress_Book.txt", ios::in);
        while(getline(addressBookFile, dataLineAddressBookFile, '|')) {
            switch(lineNumberAddressBookFile) {
            case 1:
                id = atoi(dataLineAddressBookFile.c_str());
                break;
            case 2:
                firstName = dataLineAddressBookFile;
                break;
            case 3:
                lastName = dataLineAddressBookFile;
                break;
            case 4:
                phoneNumber = dataLineAddressBookFile;
                break;
            case 5:
                email = dataLineAddressBookFile;
                break;
            case 6:
                address = dataLineAddressBookFile;
                break;
            }
            if (lineNumberAddressBookFile == 6) {
                addressBook.push_back(UserData {id, firstName, lastName, phoneNumber, email, address});
                lineNumberAddressBookFile = 0;
                numberOfContacts++;
            }
            lineNumberAddressBookFile++;
        }
        addressBookFile.close();
    }
    return numberOfContacts;
}

int deleteUserData(vector <UserData>& addressBook, int numberOfContacts) {
    int id;
    char userSelection;
    fstream addressBookFile;

    cin.ignore();
    cout << "Enter the user ID: ";
    cin >> id;
    cout << endl;

    for (int i = 0; i < numberOfContacts; i++) {
        if (addressBook[i].id == id) {
            viewContact(addressBook, i);

            cout << '\n' << "Are you sure you want to delete this user?[y/n]";
            cin >> userSelection;

            if (userSelection == 'y') {
                addressBook.erase(addressBook.begin() + i);
                remove("Adress_Book.txt");
                addressBookFile.open("Adress_Book.txt", ios::out | ios::app);
                for (int j = 0; j < addressBook.size(); j++) {
                    addressBookFile << addressBook[j].id << "|";
                    addressBookFile << addressBook[j].firstName << "|";
                    addressBookFile << addressBook[j].lastName << "|";
                    addressBookFile << addressBook[j].phoneNumber << "|";
                    addressBookFile << addressBook[j].email << "|";
                    addressBookFile << addressBook[j].address << "|" << endl;
                }
                cout << "The contact has been deleted!\n";
                Sleep(1000);
                addressBookFile.close();
                return numberOfContacts - 1;
            } else {
                cout << "The contact has not been deleted!\n";
                Sleep(1000);
                return numberOfContacts;
            }
        }
    }
    cout << "There is no contact with this ID!\n";
    Sleep(1000);
    return numberOfContacts;
}

void editUserData(vector <UserData>& addressBook, int numberOfContacts) {
    string firstName, lastName, phoneNumber, email, address;
    int id;
    char userSelection;
    fstream addressBookFile;

    cin.ignore();
    cout << "Enter the user ID: ";
    cin >> id;

    for (int i = 0; i < numberOfContacts; i++) {
        if (addressBook[i].id == id) {
            system("cls");
            viewContact(addressBook, i);

            cout << '\n' << "EDITION\n";
            cout << "1 - first name\n";
            cout << "2 - last name\n";
            cout << "3 - phone number\n";
            cout << "4 - email\n";
            cout << "5 - adress\n";
            cout << "6 - return to menu\n";
            cout << "Your choice: ";
            cin >> userSelection;
            cin.sync();

            switch (userSelection) {
            case '1': {
                cout << "Enter new first name: ";
                getline(cin, firstName, '\n');
                addressBook[i].firstName = firstName;
                break;
            }
            case '2': {
                cout << "Enter new last name: ";
                getline(cin, lastName, '\n');
                addressBook[i].lastName = lastName;
                break;
            }
            case '3': {
                cout << "Enter new phone number: ";
                getline(cin, phoneNumber, '\n');
                addressBook[i].phoneNumber = phoneNumber;
                break;
            }
            case '4': {
                cout << "Enter new email: ";
                getline(cin, email, '\n');
                addressBook[i].email = email;
                break;
            }
            case '5': {
                cout << "Enter new adress: ";
                getline(cin, address, '\n');
                addressBook[i].address = address;
                break;
            }
            case '6': {
                return;
            }
            default : {
                cout << "Invalid option! try again";
                Sleep(1000);
                i--;
                continue;
            }
            }

            remove("Adress_Book.txt");
            addressBookFile.open("Adress_Book.txt", ios::out | ios::app);
            for (int j = 0; j < addressBook.size(); j++) {
                addressBookFile << addressBook[j].id << "|";
                addressBookFile << addressBook[j].firstName << "|";
                addressBookFile << addressBook[j].lastName << "|";
                addressBookFile << addressBook[j].phoneNumber << "|";
                addressBookFile << addressBook[j].email << "|";
                addressBookFile << addressBook[j].address << "|" << endl;
            }
            cout << "Data has been changed!\n";
            Sleep(1000);
            addressBookFile.close();
            return;
        }
    }
    cout << "There is no contact with this ID!\n";
    Sleep(1000);
}

int main() {
    vector <UserData> addressBook;
    char userSelection;
    int numberOfContacts = 0;

    numberOfContacts = loadDataFileAddressBook(addressBook, numberOfContacts);

    while(1) {
        system("cls");
        cout << "---ADRESS BOOK---\n";
        cout << "1. Add contact\n";
        cout << "2. Search by first name\n";
        cout << "3. Search by last name\n";
        cout << "4. View all contacts\n";
        cout << "5. Delete contact\n";
        cout << "6. Edit contact\n";
        cout << "9. Exit\n";
        cout << "Your choice: ";
        cin >> userSelection;

        switch(userSelection) {
        case '1':
            numberOfContacts = addNewContact(addressBook, numberOfContacts);
            break;
        case '2':
            searchFirstName(addressBook, numberOfContacts);
            break;
        case '3':
            searchLastName(addressBook, numberOfContacts);
            break;
        case '4':
            viewAllContacts(addressBook, numberOfContacts);
            break;
        case '5':
            numberOfContacts = deleteUserData(addressBook, numberOfContacts);
            break;
        case '6':
            editUserData(addressBook, numberOfContacts);
            break;
        case '9':
            exit(0);
        }
    }
}
