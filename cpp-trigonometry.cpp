#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr double PI = 3.14159265358979323846;
constexpr double EPS = 1e-7;

struct TrigSet {
    optional<double> sin, cos, tan, csc, sec, cot;
};

struct Triangle {
    string side_type = "N/A";
    string angle_type = "N/A";

    optional<double> a, b, c;
    optional<double> A, B, C; 
    optional<double> ma, mb, mc;
    optional<double> la, lb, lc;
    optional<double> ha, hb, hc;
    optional<double> na, nb, nc;

    optional<double> P, s, Area, R, r;
    TrigSet trigA, trigB, trigC;
};

static double deg2rad(double deg) {
    return deg * PI / 180.0;
}

static double rad2deg(double rad) {
    return rad * 180.0 / PI;
}

static bool approx_eq(double x, double y, double eps = 1e-5) {
    return fabs(x - y) <= eps;
}

static bool set_opt(optional<double>& target, double val, bool& changed, double eps = 1e-5) {
    if (!isfinite(val)) return false;
    if (!target.has_value()) {
        target = val;
        changed = true;
        return true;
    }
    return false;
}

optional<double> get_value(const string& prompt) {
    string x;
    cout << prompt;
    cin >> x;

    if (x == "N/A" || x == "n/a")
        return nullopt;

    try {
        size_t idx = 0;
        double val = stod(x, &idx);
        if (idx == x.size() && isfinite(val))
            return val;
    } catch (...) {}

    cout << "Invalid input. Enter again: ";
    return get_value("");
}

void deduce_classifications(Triangle& t, bool& changed) {
    if (t.side_type == "Equilateral") {
        if (t.a.has_value()) {
            set_opt(t.b, *t.a, changed);
            set_opt(t.c, *t.a, changed);
        } else if (t.b.has_value()) {
            set_opt(t.a, *t.b, changed);
            set_opt(t.c, *t.b, changed);
        } else if (t.c.has_value()) {
            set_opt(t.a, *t.c, changed);
            set_opt(t.b, *t.c, changed);
        }
        set_opt(t.A, 60.0, changed);
        set_opt(t.B, 60.0, changed);
        set_opt(t.C, 60.0, changed);
    }

    if (t.angle_type == "Right") {
        if (t.C.has_value() && approx_eq(*t.C, 90.0)) {
            if (t.A.has_value()) set_opt(t.B, 90.0 - *t.A, changed);
            if (t.B.has_value()) set_opt(t.A, 90.0 - *t.B, changed);
        }
    }

    if (t.a.has_value() && t.b.has_value() && t.c.has_value()) {
        double x = *t.a, y = *t.b, z = *t.c;
        if (approx_eq(x, y) && approx_eq(y, z)) {
            if (t.side_type != "Equilateral") { t.side_type = "Equilateral"; changed = true; }
        } else if (approx_eq(x, y) || approx_eq(y, z) || approx_eq(x, z)) {
            if (t.side_type == "N/A") { t.side_type = "Isosceles"; changed = true; }
        } else {
            if (t.side_type == "N/A") { t.side_type = "Scalene"; changed = true; }
        }

        vector<double> s_vec = {x, y, z};
        sort(s_vec.begin(), s_vec.end());
        double lhs = s_vec[2] * s_vec[2];
        double rhs = s_vec[0] * s_vec[0] + s_vec[1] * s_vec[1];
        if (approx_eq(lhs, rhs)) {
            if (t.angle_type == "N/A") { t.angle_type = "Right"; changed = true; }
        } else if (lhs < rhs) {
            if (t.angle_type == "N/A") { t.angle_type = "Acute"; changed = true; }
        } else {
            if (t.angle_type == "N/A") { t.angle_type = "Obtuse"; changed = true; }
        }
    }
}

