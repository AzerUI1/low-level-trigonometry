
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

vector<string> data;

// Read a numerical value or N/A
string get_value(string prompt) {
    string x;

    cout << prompt;
    cin >> x;

    if (x == "N/A" || x == "n/a")
        return "N/A";

    try {
        stod(x);
        return x;
    }
    catch (...) {
        cout << "Invalid input. Enter again: ";
        return get_value("");
    }
}

void input() {
    cout << "How many triangles: ";

    int count_triangles;
    cin >> count_triangles;

    cout << '\n';

    for (int i = 0; i < count_triangles; i++) {

        cout << "\n========== TRIANGLE " << i + 1 << " ==========\n";

        // Triangle sides classification
        cout << "\nEquilateral (A), Isosceles (B), "
             << "Scalene (C), Not Known (N/A): ";

        string type;
        cin >> type;

        if (type == "A")
            data.push_back("Equilateral");
        else if (type == "B")
            data.push_back("Isosceles");
        else if (type == "C")
            data.push_back("Scalene");
        else
            data.push_back("N/A");


        // Triangle angles classification
        cout << "\nAcute (A), Right (B), "
             << "Obtuse (C), Not Known (N/A): ";

        cin >> type;

        if (type == "A")
            data.push_back("Acute");
        else if (type == "B")
            data.push_back("Right");
        else if (type == "C")
            data.push_back("Obtuse");
        else
            data.push_back("N/A");


        // Sides
        cout << "\n--- SIDES ---\n";

        string a = get_value("Side a: ");
        string b = get_value("Side b: ");
        string c = get_value("Side c: ");

        data.push_back("Sides: " + a + ", " + b + ", " + c);


        // Angles
        cout << "\n--- ANGLES ---\n";

        string A = get_value("Angle A: ");
        string B = get_value("Angle B: ");
        string C = get_value("Angle C: ");

        data.push_back("Angles: " + A + ", " + B + ", " + C);


        // Medians
        cout << "\n--- MEDIANS ---\n";

        string ma = get_value("Median ma: ");
        string mb = get_value("Median mb: ");
        string mc = get_value("Median mc: ");

        data.push_back("Medians: " + ma + ", " + mb + ", " + mc);


        // Bisectors
        cout << "\n--- BISECTORS ---\n";

        string la = get_value("Bisector la: ");
        string lb = get_value("Bisector lb: ");
        string lc = get_value("Bisector lc: ");

        data.push_back("Bisectors: " + la + ", " + lb + ", " + lc);


        // Heights
        cout << "\n--- HEIGHTS ---\n";

        string ha = get_value("Height ha: ");
        string hb = get_value("Height hb: ");
        string hc = get_value("Height hc: ");

        data.push_back("Heights: " + ha + ", " + hb + ", " + hc);


        // Midlines
        cout << "\n--- MIDLINES ---\n";

        string na = get_value("Midline na: ");
        string nb = get_value("Midline nb: ");
        string nc = get_value("Midline nc: ");

        data.push_back("Midlines: " + na + ", " + nb + ", " + nc);


        // Trigonometric functions
        cout << "\n--- TRIGONOMETRY ---\n";

        for (int j = 0; j < 3; j++) {

            string angle = (j == 0 ? "A" : j == 1 ? "B" : "C");

            cout << "\nAngle " << angle << ":\n";

            string sin_x = get_value("sin: ");
            string cos_x = get_value("cos: ");
            string tan_x = get_value("tan: ");
            string csc_x = get_value("csc: ");
            string sec_x = get_value("sec: ");
            string cot_x = get_value("cot: ");

            data.push_back(
                "Trigonometry " + angle + ": " +
                "sin=" + sin_x + ", " +
                "cos=" + cos_x + ", " +
                "tan=" + tan_x + ", " +
                "csc=" + csc_x + ", " +
                "sec=" + sec_x + ", " +
                "cot=" + cot_x
            );
        }
    }
}

void run() {
    cout << "Trigonometry Calculator\n";
    input();

    cout << "\n========== STORED DATA ==========\n";

    for (const string& x : data)
        cout << x << '\n';
}

int main() {
    run();
    return 0;
}
