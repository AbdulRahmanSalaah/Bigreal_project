// File:A2_S3_20220300_1.cpp
// Author1:Abdulrahman Salah ID:20220176
// Author2:Mahamed ali saed ID:20220300
// Author3:Ahmad osama ID:20220009
// Section:S3
// TA:belal


#include <iostream>
#include "BigReal.h"
#include <iostream>
#include <string>

using namespace std;

int main() {

    BigReal n1 ("11.9000000000000000000000000000000001");
    BigReal n2 ("2333333333339.1134322222222292");
    BigReal n3 = n1 + n2;
    cout << n3<<endl;

    n3 = n3 + BigReal (0.9);
    cout<<n3<<endl;

    return 0;
}
