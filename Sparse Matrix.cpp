#include <iostream>
#define MAX 50
using namespace std;

class sparse {
private:
    int sp[MAX][3]; // sparse matrix representation
    int len;        // number of non-zero elements

public:
    // constructor
    sparse(int r = 0, int c = 0, int l = 0) {
        sp[0][0] = r;
        sp[0][1] = c;
        sp[0][2] = l;
        len = 0;
    }

    // member functions
    void insert(int row, int col, int val);
    void display();
    sparse transpose();
    void add(sparse b);
    sparse fast_transpose();
    void multiplication(sparse t);
};

void sparse::insert(int row, int col, int val) {
    if (row >= sp[0][0] || col >= sp[0][1])
        cout << "Invalid insertion" << endl;
    else {
        sp[len + 1][0] = row;
        sp[len + 1][1] = col;
        sp[len + 1][2] = val;
        len++;
    }
}

void sparse::display() {
    cout << "Matrix Representation: " << endl;
    cout << "row\tcolumn\tvalue" << endl;
    for (int i = 0; i <= len; i++) {
        cout << sp[i][0] << "\t" << sp[i][1] << "\t" << sp[i][2] << endl;
    }
}

sparse sparse::transpose() {
    sparse t(sp[0][1], sp[0][0], sp[0][2]);
    for (int i = 0; i < sp[0][1]; i++) {
        for (int j = 1; j <= len; j++) {
            if (sp[j][1] == i) {
                t.len++;
                t.sp[t.len][0] = sp[j][1];
                t.sp[t.len][1] = sp[j][0];
                t.sp[t.len][2] = sp[j][2];
            }
        }
    }
    return t;
}

void sparse::add(sparse b) {
    if (sp[0][0] != b.sp[0][0] || sp[0][1] != b.sp[0][1]) {
        cout << "Cannot perform addition, matrix dimensions mismatch." << endl;
        return;
    }

    sparse result(sp[0][0], sp[0][1], 0);
    int a_pos = 1;
    int b_pos = 1;

    while (a_pos <= len && b_pos <= b.len) {
        if (sp[a_pos][0] > b.sp[b_pos][0] ||
            (sp[a_pos][0] == b.sp[b_pos][0] && sp[a_pos][1] > b.sp[b_pos][1])) {
            result.len++;
            result.sp[result.len][0] = b.sp[b_pos][0];
            result.sp[result.len][1] = b.sp[b_pos][1];
            result.sp[result.len][2] = b.sp[b_pos][2];
            b_pos++;
        } else if (sp[a_pos][0] < b.sp[b_pos][0] ||
                   (sp[a_pos][0] == b.sp[b_pos][0] && sp[a_pos][1] < b.sp[b_pos][1])) {
            result.len++;
            result.sp[result.len][0] = sp[a_pos][0];
            result.sp[result.len][1] = sp[a_pos][1];
            result.sp[result.len][2] = sp[a_pos][2];
            a_pos++;
        } else {
            result.len++;
            result.sp[result.len][0] = sp[a_pos][0];
            result.sp[result.len][1] = sp[a_pos][1];
            result.sp[result.len][2] = sp[a_pos][2] + b.sp[b_pos][2];
            a_pos++;
            b_pos++;
        }
    }

    while (a_pos <= len) {
        result.insert(sp[a_pos][0], sp[a_pos][1], sp[a_pos][2]);
        a_pos++;
    }

    while (b_pos <= b.len) {
        result.insert(b.sp[b_pos][0], b.sp[b_pos][1], b.sp[b_pos][2]);
        b_pos++;
    }

    result.sp[0][2] = result.len;
    result.display();
}

