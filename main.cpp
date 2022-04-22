#include "Vector.h"



int main(){
    Vector vec1;
    vec1.pushBack(1);
    vec1.pushFront(2);
    vec1.insert(vec1, 0);
    cout << vec1.capacity() << endl;
    for(int i = 0; i < vec1.size(); i++){
        cout << vec1[i] <<endl;
    }
    
}