#include <iostream>
#include "Position.h"
#include "ArrayLists.h"
using namespace std;


int main(){
    ArrayList<int> list;
    
    // Setup list: [10, 20, 30, 40, 50]
    list.insert(0, 50);
    list.insert(0, 40);
    list.insert(0, 30);
    list.insert(0, 20);
    list.insert(0, 10);

    cout << "Initial length: " << list.getLength() << "\n";

    list.remove(0); // Remove first (10)
    list.remove(2); // Remove middle (40)
    list.remove(2); // Remove last (50)

    cout << "\nList after removals (Should be 20, 30):\n";
    for(int i = 0; i < list.getLength(); i++) {
        cout << "Index " << i << ": " << list.get(i) << "\n";
    }

    return 0;
}