void deduce_single_trig(optional<double>& ang_deg, TrigSet& tr, const string& angle_type, bool& changed) {
    if (ang_deg.has_value()) {
        double rad = deg2rad(*ang_deg);
        set_opt(tr.sin, sin(rad), changed);
        set_opt(tr.cos, cos(rad), changed);
        if (!approx_eq(cos(rad), 0.0, 1e-9)) {
            set_opt(tr.tan, tan(rad), changed);
            set_opt(tr.sec, 1.0 / cos(rad), changed);
        }
        if (!approx_eq(sin(rad), 0.0, 1e-9)) {
            set_opt(tr.csc, 1.0 / sin(rad), changed);
        }
        if (!approx_eq(tan(rad), 0.0, 1e-9)) {
            set_opt(tr.cot, 1.0 / tan(rad), changed);
        }
    }

    if (tr.csc.has_value() && !approx_eq(*tr.csc, 0.0, 1e-9))
        set_opt(tr.sin, 1.0 / *tr.csc, changed);
    if (tr.sin.has_value() && !approx_eq(*tr.sin, 0.0, 1e-9))
        set_opt(tr.csc, 1.0 / *tr.sin, changed);

    if (tr.sec.has_value() && !approx_eq(*tr.sec, 0.0, 1e-9))
        set_opt(tr.cos, 1.0 / *tr.sec, changed);
    if (tr.cos.has_value() && !approx_eq(*tr.cos, 0.0, 1e-9))
        set_opt(tr.sec, 1.0 / *tr.cos, changed);

    if (tr.cot.has_value() && !approx_eq(*tr.cot, 0.0, 1e-9))
        set_opt(tr.tan, 1.0 / *tr.cot, changed);
    if (tr.tan.has_value() && !approx_eq(*tr.tan, 0.0, 1e-9))
        set_opt(tr.cot, 1.0 / *tr.tan, changed);

    // sin <-> cos
    if (tr.cos.has_value() && *tr.cos >= -1.0 - EPS && *tr.cos <= 1.0 + EPS) {
        double c_val = clamp(*tr.cos, -1.0, 1.0);
        set_opt(tr.sin, sqrt(max(0.0, 1.0 - c_val * c_val)), changed);
    }
    if (tr.sin.has_value() && !tr.cos.has_value() && *tr.sin >= -EPS && *tr.sin <= 1.0 + EPS) {
        double s_val = clamp(*tr.sin, 0.0, 1.0);
        double mag = sqrt(max(0.0, 1.0 - s_val * s_val));
        if (angle_type == "Acute") {
            set_opt(tr.cos, mag, changed);
        } else if (tr.tan.has_value()) {
            if (*tr.tan > EPS) set_opt(tr.cos, mag, changed);
            else if (*tr.tan < -EPS) set_opt(tr.cos, -mag, changed);
        }
    }

    if (tr.sin.has_value() && tr.cos.has_value() && !approx_eq(*tr.cos, 0.0, 1e-9)) {
        set_opt(tr.tan, *tr.sin / *tr.cos, changed);
    }

    if (!ang_deg.has_value()) {
        if (tr.cos.has_value()) {
            double c_val = clamp(*tr.cos, -1.0, 1.0);
            set_opt(ang_deg, rad2deg(acos(c_val)), changed);
        } else if (tr.tan.has_value()) {
            double deg = rad2deg(atan(*tr.tan));
            if (deg < 0.0) deg += 180.0;
            set_opt(ang_deg, deg, changed);
        } else if (tr.sin.has_value() && angle_type == "Acute") {
            double s_val = clamp(*tr.sin, 0.0, 1.0);
            set_opt(ang_deg, rad2deg(asin(s_val)), changed);
        }
    }
}

void deduce_trig_and_angles(Triangle& t, bool& changed) {
    deduce_single_trig(t.A, t.trigA, t.angle_type, changed);
    deduce_single_trig(t.B, t.trigB, t.angle_type, changed);
    deduce_single_trig(t.C, t.trigC, t.angle_type, changed);

    if (t.A.has_value() && t.B.has_value())
        set_opt(t.C, 180.0 - *t.A - *t.B, changed);
    if (t.A.has_value() && t.C.has_value())
        set_opt(t.B, 180.0 - *t.A - *t.C, changed);
    if (t.B.has_value() && t.C.has_value())
        set_opt(t.A, 180.0 - *t.B - *t.C, changed);
}

