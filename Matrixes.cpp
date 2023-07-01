#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <windows.h>
#include <cstdlib>
using namespace std;

ifstream ci("matrici.in.txt");

struct matrix {
     int n;
     int m;
    vector<vector<int>>mat;
     int s;
    matrix() : n(0), m(0), mat(), s(0) {}
};

//suma elementelor din matrice
int suma(vector<vector<int>>mat) {
    long s = 0;
    for (int i = 0; i < mat.size(); i++)
        for (int j = 0; j < mat[i].size(); j++)
            s += mat[i][j];

    return s;

}

vector<matrix>citire(int nr_elm) {
    vector<matrix>matrice;
    
    for (int i = 0; i < nr_elm; i++) {
        matrix a;
        ci >> a.n;
        ci >> a.m;
        for (int x = 0; x < a.n; x++) {
            vector<int>aux;
            for (int y = 0; y < a.m; y++)
            {
                int t;
                ci >> t;
                aux.push_back(t);

            }
            a.mat.push_back(aux);

        }

        a.s = suma(a.mat);
        matrice.push_back(a);

    }

    return matrice;

}

void afisare(vector<matrix>mat) {
 
    for (int i = 0; i < mat.size(); i++) {

        cout << "The number of lines is: " << mat[i].n<<'\n';
        cout << "The number of columns is:" << mat[i].m<<'\n';

        for (int x = 0; x < mat[i].mat.size(); x++, cout << '\n')
            for (int y = 0; y < mat[i].mat[x].size(); y++)
                cout << mat[i].mat[x][y]<<' ';

        cout << '\n';

    }



}

void afisaredimensiuni(vector<matrix>mat) {
    for (int i = 0; i < mat.size(); i++,cout<<'\n')
        cout << "The dimensions of the matrix " << i << " are: " << '\n' << mat[i].n << " linii" << '\n' << mat[i].m << " coloane" <<'\n';
    
}

void adaugare(vector<matrix>&v) {

    cout << "Which matrix do you want to modify: " << '\n';
    int t;
    cin >> t;
 
    string check = "";
    cout << "What do you want to change: " << '\n';
    cout << "Number of lines - L"<<'\n';
    cout << "Number of columns - C"<<'\n';
    cin >> check;
    if (check == "L")
    {
        cout << "How many lines do you want to add: " << '\n';
        int aux;
        cin >> aux;
        for (int i = 0; i < aux; i++) {
            cout << "Enter the items on this line: " << '\n';
            vector<int>co;
            for (int j = 0; j < v[t].m; j++) {
                int elm;
                cin >> elm;
                co.push_back(elm);
            }

            v[t].mat.push_back(co);
        }
        v[t].n += aux;

    }
    else if (check == "C")
    {
        cout << "How many columns do you want to add: " << '\n';
        int aux;
        cin >> aux;
        for (int i = 0; i < aux; i++) {
            cout << "Enter the items on this column " << '\n';
            for (int j = 0; j < v[t].n; j++) {
                int elm;
                cin >> elm;
                v[t].mat[j].push_back(elm);
            }

        }
        v[t].m += aux;
    }
    else
        cout << "You must enter the character 'L' or 'C'";
        
   

}

void inmultire(vector<matrix>& v) {
    cout << "What matrices do you want to multiply? (Insert indexes): ";
    int t1, t2;
    cin >> t1 >> t2;

    if (v[t1].m == v[t2].n) {
        int n = v[t1].mat.size();
        int m = v[t1].mat[0].size();
        int p = v[t2].mat[0].size();

        vector<vector<int>> C(n, vector<int>(p, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < p; j++) {
                for (int k = 0; k < m; k++) {
                    C[i][j] += v[t1].mat[i][k] * v[t2].mat[k][j];
                }
            }
        }
        cout << "The result of the multiplication is:" << endl;
        for (int i = 0; i < C.size(); i++) {
            for (int j = 0; j < C[i].size(); j++) {
                cout << C[i][j] << " ";
            }
            cout << endl;
        }
        cout << '\n';
    }
    else 
        cout << "Matrices are not compatible for multiplication." << '\n';
    
}

void rotire(vector<matrix>& v,int poz) {
   
    vector<vector<int>>nou(v[poz].m, vector<int>(v[poz].n));

    for(int i=0;i<v[poz].n;i++)
        for (int j = 0; j < v[poz].m; j++) {
            nou[j][i] = v[poz].mat[i][j];
        }
   for (int i = 0; i < nou.size(); i++)
        for (int x = 0, y = nou[0].size() - 1; x < y;x++,y--) 
            swap(nou[i][x], nou[i][y]);
        
    v[poz].mat = nou;
    swap(v[poz].n, v[poz].m);

}

