
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);

    int t;
    cin >> t;
    int wyn[t][2];

    for (int i = 0; i < t; i++) {
        wyn[i][0] = wyn[i][1] = 0;

        string str;
        cin >> str;

        int from = -7;
        int to = -7;
        int naj = 0;

        vector<int> vec;

        if (str[0] == 'A' || str[0] == 'G') vec.push_back(1);

        for (int j = 0; j < str.size(); j++) {

            if (str[j] == 'C' || str[j] == 'T') {
                if (((vec.size() % 2) != 0)) {
                    vec.back()++;
                } else {
                    vec.push_back(1);
                }
            } else {
                if (((vec.size() % 2) == 0)) {
                    vec.back()++;
                } else {
                    vec.push_back(1);
                }
            }
        }

        if ((vec.size() % 2) == 0) vec.push_back(1);


        for (int j = 0, dlugosc = 0; j < vec.size(); j++) {
            dlugosc += vec[j];
            if ((j % 2) == 0) {
                if (j < vec.size() - 2) {
                    if (naj < vec[j+1] || (naj == vec[j+1] && vec[j+1] + 1 > to - from)) {
                        naj = vec[j+1];
                        from = dlugosc - 1;
                        to = dlugosc + vec[j+1];
                    }
                    if (j < vec.size() - 4) {
                        if (vec[j+2] == 1 && (naj < vec[j+1] + vec[j+3] || (naj == vec[j+1] + vec[j+3] && vec[j+1] + vec[j+2] + vec[j+3] > to - from))) {
                            naj = vec[j+1] + vec[j+3];
                            from = dlugosc;
                            to = dlugosc + vec[j+1] + vec[j+2] + vec[j+3];
                        } else if ((vec[j+2] == 2 && vec[j+1] == vec[j+3]) && (naj < vec[j+1] || (naj == vec[j+1] && vec[j+1]*2 + 2 > to - from))) {
                            naj = vec[j+1];
                            from = dlugosc;
                            to = dlugosc + vec[j+1] + vec[j+2] + vec[j+3];
                        }
                    }
                }
            }
        }

        if (! naj) {
            from = 0;
            to = str.size();
        }

        //cout<<"$"<<naj<<" "<<from<<" "<<to<<endl;

        for (int j = from; j < to; j++) {
            if (str[j] == 'C' || str[j] == 'T') {
                wyn[i][1]++;
            } else {
                wyn[i][0]++;
            }
        }
    }

    for (int i = 0; i < t; i++) {
        cout << wyn[i][0] << " " << wyn[i][1] << endl;
    }
}