void deduce_midlines_and_sides(Triangle& t, bool& changed) {
    if (t.a.has_value()) set_opt(t.na, *t.a / 2.0, changed);
    if (t.b.has_value()) set_opt(t.nb, *t.b / 2.0, changed);
    if (t.c.has_value()) set_opt(t.nc, *t.c / 2.0, changed);

    if (t.na.has_value()) set_opt(t.a, *t.na * 2.0, changed);
    if (t.nb.has_value()) set_opt(t.b, *t.nb * 2.0, changed);
    if (t.nc.has_value()) set_opt(t.c, *t.nc * 2.0, changed);
    if (t.a.has_value() && t.b.has_value() && t.c.has_value()) {
        double p = *t.a + *t.b + *t.c;
        set_opt(t.P, p, changed);
        set_opt(t.s, p / 2.0, changed);
    }
    if (t.P.has_value()) set_opt(t.s, *t.P / 2.0, changed);
    if (t.s.has_value()) set_opt(t.P, *t.s * 2.0, changed);
}

void deduce_law_of_sines_cosines(Triangle& t, bool& changed) {
    if (t.a.has_value() && t.b.has_value() && t.c.has_value()) {
        double a = *t.a, b = *t.b, c = *t.c;
        if (b > 0 && c > 0)
            set_opt(t.trigA.cos, clamp((b * b + c * c - a * a) / (2.0 * b * c), -1.0, 1.0), changed);
        if (a > 0 && c > 0)
            set_opt(t.trigB.cos, clamp((a * a + c * c - b * b) / (2.0 * a * c), -1.0, 1.0), changed);
        if (a > 0 && b > 0)
            set_opt(t.trigC.cos, clamp((a * a + b * b - c * c) / (2.0 * a * b), -1.0, 1.0), changed);
    }

    // Law of Cosines: SAS -> side
    if (t.b.has_value() && t.c.has_value() && t.trigA.cos.has_value()) {
        double val = (*t.b) * (*t.b) + (*t.c) * (*t.c) - 2.0 * (*t.b) * (*t.c) * (*t.trigA.cos);
        if (val >= 0.0) set_opt(t.a, sqrt(val), changed);
    }
    if (t.a.has_value() && t.c.has_value() && t.trigB.cos.has_value()) {
        double val = (*t.a) * (*t.a) + (*t.c) * (*t.c) - 2.0 * (*t.a) * (*t.c) * (*t.trigB.cos);
        if (val >= 0.0) set_opt(t.b, sqrt(val), changed);
    }
    if (t.a.has_value() && t.b.has_value() && t.trigC.cos.has_value()) {
        double val = (*t.a) * (*t.a) + (*t.b) * (*t.b) - 2.0 * (*t.a) * (*t.b) * (*t.trigC.cos);
        if (val >= 0.0) set_opt(t.c, sqrt(val), changed);
    }

    optional<double> two_R;
    if (t.a.has_value() && t.trigA.sin.has_value() && *t.trigA.sin > EPS)
        two_R = *t.a / *t.trigA.sin;
    else if (t.b.has_value() && t.trigB.sin.has_value() && *t.trigB.sin > EPS)
        two_R = *t.b / *t.trigB.sin;
    else if (t.c.has_value() && t.trigC.sin.has_value() && *t.trigC.sin > EPS)
        two_R = *t.c / *t.trigC.sin;

    if (two_R.has_value()) {
        set_opt(t.R, *two_R / 2.0, changed);
        if (t.trigA.sin.has_value()) set_opt(t.a, (*two_R) * (*t.trigA.sin), changed);
        if (t.trigB.sin.has_value()) set_opt(t.b, (*two_R) * (*t.trigB.sin), changed);
        if (t.trigC.sin.has_value()) set_opt(t.c, (*two_R) * (*t.trigC.sin), changed);

        if (t.a.has_value() && *two_R > EPS)
            set_opt(t.trigA.sin, clamp(*t.a / (*two_R), 0.0, 1.0), changed);
        if (t.b.has_value() && *two_R > EPS)
            set_opt(t.trigB.sin, clamp(*t.b / (*two_R), 0.0, 1.0), changed);
        if (t.c.has_value() && *two_R > EPS)
            set_opt(t.trigC.sin, clamp(*t.c / (*two_R), 0.0, 1.0), changed);
    }
}

