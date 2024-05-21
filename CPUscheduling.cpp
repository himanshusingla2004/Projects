#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

struct Process {
    int id;
    int burstTime;
    int priority;
    int arrivalTime;
    int remainingTime;
    int startTime;
    int finishTime;
    int waitTime;
    int turnAroundTime;
};

// Function to print the scheduling results
void printResults(vector<Process>& processes) {
    cout << "PID\tBurst Time\tArrival Time\tPriority\tStart Time\tFinish Time\tWait Time\tTurnaround Time\n";
    for (auto& p : processes) {
        cout << p.id << "\t"
             << p.burstTime << "\t\t"
             << p.arrivalTime << "\t\t"
             << p.priority << "\t\t"
             << p.startTime << "\t\t"
             << p.finishTime << "\t\t"
             << p.waitTime << "\t\t"
             << p.turnAroundTime << "\n";
    }
}

// First-Come, First-Served (FCFS) Scheduling
void fcfs(vector<Process> processes) {
    int currentTime = 0;
    for (auto& p : processes) {
        p.startTime = max(currentTime, p.arrivalTime);
        p.finishTime = p.startTime + p.burstTime;
        p.waitTime = p.startTime - p.arrivalTime;
        p.turnAroundTime = p.finishTime - p.arrivalTime;
        currentTime = p.finishTime;
    }
    printResults(processes);
}

// Shortest Job First (SJF) Scheduling
void sjf(vector<Process> processes) {
    // int n = processes.size();
    vector<Process> readyQueue;
    int currentTime = 0;
    while (!processes.empty() || !readyQueue.empty()) {
        for (auto it = processes.begin(); it != processes.end();) {
            if (it->arrivalTime <= currentTime) {
                readyQueue.push_back(*it);
                it = processes.erase(it);
            } else {
                ++it;
            }
        }
        if (!readyQueue.empty()) {
            sort(readyQueue.begin(), readyQueue.end(), [](const Process& a, const Process& b) {
                return a.burstTime < b.burstTime;
            });
            Process& p = readyQueue.front();
            p.startTime = currentTime;
            p.finishTime = p.startTime + p.burstTime;
            p.waitTime = p.startTime - p.arrivalTime;
            p.turnAroundTime = p.finishTime - p.arrivalTime;
            currentTime = p.finishTime;
            readyQueue.erase(readyQueue.begin());
        } else {
            currentTime++;
        }
    }
    printResults(processes);
}

// Longest Job First (LJF) Scheduling
void ljf(vector<Process> processes) {
    // int n = processes.size();
    vector<Process> readyQueue;
    int currentTime = 0;
    while (!processes.empty() || !readyQueue.empty()) {
        for (auto it = processes.begin(); it != processes.end();) {
            if (it->arrivalTime <= currentTime) {
                readyQueue.push_back(*it);
                it = processes.erase(it);
            } else {
                ++it;
            }
        }
        if (!readyQueue.empty()) {
            sort(readyQueue.begin(), readyQueue.end(), [](const Process& a, const Process& b) {
                return a.burstTime > b.burstTime;
            });
            Process& p = readyQueue.front();
            p.startTime = currentTime;
            p.finishTime = p.startTime + p.burstTime;
            p.waitTime = p.startTime - p.arrivalTime;
            p.turnAroundTime = p.finishTime - p.arrivalTime;
            currentTime = p.finishTime;
            readyQueue.erase(readyQueue.begin());
        } else {
            currentTime++;
        }
    }
    printResults(processes);
}

