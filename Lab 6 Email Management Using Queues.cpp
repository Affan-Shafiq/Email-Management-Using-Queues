#include<iostream>
#include<string.h>
#include<ctime>

using namespace std;

class node {
    public:
        string content;
        string subject;
        string sender;
        string recipient;
        string priority;
        time_t timeStamp;
        node* next;
        node() {
            next = NULL;
            timeStamp = time(NULL);
        }
};

class queue {
    private:
        node* front;
        node* rear;
    public:
        
        queue() {
            front = NULL;
            rear = NULL;
        }
        
        void enqueue(string s, string sub, string c, string r, string p) {
            node* newNode = new node;
            newNode->content = c;
            newNode->subject = sub;
            newNode->sender = s;
            newNode->recipient = r;
            newNode->priority = p;
            if(front == NULL) {
                front = newNode;
                rear = newNode;
            } else {
                rear->next = newNode;
                rear = newNode;
            }
            cout << "Queued Successfully!!!" << endl;
        }
        
        void dequeue() {
            if(isEmpty()) {
                cout << "Queue Underflow!!!" << endl;
                return;
            }
            node* temp = front;
            time_t firstTimeStamp = front->timeStamp;
            if(temp->priority == "Yes") {
                firstTimeStamp = front->next->timeStamp;
                front = front->next;
                cout << "Time Stamp:" << formatTime(temp->timeStamp) << endl;
                cout << "Email Sender:" << temp->sender << endl;
                cout << "Email Subject:" << temp->subject << endl;
                cout << "Email Content:" << temp->content << endl;
                cout << "Email Recipient:" << temp->recipient << endl;
                if(front == NULL) {
                    rear = NULL;
                }
                delete temp;
                cout << "Dequeued Successfully!!!" << endl;
                return;
            }
            while(temp->next != NULL) {
                if((temp->next->priority == "Yes") || (temp->next->timeStamp > firstTimeStamp)) {
                    node* newNode = temp->next;
                    cout << "Time Stamp:" << formatTime(newNode->timeStamp) << endl;
                    cout << "Email Sender:" << newNode->sender << endl;
                    cout << "Email Subject:" << newNode->subject << endl;
                    cout << "Email Content:" << newNode->content << endl;
                    cout << "Email Recipient:" << newNode->recipient << endl; 
                    temp->next = temp->next->next;
                    delete newNode;
                    cout << "Dequeued Successfully!!!" << endl;
                    return;
                }
                temp = temp->next;
            }
            front = front->next;
            cout << "Time Stamp:" << formatTime(temp->timeStamp) << endl;
            cout << "Email Sender:" << temp->sender << endl;
            cout << "Email Subject:" << temp->subject << endl;
            cout << "Email Content:" << temp->content << endl;
            cout << "Email Recipient:" << temp->recipient << endl;
            if(front == NULL) {
                rear = NULL;
            }
            delete temp;
            cout << "Dequeued Successfully!!!" << endl;
        }
        
        void searchSender(string s) {
            if(isEmpty()) {
                cout << "Queue Underflow!!!" << endl;
                return;
            }
            node* temp = front;
            while(temp) {
                if(temp->sender == s) {
                    cout << "Time Stamp:" << formatTime(temp->timeStamp) << endl;
                    cout << "Email by: " << temp->sender << " located!!!" << endl;
                    cout << "Email Subject:" << temp->subject << endl;
                    cout << "Email Content:" << temp->content << endl;
                    cout << "Email Recipient:" << temp->recipient << endl;
                    return;
                }
                temp = temp->next;
            }
            cout << "No Email from Sender " << s << " Found!!!" << endl;
        }
        
        void searchRecipient(string r) {
            if(isEmpty()) {
                cout << "Queue Underflow!!!" << endl;
                return;
            }
            node* temp = front;
            while(temp) {
                if(temp->recipient == r) {
                    cout << "Time Stamp:" << formatTime(temp->timeStamp) << endl;
                    cout << "Email by: " << temp->recipient << " located!!!" << endl;
                    cout << "Email Sender:" << temp->sender << endl;
                    cout << "Email Subject:" << temp->subject << endl;
                    cout << "Email Content:" << temp->content << endl;
                    return;
                }
                temp = temp->next;
            }
            cout << "No Email to Recipient " << r << " Found!!!" << endl;
        }
        
        void searchSubject(string sub) {
            if(isEmpty()) {
                cout << "Queue Underflow!!!" << endl;
                return;
            }
            node* temp = front;
            while(temp) {
                if(temp->subject == sub) {
                    cout << "Time Stamp:" << formatTime(temp->timeStamp) << endl;
                    cout << "Email by: " << temp->subject << " located!!!" << endl;
                    cout << "Email Sender:" << temp->sender << endl;
                    cout << "Email Content:" << temp->content << endl;
                    cout << "Email Recipient:" << temp->recipient << endl;
                    return;
                }
                temp = temp->next;
            }
            cout << "No Email of this Subject Found!!!" << endl; 
        }
        
        bool isEmpty() {
            return(front == NULL);
        }
        
        string formatTime(time_t timeStamp) {
            struct tm* timeInfo;
            char buffer[100];
            timeInfo = localtime(&timeStamp);
            strftime(buffer, 100, "%Y-%m-%d %H:%M:%S", timeInfo);
            return string(buffer);
        }
};

