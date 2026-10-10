       
#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Patient {
    int id;
    string name;
    int age;
    string disease;
    int visitCount;
    bool isEmergency;
    Patient* next;
};

Patient* head = NULL;
int nextID = 100;
Patient* findPatientByName(string name) {
    Patient* temp = head;
    while (temp != NULL) {
        if (temp->name == name)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void insert_begin(Patient* newNode) {
    newNode->next = head;
    head = newNode;
}

void insert_last(Patient* newNode) {
    if (head == NULL) {
        head = newNode;
        return;
    }

    Patient* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

void delete_begin() {
    if (head == NULL) {
        cout << "List is empty!\n";
        return;
    }

    Patient* temp = head;
    head = head->next;
    delete temp;

    cout << "Deleted from beginning!\n";
}


void delete_last() {
    if (head == NULL) {
        cout << "List is empty!\n";
        return;
    }

    if (head->next == NULL) {
        delete head;
        head = NULL;
        cout << "Deleted from end!\n";
        return;
    }

    Patient* temp = head;
    while (temp->next->next != NULL)
        temp = temp->next;

    delete temp->next;
    temp->next = NULL;

    cout << "Deleted from end!\n";
}

void addPatient() {
    Patient* newNode = new Patient;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Name: ";
    getline(cin, newNode->name);

    cout << "Enter Age: ";
    cin >> newNode->age;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Disease: ";
    getline(cin, newNode->disease);

    cout << "Is Emergency? (1 = Yes, 0 = No): ";
    cin >> newNode->isEmergency;

    Patient* existing = findPatientByName(newNode->name);

    if (existing != NULL) {
        existing->visitCount++;
        cout << "Existing patient found. Visit count increased!\n";
        delete newNode;
        return;
    }

    newNode->id = nextID++;
    newNode->visitCount = 1;
    newNode->next = NULL;
    if (newNode->isEmergency)
        insert_begin(newNode);
    else
        insert_last(newNode);

    cout << "Patient Added! ID = " << newNode->id << endl;
}

void displayPatients() {
    if (head == NULL) {
        cout << "No patients found!\n";
        return;
    }

    Patient* temp = head;
    while (temp != NULL) {
        cout << "\n---------------------\n";
        cout << "ID: " << temp->id << endl;
        cout << "Name: " << temp->name << endl;
        cout << "Age: " << temp->age << endl;
        cout << "Disease: " << temp->disease << endl;
        cout << "Visits: " << temp->visitCount << endl;

        cout << "Priority: " 
             << (temp->isEmergency ? "EMERGENCY ??" : "Normal") 
             << endl;

        temp = temp->next;
    }
}

void searchPatient() {
    int id;
    cout << "Enter Patient ID: ";
    cin >> id;

    Patient* temp = head;

    while (temp != NULL) {
        if (temp->id == id) {
            cout << "\nPatient Found!\n";
            cout << "Name: " << temp->name << endl;
            cout << "Age: " << temp->age << endl;
            cout << "Disease: " << temp->disease << endl;
            cout << "Visits: " << temp->visitCount << endl;
            return;
        }
        temp = temp->next;
    }

    cout << "Patient Not Found!\n";
}

void updatePatient() {
    int id;
    cout << "Enter Patient ID to update: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Patient* temp = head;

    while (temp != NULL) {
        if (temp->id == id) {
            cout << "Enter New Name: ";
            getline(cin, temp->name);

            cout << "Enter New Age: ";
            cin >> temp->age;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');


            cout << "Enter New Disease: ";
            getline(cin, temp->disease);

            cout << "Updated Successfully!\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Patient Not Found!\n";
}


void countPatients() {
    int count = 0;
    Patient* temp = head;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    cout << "Total Patients: " << count << endl;
}


void deletePatient() {
    int choice;
    cout << "1. Delete from Beginning\n2. Delete from End\nChoose: ";
    cin >> choice;

    if (choice == 1)
        delete_begin();
    else
        delete_last();
}

int main() {
    int choice;

    do {
        cout << "\n===== Hospital Management System =====\n";
        cout << "1. Add Patient\n";
        cout << "2. Display Patients\n";
        cout << "3. Search Patient\n";
        cout << "4. Delete Patient\n";
        cout << "5. Update Patient\n";
        cout << "6. Count Patients\n";
        cout << "7. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addPatient(); break;
            case 2: displayPatients(); break;
            case 3: searchPatient(); break;
            case 4: deletePatient(); break;
            case 5: updatePatient(); break;
            case 6: countPatients(); break;
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 7);

    return 0;
}
