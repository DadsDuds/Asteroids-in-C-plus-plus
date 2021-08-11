#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class Student
{
    int rollnum;
    char name[50];
    int p_marks, c_marks, m_marks, e_marks, cs_marks;   // Physics, Chemister, Math, English, & Computer Science respectively
    double per;
    char grade;
    void calculate();   // function to calculate grade 

public:
    void getdata();         // function to accept data from user
    void showdata() const;  // function to show data on screen
    void show_tabular() const;
    int retrollnum() const;
};

void Student::calculate()
{
    per = (p_marks + c_marks + m_marks + e_marks + cs_marks) / 5.0; 
    if (per >= 60)
        grade = 'A'; 
    else if (per >= 50)
        grade = 'B';
    else if (per > 33)
        grade = 'C';
    else
        grade = 'F';
}

// asks the user for student's marks
void Student::getdata()
{
    cout << "\nEnter the roll number of the student: ";
    cin >> rollnum;
    cout << "\nEnter student's name: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nEnter student's marks in physics (out of 100): ";
    cin >> p_marks;
    cout << "\nEnter student's marks in chemistry (out of 100): ";
    cin >> c_marks;
    cout << "\nEnter student's marks in mathematics (out of 100): ";
    cin >> m_marks;
    cout << "\nEnter student's marks in english (out of 100): ";
    cin >> e_marks;
    cout << "\nEnter student's marks in computer science (out of 100): ";
    cin >> cs_marks;
    calculate();
}

// shows the requested data
void Student::showdata() const
{
    cout << "\nRoll number: " <<rollnum;
    cout <<" \nName of student: " <<name;
    cout << "\nMarks in Physics: " <<p_marks;
    cout << "\nMarks in Chemistry: " <<c_marks;
    cout << "\nMarks in Mathematics: " <<m_marks;
    cout << "\nMarks in English: " <<e_marks;
    cout << "\nMarks in Computer Science: " <<cs_marks;
    cout << "\nPercentage of student is: " << per;
    cout << "\nGrade of student is: " << grade;
}

void Student::show_tabular() const
{
    cout << rollnum << setw(6) << " " << name << setw(10) << p_marks << setw(4)
        << c_marks << setw(4) << m_marks << setw(4) << e_marks << setw(4) << cs_marks << setw(8)
            << per << setw(6) << grade << endl;
}

int Student::retrollnum() const
{
    return rollnum;
}

// a couple function declarations
void write_student();
void display_all();
void display_sp(int);
void modify_student(int);
void delete_student(int);
void class_result(int);
void result();
void intro();
void entry_menu();

// finally. the main function
int main()
{
    char ch;
    cout.setf(ios::fixed|ios::showpoint);
    cout << setprecision(2);    // program outputs decimal number to two decimal places
    intro();
    do
    {
        system("cls");
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. RESULT MENU";
        cout << "\n\n\t02. ENTRY/EDIT MENU";
        cout << "\n\n\t03. EXIT";
        cout << "\n\n\tPlease select an option (1-3) ";
        cin >> ch;
        switch(ch)
        {
            case '1': 
                result();
                break;
            case '2': 
                entry_menu();
                break;
            case '3': 
                break;
            default: cout << "\a";
        }
    } while (ch != '3');
        return 0;

}

// this function allows the user to write in a file
void write_student()
{
    Student st;
    ofstream outFile;
    outFile.open("student.dat", ios::binary|ios::app);
    st.getdata();
    outFile.write(reinterpret_cast<char *> (&st), sizeof(Student));
    outFile.close();
    cout << "\nStudent record has been created.";
    cin.ignore();
    cin.get();
}

