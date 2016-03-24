#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <cmath>

using namespace std;

#define left(n)  (2*n+1)
#define right(n) (2*n+2)

enum ORDERING {ASCENDING, DESCENDING};


template<typename T>
void heapSort(vector<T> &list, ORDERING theorder);

template<typename T>
void reheapifyUp(vector<T> &list, size_t pos, ORDERING theorder);

template<typename T>
void reheapifyDown(vector<T> &list, size_t pos, ORDERING theorder);

template<typename T>
void print(const vector<T>&list, char* title);

template<typename T>
size_t maxOfList(const vector<T>& list);

template<typename T>
void initialize(vector<T> &list, ORDERING &theorder);


template<typename T>
bool lessThan (const T &a, const T &b);

template<typename T>
bool greaterThan (const T &a, const T &b);



int main()
{
    vector<size_t> list;
    ORDERING theorder = (ORDERING)0;
    srand(time(NULL));
    initialize(list, theorder);
    print(list,"unsorted");
    heapSort(list, theorder);
    print(list,"sorted");
}


template<typename T>
void heapSort(vector<T> &list, ORDERING theorder)
{
    //Put items size_to the heap
    for(size_t i = 1; i <list.size(); ++i)
        reheapifyUp(list,i, theorder);
    //Take items out of the heap
    for(size_t i = list.size()-1; i > 0; --i)
    {
        swap(list[i], list[0]);
        reheapifyDown(list,i-1, theorder);
    }
}


template<typename T>
void initialize(vector<T> &list, ORDERING &theorder)
{
    size_t largest, qty;
    string ans;
    cout<<"How many random numbers do you want? ";
    cin>>qty;
    cout<<"What is the largest random number to see? ";
    cin>>largest;
    cin.ignore(INT_MAX, '\n');
    cout<<"Sort in [a]scending or [d]escending order? ";
    getline (cin, ans);
    theorder = (ORDERING)(toupper(ans[0]) == 'D');
    cout<<"the order = "<<theorder<<endl;
    for(size_t i = 0; i < qty; ++i)
        list.push_back(rand()%largest + 1);
}

template<typename T>
void reheapifyUp(vector<T> &list, size_t pos, ORDERING theorder)
{
    size_t child = pos,
            parent = (child-1)/2;

    bool(*func_ptr[2])(const T&, const T&) = {&lessThan, &greaterThan};



    bool notDone = true;
    while(child && notDone)
        if(func_ptr[theorder](list[parent],list[child]))
        {
            swap(list[child],list[parent]);
            child = (child-1)/2;
            parent = (child-1)/2;
        }
        else
            notDone = false;
}

template<typename T>
void reheapifyDown(vector<T> &list, size_t pos, ORDERING theorder)
{
    bool notDone = true;
    size_t parent = 0, toSwap;
    bool(*func_ptr[2])(const T&, const T&) = {&lessThan, &greaterThan};
    while(notDone && parent < pos)
        //No Children
        if( left(parent) > pos)
            notDone=false;
        else
        {
            //Two kids?????
            if(right(parent) <= pos)
            {
                toSwap = (func_ptr[theorder](list[left(parent)],list[right(parent)]))
                        ?
                            right(parent) : left(parent);
            }
            else
                toSwap = left(parent); //Only child
            if(func_ptr[theorder](list[parent],list[toSwap]))
            {
                swap(list[parent], list[toSwap]);
                parent=toSwap;
            }
            else
                notDone = false;
        }
}

template<typename T>
size_t maxOfList(const vector<T>& list)
{
    size_t maximum = list[0];
    for(size_t i = 1; i < list.size(); ++i)
        maximum = max(maximum, list[i]);
    return maximum;
}

template<typename T>
void print(const vector<T>&list, char* title)
{
    size_t digits = 2 + log10(maxOfList(list))+1,
            col = 65/digits;
    cout<<"Your "<<title<<" list is: "<<endl;
    for(size_t i = 0; i < list.size(); ++i)
    {
        if(!(i%col))
            cout<<endl;
        cout<<setw(digits)<<list[i];
    }
    cout<<endl<<endl;
}

template<typename T>
bool lessThan (const T &a, const T &b)
{
    return a < b;
}

template<typename T>
bool greaterThan (const T &a, const T &b)
{
    return b < a;
}
