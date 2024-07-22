#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>

using namespace std;

// User Class
class User {
public:
    string firstName;
    string lastName;
    int age;
    string gender;

    User() {};

    User(string firstName, string lastName, int age, string gender) {
        this->firstName = firstName;
        this->lastName = lastName;
        this->age = age;
        this->gender = gender;
    }
};

// Message Class
class Message {
public:
    string sender;
    string receiver; // It can be a username or a group name
    string content;
    bool isGroupMessage;

    Message(string sender, string receiver, string content, bool isGroupMessage = false) {
        this->sender = sender;
        this->receiver = receiver;
        this->content = content;
        this->isGroupMessage = isGroupMessage;
    }
};

// Group Class
class Group {
public:
    string groupName;
    set<string> members;

    Group() {};

    Group(string groupName) {
        this->groupName = groupName;
    }

    void addMember(string userName) {
        members.insert(userName);
    }

    void displayMembers() {
        cout << "Group: " << groupName << "\nMembers:\n";
        for (auto member : members) {
            cout << member << "\n";
        }
    }
};

// Global Variables
map<string, User> mapUserName;
map<string, set<string>> Friends;
vector<Message> userMessages;
map<string, Group> groups;

void addUser(string userName, User user) {
    if (mapUserName.find(userName) == mapUserName.end()) {
        mapUserName[userName] = user;
    } else {
        cout << "UserName Already Taken\n";
    }
}

void makeThemFriend(string userName1, string userName2) {
    Friends[userName1].insert(userName2);
    Friends[userName2].insert(userName1);
}

void displayAllUsers() {
    for (auto i : mapUserName) {
        cout << "UserName: " << i.first << " " << i.second.firstName << " " << i.second.lastName << "\n";
    }
}

void displayAllFriendships() {
    for (auto i : Friends) {
        cout << i.first << ": ";
        set<string> friends = i.second;
        for (auto j : friends) {
            cout << j << " ";
        }
        cout << "\n";
    }
}

void sendMessage(string sender, string receiver, string content, bool isGroupMessage = false) {
    if (isGroupMessage) {
        if (groups.find(receiver) != groups.end()) {
            for (auto member : groups[receiver].members) {
                Message message(sender, member, content, true);
                userMessages.push_back(message);
            }
        } else {
            cout << "Group does not exist\n";
        }
    } else {
        Message message(sender, receiver, content);
        userMessages.push_back(message);
    }
}

void displayMessages() {
    for (auto message : userMessages) {
        if (message.isGroupMessage) {
            cout << message.sender << " -> " << message.receiver << " (Group Message): " << message.content << "\n";
        } else {
            cout << message.sender << " -> " << message.receiver << ": " << message.content << "\n";
        }
    }
}

void createGroup(string groupName) {
    if (groups.find(groupName) == groups.end()) {
        Group group(groupName);
        groups[groupName] = group;
    } else {
        cout << "Group already exists\n";
    }
}

void addMemberToGroup(string groupName, string userName) {
    if (groups.find(groupName) != groups.end()) {
        groups[groupName].addMember(userName);
    } else {
        cout << "Group does not exist\n";
    }
}

void displayGroups() {
    for (auto group : groups) {
        group.second.displayMembers();
    }
}

int main() {
    int choice;
    do {
        cout << "1. Add User\n2. Make Friends\n3. Display All Users\n4. Display All Friendships\n5. Send Message\n6. Display All Messages\n7. Create Group\n8. Add Member to Group\n9. Display All Groups\n10. Send Message to Group\n11. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Ignore newline left in the input buffer

        if (choice == 1) {
            string userName, firstName, lastName, gender;
            int age;
            cout << "Enter UserName: ";
            getline(cin, userName);
            cout << "Enter First Name: ";
            getline(cin, firstName);
            cout << "Enter Last Name: ";
            getline(cin, lastName);
            cout << "Enter Age: ";
            cin >> age;
            cin.ignore();
            cout << "Enter Gender: ";
            getline(cin, gender);
            User user(firstName, lastName, age, gender);
            addUser(userName, user);
        } else if (choice == 2) {
            string userName1, userName2;
            cout << "Enter UserName1: ";
            getline(cin, userName1);
            cout << "Enter UserName2: ";
            getline(cin, userName2);
            makeThemFriend(userName1, userName2);
        } else if (choice == 3) {
            displayAllUsers();
        } else if (choice == 4) {
            displayAllFriendships();
        } else if (choice == 5) {
            string sender, receiver, content;
            cout << "Enter Sender UserName: ";
            getline(cin, sender);
            cout << "Enter Receiver UserName: ";
            getline(cin, receiver);
            cout << "Enter Message Content: ";
            getline(cin, content);
            sendMessage(sender, receiver, content);
        } else if (choice == 6) {
            displayMessages();
        } else if (choice == 7) {
            string groupName;
            cout << "Enter Group Name: ";
            getline(cin, groupName);
            createGroup(groupName);
        } else if (choice == 8) {
            string groupName, userName;
            cout << "Enter Group Name: ";
            getline(cin, groupName);
            cout << "Enter UserName to Add: ";
            getline(cin, userName);
            addMemberToGroup(groupName, userName);
        } else if (choice == 9) {
            displayGroups();
        } else if (choice == 10) {
            string sender, groupName, content;
            cout << "Enter Sender UserName: ";
            getline(cin, sender);
            cout << "Enter Group Name: ";
            getline(cin, groupName);
            cout << "Enter Message Content: ";
            getline(cin, content);
            sendMessage(sender, groupName, content, true);
        } else if (choice != 11) {
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 11);

    return 0;
}