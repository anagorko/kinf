#include <iostream>
using namespace std;

int pierwsza (int n) {
    for (int i = 2; ; i++) {
	if (i*i > n) return true;
	if ((n%i)==0) return false;
    }
    return true;
}

int main() {

    int N;
    cin >> N;

    if (N == 1) {
	cout << "3 5";
	return 0;
    }
    //N--;

    for (int k = 0; ; k++) {
	if (pierwsza(6*k-1) && pierwsza(6*k+1)) {
	    N--;
	    if (N == 0) {
		cout << 6*k-1 << " " << 6*k+1; break;
	    }
	}
    }

}