int main() {
    queue personal, work, spam;
    string sender, subject, content, recipient, priority;
    int choice = 0;
    char choice2; 
    cout << "\t\t\tWelcome to My Chinese Copy of GMail" << endl << endl;
    do {
        cout << "Enter P for Personal, W for Work, S for Spam Emails, and E for Exit:" << endl;
        cin >> choice2;
        switch(choice2) {
            case 'P':
            case 'p':
                cout << "1. To Enqueue an Email" << endl;
                cout << "2. To Dequeue an Email" << endl;
                cout << "3. To Search using Sender" << endl;
                cout << "4. To Search using Recipient" << endl;
                cout << "5. To Search using Subject" << endl;
                cout << "6. To Exit" << endl;
                cin >> choice;
                cin.ignore();
                switch(choice) {
                    case 1:
                        cout << "Enter Name Of Sender:";
                        getline(cin, sender);
                        cout << "Enter Subject of Email:";
                        getline(cin, subject);
                        cout << "Enter Content of Email:";
                        getline(cin, content);
                        cout << "Enter Name Of Recipient:";
                        getline(cin, recipient);
                        cout << "Enter Priority of Email(Yes/No):";
                        getline(cin, priority);
                        personal.enqueue(sender, subject, content, recipient, priority);
                        break;
                    case 2:
                        personal.dequeue();
                        break;
                    case 3:
                        cout << "Enter Name Of Sender with which you want to Search:";
                        getline(cin, sender);
                        personal.searchSender(sender);
                        break;
                    case 4:
                        cout << "Enter Name Of Recipient with which you want to Search:";
                        getline(cin, recipient);
                        personal.searchRecipient(recipient);
                        break;
                    case 5:
                        cout << "Enter Subject with which you want to Search:";
                        getline(cin, subject);
                        personal.searchSubject(subject);
                        break;
                    default:
                        cout << "Exited Successfully!!!" << endl;
                }
                break;
            case 'W':
            case 'w':
                cout << "1. To Enqueue an Email" << endl;
                cout << "2. To Dequeue an Email" << endl;
                cout << "3. To Search using Sender" << endl;
                cout << "4. To Search using Recipient" << endl;
                cout << "5. To Search using Subject" << endl;
                cout << "6. To Exit" << endl;
                cin >> choice;
                cin.ignore();
                switch(choice) {
                    case 1:
                        cout << "Enter Name Of Sender:";
                        getline(cin, sender);
                        cout << "Enter Subject of Email:";
                        getline(cin, subject);
                        cout << "Enter Content of Email:";
                        getline(cin, content);
                        cout << "Enter Name Of Recipient:";
                        getline(cin, recipient);
                        cout << "Enter Priority of Email(Yes/No):";
                        getline(cin, priority);
                        work.enqueue(sender, subject, content, recipient, priority);
                        break;
                    case 2:
                        work.dequeue();
                        break;
                    case 3:
                        cout << "Enter Name Of Sender with which you want to Search:";
                        getline(cin, sender);
                        work.searchSender(sender);
                        break;
                    case 4:
                        cout << "Enter Name Of Recipient with which you want to Search:";
                        getline(cin, recipient);
                        work.searchRecipient(recipient);
                        break;
                    case 5:
                        cout << "Enter Subject with which you want to Search:";
                        getline(cin, subject);
                        work.searchSubject(subject);
                        break;
                    default:
                        cout << "Exited Successfully!!!" << endl;
                }
                break;
            case 'S':
            case 's':
                cout << "1. To Enqueue an Email" << endl;
                cout << "2. To Dequeue an Email" << endl;
                cout << "3. To Search using Sender" << endl;
                cout << "4. To Search using Recipient" << endl;
                cout << "5. To Search using Subject" << endl;
                cout << "6. To Exit" << endl;
                cin >> choice;
                cin.ignore();
                switch(choice) {
                    case 1:
                        cout << "Enter Name Of Sender:";
                        getline(cin, sender);
                        cout << "Enter Subject of Email:";
                        getline(cin, subject);
                        cout << "Enter Content of Email:";
                        getline(cin, content);
                        cout << "Enter Name Of Recipient:";
                        getline(cin, recipient);
                        cout << "Enter Priority of Email(Yes/No):";
                        getline(cin, priority);
                        spam.enqueue(sender, subject, content, recipient, priority);
                        break;
                    case 2:
                        spam.dequeue();
                        break;
                    case 3:
                        cout << "Enter Name Of Sender with which you want to Search:";
                        getline(cin, sender);
                        spam.searchSender(sender);
                        break;
                    case 4:
                        cout << "Enter Name Of Recipient with which you want to Search:";
                        getline(cin, recipient);
                        spam.searchRecipient(recipient);
                        break;
                    case 5:
                        cout << "Enter Subject with which you want to Search:";
                        getline(cin, subject);
                        spam.searchSubject(subject);
                        break;
                    default:
                        cout << "Exited Successfully!!!" << endl;
                }
                break;
            default:
                cout << "Exited Successfully!!!" << endl;
        }
    } while((choice != 6) && ((choice2 != 'E') && (choice2 != 'e')));
}