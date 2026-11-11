#include <bits/stdc++.h> 

using namespace std; 
using ll = long long;   

vector<string> data; // 1 triangle -> cnt triangle; TREAT!!!


void input() { // Basic Input; Next Point, Adding medina, bissektris, hieght, middle line and sin_cos_tan_css_sec_cot(a) (it here are there) 
    cout << "How many triangles: ";

    int count_triangles;
    cin >> count_triangles;

    cout << '\n';

    while (count_triangles--) {
        cout << "Data about a triangle...\n";

        cout << "Equilateral (A), Isosceles (B), Scalene (C), Not Known (N/A):\n";

        string type;
        cin >> type;

        if (type == "A") {
            data.push_back("Equilateral");
        } 
        else if (type == "B") {
            data.push_back("Isosceles");
        } 
        else if (type == "C") {
            data.push_back("Scalene");
        } 
        else {
            data.push_back("N/A");
        }

                
        cout << "Acute (A), Right (B), Obtuse (C), Not Known (N/A):\n";
        
        cin >> type;

        if (type == "A") {
            data.push_back("Acute");
        }
        else if (type == "B") {
            data.push_back("Right");
        }
        else if (type == "C") {
            data.push_back("Obtuse");
        }
        else {
            data.push_back("N/A");
        }

        double a, b, c;
        
        cout << "Enter sides [a, b, c] (If side is unknown input N/A): ";
        cin >> a >> b >> c;

        data.push_back("Sides: " + to_string(a) + ", " +
                       to_string(b) + ", " + to_string(c));

        double A, B, C;

        cout << "Enter angles [a, b, c] (If angle is unknown input N/A): ";
        cin >> A >> B >> C;

        data.push_back("Angles: " + to_string(A) + ", " +
                       to_string(B) + ", " + to_string(C));

    }

    return;
}


void run() {
        cout << "Trigonometry Calculator\n";
        input(); 
} 

int main() {
        run(); 
        return (0);
} 
