#include <iostream>
using namespace std;
#include <string>
#include <fstream>

struct todolist
{
    int id;
    string task;
};

int ID;
void banner();
void addTask();
void showTask();
int searchTask();
void deleteTask();
void updateTask();

int main()
{
  system("cls");
  while (true)
  {
    banner();
    cout << "\n\t1. Add Task";
    cout << "\n\t2. Show Task";
    cout << "\n\t3. Search Task";
    cout << "\n\t4. Delete Task";
    cout << "\n\t5. Update Task";
    cout << endl;

    int choice;
    cout << "\n\tEnter Choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
      addTask();
      break;
    case 2:
      showTask();
      break;
    case 3:
      searchTask();
      break;
    case 4:
      deleteTask();
      break;
    case 5:
      updateTask();
      break;
    default:
      break;
    }
  }
  return 0;
}

void banner(){
  cout << ".................................................."<< endl;
  cout << "\t             MY TODOLIST                       " << endl;
  cout << ".................................................."<< endl;
}

void addTask(){
  system("cls");
  banner();
  todolist todo;
  cout << "Enter new task: " << endl;
  cin.get();
  getline(cin, todo.task);
  char save;
  cout << "Save (y/n):";
  cin>> save;
  if(save == 'y'){
    ID++;
    ofstream fout;
    fout.open("todo.txt", ios::app);
    fout << "\n" << ID;
    fout << "\n" << todo.task;
    fout.close();

    char more;
    cout << "Add more task? (y/n): ";
    cin >> more;

    if(more == 'y'){
      addTask();
    }else{
      system("cls");
      cout << "Added Successfully!" << endl;
      return;
    }
  }
  system("cls");
}

void showTask(){
  system("cls");
  banner();
  todolist todo;
  ifstream fin;
  fin.open("todo.txt");
  cout << "Task: " <<endl;
  while(!fin.eof())
  {
    fin >> todo.id;
    fin.ignore();
    getline(fin, todo.task);
    if(todo.task != ""){
      cout << "\t" << todo.id << ": " << todo.task << endl;
    }
    else{
      cout << "\tEmpty!" <<endl;
    }
  }
  fin.close();
  char exit;
  cout << "Exist? (y/n): ";
  cin >> exit;
  if(exit != 'y'){
    showTask();
  }
  system("cls");
}

int searchTask(){
    system("cls");
  banner();
  int id;
  cout << "Enter task id: ";
  cin >> id;
  todolist todo;
  ifstream fin("todo.txt");
  while(!fin.eof())
  {
    fin >> todo.id;
    fin.ignore();
    getline(fin, todo.task);
    if(todo.id == id){
      system("cls");
      cout << "\t"  << todo.id << ": " << todo.task << endl;
      return id;
    }
  }
  system("cls");
  cout << "Not Found!" << endl;
  return 0;
}

void deleteTask(){
  system("cls");
  int id = searchTask();
  if(id != 0){
    char del;
    cout << "\n\tDelete? (y/n): ";
    cin >> del;
    if(del == 'y'){
      todolist todo;
      ofstream tempFile;
      tempFile.open("temp.txt");
      ifstream fin;
      fin.open("todo.txt");
      int index = 1;
      while(!fin.eof()){
        fin >> todo.id;
        fin.ignore();
        getline(fin,todo.task);
        if(todo.id != id){
          tempFile << "\n" << index;
          tempFile << "\n" << todo.task;
          index++;
          ID--;
        }
      }
      fin.close();
      tempFile.close();
      remove("todo.txt");
      rename("temp.txt","todo.txt");
      system("cls");
      cout << "\n\tDeleted Successfully!" << endl;
    }
    else{
      system("cls");
      cout << "Not Deleted!" << endl;
    }
  }
}

void updateTask() {
  system("cls");
 // banner();
  int id = searchTask(); // Search for the task to update

  if (id != 0) {
    todolist todo;
    ifstream fin("todo.txt");
    ofstream tempFile("temp.txt");

    while (!fin.eof()) {
      fin >> todo.id;
      fin.ignore();
      getline(fin, todo.task);

      if (todo.id == id) {
        // Display current task details
        cout << "\n\tCurrent Task: " << todo.task << endl;

        // Prompt user for updated task
        cout << "\tEnter new task: ";
        cin.get();
        getline(cin, todo.task);

        // Write updated task to temp file
        tempFile << todo.id << "\n" << todo.task << "\n";
        cout << "\n\tUpdated Successfully!" << endl;
      } else {
        // Write unchanged task to temp file
        if (!fin.eof()) {
          tempFile << todo.id << "\n" << todo.task << "\n";
        }
      }
    }
    fin.close();
    tempFile.close();
    // Replace original file with updated temp file
    remove("todo.txt");
    rename("temp.txt", "todo.txt");
  } else {
    cout << "\n\tTask not found!" << endl;
  }

  char exit;
  cout << "\n\tExit? (y/n): ";
  cin >> exit;
  if (exit != 'y') {
    updateTask(); // Recursively call updateTask() if user wants to continue
  }
  system("cls");
}




