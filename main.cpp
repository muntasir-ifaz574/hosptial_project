#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

struct Patient {
    char fname[20];
    char sname[20];
    char address[200];
    char contact[10];
    char cnic[100];
    int age;
    char gender[8];
    char blood_gp[5];
    char disease_past[50];
    int id;
    char symptom[500];
    char diagnosis[500];
    char medicine[500];
    char admission[30];
    bool diagnosed;
    string doctorName;
    string appointmentDate;
    Patient* next;

    Patient() {
        next = NULL;
        diagnosed = false;
    }
};

struct Doctor {
    string name;
    string specialization;
    string contact;
    string email;

};

class DoctorManagementSystem {
private:
    vector<Doctor> doctors;

public:
    DoctorManagementSystem() {
        loadData();
    }

    void addDoctor(const Doctor& doctor) {
        doctors.push_back(doctor);
        saveData();
    }

    Doctor* getDoctor(const string& name) {
        for (auto& doctor : doctors) {
            if (doctor.name == name) {
                return &doctor;
            }
        }
        return nullptr;
    }

    void displayDoctorDetails(const string& name) {
        Doctor* doctor = getDoctor(name);
        if (doctor) {
            cout << "Doctor Name: " << doctor->name << endl;
            cout << "Specialization: " << doctor->specialization << endl;
            cout << "Contact: " << doctor->contact << endl;
            cout << "Email: " << doctor->email << endl;

        }
        else {
            cout << "Doctor not found!" << endl;
        }
    }

    void saveData() {
        ofstream file("doctor_data.txt");
        if (!file) {
            cout << "Error opening file to save doctor data!" << endl;
            return;
        }

        file << doctors.size() << endl;

        for (const auto& doctor : doctors) {
            file << doctor.name << endl;
            file << doctor.specialization << endl;
            file << doctor.contact << endl;
            file << doctor.email << endl;
        }

        file.close();
        cout << "Doctor data saved successfully!" << endl;
    }

    void loadData() {
        ifstream file("doctor_data.txt");
        if (!file) {
            cout << "No existing doctor data found." << endl;
            return;
        }

        doctors.clear();

        int count;
        file >> count;
        file.ignore();

        for (int i = 0; i < count; i++) {
            Doctor doctor;
            getline(file, doctor.name);
            getline(file, doctor.specialization);
            getline(file, doctor.contact);
            getline(file, doctor.email);
            doctors.push_back(doctor);
        }

        file.close();
        cout << "Doctor data loaded successfully!" << endl;
    }
};

class HospitalManagementSystem {
private:
    Patient* head;
    int count;
    DoctorManagementSystem doctorSystem;

public:
    HospitalManagementSystem() {
        head = NULL;
        count = 0;
        loadData();
    }

    ~HospitalManagementSystem() {
        saveData();
        clearData();
    }

    void addPatient() {
        Patient* newPatient = new Patient;

        cout << "Enter Patient ID: ";
        cin >> newPatient->id;
        cout << "Enter Patient First Name: ";
        cin >> newPatient->fname;
        cout << "Enter Patient Last Name: ";
        cin >> newPatient->sname;
        cout << "Enter Patient Age: ";
        cin >> newPatient->age;
        cout << "Enter Patient Gender: ";
        cin >> newPatient->gender;
        cout << "Enter Patient Blood Group: ";
        cin >> newPatient->blood_gp;
        cout << "Enter Patient Contact: ";
        cin >> newPatient->contact;
        cout << "Enter Patient NID: ";
        cin.ignore();
        cin.getline(newPatient->cnic, 100);
        cout << "Enter Patient Address: ";
        cin.getline(newPatient->address, 200);

        if (head == NULL) {
            head = newPatient;
        }
        else {
            Patient* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newPatient;
        }

        count++;
        cout << "Patient added successfully!" << endl;
        clearConsole();
        saveData(); // Save patient data after adding
    }

