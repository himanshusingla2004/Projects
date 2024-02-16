#include <bits/stdc++.h>
using namespace std;

struct Task
{
    string description;
    string dueDate;
    int priority;
};

void displayToDoList(const vector<Task> &toDoList)
{
    cout << "\nYOUR TO DO LIST :" << endl;
    for (size_t i = 0; i < toDoList.size(); i++)
    {
        cout << i + 1 << ". "
             << "Description :  " << toDoList[i].description << "  |  Due Date: " << toDoList[i].dueDate << "  |  Priority: " << toDoList[i].priority << endl;
    }
}


struct Id
{
    string userId;
    string password;
};

void addUser(vector<Id> &users, const string &newId, const string &newPassword)
{
    Id newUser;
    newUser.userId = newId;
    newUser.password = newPassword;
    users.push_back(newUser);

    ofstream userFileWrite("userAuthentication.txt");
    for (const Id &user : users)
    {
        userFileWrite << user.userId << "\n" << user.password << endl;
    }
    userFileWrite.close();
}



int main()
{
    vector<Id> users;
    ifstream userFile("userAuthentication.txt");

    if(userFile.is_open())
    {
        Id id;
        while(getline(userFile,id.userId))
        {
            userFile >> id.password;
            userFile.ignore();
            users.push_back(id);
        }
        userFile.close();
    }
    else{
        ofstream userFile("userAuthentication.txt");
        cout<<"Please restart the program";
        return 0;
    }

    cout<<"--------   WELCOME TO TASK LIST  --------\n";
    

    string currId;
    int i = 0;
    auto itt = 0;

    while(i < 5){
        if(i == 0)
            cout<<"\nTo Log In Enter ID :  ";
        if(i > 0)
            cout<<"Enter ID Again :  ";
        cin>>currId;
        auto it = find_if(users.begin(),users.end(), [&currId](const Id &id){
            return id.userId == currId;
        });
        cin.ignore();

        if(it != users.end()){
            itt = it - users.begin();
            // cout<<"ID Correct"<<endl;
            break;
        }
        else{
            cout<<"Incorrect ID"<<endl;
            if(i == 0){
                string ans;
                cout<<"\nAre you a New User ? \n"<<"Yes or No :  ";
                cin>>ans;
                cout<<endl;
                if(ans == "Yes" || ans == "yes"){
                    cout<<"---  Let`s Create Your ID and Password  ---"<<endl;
                    
                    string newId, newPassword;
                    int k = 0;
                    while(true){
                        if(k == 0)
                            cout<<"     Enter Name of Your ID :  ";
                        if(k > 0)
                            cout<<"     Enter Different Name of Your ID :  ";
                        cin>> newId;
                        auto it = find_if(users.begin(),users.end(), [&newId](const Id &id){
                            return id.userId == newId;
                        });
                        if(it == users.end()){
                            break;
                        }
                        else{
                            cout<<"     ! User ID Taken already"<<endl;
                        }
                        k++;
                        if(k > 5){
                            cout<<"Please Try to Create unique ID and return After some time";
                            return 0;
                        }
                    }
                    
                    
                    cout<<"     Enter You Password :  ";
                    cin>> newPassword;

                    // Function Call
                    addUser(users, newId, newPassword);
                    cout<<"     \nID and Password Created"<<endl;
                    continue;
                }
            }
        }

        if( i == 4){
            cout<<"\nERROR !  You have Entered too many times wrong ID"<<endl;
            cout<<"Can Not LogIn You Exiting";
            return 0;
        }

        i++;
    }
    
    i = 0;
    string password;
    while(i < 5){
        if( i == 0)
            cout<<"Enter Password :  ";
        if( i > 0)
            cout<<"Incorrect\nEnter Password Again :  ";
        cin>>password;

        bool find = false;
        if(itt < users.size())
        {
            if(users[itt].password == password)
            {
                // User Authincated
                cout<<"\nUser Authenticated Logging In"<<endl;
                find = true;
                break;
            }
        }

        cin.ignore();

        if(find == true){
            break;
        }
        if(i == 4){
            cout<<"\nERROR !  You have Entered too many times wrong password "<<endl;
            cout<<"Can Not LogIn You";
            return 0;
        }
        i++;
    }

    cout<<"---  SUCCESS Logged In  ---"<<endl;

    
    //  Below All Functionalities
    cout<<"\n-----  WELCOME "<<currId<<"  -----"<<endl;

    string fileName = "";
    fileName += currId + password + ".txt";
    
    vector<Task> toDoList;
    ifstream inFile(fileName);

    if (inFile.is_open())
    {
        Task task;
        while (getline(inFile, task.description) && getline(inFile, task.dueDate))
        {
            inFile >> task.priority;
            inFile.ignore();
            toDoList.push_back(task);
        }
        inFile.close();
    }
    else{
        cout<<"File not exist\n";
    }

    unordered_set<string> prevTask;    

    while (true)
    {
        cout << "\nEnter Options that You want to do :\n" << endl;
        cout << "1.  ADD a Task" << endl;
        cout << "2.  REMOVE a Task" << endl;
        cout << "3.  MODIFY an existing Task" << endl;
        cout << "4.  VIEW to-do list" << endl;
        cout << "5.  SAVE and EXIT" << endl;

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            cin.ignore();
            Task newTask;
            cout << "Enter task description: ";
            getline(cin, newTask.description);

            if (prevTask.find(newTask.description) != prevTask.end())
            {
                cout << "Task with the same description already exists. Please enter a unique description." << endl;
                continue;
            }

            cout << "Enter due date (DD-MM-YYYY): ";
            cin >> newTask.dueDate;
            cout << "Enter task priority (1 for low, 2 for medium, 3 for high): ";
            cin >> newTask.priority;

            prevTask.insert(newTask.description);

            toDoList.push_back(newTask);
            cout << "TASK ADDED." << endl;
        }

        else if (choice == 2)
        {

            cin.ignore();

            displayToDoList(toDoList);

            cout << "\nEnter the task description to remove : ";
            string descriptionToRemove;
            getline(cin, descriptionToRemove);

            ifstream file(fileName);

            if (file.is_open())
            {
                vector<Task> tempTasks;
                Task tempTask;

                while (getline(file, tempTask.description) && getline(file, tempTask.dueDate))
                {
                    file >> tempTask.priority;
                    file.ignore();
                    tempTasks.push_back(tempTask);
                }
                file.close();

                auto it = find_if(tempTasks.begin(), tempTasks.end(), [&descriptionToRemove](const Task &task)
                                  { return task.description == descriptionToRemove; });

                if (it != tempTasks.end())
                {
                    tempTasks.erase(it);
                    cout << "Task removed." << endl;

                    // Write the updated tasks back to the file
                    fstream file(fileName);
                    for (const Task &task : tempTasks)
                    {
                        file << task.description << '\n'
                             << task.dueDate << '\n'
                             << task.priority << '\n';
                    }

                    toDoList.swap(tempTasks);

                    file.close();
                    cout << "File updated." << endl;
                }
                else
                {
                    // Task not found
                    cout << "Task not found. Please enter a valid task description." << endl;
                    file.close();
                }
            }
            else
            {
                cout << "Error opening file." << endl;
            }
        }

        else if (choice == 3)
        {
            cin.ignore();

            displayToDoList(toDoList);

            string oldTask; // To be searched and remove
            cout << "\nEnter the task description that you want to Modify : ";
            getline(cin, oldTask);

            string descriptionToModify;
            cout<<"Enter new name of the Task : ";
            getline(cin,descriptionToModify);

            string dueDateToModify;
            cout << "Enter new Due Date to Modify : ";
            getline(cin, dueDateToModify);

            int newProirity;
            cout << "Enter new Priority to assign : ";
            cin>>newProirity;
            cout<<endl;
            
            Task newTask;
            newTask.description = descriptionToModify;
            newTask.dueDate = dueDateToModify;
            newTask.priority = newProirity;

            ifstream file(fileName);

            if (file.is_open())
            {
                vector<Task> tempTasks;
                Task tempTask;

                while (getline(file, tempTask.description) && getline(file, tempTask.dueDate))
                {
                    file >> tempTask.priority;
                    file.ignore();
                    tempTasks.push_back(tempTask);
                }
                file.close();

                auto it = find_if(tempTasks.begin(), tempTasks.end(), [&oldTask](const Task &task)
                                  { return task.description == oldTask; });

                if (it != tempTasks.end())
                {

                    if(tempTasks[it-tempTasks.begin()].priority == newProirity){
                        tempTasks[it-tempTasks.begin()].description = descriptionToModify;
                        tempTasks[it-tempTasks.begin()].dueDate = dueDateToModify;

                        cout<<"Same Priority Updated the Task"<<endl;

                        toDoList.swap(tempTasks);

                        // Write the updated tasks back to the file
                        fstream file(fileName);
                        for (const Task &task : toDoList)
                        {
                            file << task.description << '\n'
                                << task.dueDate << '\n'
                                << task.priority << '\n';
                        }
                        file.close();
                        cout<<"File Updated"<<endl;
                    }
                    else{
                        tempTasks.erase(it); 
                        tempTasks.push_back(newTask);
                        cout << "Task Modified." << endl;

                        // Write the updated tasks back to the file
                        fstream file(fileName);
                        for (const Task &task : tempTasks)
                        {
                            file << task.description << '\n'
                                << task.dueDate << '\n'
                                << task.priority << '\n';
                        }

                        toDoList.swap(tempTasks);

                        file.close();
                        cout << "File updated." << endl;
                    }
                }
                else
                {
                    cout << "Task not found. Please enter a valid task description." << endl;
                    file.close();
                }
            }
            else
            {
                cout << "Error opening file." << endl;
            }

        }

        else if (choice == 4)
        {
            sort(toDoList.begin(), toDoList.end(), [](const Task &a, const Task &b)
                 { return a.priority > b.priority; });
            displayToDoList(toDoList);
        }

        else if (choice == 5)
        {
            ofstream outFile(fileName);
            if (outFile.is_open())
            {
                for (const Task &task : toDoList)
                {
                    outFile << task.description << endl;
                    outFile << task.dueDate << endl;
                    outFile << task.priority << endl;
                }
                outFile.close();
            }
            else
            {
                cout << "Error: Could not save to-do list." << endl;
            }
            cout << "To-do list saved. Exiting." << endl;
            break;
        }

        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
