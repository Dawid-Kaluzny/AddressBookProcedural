#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>

using namespace std;

struct UserData {
    int id;
    string login, password;
};

struct ContactData {
    int id;
    string firstName, lastName, phoneNumber, email, address;
};

int addNewUser(vector <UserData>& users, int numberOfUsers) {
    string login, password;
    int id = 1;
    fstream usersFile;

    cin.sync();
    cout << "Enter login: ";
    getline(cin, login, '\n');
    cout << "Enter password: ";
    getline(cin, password, '\n');

    for (int i = 0; i < numberOfUsers; i++) {
        if (users[i].login == login) {
            cout << "Such login already exists! Return to the main menu\n";
            Sleep(1000);
            return numberOfUsers;
        }
    }

    if (numberOfUsers != 0) {
        id = users[numberOfUsers - 1].id + 1;
    }

    users.push_back(UserData {id, login, password});
    usersFile.open("Users.txt", ios::out | ios::app);
    usersFile << id << "|";
    usersFile << login << "|";
    usersFile << password << "|" << endl;
    usersFile.close();
    cout << "User added correctly!\n";
    Sleep(1000);

    return numberOfUsers + 1;
}

int addNewContact(int idLoggedUser, vector <ContactData>& addressBook, int numberOfContacts, int &idLastContactAdressBook) {
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

    id = ++idLastContactAdressBook;

    addressBook.push_back(ContactData {id, firstName, lastName, phoneNumber, email, address});
    addressBookFile.open("Adress_Book.txt", ios::out | ios::app);
    addressBookFile << id << "|";
    addressBookFile << idLoggedUser << "|";
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

int loginUser(vector <UserData>& users, int numberOfUsers) {
    string login, password;

    cin.sync();
    cout << "Enter login: ";
    getline(cin, login, '\n');
    int i = 0;
    while (i < numberOfUsers) {
        if (users[i].login == login) {
            for (int attempt = 0; attempt < 3; attempt++) {
                cout << "Enter password. " << 3 - attempt << " attempts left: ";
                getline(cin, password, '\n');
                if (users[i].password == password) {
                    cout << "You have logged in\n";
                    Sleep(1000);
                    return users[i].id;
                }
            }
            cout << "You have entered the password incorrectly 3 times. Return to the main menu\n";
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "There is no such user!\n";
    Sleep(1000);
    return 0;
}

void viewContact(vector <ContactData>& addressBook, int i) {
    cout << addressBook[i].id << "|";
    cout << addressBook[i].firstName << "|" << addressBook[i].lastName << "|";
    cout << addressBook[i].phoneNumber << "|";
    cout << addressBook[i].email << "|";
    cout << addressBook[i].address << "|" << '\n';
}

void searchFirstName(vector <ContactData>& addressBook, int numberOfContacts) {
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

void searchLastName(vector <ContactData>& addressBook, int numberOfContacts) {
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

void viewAllContacts(vector <ContactData>& addressBook, int numberOfContacts) {
    for (int i = 0; i < numberOfContacts; i++) {
        viewContact(addressBook, i);
    }
    system("pause");
}

int loadDataFileUsers (vector <UserData>& users) {
    fstream usersFile;
    int id;
    string login, password, dataLineUsersFile;
    int lineNumberUsersFile = 1;
    int numberOfUsers = 0;

    if (usersFile.good()) {
        usersFile.open("Users.txt", ios::in);
        while(getline(usersFile, dataLineUsersFile, '|')) {
            switch(lineNumberUsersFile) {
            case 1:
                id = atoi(dataLineUsersFile.c_str());
                break;
            case 2:
                login = dataLineUsersFile;
                break;
            case 3:
                password = dataLineUsersFile;
                break;
            }
            if (lineNumberUsersFile == 3) {
                users.push_back(UserData {id, login, password});
                lineNumberUsersFile = 0;
                numberOfUsers++;
            }
            lineNumberUsersFile++;
        }
        usersFile.close();
    }
    return numberOfUsers;
}

int loadDataFileAddressBook (int idLoggedUser, vector <ContactData>& addressBook, int &idLastContactAdressBook) {
    fstream addressBookFile;
    int idUser, idContact;
    string firstName, lastName, phoneNumber, email, address, dataLineAddressBookFile;
    int lineNumberAddressBookFile = 1;
    int numberOfContacts = 0;

    if (addressBookFile.good()) {
        addressBookFile.open("Adress_Book.txt", ios::in);
        while(getline(addressBookFile, dataLineAddressBookFile, '|')) {
            switch(lineNumberAddressBookFile) {
            case 1:
                idContact = atoi(dataLineAddressBookFile.c_str());
                break;
            case 2:
                idUser = atoi(dataLineAddressBookFile.c_str());
                break;
            case 3:
                firstName = dataLineAddressBookFile;
                break;
            case 4:
                lastName = dataLineAddressBookFile;
                break;
            case 5:
                phoneNumber = dataLineAddressBookFile;
                break;
            case 6:
                email = dataLineAddressBookFile;
                break;
            case 7:
                address = dataLineAddressBookFile;
                break;
            }
            if (lineNumberAddressBookFile == 7) {
                if (idUser == idLoggedUser) {
                    addressBook.push_back(ContactData {idContact, firstName, lastName, phoneNumber, email, address});
                    numberOfContacts++;
                }
                idLastContactAdressBook = idContact;
                lineNumberAddressBookFile = 0;
            }
            lineNumberAddressBookFile++;
        }
        addressBookFile.close();
    }
    return numberOfContacts;
}

int deleteContactData(vector <ContactData>& addressBook, int numberOfContacts) {
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

void editContactData(vector <ContactData>& addressBook, int numberOfContacts) {
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
    vector <UserData> users;
    vector <ContactData> addressBook;
    char userSelection;
    int idLoggedUser = 0;
    int numberOfUsers = 0;
    int numberOfContacts = 0;
    int idLastContactAdressBook = 0;

    numberOfUsers = loadDataFileUsers(users);

    while(1) {
        if (idLoggedUser == 0) {
            system("cls");
            cout << "---ADRESS BOOK---\n";
            cout << "1. Log in\n";
            cout << "2. Registration\n";
            cout << "3. Exit\n";
            cout << "Your choice: ";
            cin >> userSelection;

            switch(userSelection) {
            case '1':
                idLoggedUser = loginUser(users, numberOfUsers);
                if (idLoggedUser != 0)
                    numberOfContacts = loadDataFileAddressBook(idLoggedUser, addressBook, idLastContactAdressBook);
                break;
            case '2':
                numberOfUsers = addNewUser(users, numberOfUsers);
                break;
            case '3':
                exit (0);
            }
        } else {
            system("cls");
            cout << "---ADRESS BOOK---\n";
            cout << "1. Add contact\n";
            cout << "2. Search by first name\n";
            cout << "8. Log out\n";
            cout << "Your choice: ";
            cin >> userSelection;

            switch(userSelection) {
            case '1':
                numberOfContacts = addNewContact(idLoggedUser, addressBook, numberOfContacts, idLastContactAdressBook);
                break;
            case '2':
                searchFirstName(addressBook, numberOfContacts);
                break;
            case '8':
                addressBook.clear();
                idLoggedUser = 0;
                break;
            }
        }
        /*
            cout << "3. Search by last name\n";
            cout << "4. View all contacts\n";
            cout << "5. Delete contact\n";
            cout << "6. Edit contact\n";

            case '3':
                searchLastName(addressBook, numberOfContacts);
                break;
            case '4':
                viewAllContacts(addressBook, numberOfContacts);
                break;
            case '5':
                numberOfContacts = deleteContactData(addressBook, numberOfContacts);
                break;
            case '6':
                editContactData(addressBook, numberOfContacts);
                break;
        */
    }
}
