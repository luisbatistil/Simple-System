#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

/*

BATISTIL LUISVELLE || BSIT-1245
Computer Programming 2
Simple System Management

Main Menu 
Teacher

    Create
    Edit
    Remove 
    Display 
Student 

     Search students name /no. 
     View complete Grades
Public 

     Add announcements 
     View announcements*/

void MainMenu();
void TeacherMenu();
void StudentMenu();
void PublicMenu();

void CreateRecord();
void EditRecord();
void RemoveRecord();
void DisplayRecords();

void SearchStudent();
void ViewGrades();

void AddAnnouncement();
void ViewAnnouncements();

// input validation function
int GetValidatedInput()
{
    int input;
    while (!(cin >> input))
    {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Invalid input. Please enter a number: ";
    }
    return input;
}

int main()
{
    MainMenu();
    return 0;
}

void MainMenu()
{
    int choice;
    cout << "============MAIN MENU============" << endl;
    cout << "|1| Teacher || |2| Student     ||" << endl;
    cout << "|3| Public  ||                 ||" << endl;
    cout << "=================================" << endl;
    cout << "Select your option: ";
    choice = GetValidatedInput();

    switch (choice)
    {
        case 1:
            TeacherMenu();
            break;
        case 2:
            StudentMenu();
            break;
        case 3:
            PublicMenu();
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
            MainMenu();
    }
}

void TeacherMenu()
{
    int choice;
    cout << "==========TEACHER MENU==========" << endl;
    cout << "|1| Create Record              ||" << endl;
    cout << "|2| Edit Record                ||" << endl;
    cout << "|3| Remove Record              ||" << endl;
    cout << "|4| Display Records            ||" << endl;
    cout << "|5| Back to Main Menu          ||" << endl;
    cout << "=================================" << endl;
    cout << "Select your option: ";
    choice = GetValidatedInput();

    switch (choice)
    {
        case 1:
            CreateRecord();
            break;
        case 2:
            EditRecord();
            break;
        case 3:
            RemoveRecord();
            break;
        case 4:
            DisplayRecords();
            break;
        case 5:
            MainMenu();
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
            TeacherMenu();
    }
}

void StudentMenu()
{
    int choice;
    cout << "==========STUDENT MENU==========" << endl;
    cout << "|1| Search Student             ||" << endl;
    cout << "|2| View Grades                ||" << endl;
    cout << "|3| Back to Main Menu          ||" << endl;
    cout << "=================================" << endl;
    cout << "Select your option: ";
    choice = GetValidatedInput();

    switch (choice)
    {
        case 1:
            SearchStudent();
            break;
        case 2:
            ViewGrades();
            break;
        case 3:
            MainMenu();
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
            StudentMenu();
    }
}

void PublicMenu()
{
    int choice;
    cout << "==========PUBLIC MENU==========" << endl;
    cout << "|1| Add Announcement           ||" << endl;
    cout << "|2| View Announcements         ||" << endl;
    cout << "|3| Back to Main Menu          ||" << endl;
    cout << "=================================" << endl;
    cout << "Select your option: ";
    choice = GetValidatedInput();

    switch (choice)
    {
        case 1:
            AddAnnouncement();
            break;
        case 2:
            ViewAnnouncements();
            break;
        case 3:
            MainMenu();
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
            PublicMenu();
    }
}

// Teacher functionalities
void CreateRecord()
{
    ofstream file("records.txt", ios::app);
    string name;
    int grades[9];
    string subjects[] = {"Pathfit", "Fildis", "NSTP", "Math", "Purpcom", "Artapp", "Comprog2", "STS", "Ethics"};

    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, name);

    for (int i = 0; i < 9; i++)
    {
        cout << "Enter grade for " << subjects[i] << ": ";
        grades[i] = GetValidatedInput();
    }

    file << name;
    for (int i = 0; i < 9; i++)
    {
        file << " " << grades[i];
    }
    file << endl;
    file.close();
    cout << "Record created successfully!" << endl;
    TeacherMenu();
}