    void displayPatientDetails(int id) {
        Patient* temp = head;
        while (temp != NULL) {
            if (temp->id == id) {
                cout << "Patient ID: " << temp->id << endl;
                cout << "First Name: " << temp->fname << endl;
                cout << "Last Name: " << temp->sname << endl;
                cout << "Age: " << temp->age << endl;
                cout << "Gender: " << temp->gender << endl;
                cout << "Blood Group: " << temp->blood_gp << endl;
                cout << "Contact: " << temp->contact << endl;
                cout << "CNIC: " << temp->cnic << endl;
                cout << "Address: " << temp->address << endl;
                cout << "Diagnosed: " << (temp->diagnosed ? "Yes" : "No") << endl;

                if (temp->diagnosed) {
                    cout << "Symptoms: " << temp->symptom << endl;
                    cout << "Diagnosis: " << temp->diagnosis << endl;
                    cout << "Medicine: " << temp->medicine << endl;
                    cout << "Admission Required: " << temp->admission << endl;
                }

                return;
            }
            temp = temp->next;
        }

        cout << "Patient not found!" << endl;
        clearConsole();
    }

    void updatePatientDetails(int id) {
        Patient* temp = head;
        while (temp != NULL) {
            if (temp->id == id) {
                cout << "Update Options:" << endl;
                cout << "1. First Name" << endl;
                cout << "2. Last Name" << endl;
                cout << "3. Age" << endl;
                cout << "4. Gender" << endl;
                cout << "5. Blood Group" << endl;
                cout << "6. Contact" << endl;
                cout << "7. CNIC" << endl;
                cout << "8. Address" << endl;
                cout << "Enter your choice: ";

                int choice;
                cin >> choice;

                switch (choice) {
                case 1:
                    cout << "Enter First Name: ";
                    cin >> temp->fname;
                    break;
                case 2:
                    cout << "Enter Last Name: ";
                    cin >> temp->sname;
                    break;
                case 3:
                    cout << "Enter Age: ";
                    cin >> temp->age;
                    break;
                case 4:
                    cout << "Enter Gender: ";
                    cin >> temp->gender;
                    break;
                case 5:
                    cout << "Enter Blood Group: ";
                    cin >> temp->blood_gp;
                    break;
                case 6:
                    cout << "Enter Contact: ";
                    cin >> temp->contact;
                    break;
                case 7:
                    cout << "Enter CNIC: ";
                    cin.ignore();
                    cin.getline(temp->cnic, 100);
                    break;
                case 8:
                    cout << "Enter Address: ";
                    cin.ignore();
                    cin.getline(temp->address, 200);
                    break;
                default:
                    cout << "Invalid option!" << endl;
                    return;
                }

                cout << "Patient information updated successfully!" << endl;
                clearConsole();
                saveData(); // Save patient data after updating
                return;
            }
            temp = temp->next;
        }

        cout << "Patient not found!" << endl;
        clearConsole();
    }

    void diagnosePatient(int id) {
        Patient* temp = head;
        while (temp != NULL) {
            if (temp->id == id) {
                cout << "Enter Symptoms: ";
                cin.ignore();
                cin.getline(temp->symptom, 500);
                cout << "Enter Diagnosis: ";
                cin.getline(temp->diagnosis, 500);
                cout << "Enter Medicines: ";
                cin.getline(temp->medicine, 500);
                cout << "Admission Required to Hospital? ";
                cin.getline(temp->admission, 30);

                temp->diagnosed = true;
                cout << "Patient diagnosed successfully!" << endl;
                clearConsole();
                saveData(); // Save patient data after diagnosing
                return;
            }
            temp = temp->next;
        }

        cout << "Patient not found!" << endl;
        clearConsole();
    }

