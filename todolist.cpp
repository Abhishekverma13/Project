#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct todolist // Giving numbers to each task which needs to be performed.
{
    int id;
    string task;
};

int ID;
void banner(); // declaring all the functions
void addTask();
void statusTask();
int searchTask();
void deleteTask();

int main()
{
    system("cls"); // clear terminal
    while (true)   // app be on running condition
    {
        banner(); // displaying all the option for the user
        cout << "\n\t1. Add task";
        cout << "\n\t2. Status task";
        cout << "\n\t3. Search task";
        cout << "\n\t4. Delete task";

        int choice;
        cout << "\n\t Enter choice: ";
        cin >> choice;
        switch (choice) // to choose from the options for the user
        {
        case 1:
            addTask();
            break;
        case 2:
            statusTask();
            break;
        case 3:
            searchTask();
            break;
        case 4:
            deleteTask();
            break;
        }
    }
    return 0;
}

// END OF MAIN FUNCTION //
void banner()
{
    cout << "_______________________ " << endl;
    cout << "\t   MY TO DO LIST     " << endl;
    cout << "________________________" << endl;
}

void addTask()
{ // Implementing Add Task
    system("cls"); // clears the system so a new screen is drawn
    banner();
    todolist todo; // object for todo list
    cout << " Enter new task" << endl;
    cin.get();
    getline(cin, todo.task); // storing task in todo
    char save;
    cout << " Save? (y/n): ";
    cin >> save;
    if (save == 'y')
    {
        ID++;
        ofstream fout; // to write something in the file
        fout.open("todolist.txt", ios::app);
        fout << "\n"
             << ID;
        fout << "\n"
             << todo.task;
        fout.close();

        char more;
        cout << "ADD more task? (y/n):";
        cin >> more;

        if (more == 'y')
        {
            addTask();
        }
        else
        {
            system("cls");
            cout << "Added Successfully!" << endl;
            return;
        }
    }
    system("cls");
}

void statusTask()
{
    system("cls");
    banner();
    todolist todo;
    ifstream fin; // relating to cin(fin)
    fin.open("todolist.txt");
    cout << "Task :" << endl;

    while (!fin.eof())
    { // loop runs until the file ends
        fin >> todo.id;
        fin.ignore();
        getline(fin, todo.task);
        if (todo.task != "")
        {
            cout << "\t" << todo.id << ":" << todo.task << endl;
        }
    }
    fin.close();
    char exit; // to ask whether to stay in the terminal or not
    cout << "Exit? (y/n) :";
    cin >> exit;
    if (exit != 'y')
    {
        statusTask();
    }
    system("cls");
}

int searchTask()
{
    system("cls");
    banner();
    int id;
    cout << "Enter Task ID :";
    cin >> id;
    todolist todo;
    ifstream fin("todolist.txt");
    while (!fin.eof())
    {
        fin >> todo.id;
        fin.ignore();
        getline(fin, todo.task);
        if (todo.id == id)
        {
            system("cls");
            cout << "\t" << todo.id << ": " << todo.task << endl;
            return id;
        }
    }
    system("cls");
    cout << "Not found!" << endl;
    return 0;
}

void deleteTask()
{

    int id = searchTask();
    if (id != 0)
    {
        char del;
        cout << "\n\t Delete? (y/n): ";
        cin >> del;
        if (del == 'y')
        {
            todolist todo;
            ofstream tempFile;
            tempFile.open("temp.txt");
            ifstream fin;
            fin.open("todolist.txt");
            int index = 1;
            while (!fin.eof())
            {
                fin >> todo.id;
                fin.ignore();
                getline(fin, todo.task);
                if (todo.id != id)
                {
                    tempFile << "\n"
                             << index;
                    tempFile << "\n"
                             << todo.task;
                    index++;
                }
            }
            fin.close();
            tempFile.close();
            remove("todolist.txt");
            rename("temp.txt", "todolist.txt");
            system("cls");
            cout << "\n\t DELETED SUCCESSFULLY ! " << endl;
        }
        else
        {
            system("cls");
            cout << "\n\t NOT DELETED!" << endl;
        }
    }
}
