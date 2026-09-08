#include <iostream>
#include <string>
using namespace std;

class MyString {
private:
    int* ptr;
    
};


bool MyString::operator==(const MyString& b) const {
    return str == b.str;
}

int main() {
    MyString s1("Hello");
    MyString s2(" World");
    MyString s3("!!!");
        
    MyString result = s1 + s2 + s3;
    
    cout << "RESULT: ";
    result.print();
    cout << endl;
    
    MyString s4("C++");
    MyString s5(" is ");
    
    MyString s6("awesome!");
    
    MyString result2 = s4 + s5 + s6;
    if (result == result2){
        cout << "The results are equal." << endl;
    } else {
        cout << "The results are not equal." << endl;
    }
    
    cout << "RESULT2: ";
    result2.print();
    cout << endl;
    
    return 0;
}