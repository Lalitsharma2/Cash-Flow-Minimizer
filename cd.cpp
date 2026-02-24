#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

class CashFlowMinimizer {
    int n;
    vector<string> names;
    vector<double> paid;
    vector<double> net;

public:
    CashFlowMinimizer(int size) {
        n = size;
        names.resize(n);
        paid.resize(n);
        net.resize(n);
    }

    void inputNames() {
        cout << "\nEnter names of participants:\n";
        for(int i = 0; i < n; i++)
            cin >> names[i];
    }

    void inputPayments() {
        cout << "\nEnter amount paid by each participant:\n";
        for(int i = 0; i < n; i++) {
            cout << names[i] << ": ";
            cin >> paid[i];
        }
    }

    void calculateNet(double &total, double &share) {
        total = 0.0;

        for(int i = 0; i < n; i++)
            total += paid[i];

        share = total / n;

        for(int i = 0; i < n; i++)
            net[i] = paid[i] - share;
    }

    int getMaxCredit() {
        int idx = 0;
        for(int i = 1; i < n; i++)
            if(net[i] > net[idx])
                idx = i;
        return idx;
    }

    int getMaxDebit() {
        int idx = 0;
        for(int i = 1; i < n; i++)
            if(net[i] < net[idx])
                idx = i;
        return idx;
    }

    void minimizeCashFlow() {
        double total, share;
        calculateNet(total, share);

        cout << fixed << setprecision(2);

        cout << "\n----- Expense Summary -----\n";
        cout << "Total Expense : Rs " << total << endl;
        cout << "Equal Share   : Rs " << share << endl;

        cout << "\n----- Net Balances -----\n";
        for(int i = 0; i < n; i++) {
            if(net[i] > 0.001)
                cout << names[i] << " should receive Rs " << net[i] << endl;
            else if(net[i] < -0.001)
                cout << names[i] << " should pay Rs " << -net[i] << endl;
            else
                cout << names[i] << " is settled up." << endl;
        }

        cout << "\n----- Optimized Transactions -----\n";

        while(true) {
            int maxCredit = getMaxCredit();
            int maxDebit = getMaxDebit();

            if(fabs(net[maxCredit]) < 0.001 && fabs(net[maxDebit]) < 0.001)
                break;

            double amount = min(-net[maxDebit], net[maxCredit]);

            if(amount < 0.001)
                break;

            net[maxCredit] -= amount;
            net[maxDebit] += amount;

            cout << names[maxDebit] << " pays "
                 << names[maxCredit] << " Rs "
                 << amount << endl;
        }
    }
};

int main() {
    int n;

    cout << "===== CASH FLOW MINIMIZER (AUTO) =====\n";
    cout << "Enter number of participants: ";
    cin >> n;

    if(n <= 0) {
        cout << "Invalid number of participants.\n";
        return 0;
    }

    CashFlowMinimizer cfm(n);

    cfm.inputNames();
    cfm.inputPayments();
    cfm.minimizeCashFlow();

    return 0;
}