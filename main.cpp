#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
using namespace std;

class task
{
private:
  int id;
  string title;
  bool status;

public:
  task(int id, const string &title, bool completed) : id(id), title(title), status(completed)
  {
  }
  string gtitle() const
  {
    return title;
  }
  int gid() const
  {
    return id;
  }
  void markComplete()
  {
    status = true;
  }
  string getstatus() const
  {
    if (status)
      return "DONE";
    return "PENDING";
  }
};

void takeinput(vector<task> &temptasks)
{
  static int id = 0 ;
  if(temptasks.empty()) id = 0;
  else for(int i =0;i<temptasks.size();i++){
  id =  max(id,temptasks[i].gid());
  }
  string title;
  cout << " ENTER DETAILS OF TASKS" << endl;
  cout << "Enter Title ";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  getline(cin, title);
  id++;
  task newtask(id, title, false);
  temptasks.push_back(newtask);
}

void display(const vector<task> &toprint)
{
   if (toprint.empty())  cout << "No tasks available" << endl;

  for (const task &t : toprint)
  {
    cout << t.gid() << "  " << t.gtitle() << " " << t.getstatus() << endl;
  }
  cout << endl;
}

void modify(vector<task> &modifytasks)
{
  cout << "Enter Task ID to Mark it Complete" << endl;
  int m;
  cin >> m;
  bool found = false;
  int i = 0;
  for (i = 0; i < modifytasks.size(); i++)
  {
    if (modifytasks[i].gid() == m)
    {
      modifytasks[i].markComplete();
      found = true;
      break;
    }
  }
  if (found == false)
    cout << "NO SUCH TASK EXISTS" << endl;
}

void deletetask(vector<task> &deletetasks)
{
  int m;
  bool found = false;
  cout << "Enter ID of Task - ";
  cin >> m;
  for (int i = 0; i < deletetasks.size(); i++)
  {
    if (deletetasks[i].gid() == m)
    {
      deletetasks.erase(deletetasks.begin() + i);
      found = true;
      break;
    }
  }
  if (found != true)
    cout << "NO SUCH TASK EXISTS" << endl;
}
void menu(int choice, vector<task> &tasks)
{
  switch (choice)
  {
  case 1:
    takeinput(tasks);
    break;

  case 2:
    display(tasks);
    break;
  case 3:
    modify(tasks);
    break;

  case 4:
    deletetask(tasks);
    break;
  default:
    break;
  }
}

void saveTasks(const vector<task> &saveit)
{
  ofstream fout;
  fout.open("task.txt");
  for (int i = 0; i < saveit.size(); i++)
  {
    fout << saveit[i].gid() << "|" << saveit[i].gtitle() << "|" << saveit[i].getstatus() << "\n";
  }
  fout.close();
}
void loadTasks(vector<task> &tasks)
{

  ifstream fin;
  fin.open("task.txt");
  string line;
  while (getline(fin, line))
  {
    stringstream ss(line);
    string idstr;
    string titlestr;
    string statusstr;
    getline(ss,idstr,'|');
    getline(ss,titlestr,'|');
    getline(ss,statusstr,'|');
    
    bool finalstatus;
    if(statusstr == "DONE" )  finalstatus = true;
    else finalstatus = false;
    task loadedtask(stoi(idstr),titlestr,finalstatus);
    tasks.push_back(loadedtask);
  }
  fin.close();
}

int main()
{
  vector<task> tasks;
  loadTasks(tasks);
 
  int choice = 0;
  cout << "         MENU        " << endl;
  while (choice != 5)
  {
    cout << "1. Add Task " << endl;
    cout << "2. View Tasks " << endl;
    cout << "3. Mark complete " << endl;
    cout << "4. Delete Task " << endl;
    cout << "5. exit " << endl;
    cin >> choice;
    if (choice > 5 || choice< 1) cout << "Invalid Choice" << endl;
    menu(choice, tasks);
  }
  saveTasks(tasks);
  return 0;
}