// Priority Scheduling
void priorityScheduling(vector<Process> processes) {
    // int n = processes.size();
    vector<Process> readyQueue;
    int currentTime = 0;
    while (!processes.empty() || !readyQueue.empty()) {
        for (auto it = processes.begin(); it != processes.end();) {
            if (it->arrivalTime <= currentTime) {
                readyQueue.push_back(*it);
                it = processes.erase(it);
            } else {
                ++it;
            }
        }
        if (!readyQueue.empty()) {
            sort(readyQueue.begin(), readyQueue.end(), [](const Process& a, const Process& b) {
                return a.priority < b.priority;
            });
            Process& p = readyQueue.front();
            p.startTime = currentTime;
            p.finishTime = p.startTime + p.burstTime;
            p.waitTime = p.startTime - p.arrivalTime;
            p.turnAroundTime = p.finishTime - p.arrivalTime;
            currentTime = p.finishTime;
            readyQueue.erase(readyQueue.begin());
        } else {
            currentTime++;
        }
    }
    printResults(processes);
}

// Round Robin (RR) Scheduling
void roundRobin(vector<Process> processes, int quantum) {
    int n = processes.size();
    queue<Process> readyQueue;
    int currentTime = 0;
    int index = 0;
    while (!readyQueue.empty() || index < n) {
        while (index < n && processes[index].arrivalTime <= currentTime) {
            readyQueue.push(processes[index]);
            index++;
        }
        if (!readyQueue.empty()) {
            Process& p = readyQueue.front();
            readyQueue.pop();
            if (p.remainingTime > quantum) {
                currentTime += quantum;
                p.remainingTime -= quantum;
                while (index < n && processes[index].arrivalTime <= currentTime) {
                    readyQueue.push(processes[index]);
                    index++;
                }
                readyQueue.push(p);
            } else {
                currentTime += p.remainingTime;
                p.remainingTime = 0;
                p.finishTime = currentTime;
                p.turnAroundTime = p.finishTime - p.arrivalTime;
                p.waitTime = p.turnAroundTime - p.burstTime;
            }
        } else {
            currentTime++;
        }
    }
    printResults(processes);
}

// Shortest Remaining Time First (SRTF) Scheduling
void srtf(vector<Process> processes) {
    // int n = processes.size();
    vector<Process> readyQueue;
    int currentTime = 0;
    while (!processes.empty() || !readyQueue.empty()) {
        for (auto it = processes.begin(); it != processes.end();) {
            if (it->arrivalTime <= currentTime) {
                readyQueue.push_back(*it);
                it = processes.erase(it);
            } else {
                ++it;
            }
        }
        if (!readyQueue.empty()) {
            sort(readyQueue.begin(), readyQueue.end(), [](const Process& a, const Process& b) {
                return a.remainingTime < b.remainingTime;
            });
            Process& p = readyQueue.front();
            currentTime++;
            p.remainingTime--;
            if (p.remainingTime == 0) {
                p.finishTime = currentTime;
                p.turnAroundTime = p.finishTime - p.arrivalTime;
                p.waitTime = p.turnAroundTime - p.burstTime;
                readyQueue.erase(readyQueue.begin());
            }
        } else {
            currentTime++;
        }
    }
    printResults(processes);
}

// Helper function to input process details
vector<Process> inputProcesses() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        cout << "Enter burst time, priority, and arrival time for process " << i + 1 << ": ";
        cin >> processes[i].burstTime >> processes[i].priority >> processes[i].arrivalTime;
        processes[i].id = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].startTime = -1;
        processes[i].finishTime = -1;
        processes[i].waitTime = -1;
        processes[i].turnAroundTime = -1;
    }
    return processes;
}

// Main function
int main() {
    while (true) {
        cout << "Scheduling Algorithms:\n";
        cout << "1. FCFS\n2. SJF\n3. LJF\n4. Priority Scheduling\n5. Round Robin\n6. SRTF\n7. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 7) break;

        vector<Process> processes = inputProcesses();
        switch (choice) {
            case 1:
                fcfs(processes);
                break;
            case 2:
                sjf(processes);
                break;
            case 3:
                ljf(processes);
                break;
            case 4:
                priorityScheduling(processes);
                break;
            case 5: {
                int quantum;
                cout << "Enter time quantum: ";
                cin >> quantum;
                roundRobin(processes, quantum);
                break;
            }
            case 6:
                srtf(processes);
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
