#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <iomanip>
#include <ctime>  // For date handling

using namespace std;

// Task Entity
class Task {
public:
    int id;
    string name;
    int priority;     // 1 = High, 2 = Medium, 3 = Low
    string date;      // Format: DD/MM/YYYY

    Task() : id(0), priority(0) {}

    Task(int id, string name, int priority, string date)
        : id(id), name(name), priority(priority), date(date) {}

    // For displaying
    void display() const {
        cout << left << setw(5) << id
             << setw(25) << name
             << setw(10) << getPriorityString()
             << setw(15) << date << endl;
    }

    string getPriorityString() const {
        if (priority == 1) return "High";
        if (priority == 2) return "Medium";
        return "Low";
    }

    // For sorting by ID (needed for Binary Search)
    bool operator<(const Task& other) const {
        return id < other.id;
    }
};

// TaskManager
class TaskManager {
private:
    vector<Task> tasks;
    stack<Task> deletedTasks;
    int nextId = 1;

    // Linear Search by name or ID
    int linearSearch(const string& query) {
        for (size_t i = 0; i < tasks.size(); ++i) {
            if (tasks[i].name == query || to_string(tasks[i].id) == query) {
                return i;
            }
        }
        return -1;
    }

    // Binary Search (assumes vector is sorted by ID)
    int binarySearch(int id) {
        int left = 0;
        int right = tasks.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (tasks[mid].id == id) {
                return mid;
            }
            if (tasks[mid].id < id) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }

public:
    void createTask() {
        string name, date;
        int priority;

        cout << "\n=== Create New Task ===\n";
        cout << "Task Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Priority (1-High, 2-Medium, 3-Low): ";
        cin >> priority;

        cout << "Date of birth: ";
        cin >> date;

        Task newTask(nextId++, name, priority, date);
        tasks.push_back(newTask);

        // Keep sorted by ID for binary search
        sort(tasks.begin(), tasks.end());

        cout << "Task created successfully! ID: " << newTask.id << endl;
    }

    void deleteTask() {
        if (tasks.empty()) {
            cout << "No tasks to delete!\n";
            return;
        }

        int id;
        cout << "\nEnter Task ID to delete: ";
        cin >> id;

        auto it = find_if(tasks.begin(), tasks.end(), [id](const Task& t) {
            return t.id == id;
        });

        if (it != tasks.end()) {
            deletedTasks.push(*it);
            tasks.erase(it);
            cout << "Task deleted successfully. You can undo this operation.\n";
        } else {
            cout << "Task with ID " << id << " not found!\n";
        }
    }

    void undoDelete() {
        if (deletedTasks.empty()) {
            cout << "Nothing to undo!\n";
            return;
        }

        Task restored = deletedTasks.top();
        deletedTasks.pop();
        tasks.push_back(restored);
        sort(tasks.begin(), tasks.end());  // Maintain sorted order

        cout << "Task ID " << restored.id << " has been restored.\n";
    }

    void showTasks() const {
        if (tasks.empty()) {
            cout << "No tasks available.\n";
            return;
        }

        cout << "\n=== All Tasks ===\n";
        cout << left << setw(5) << "ID"
             << setw(25) << "Name"
             << setw(10) << "Priority"
             << setw(15) << "Date of birth" << endl;
        cout << string(55, '-') << endl;

        for (const auto& task : tasks) {
            task.display();
        }
    }

    void searchTask() {
        if (tasks.empty()) {
            cout << "No tasks to search!\n";
            return;
        }

        int choice;
        cout << "\nSearch Options:\n";
        cout << "1. Linear Search (by Name or ID)\n";
        cout << "2. Binary Search (by ID)\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string query;
            cout << "Enter Name or ID to search: ";
            cin.ignore();
            getline(cin, query);

            int index = linearSearch(query);
            if (index != -1) {
                cout << "Task found:\n";
                tasks[index].display();
            } else {
                cout << "Task not found!\n";
            }
        }
        else if (choice == 2) {
            int id;
            cout << "Enter Task ID: ";
            cin >> id;

            int index = binarySearch(id);
            if (index != -1) {
                cout << "Task found:\n";
                tasks[index].display();
            } else {
                cout << "Task not found!\n";
            }
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
};

// Main Menu
int main() {
    TaskManager manager;
    int choice;

    cout << "=== Todo Application (OOP C++) ===\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Create Task\n";
        cout << "2. Delete Task\n";
        cout << "3. Undo Delete\n";
        cout << "4. Show All Tasks\n";
        cout << "5. Search Task\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: manager.createTask(); break;
            case 2: manager.deleteTask(); break;
            case 3: manager.undoDelete(); break;
            case 4: manager.showTasks(); break;
            case 5: manager.searchTask(); break;
            case 6: cout << "Goodbye!\n"; break;
            default: cout << "Invalid option! Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
