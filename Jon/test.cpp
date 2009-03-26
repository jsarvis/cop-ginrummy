#include <iostream>
#include <string>

using namespace std;

using namespace std;

void sort(int a[]);
void printCard(int a);

int main() {
	int cards[52];
	for(int i = 0; i < 52; i++) {
		cards[i] = ((51 - i) + 52) % 52 + 1;
		cout << cards[i] << " ";
	}	
	sort(cards);

	for(int i = 0; i < 52; i++) {
		if(i%13 == 0) cout << endl;
		printCard(cards[i]);
		cout << " ";
	}
	
	cin >> cards[0];
}

void sort(int a[]) {
	for(int i = 0; i < 51; i++) {
		for(int k = i+1; k < 52; k++) {
			if(a[k] < a[i]) {
				a[k] += a[i];
				a[i] = a[k] - a[i];
				a[k] -= a[i];
			}
		}
	}
}

void printCard(int a) {
	string suits[4] = {"Hearts", "Diamonds", "Spades", "Clubs"};
	cout << ((a-1)%13 + 1) << " of " << suits[(a-1)/13] ;

	return;
}
