#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<double> separated_differences(const vector<double> &x_axis, const vector<double> &y_axis) {
    int n = x_axis.size();
    vector<double> a = y_axis;

    for (int j = 1; j < n; j++) {
        for (int i = n - 1; i >= j; i--) {
            a[i] = (a[i] - a[i-1]) / (x_axis[i] - x_axis[i-j]);
        }
    }
    return a;
}

double calculating_a_polynomial_at_a_point(const vector<double>& x, const vector<double>& a, double x_point) {
    double result = a[0];
    double term = 1.0;

    for (int i = 1; i < x.size(); i++) {
        term *= (x_point - x[i-1]);
        result += a[i] * term;
    }
    return result;
}

double interpolate_by_newton(vector<double> x_axis, vector<double> y_axis, double x) {
    auto a = separated_differences(x_axis, y_axis);
    return calculating_a_polynomial_at_a_point(x_axis, a, x);
}


string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}


int main()
{
    string x_axis_count_temp;
    getline(cin, x_axis_count_temp);

    int axis_count = stoi(ltrim(rtrim(x_axis_count_temp)));

    vector<double> x_axis(axis_count);
    string matrix_row_temp_temp;
    getline(cin, matrix_row_temp_temp);
    vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

    for (int j = 0; j < axis_count; j++) {
        double matrix_row_item = stod(matrix_row_temp[j]);

        x_axis[j] = matrix_row_item;
    }

    vector<double> y_axis(axis_count);
    getline(cin, matrix_row_temp_temp);
    matrix_row_temp = split(rtrim(matrix_row_temp_temp));

    for (int j = 0; j < axis_count; j++) {
        double matrix_row_item = stod(matrix_row_temp[j]);

        y_axis[j] = matrix_row_item;
    }

    string x_temp;
    getline(cin, x_temp);

    double x = stod(ltrim(rtrim(x_temp)));

    double result = interpolate_by_newton(x_axis, y_axis, x);

    cout << result << "\n";

    return 0;
}