void deduce_area_and_altitudes(Triangle& t, bool& changed) {
    if (t.s.has_value() && t.a.has_value() && t.b.has_value() && t.c.has_value()) {
        double s = *t.s;
        double prod = s * (s - *t.a) * (s - *t.b) * (s - *t.c);
        if (prod >= 0.0) set_opt(t.Area, sqrt(prod), changed);
    }

    if (t.a.has_value() && t.b.has_value() && t.trigC.sin.has_value())
        set_opt(t.Area, 0.5 * (*t.a) * (*t.b) * (*t.trigC.sin), changed);
    if (t.b.has_value() && t.c.has_value() && t.trigA.sin.has_value())
        set_opt(t.Area, 0.5 * (*t.b) * (*t.c) * (*t.trigA.sin), changed);
    if (t.a.has_value() && t.c.has_value() && t.trigB.sin.has_value())
        set_opt(t.Area, 0.5 * (*t.a) * (*t.c) * (*t.trigB.sin), changed);

    // Side + Altitude <-> Area
    if (t.a.has_value() && t.ha.has_value()) set_opt(t.Area, 0.5 * (*t.a) * (*t.ha), changed);
    if (t.b.has_value() && t.hb.has_value()) set_opt(t.Area, 0.5 * (*t.b) * (*t.hb), changed);
    if (t.c.has_value() && t.hc.has_value()) set_opt(t.Area, 0.5 * (*t.c) * (*t.hc), changed);

    if (t.Area.has_value() && *t.Area > 0.0) {
        if (t.a.has_value() && *t.a > EPS) set_opt(t.ha, 2.0 * (*t.Area) / (*t.a), changed);
        if (t.b.has_value() && *t.b > EPS) set_opt(t.hb, 2.0 * (*t.Area) / (*t.b), changed);
        if (t.c.has_value() && *t.c > EPS) set_opt(t.hc, 2.0 * (*t.Area) / (*t.c), changed);

        if (t.ha.has_value() && *t.ha > EPS) set_opt(t.a, 2.0 * (*t.Area) / (*t.ha), changed);
        if (t.hb.has_value() && *t.hb > EPS) set_opt(t.b, 2.0 * (*t.Area) / (*t.hb), changed);
        if (t.hc.has_value() && *t.hc > EPS) set_opt(t.c, 2.0 * (*t.Area) / (*t.hc), changed);
    }

    if (t.ha.has_value() && t.hb.has_value() && t.hc.has_value() &&
        *t.ha > EPS && *t.hb > EPS && *t.hc > EPS) {
        double inv_a = 1.0 / *t.ha;
        double inv_b = 1.0 / *t.hb;
        double inv_c = 1.0 / *t.hc;
        double H = 0.5 * (inv_a + inv_b + inv_c);
        double rad_val = H * (H - inv_a) * (H - inv_b) * (H - inv_c);
        if (rad_val > 0.0) {
            double inv_area = 4.0 * sqrt(rad_val);
            if (inv_area > EPS) set_opt(t.Area, 1.0 / inv_area, changed);
        }
    }
}

