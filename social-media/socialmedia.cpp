#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>

using namespace std;

class User {
public:
    string firstName;
    string lastName;
    int age;
    string gender;

    User() {}

    User(string firstName, string lastName, int age, string gender) {
        this->firstName = firstName;
        this->lastName = lastName;
        this->age = age;
        this->gender = gender;
    }
};

class Message {
public:
    string sender;
    string content;

    Message(string sender, string content) {
        this->sender = sender;
        this->content = content;
    }
};

class Group {
public:
    string groupName;
    set<string> members;
    vector<Message> messages;

    Group() {} // Default constructor

    Group(string groupName) {
        this->groupName = groupName;
    }

    void addMember(string userName) {
        members.insert(userName);
    }

    void addMessage(string sender, string content) {
        messages.push_back(Message(sender, content));
    }

    void displayMessages() {
        for (auto &msg : messages) {
            cout << msg.sender << ": " << msg.content << endl;
        }
    }
};

// MAP user-name to USER
map<string, User> mapUserName;

// MAPPING ONE FRIEND TO ANOTHER FRIEND
map<string, set<string>> Friends;

// MAP group-name to GROUP
map<string, Group> Groups;

void addUser(string userName, User user) {
    if (mapUserName.find(userName) == mapUserName.end()) {
        mapUserName[userName] = user;
        cout << "User " << userName << " added successfully." << endl;
    } else {
        cout << "Username already taken." << endl;
    }
}

void makeThemFriend(string userName1, string userName2) {
    if (mapUserName.find(userName1) != mapUserName.end() && mapUserName.find(userName2) != mapUserName.end()) {
        Friends[userName1].insert(userName2);
        Friends[userName2].insert(userName1);
        cout << userName1 << " and " << userName2 << " are now friends." << endl;
    } else {
        cout << "One or both usernames do not exist." << endl;
    }
}

void displayAllUser() {
    if (mapUserName.empty()) {
        cout << "No users to display." << endl;
    } else {
        for (auto &i : mapUserName) {
            cout << "Username: " << i.first << " "
                 << "Name: " << i.second.firstName << " " << i.second.lastName << " "
                 << "Age: " << i.second.age << " "
                 << "Gender: " << i.second.gender << endl;
        }
    }
}

void displayAllFriendships() {
    if (Friends.empty()) {
        cout << "No friendships to display." << endl;
    } else {
        for (auto &i : Friends) {
            cout << i.first << ": ";
            set<string> friends = i.second;
            for (auto &j : friends) {
                cout << j << " ";
            }
            cout << "\n";
        }
    }
}

void createGroup(string groupName) {
    if (Groups.find(groupName) == Groups.end()) {
        Groups[groupName] = Group(groupName);
        cout << "Group " << groupName << " created successfully." << endl;
    } else {
        cout << "Group name already taken." << endl;
    }
}

void addMemberToGroup(string groupName, string userName) {
    if (Groups.find(groupName) != Groups.end()) {
        if (mapUserName.find(userName) != mapUserName.end()) {
            Groups[groupName].addMember(userName);
            cout << "User " << userName << " added to group " << groupName << "." << endl;
        } else {
            cout << "User does not exist." << endl;
        }
    } else {
        cout << "Group does not exist." << endl;
    }
}

void addMessageToGroup(string groupName, string sender, string content) {
    if (Groups.find(groupName) != Groups.end()) {
        if (Groups[groupName].members.find(sender) != Groups[groupName].members.end()) {
            Groups[groupName].addMessage(sender, content);
            cout << "Message added to group " << groupName << "." << endl;
        } else {
            cout << "Sender is not a member of the group." << endl;
        }
    } else {
        cout << "Group does not exist." << endl;
    }
}

void displayGroupMessages(string groupName) {
    if (Groups.find(groupName) != Groups.end()) {
        Groups[groupName].displayMessages();
    } else {
        cout << "Group does not exist." << endl;
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add User\n";
        cout << "2. Make Friends\n";
        cout << "3. Display All Users\n";
        cout << "4. Display All Friendships\n";
        cout << "5. Create Group\n";
        cout << "6. Add Member to Group\n";
        cout << "7. Add Message to Group\n";
        cout << "8. Display Group Messages\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string userName, firstName, lastName, gender;
            int age;
            cout << "Enter username: ";
            cin >> userName;
            cout << "Enter first name: ";
            cin >> firstName;
            cout << "Enter last name: ";
            cin >> lastName;
            cout << "Enter age: ";
            cin >> age;
            cout << "Enter gender: ";
            cin >> gender;

            User user(firstName, lastName, age, gender);
            addUser(userName, user);
        } else if (choice == 2) {
            string userName1, userName2;
            cout << "Enter first username: ";
            cin >> userName1;
            cout << "Enter second username: ";
            cin >> userName2;
            makeThemFriend(userName1, userName2);
        } else if (choice == 3) {
            displayAllUser();
        } else if (choice == 4) {
            displayAllFriendships();
        } else if (choice == 5) {
            string groupName;
            cout << "Enter group name: ";
            cin >> groupName;
            createGroup(groupName);
        } else if (choice == 6) {
            string groupName, userName;
            cout << "Enter group name: ";
            cin >> groupName;
            cout << "Enter username: ";
            cin >> userName;
            addMemberToGroup(groupName, userName);
        } else if (choice == 7) {
            string groupName, sender, content;
            cout << "Enter group name: ";
            cin >> groupName;
            cout << "Enter sender username: ";
            cin >> sender;
            cout << "Enter message content: ";
            cin.ignore();
            getline(cin, content);
            addMessageToGroup(groupName, sender, content);
        } else if (choice == 8) {
            string groupName;
            cout << "Enter group name: ";
            cin >> groupName;
            displayGroupMessages(groupName);
        } else if (choice == 9) {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