    void deletePatient(int id) {
        if (head == NULL) {
            cout << "List is empty. No patient to delete!" << endl;
            clearConsole();
            return;
        }

        if (head->id == id) {
            Patient* temp = head;
            head = head->next;
            delete temp;
            count--;
            cout << "Patient deleted successfully!" << endl;
            clearConsole();
            saveData(); // Save patient data after deleting
            return;
        }

        Patient* prev = head;
        Patient* current = head->next;
        while (current != NULL) {
            if (current->id == id) {
                prev->next = current->next;
                delete current;
                count--;
                cout << "Patient deleted successfully!" << endl;
                clearConsole();
                saveData(); // Save patient data after deleting
                return;
            }
            prev = current;
            current = current->next;
        }

        cout << "Patient not found!" << endl;
        clearConsole();
    }

    void clearData() {
        Patient* temp = head;
        while (temp != NULL) {
            Patient* next = temp->next;
            delete temp;
            temp = next;
        }
        head = NULL;
        count = 0;
    }

    void saveData() {
        ofstream file("patient_data.txt");
        if (!file) {
            cout << "Error opening file to save data!" << endl;
            return;
        }

        file << count << endl;

        Patient* temp = head;
        while (temp != NULL) {
            file << temp->id << endl;
            file << temp->fname << endl;
            file << temp->sname << endl;
            file << temp->age << endl;
            file << temp->gender << endl;
            file << temp->blood_gp << endl;
            file << temp->contact << endl;
            file << temp->cnic << endl;
            file << temp->address << endl;
            file << temp->diagnosed << endl;
            file << temp->doctorName << endl;
            file << temp->diagnosed << endl;
            file << temp->doctorName << endl;
            file << temp->appointmentDate << endl;

            if (temp->diagnosed) {
                file << temp->symptom << endl;
                file << temp->diagnosis << endl;
                file << temp->medicine << endl;
                file << temp->admission << endl;
            }

            temp = temp->next;
        }

        file.close();
        cout << "Data saved successfully!" << endl;
    }

    void loadData() {
        ifstream file("patient_data.txt");
        if (!file) {
            cout << "No existing data found." << endl;
            return;
        }

        clearData();

        file >> count;
        file.ignore();

        for (int i = 0; i < count; i++) {
            Patient* newPatient = new Patient;

            file >> newPatient->id;
            file.ignore();
            file >> newPatient->fname;
            file.ignore();
            file >> newPatient->sname;
            file.ignore();
            file >> newPatient->age;
            file.ignore();
            file >> newPatient->gender;
            file.ignore();
            file >> newPatient->blood_gp;
            file.ignore();
            file >> newPatient->contact;
            file.ignore();
            file.getline(newPatient->cnic, 100);
            file.getline(newPatient->address, 200);
            file >> newPatient->diagnosed;
            file.ignore();
            file.getline(newPatient->symptom, 500);
            file.getline(newPatient->diagnosis, 500);
            file.getline(newPatient->medicine, 500);
            file.getline(newPatient->admission, 30);

            if (head == NULL) {
                head = newPatient;
            } else {
                Patient* temp = head;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newPatient;
            }
        }

        file.close();
        cout << "Data loaded successfully!" << endl;
    }

    void displayWelcomeMessage() {
        cout << "-------------------------------------" << endl;
        cout << "           WELCOME TO                " << endl;
        cout << "                                     " << endl;
        cout << "   HOSPITAL MANAGEMENT SYSTEM        " << endl;
        cout << "-------------------------------------" << endl;
    }

    void displayExitMessage() {
        cout << "-------------------------------------" << endl;
        cout << "     THANK YOU FOR USING              " << endl;
        cout << "                                     " << endl;
        cout << "   HOSPITAL MANAGEMENT SYSTEM        " << endl;
        cout << "-------------------------------------" << endl;
    }

    void displayMenu() {
        cout << "----------------------" << endl;
        cout << "      MAIN MENU       " << endl;
        cout << "----------------------" << endl;
        cout << "1. Add Patient" << endl;
        cout << "2. Display Patient Details" << endl;
        cout << "3. Update Patient Details" << endl;
        cout << "4. Diagnose Patient" << endl;
        cout << "5. Delete Patient" << endl;
        cout << "6. Add Doctor" << endl;
        cout << "7. Display Doctor Details" << endl;
        cout << "8. Schedule Patient Appointment" << endl;
        cout << "9. Display Doctor-wise Appointment List" << endl;
        cout << "10. Logout" << endl;
        cout << "----------------------" << endl;
        cout << "Enter your choice: ";
    }