void EditRecord()
{
    ifstream file("records.txt");
    ofstream tempFile("temp.txt");
    string name, searchName;
    int grades[9];
    string subjects[] = {"Pathfit", "Fildis", "NSTP", "Math", "Purpcom", "Artapp", "Comprog2", "STS", "Ethics"};

    cout << "Enter the name of the student to edit: ";
    cin.ignore();
    getline(cin, searchName);

    bool found = false;
    while (file >> name)
    {
        for (int i = 0; i < 9; i++)
        {
            file >> grades[i];
        }

        if (name == searchName)
        {
            found = true;
            cout << "Editing record for " << name << endl;
            for (int i = 0; i < 9; i++)
            {
                cout << "Enter new grade for " << subjects[i] << ": ";
                grades[i] = GetValidatedInput();
            }
        }

        tempFile << name;
        for (int i = 0; i < 9; i++)
        {
            tempFile << " " << grades[i];
        }
        tempFile << endl;
    }

    file.close();
    tempFile.close();
    remove("records.txt");
    rename("temp.txt", "records.txt");

    if (found)
        cout << "Record updated successfully!" << endl;
    else
        cout << "Student not found!" << endl;

    TeacherMenu();
}

void RemoveRecord()
{
    ifstream file("records.txt");
    ofstream tempFile("temp.txt");
    string name, searchName;
    int grades[9];

    cout << "Enter the name of the student to remove: ";
    cin.ignore();
    getline(cin, searchName);

    bool found = false;
    while (file >> name)
    {
        for (int i = 0; i < 9; i++)
        {
            file >> grades[i];
        }

        if (name == searchName)
        {
            found = true;
            continue; 
        }

        tempFile << name;
        for (int i = 0; i < 9; i++)
        {
            tempFile << " " << grades[i];
        }
        tempFile << endl;
    }

    file.close();
    tempFile.close();
    remove("records.txt");
    rename("temp.txt", "records.txt");

    if (found)
        cout << "Record removed successfully!" << endl;
    else
        cout << "Student not found!" << endl;

    TeacherMenu();
}

void DisplayRecords()
{
    ifstream file("records.txt");
    string name;
    int grades[9];
    string subjects[] = {"Pathfit", "Fildis", "NSTP", "Math", "Purpcom", "Artapp", "Comprog2", "STS", "Ethics"};

    cout << "Student Records:" << endl;
    while (file >> name)
    {
        cout << "Name: " << name << endl;
        for (int i = 0; i < 9; i++)
        {
            file >> grades[i];
            cout << subjects[i] << ": " << grades[i] << endl;
        }
        cout << "------------------------" << endl;
    }
    file.close();
    TeacherMenu();
}

// Student functionalities
void SearchStudent()
{
    ifstream file("records.txt");
    string name, searchName;
    int grades[9];
    string subjects[] = {"Pathfit", "Fildis", "NSTP", "Math", "Purpcom", "Artapp", "Comprog2", "STS", "Ethics"};

    cout << "Enter the name of the student to search: ";
    cin.ignore();
    getline(cin, searchName);

    bool found = false;
    while (file >> name)
    {
        for (int i = 0; i < 9; i++)
        {
            file >> grades[i];
        }

        if (name == searchName)
        {
            found = true;
            cout << "Name: " << name << endl;
            for (int i = 0; i < 9; i++)
            {
                cout << subjects[i] << ": " << grades[i] << endl;
            }
            break;
        }
    }

    if (!found)
        cout << "Student not found!" << endl;

    file.close();
    StudentMenu();
}

void ViewGrades()
{
    DisplayRecords(); 
    StudentMenu();
}

void AddAnnouncement()
{
    ofstream file("announcements.txt", ios::app);
    string announcement;
    cout << "Enter announcement: ";
    cin.ignore();
    getline(cin, announcement);
    file << announcement << endl;
    file.close();
    cout << "Announcement added successfully!" << endl;
    PublicMenu();
}

void ViewAnnouncements()
{
    ifstream file("announcements.txt");
    string announcement;
    cout << "Announcements:" << endl;
    while (getline(file, announcement))
    {
        cout << "- " << announcement << endl;
    }
    file.close();
    PublicMenu();
}
