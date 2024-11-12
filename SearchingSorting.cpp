#include <iostream>
#include <string>
using namespace std;

class student {
public:
    string name;
    int roll_no;
    float CGPA;
    string department;

    void getinfo() {
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter roll_no: ";
        cin >> roll_no;
        cout << "Enter CGPA: ";
        cin >> CGPA;
        cout << "Enter the department: ";
        cin >> department;
    }

    void display() {
        cout << name << "\t" << roll_no << "\t" << CGPA << "\t" << department << endl;
    }
};

void BubbleSort(student S[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (S[j].roll_no > S[j + 1].roll_no) {
               
                student temp = S[j];
                S[j] = S[j + 1];
                S[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void InsertionSort(student S[], int n) {
    for (int i = 1; i < n; i++) {
        student temp = S[i];
        int j = i - 1;
        while (j >= 0 && S[j].roll_no > temp.roll_no) {
            S[j + 1] = S[j];
            j--;
        }
        S[j + 1] = temp;
    }
}

int partition(student S[], int l, int r) {
    student pivot = S[r];
    int i = l - 1;
    for (int j = l; j < r; j++) {
        if (S[j].roll_no <= pivot.roll_no) {
            i++;
         
            student temp = S[i];
            S[i] = S[j];
            S[j] = temp;
        }
    }

    student temp = S[i + 1];
    S[i + 1] = S[r];
    S[r] = temp;
    return i + 1;
}

void QuickSort(student S[], int l, int r) {
    if (l < r) {
        int pi = partition(S, l, r);
        QuickSort(S, l, pi - 1);
        QuickSort(S, pi + 1, r);
    }
}

int LinearSearch(student S[], int n, int search_key) {
    for (int i = 0; i < n; i++) {
        if (S[i].roll_no == search_key) {
            cout << "\nElement found: " << S[i].name << " at position: " << i + 1 << endl;
            return i;
        }
    }
    cout << "Key Element not Found" << endl;
    return -1;
}

int BinarySearch(student S[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (S[mid].roll_no == key)
            return mid;
        else if (S[mid].roll_no < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int FibonacciSearch(student S[], int n, int key) {
    int fb_prev2 = 0, fb_prev1 = 1, fb_curr = fb_prev2 + fb_prev1;
    while (fb_curr < n) {
        fb_prev2 = fb_prev1;
        fb_prev1 = fb_curr;
        fb_curr = fb_prev2 + fb_prev1;
    }
    int offset = -1;
    while (fb_curr > 1) {
        int i = min(offset + fb_prev2, n - 1);
        if (S[i].roll_no < key) {
            fb_curr = fb_prev1;
            fb_prev1 = fb_prev2;
            fb_prev2 = fb_curr - fb_prev1;
            offset = i;
        } else if (S[i].roll_no > key) {
            fb_curr = fb_prev2;
            fb_prev1 -= fb_prev2;
            fb_prev2 = fb_curr - fb_prev1;
        } else {
            return i;
        }
    }
    if (fb_prev1 && S[offset + 1].roll_no == key)
        return offset + 1;
    return -1;
}

int main() {
    student S[20];
    int searchkey, ch, ch1;
    char ch2;
    int n;
    do {
        cout << "Enter \n1. Accept the data\n2. Display\n3. Sort\n4. Search" << endl;
        cout << "Enter your choice: ";
        cin >> ch;
        switch (ch) {
            case 1:
                cout << "How many student's info you want: ";
                cin >> n;
                for (int i = 0; i < n; i++) {
                    S[i].getinfo();
                }
                break;
            case 2:
                cout << "The data you entered:" << endl;
                cout << "Name\tRoll_no\tCGPA\tDepartment" << endl;
                for (int i = 0; i < n; i++) {
                    S[i].display();
                }
                break;
            case 3:
                cout << "Enter the type of Sort you want to use:\n1. BubbleSort\n2. QuickSort\n3. InsertionSort" << endl;
                cin >> ch1;
                switch (ch1) {
                    case 1:
                        BubbleSort(S, n);
                        cout << "Sorted data using BubbleSort:" << endl;
                        break;
                    case 2:
                        QuickSort(S, 0, n - 1);
                        cout << "Sorted data using QuickSort:" << endl;
                        break;
                    case 3:
                        InsertionSort(S, n);
                        cout << "Sorted data using InsertionSort:" << endl;
                        break;
                    default:
                        cout << "Wrong Choice!!" << endl;
                }
                cout << "Name\tRoll_no\tCGPA\tDepartment" << endl;
                for (int i = 0; i < n; i++) {
                    S[i].display();
                }
                break;
            case 4:
                cout << "Enter the type of Search you want:\n1. LinearSearch\n2. BinarySearch\n3. FibonacciSearch" << endl;
                cin >> ch1;
                cout << "Enter search key: ";
                cin >> searchkey;
                switch (ch1) {
                    case 1:
                        LinearSearch(S, n, searchkey);
                        break;
                    case 2:
                        if (BinarySearch(S, n, searchkey) != -1)
                            cout << "Element found using BinarySearch" << endl;
                        else
                            cout << "Element not found" << endl;
                        break;
                    case 3:
                        if (FibonacciSearch(S, n, searchkey) != -1)
                            cout << "Element found using FibonacciSearch" << endl;
                        else
                            cout << "Element not found" << endl;
                        break;
                    default:
                        cout << "Wrong Choice!!" << endl;
                }
                break;
            default:
                cout << "Wrong Choice!!" << endl;
        }
        cout << "Do you want to continue? [Y/N]: ";
        cin >> ch2;
    } while (ch2 == 'Y' || ch2 == 'y');

    return 0;
}