    void clearConsole() {
        cin.ignore();
        cout << "Press Enter to continue...";
        cin.get();
        system("cls");
    }

    void scheduleAppointment(int id) {
        Patient* temp = head;
        while (temp != NULL) {
            if (temp->id == id) {
                cout << "Enter Appointment Date and Time: ";
                cin.ignore();
                getline(cin, temp->appointmentDate);

                cout << "Enter Doctor Name: ";
                string doctorName;
                getline(cin, doctorName);
                temp->doctorName = doctorName;

                Doctor* doctor = doctorSystem.getDoctor(doctorName);
                if (doctor) {
                    cout << "Appointment Scheduled Successfully!" << endl;
                } else {
                    cout << "Doctor not found!" << endl;
                }

                clearConsole();
                saveData(); // Save patient data after scheduling appointment
                return;
            }
            temp = temp->next;
        }

        cout << "Patient not found!" << endl;
        clearConsole();
    }


    void displayDoctorAppointments(const string& doctorName) {
    Patient* temp = head;
    bool found = false;

    cout << "Doctor-wise Appointment List for " << doctorName << ":" << endl;

    while (temp != NULL) {
        if (temp->doctorName == doctorName) {
            cout << "Patient ID: " << temp->id << " | Appointment: " << temp->appointmentDate << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "No appointments found for this doctor." << endl;
    }

    clearConsole();
}






    void run() {
        string password;
        cout << "Enter the password: ";
        cin >> password;

        if (password != "password") {
            cout << "Incorrect password. Exiting..." << endl;
            return;
        }

        displayWelcomeMessage();
        bool isRunning = true;

        while (isRunning) {
            displayMenu();
            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    addPatient();
                    break;
                case 2: {
                    int id;
                    cout << "Enter Patient ID: ";
                    cin >> id;
                    displayPatientDetails(id);
                    break;
                }
                case 3: {
                    int id;
                    cout << "Enter Patient ID: ";
                    cin >> id;
                    updatePatientDetails(id);
                    break;
                }
                case 4: {
                    int id;
                    cout << "Enter Patient ID: ";
                    cin >> id;
                    diagnosePatient(id);
                    break;
                }
                case 5: {
                    int id;
                    cout << "Enter Patient ID: ";
                    cin >> id;
                    deletePatient(id);
                    break;
                }
                case 6: {
                    Doctor newDoctor;
                    cout << "Enter Doctor Name: ";
                    cin.ignore();
                    getline(cin, newDoctor.name);
                    cout << "Enter Doctor Specialization: ";
                    getline(cin, newDoctor.specialization);
                    cout << "Enter Doctor Contact: ";
                    getline(cin, newDoctor.contact);
                    cout << "Enter Doctor Email: ";
                    getline(cin, newDoctor.email);

                    doctorSystem.addDoctor(newDoctor);
                    cout << "Doctor added successfully!" << endl;
                    clearConsole();
                    break;
                }
                case 7: {
                    string name;
                    cout << "Enter Doctor Name: ";
                    cin.ignore();
                    getline(cin, name);
                    doctorSystem.displayDoctorDetails(name);
                    break;
                }
                case 8: {
                    int id;
                    cout << "Enter Patient ID: ";
                    cin >> id;
                    scheduleAppointment(id);
                    break;
                }case 9: {
                    string doctorName;
                    cout << "Enter Doctor Name: ";
                    cin.ignore();
                    getline(cin, doctorName);
                    displayDoctorAppointments(doctorName);
                    break;
                }
                case 10:
                    isRunning = false;
                    break;
                default:
                    cout << "Invalid choice!" << endl;
                    break;
            }

            clearConsole();
        }

        displayExitMessage();
    }
};

int main() {
    HospitalManagementSystem system;
    system.run();

    return 0;
}
