#include <iostream>
using namespace std;

int main_1();
int main_2();
int main_3();
int main_4();
int main_5();

int main() {
    while (true) {
        cout << "This is Airport simulation. Please choose an example version below (1-5): " << endl;
        cout << "1. Run P1 version of Airport simulator" << endl;
        cout << "2. Run P2 version of Airport simulator" << endl;
        cout << "3. Run P3 version of Airport simulator" << endl;
        cout << "4. Run P4 version of Airport simulator" << endl;
        cout << "5. Run P5 version of Airport simulator" << endl;
        cout << "6. Quit the program" << endl;
        cout << "Your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: main_1(); break;
            case 2: main_2(); break;
            case 3: main_3(); break;
            case 4: main_4(); break;
            case 5: main_5(); break;
            case 6: return 0;
            default: cout << "Invalid choice.\n";
        }
    }
}