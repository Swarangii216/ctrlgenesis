#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Room {
private:
    int roomNumber;
    string studentName;
    bool vacant;

public:
    Room(int num) : roomNumber(num), studentName(""), vacant(true) {}

    int getRoomNumber() const { return roomNumber; }
    string getStudentName() const { return studentName; }
    bool isVacant() const { return vacant; }

    void allotRoom(const string& name) {
        studentName = name;
        vacant = false;
    }
};

class Student {
private:
    string name;
    string rollNo;
    string department;
    int roomNumber;

public:
    Student(string n, string r, string d, int room) : name(n), rollNo(r), department(d), roomNumber(room) {}

    string getName() const { return name; }
    string getRollNo() const { return rollNo; }
    string getDepartment() const { return department; }
    int getRoomNumber() const { return roomNumber; }

    void writeToFile(ofstream& file) const {
        file << name << "," << rollNo << "," << department << "," << roomNumber << endl;
    }
};

Student createStudent() {
    string name, rollNo, department;
    cout << "Enter student name: ";
    getline(cin, name);
    cout << "Enter student roll number: ";
    getline(cin, rollNo);
    cout << "Enter student department: ";
    getline(cin, department);
    return Student(name, rollNo, department, -1);
}

vector<Student> readStudentsFromFile(const string& filename) {
    vector<Student> students;
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return students;
    }

    string line;
    while (getline(file, line)) {
        string name, rollNo, department;
        int roomNumber;
        size_t pos = line.find(',');
        if (pos != string::npos) {
            name = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(',');
            if (pos != string::npos) {
                rollNo = line.substr(0, pos);
                line.erase(0, pos + 1);
                pos = line.find(',');
                if (pos != string::npos) {
                    department = line.substr(0, pos);
                    line.erase(0, pos + 1);
                    roomNumber = stoi(line);
                    students.push_back(Student(name, rollNo, department, roomNumber));
                }
            }
        }
    }

    file.close();
    return students;
}

void writeStudentsToFile(const string& filename, const vector<Student>& students) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    for (const auto& student : students) {
        student.writeToFile(file);
    }

    file.close();
}

bool adminLogin() {
    string username, password;
    cout << "Enter admin username: ";
    getline(cin, username);
    cout << "Enter admin password: ";
    getline(cin, password);
    return (username == "admin" && password == "admin123");
}

bool studentLogin(const vector<Student>& students) {
    string rollNo;
    cout << "Enter your roll number: ";
    getline(cin, rollNo);

    for (const auto& student : students) {
        if (student.getRollNo() == rollNo) {
            cout << "Student login successful. Welcome, " << student.getName() << "!" << endl;
            if (student.getRoomNumber() != -1) {
                cout << "Room allotted: " << student.getRoomNumber() << endl;
            } else {
                cout << "You have not been allotted any room yet." << endl;
            }
            return true;
        }
    }

    cout << "Student with roll number " << rollNo << " not found." << endl;
    return false;
}

void studentSignup(vector<Student>& students) {
    cout << "Student Signup\n";
    Student newStudent = createStudent();
    students.push_back(newStudent);
    cout << "Student registered successfully." << endl;
}

int main() {
    const string studentFilename = "students.txt";
    vector<Student> students = readStudentsFromFile(studentFilename);

    int choice;
    do {
        cout << "\nHostel Management System\n";
        cout << "1. Admin Login\n";
        cout << "2. Student Login\n";
        cout << "3. Student Signup\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                cout << "\nAdmin Login\n";
                if (adminLogin()) {
                    cout << "Admin login successful. Welcome, Admin!" << endl;

                    // Display room management options
                    cout << "\nRoom Management\n";
                    cout << "1. View All Rooms\n";
                    cout << "2. Allot Room\n";
                    cout << "3. Vacate Room\n";
                    cout << "4. View Occupancy\n";

                    int roomChoice;
                    cout << "Enter your choice: ";
                    cin >> roomChoice;
                    cin.ignore();

                    switch (roomChoice) {
                        case 1:
                            // Implement View All Rooms functionality
                            break;
                        case 2:
                            // Implement Allot Room functionality
                            break;
                        case 3:
                            // Implement Vacate Room functionality
                            break;
                        case 4:
                            // Implement View Occupancy functionality
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                    }
                } else {
                    cout << "Invalid admin credentials." << endl;
                }
                break;
            }

            case 2: {
                if (studentLogin(students)) {
                    // After successful student login, you can add functionalities or options here
                    // For example:
                    cout << "\nStudent Menu\n";
                    cout << "1. View Room Allotment Details\n";
                    cout << "2. Update Profile\n";
                    cout << "3. Logout\n";

                    int studentChoice;
                    cout << "Enter your choice: ";
                    cin >> studentChoice;
                    cin.ignore();

                    switch (studentChoice) {
                        case 1:
                            // Implement View Room Allotment Details functionality
                            break;
                        case 2:
                            // Implement Update Profile functionality
                            break;
                        case 3:
                            cout << "Logging out. Goodbye!" << endl;
                            return true; // or break; depending on your logic
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                    }
                }
                break;
            }

            case 3: {
                studentSignup(students);
                break;
            }

            case 4: {
                cout << "Exiting program. Goodbye!" << endl;
                break;
            }

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    writeStudentsToFile(studentFilename, students);
    return 0;
}