void deduce_medians_bisectors_radii(Triangle& t, bool& changed) {

    if (t.a.has_value() && t.b.has_value() && t.c.has_value()) {
        double a = *t.a, b = *t.b, c = *t.c;
        double v_a = 2.0 * b * b + 2.0 * c * c - a * a;
        double v_b = 2.0 * a * a + 2.0 * c * c - b * b;
        double v_c = 2.0 * a * a + 2.0 * b * b - c * c;
        if (v_a >= 0.0) set_opt(t.ma, 0.5 * sqrt(v_a), changed);
        if (v_b >= 0.0) set_opt(t.mb, 0.5 * sqrt(v_b), changed);
        if (v_c >= 0.0) set_opt(t.mc, 0.5 * sqrt(v_c), changed);
    }

    if (t.ma.has_value() && t.mb.has_value() && t.mc.has_value()) {
        double ma = *t.ma, mb = *t.mb, mc = *t.mc;
        double v_a = 2.0 * mb * mb + 2.0 * mc * mc - ma * ma;
        double v_b = 2.0 * ma * ma + 2.0 * mc * mc - mb * mb;
        double v_c = 2.0 * ma * ma + 2.0 * mb * mb - mc * mc;
        if (v_a >= 0.0) set_opt(t.a, (2.0 / 3.0) * sqrt(v_a), changed);
        if (v_b >= 0.0) set_opt(t.b, (2.0 / 3.0) * sqrt(v_b), changed);
        if (v_c >= 0.0) set_opt(t.c, (2.0 / 3.0) * sqrt(v_c), changed);
    }

    if (t.s.has_value() && t.a.has_value() && t.b.has_value() && t.c.has_value()) {
        double s = *t.s, a = *t.a, b = *t.b, c = *t.c;
        if (b + c > EPS) {
            double v = b * c * s * (s - a);
            if (v >= 0.0) set_opt(t.la, (2.0 * sqrt(v)) / (b + c), changed);
        }
        if (a + c > EPS) {
            double v = a * c * s * (s - b);
            if (v >= 0.0) set_opt(t.lb, (2.0 * sqrt(v)) / (a + c), changed);
        }
        if (a + b > EPS) {
            double v = a * b * s * (s - c);
            if (v >= 0.0) set_opt(t.lc, (2.0 * sqrt(v)) / (a + b), changed);
        }
    }

    if (t.a.has_value() && t.b.has_value() && t.c.has_value() && t.Area.has_value() && *t.Area > EPS) {
        set_opt(t.R, ((*t.a) * (*t.b) * (*t.c)) / (4.0 * (*t.Area)), changed);
    }
    if (t.Area.has_value() && t.s.has_value() && *t.s > EPS) {
        set_opt(t.r, (*t.Area) / (*t.s), changed);
    }
}

void solve_triangle(Triangle& t) {
    bool changed = true;
    int guards = 30;
    while (changed && guards--) {
        changed = false;
        deduce_classifications(t, changed);
        deduce_trig_and_angles(t, changed);
        deduce_midlines_and_sides(t, changed);
        deduce_law_of_sines_cosines(t, changed);
        deduce_area_and_altitudes(t, changed);
        deduce_medians_bisectors_radii(t, changed);
    }
}

string fmt(const optional<double>& val) {
    if (!val.has_value()) return "N/A";
    ostringstream oss;
    oss << fixed << setprecision(6) << *val;
    return oss.str();
}

void print_trig(const string& label, const TrigSet& tr) {
    cout << "  Trig " << label << ": "
         << "sin=" << fmt(tr.sin) << ", "
         << "cos=" << fmt(tr.cos) << ", "
         << "tan=" << fmt(tr.tan) << ", "
         << "csc=" << fmt(tr.csc) << ", "
         << "sec=" << fmt(tr.sec) << ", "
         << "cot=" << fmt(tr.cot) << '\n';
}