// this function displays all recorded student reports
void display_all()
{
    Student st;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if (!inFile)
    {
        cout << "\nFile could not be opened.";
        cout << "\nFile may be misplaced or unrecognizable.";
        cout << "\nPress any key to return to the main menu.";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "\n\n\n\t\tALL RECORDS \n\n";
    while (inFile.read(reinterpret_cast<char *> (&st), sizeof(Student)))
    {
        st.showdata();
        cout << "\n\n====================================\n";
    }
    inFile.close();
    cin.ignore();
    cin.get();
}

// this function reads a specific record
void display_sp(int n)
{
    Student st;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if (!inFile)
    {
        cout << "\nFile could not be opened.";
        cout << "\nFile may be misplaced or unrecognizable.";
        cout << "\nPress any key to return to the main menu.";
        cin.ignore();
        cin.get();
        return;
    }

    bool flag = false;
    while (inFile.read(reinterpret_cast<char *> (&st), sizeof(Student)))
    {
        if (st.retrollnum() == n)
        {
            st.showdata();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\nRecord does not exist.";
    cin.ignore();
    cin.get();
}

// this function allows the user to modify a student's record
void modify_student(int n)
{
    bool found = false;
    Student st;
    fstream File;
    File.open("student.dat", ios::binary|ios::in|ios::out);
    if (!File)
    {
        cout << "\nFile could not be opened.";
        cout << "\nFile may be misplaced or unrecognizable.";
        cout << "\nPress any key to return to the main menu.";
        cin.ignore();
        cin.get();
        return;
    }

    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *> (&st), sizeof(Student));
        if (st.retrollnum() == n)
        {
            st.showdata();
            cout << "\n\nPlease enter the new details of student." << endl;
            st.getdata();
            int pos = (-1) * static_cast<int>(sizeof(st));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *> (&st), sizeof(Student));
            cout << "\n\n\t Record updated.";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n Record not found.";
    cin.ignore();
    cin.get();
}

// this function allows the user to delete a student's record
void delete_student(int n)
{
    Student st;
    ifstream inFile;
    ofstream outFile;
    inFile.open("student.dat", ios::binary);
    if (!inFile)
    {
        cout << "\nFile could not be opened.";
        cout << "\nFile may be misplaced or unrecognizable.";
        cout << "\nPress any key to return to the main menu.";
        cin.ignore();
        cin.get();
        return;
    }
    outFile.open("Temp.dat", ios::out);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char *> (&st), sizeof(Student)))
    {
        if (st.retrollnum()!=n)
            outFile.write(reinterpret_cast<char *> (&st), sizeof(Student));
    }

    outFile.close();
    inFile.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    cout << "\n\n\tRecord removed.";
    cin.ignore();
    cin.get();
}

// this function displays all student grades on file
void class_result()
{
    Student st;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if (!inFile)
    {
        cout << "\nFile could not be opened.";
        cout << "\nFile may be misplaced or unrecognizable.";
        cout << "\nPress any key to return to the main menu.";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "\n\n\t\tALL STUDENT RECORDS \n\n";
    cout<< "==========================================================\n";
	cout<< "R.No       Name        P   C   M   E   CS   %age   Grade" << endl;
	cout<< "==========================================================\n";

    while (inFile.read(reinterpret_cast<char *> (&st), sizeof(Student)))
        st.show_tabular();
    
    cin.ignore();
    cin.get();
    inFile.close();
}

// function to display result menu
void result()
{
    char ch;
    int rno;
    system("cls");

    cout << "\n\n\n\tRESULT MENU";
    cout << "\n\n\n\t1. Class Result";
    cout << "\n\n\t2. Student Report Card";
    cout << "\n\n\t3. Back to the Main Menu";
    cout << "\n\n\n\tEnter choice (1/2/3)? ";
    cin >> ch;
    system("cls");

    switch(ch)
    {
        case '1':
            class_result();
            break;
        case '2': 
            cout << "\n\n\tEnter roll number of student: ";
            cin >> rno;
            display_sp(rno);
            break;
        case '3':
            break;
        default: cout << "\a";
    }
}

// what the user will first see
void intro()
{
    cout<<"\n\n\n\t\t  STUDENT";
	cout<<"\n\n\t\tREPORT CARD";
	cout<<"\n\n\t\t  PROJECT";
	cout<<"\n\n\n\tMADE BY : SULABH AGRAWAL";
	cout<<"\n\tSCHOOL : CAMBRIDGE SCHOOL";
	cin.get();
}

// the entry menu function
void entry_menu()
{
    char ch;
    int num;
    system("cls");

    cout<<"\n\n\n\tENTRY MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
	cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
	cout<<"\n\n\t4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
	cout<<"\n\n\t6.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
    cin >> ch;
    system("cls");

    switch(ch)
    {
        case '1':
            write_student();
            break;
        case '2':
            display_all();
            break;
        case '3':
            cout << "\n\n\tPleae enter the student's roll number: ";
            cin >> num;
            display_sp(num);
            break;
        case '4':
            cout << "\n\n\tPlease enter the student's roll number: ";
            modify_student(num);
            break;
        case '5':
            cout << "\n\n\tPlease enter the student's roll number: ";
            delete_student(num);
            break;
        case '6':
            break;
        default: cout << "\a";
    }

}