void rotiregood(vector<matrix>& v) {
    cout << "By how many degrees do you want to rotate the matrix: ";
    int t;
    cin >> t;
    cout << "Which matrix do you want us to rotate: ";
    int poz;
    cin >> poz;
   
    t = t / 90;
    for (int i = 0; i < t; i++)
        rotire(v,poz);

}

bool sume_matrici(matrix &a, matrix &b){
    return a.s < b.s;
}
void sortare(vector<matrix>&v) {
    sort(v.begin(), v.end(), sume_matrici);

}

void eliminare(vector<matrix>&v) {
    cout << "Which matrix do you want to remove: ";
    int t;
    cin >> t;
    for (int i = t; i < v.size()-1; i++)
        swap(v[i], v[i + 1]);
    v.pop_back();
}

void redimensionare(vector<matrix>& v) {
    cout << "Which matrix do you want to modify: ";
    int t;
    cin >> t;
    system("cls");
    for (int i = 0; i < v[t].n; i++, cout << '\n') {
        for (int j = 0; j < v[t].m; j++) {
            cout << v[t].mat[i][j] << ' ';
        }
    }
    cout << '\n';
    string check1 = "";
    cout << "What do you want to modify: " << '\n';
    cout << "Number of rows - L" << '\n';
    cout << "Number of columns - C" << '\n';
    cin >> check1;
    if (check1 == "L") {
        cout << "Enter the row position: ";
        int poz = 0;
        cin >> poz; //row position
        cout << "Add '+' " << '\n' << "Remove '-' " << '\n';
        string check2 = "";
        cin >> check2;
        if (check2 == "+") {
            vector<int> aux;
            cout << "Elements in the row: ";
            for (int i = 0; i < v[t].m; i++) {
                int ter;
                cin >> ter;
                aux.push_back(ter);
            }
            v[t].mat.push_back(aux);
            for (int i = v[t].mat.size() - 1; i > poz; i--) {
                swap(v[t].mat[i], v[t].mat[i - 1]);
            }
            v[t].n++;
        }
        if (check2 == "-") {
            for (int i = poz; i < v[t].mat.size() - 1; i++) {
                swap(v[t].mat[i], v[t].mat[i + 1]);
            }
            v[t].mat.pop_back();
            v[t].n--;
        }
    }
    if (check1 == "C") {
        cout << "Enter the column position: ";
        int poz = 0;
        cin >> poz; //column position
        cout << "Add '+' " << '\n' << "Remove '-' ";
        string check2 = "";
        cin >> check2;
        if (check2 == "+") {
            cout << "Elements in the column: ";
            for (int i = 0; i < v[t].mat.size(); i++) {
                int ter;
                cin >> ter;
                v[t].mat[i].push_back(ter);
                for (int j = v[t].mat[i].size() - 1; j > poz; j--) {
                    swap(v[t].mat[i][j], v[t].mat[i][j - 1]);
                }
            }
            v[t].m++;
        }
        if (check2 == "-") {
            for (int i = 0; i < v[t].mat.size(); i++) {
                for (int j = poz; j < v[t].m - 1; j++) {
                    swap(v[t].mat[i][j], v[t].mat[i][j + 1]);
                }
                v[t].mat[i].pop_back();
            }
            v[t].m--;
        }
    }
}

int main()
{
    cout << "How many matrices are we working with: " ;
    int nr;
    cin >> nr;
   
    if (nr == 0)
    {
        cout << "We cannot work with 0 matrices";
        exit(0);
    }
    system("cls");
    vector<matrix>v=citire(nr);
   
    
   
    while (true) {
            cout << "1 -> Display matrices" << '\n';
            cout << "2 -> Display matrix dimensions" << '\n';
            cout << "3 -> Add elements to a matrix" << '\n';
            cout << "4 -> Multiply two matrices" << '\n';
            cout << "5 -> Resize a matrix" << '\n';
            cout << "6 -> Sort matrices based on the sum of elements" << '\n';
            cout << "7 -> Remove a matrix from memory" << '\n';
            cout << "8 -> Rotate a matrix by 90 degrees, 180, 270, etc." << '\n';
            cout << "9 -> Exit" << '\n';
        int aux = -1;
        cin >> aux;
        system("cls");
        switch (aux)
        {
        case 1:
            afisare(v);
            break;
        case 2:
            afisaredimensiuni(v);
            break;
        case 3:
            adaugare(v);
            break;
        case 4:
            inmultire(v);
            break;
        case 5:
            redimensionare(v);
            break;
        case 6:
            sortare(v);
            break;
        case 7:
            eliminare(v);
            break;
        case 8:
            rotiregood(v);
            break;
        case 9:
            exit(0);

        default:
            break;
        }
    }
    
    return 0;
}

