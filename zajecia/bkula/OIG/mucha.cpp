#include <iostream>
using namespace std;
int main() {

    int t;
    cin >> t;
    bool wyn[t];
    for (int i = 0; i < t; i++) {
	wyn[i] = true;
	int n;
	cin >> n;
	int x[n], y[n];
	for (int j = 0; j < n; j++) {

	    cin >> x[j] >> y[j];
	
	    if (j != 1 && j != 0)    
		if (x[j-1]*y[j] - y[j-1]*x[j] > 0) {wyn[i] = false;}
	} 
    }
    for (int i = 0; i < t; i++) {
	if (wyn[i]) cout << "TAK\n";
	else cout << "NIE\n";
    }
    return 0;
}
