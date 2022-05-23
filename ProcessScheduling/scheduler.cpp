#include <bits/stdc++.h>
using namespace std;
int CURR_TIME = 0;
int TIME_SLICE;
string SCHEDULE_TYPE;

struct Process {
    string name;
    int id;
    int burstTime;
    int priority;
    int arrivalTime;
    int remainingTime;
};

class Comparator {
    public:

        bool operator()(Process& a, Process& b) {
            if(SCHEDULE_TYPE == "PRIORITY")
                return a.priority > b.priority;
            else if(SCHEDULE_TYPE == "SHORTEST_REMAINING_TIME") {
                return a.remainingTime > b.remainingTime;
            } else if(SCHEDULE_TYPE == "FIRST_COME_FIRST_SERVE") {
                return a.arrivalTime > b.arrivalTime;
            } else if(SCHEDULE_TYPE == "SHORTEST_JOB_FIRST") {
                return a.burstTime > b.burstTime;
            } else {
                exit(1);
            }
        }
};

bool sortByArrivalTime(Process a, Process b) {
    return a.arrivalTime < b.arrivalTime;
}

int main() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    // Get the time slice and scheduling type
    cin>>TIME_SLICE>>SCHEDULE_TYPE;
    // Get the input processes and store it
    int numProcesses;
    cin>>numProcesses;
    vector<Process> processes;
    // Input order: 
        // Process name
        // Process id
        // Burst Time
        // Priority
        // Arrival Time
    while(numProcesses--) {
        Process proc;
        cin>>proc.name>>proc.id>>proc.burstTime>>proc.priority>>proc.arrivalTime;
        proc.remainingTime = proc.burstTime;
        processes.push_back(proc);
    }

    vector<Process> permRecord = processes;

    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), sortByArrivalTime);

    Process currProcess;
    priority_queue<Process, vector<Process>, Comparator> waitQueue;
    map<int, int> completionTime;
    cout<<"GANTT CHART:"<<endl;
    while(!waitQueue.empty() || processes.size()) {
        bool noSchedule = true;

        // Check for processes that might have arrived
        while(processes.size()) {
            if(processes.front().arrivalTime <= CURR_TIME) {
                waitQueue.push(processes.front());
                processes.erase(processes.begin());
            } else {
                break;
            }
        }

        // Schedule a process in the waitQueue
        if(!waitQueue.empty()) {
            noSchedule = false;
            currProcess = waitQueue.top(); waitQueue.pop();

            cout<<CURR_TIME<<" "<<currProcess.name<<" ";
            if (currProcess.remainingTime <= TIME_SLICE) {
                // If the remaining time is less than a time slice, 
                // the process would not take the whole time slice

                cout<<currProcess.remainingTime<<" Process Complete";
                CURR_TIME += currProcess.remainingTime;

                // Record the completion time
                completionTime[currProcess.id] = CURR_TIME;
            } else {
                cout<<TIME_SLICE;
                currProcess.remainingTime -= TIME_SLICE;
                waitQueue.push(currProcess);
                CURR_TIME += TIME_SLICE;
            }
            cout<<endl;
        }

        if(noSchedule) {
            CURR_TIME += 1;
        }
    }
    cout<<endl;

    cout<<"Scheduling over at: "<<CURR_TIME<<endl;

    map<int, int> turnAroundTime, waitingTime;

    int waitingTimeSum = 0;
    for(Process proc: permRecord) {
        turnAroundTime[proc.id] = completionTime[proc.id] - proc.arrivalTime;
        waitingTime[proc.id] = turnAroundTime[proc.id] - proc.burstTime;
        waitingTimeSum += waitingTime[proc.id];
    }

    cout<<"Average Waiting Time: "<<(double)(waitingTimeSum)/(double)(permRecord.size())<<endl;

    return 0;
}