sparse sparse::fast_transpose() {
    sparse result(sp[0][1], sp[0][0], sp[0][2]);
    int* cnt = new int[sp[0][1]]();
    int* loc = new int[sp[0][1]]();

    for (int i = 1; i <= len; i++)
        cnt[sp[i][1]]++;

    loc[0] = 1;
    for (int i = 1; i < sp[0][1]; i++)
        loc[i] = loc[i - 1] + cnt[i - 1];

    for (int i = 1; i <= len; i++) {
        int col = sp[i][1];
        int pos = loc[col];
        result.sp[pos][0] = sp[i][1];
        result.sp[pos][1] = sp[i][0];
        result.sp[pos][2] = sp[i][2];
        loc[col]++;
    }

    result.len = sp[0][2];
    delete[] cnt;
    delete[] loc;
    return result;
}

void sparse::multiplication(sparse t) {
    int sum, t1, t2;
    sparse m_result(sp[0][0], t.sp[0][1], 0);

    for (int i = 0; i < sp[0][0]; i++) {
        for (int j = 0; j < t.sp[0][1]; j++) {
            sum = 0;
            t1 = 1;
            t2 = 1;
            int flag_1 = 0;
            int flag_2 = 0;

            while (t1 <= len) {
                if (sp[t1][0] == i) {
                    flag_1 = 1;
                    break;
                }
                t1++;
            }

            while (t2 <= t.len) {
                if (t.sp[t2][0] == j) {
                    flag_2 = 1;
                    break;
                }
                t2++;
            }

            if (flag_1 == 1 && flag_2 == 1) {
                while (sp[t1][0] == i && t.sp[t2][0] == j) {
                    if (sp[t1][1] == t.sp[t2][1]) {
                        sum += sp[t1][2] * t.sp[t2][2];
                        t1++;
                        t2++;
                    } else if (sp[t1][1] < t.sp[t2][1]) {
                        t1++;
                    } else {
                        t2++;
                    }
                }
                if (sum > 0) {
                    m_result.insert(i, j, sum);
                }
            }
        }
    }
    m_result.sp[0][2] = m_result.len;
    m_result.display();
}

int main() {
    sparse s1, s2;
    int choice;

    cout << "Enter the number of rows for Matrix 1: ";
    int r1, c1, l1;
    cin >> r1;
    cout << "Enter the number of columns for Matrix 1: ";
    cin >> c1;
    cout << "Enter the number of non-zero values for Matrix 1: ";
    cin >> l1;
    s1 = sparse(r1, c1, l1);

    for (int i = 0; i < l1; i++) {
        int r, c, val;
        cout << "Enter row index: ";
        cin >> r;
        cout << "Enter column index: ";
        cin >> c;
        cout << "Enter value: ";
        cin >> val;
        s1.insert(r, c, val);
    }

    cout << "Enter the number of rows for Matrix 2: ";
    int r2, c2, l2;
    cin >> r2;
    cout << "Enter the number of columns for Matrix 2: ";
    cin >> c2;
    cout << "Enter the number of non-zero values for Matrix 2: ";
    cin >> l2;
    s2 = sparse(r2, c2, l2);

    for (int i = 0; i < l2; i++) {
        int r, c, val;
        cout << "Enter row index: ";
        cin >> r;
        cout << "Enter column index: ";
        cin >> c;
        cout << "Enter value: ";
        cin >> val;
        s2.insert(r, c, val);
    }

    do {
        cout << "\nMenu:\n";
        cout << "1. Display Matrix 1\n";
        cout << "2. Display Matrix 2\n";
        cout << "3. Transpose of Matrix 1\n";
        cout << "4. Fast Transpose of Matrix 1\n";
        cout << "5. Add Matrices\n";
        cout << "6. Multiply Matrices\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                s1.display();
                break;
            case 2:
                s2.display();
                break;
            case 3: {
                sparse t1 = s1.transpose();
                t1.display();
                break;
            }
            case 4: {
                sparse ft1 = s1.fast_transpose();
                ft1.display();
                break;
            }
            case 5:
                s1.add(s2);
                break;
            case 6:
                s1.multiplication(s2.transpose());
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