void print_triangle(int idx, const Triangle& t) {
    cout << "\n========== SOLVED TRIANGLE " << idx + 1 << " ==========\n";
    cout << "Side Classification : " << t.side_type << '\n';
    cout << "Angle Classification: " << t.angle_type << '\n';
    cout << "Sides (a, b, c)     : " << fmt(t.a) << ", " << fmt(t.b) << ", " << fmt(t.c) << '\n';
    cout << "Angles (A, B, C)    : " << fmt(t.A) << ", " << fmt(t.B) << ", " << fmt(t.C) << '\n';
    cout << "Medians (ma,mb,mc)  : " << fmt(t.ma) << ", " << fmt(t.mb) << ", " << fmt(t.mc) << '\n';
    cout << "Bisectors (la,lb,lc): " << fmt(t.la) << ", " << fmt(t.lb) << ", " << fmt(t.lc) << '\n';
    cout << "Heights (ha, hb, hc): " << fmt(t.ha) << ", " << fmt(t.hb) << ", " << fmt(t.hc) << '\n';
    cout << "Midlines (na,nb,nc) : " << fmt(t.na) << ", " << fmt(t.nb) << ", " << fmt(t.nc) << '\n';
    cout << "Perimeter / Semi    : " << fmt(t.P) << " / " << fmt(t.s) << '\n';
    cout << "Area / R / r        : " << fmt(t.Area) << " / " << fmt(t.R) << " / " << fmt(t.r) << '\n';
    print_trig("A", t.trigA);
    print_trig("B", t.trigB);
    print_trig("C", t.trigC);
}

vector<Triangle> input_triangles() {
    cout << "How many triangles: ";
    int count_triangles;
    if (!(cin >> count_triangles) || count_triangles < 0) return {};
    cout << '\n';

    vector<Triangle> triangles;
    triangles.reserve(count_triangles);

    for (int i = 0; i < count_triangles; i++) {
        Triangle t;
        cout << "\n TRIANGLE " << i + 1 << " \n";

        cout << "\nEquilateral (A), Isosceles (B), "
             << "Scalene (C), Not Known (N/A): ";
        string type;
        cin >> type;
        if (type == "A" || type == "a") t.side_type = "Equilateral";
        else if (type == "B" || type == "b") t.side_type = "Isosceles";
        else if (type == "C" || type == "c") t.side_type = "Scalene";
        else t.side_type = "N/A";

        cout << "\nAcute (A), Right (B), "
             << "Obtuse (C), Not Known (N/A): ";
        cin >> type;
        if (type == "A" || type == "a") t.angle_type = "Acute";
        else if (type == "B" || type == "b") t.angle_type = "Right";
        else if (type == "C" || type == "c") t.angle_type = "Obtuse";
        else t.angle_type = "N/A";

        cout << "\nSIDES\n";
        t.a = get_value("Side a: ");
        t.b = get_value("Side b: ");
        t.c = get_value("Side c: ");

        cout << "\nANGLES\n";
        t.A = get_value("Angle A: ");
        t.B = get_value("Angle B: ");
        t.C = get_value("Angle C: ");

        cout << "\nMEDIANS\n";
        t.ma = get_value("Median ma: ");
        t.mb = get_value("Median mb: ");
        t.mc = get_value("Median mc: ");

        cout << "\nBISECTORS\n";
        t.la = get_value("Bisector la: ");
        t.lb = get_value("Bisector lb: ");
        t.lc = get_value("Bisector lc: ");

        cout << "\nHEIGHTS\n";
        t.ha = get_value("Height ha: ");
        t.hb = get_value("Height hb: ");
        t.hc = get_value("Height hc: ");

        cout << "\nMIDLINES\n";
        t.na = get_value("Midline na: ");
        t.nb = get_value("Midline nb: ");
        t.nc = get_value("Midline nc: ");

        cout << "\nTRIGONOMETRY\n";
        for (int j = 0; j < 3; j++) {
            string angle = (j == 0 ? "A" : j == 1 ? "B" : "C");
            TrigSet& tr = (j == 0 ? t.trigA : j == 1 ? t.trigB : t.trigC);

            cout << "\nAngle " << angle << ":\n";
            tr.sin = get_value("sin: ");
            tr.cos = get_value("cos: ");
            tr.tan = get_value("tan: ");
            tr.csc = get_value("csc: ");
            tr.sec = get_value("sec: ");
            tr.cot = get_value("cot: ");
        }

        triangles.push_back(t);
    }

    return triangles;
}

void run() {
    cout << "Trigonometry Calculator\n";
    vector<Triangle> triangles = input_triangles();

    for (size_t i = 0; i < triangles.size(); i++) {
        solve_triangle(triangles[i]);
        print_triangle(static_cast<int>(i), triangles[i]);
    }
}

int main() {
    run();
    return 0;
}
