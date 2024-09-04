/*******************************************************************/
/*                                                                 */
/*  A1 Part 3: Majority Element starter file                       */
/*                                                                 */
/*  Author1 Name: Royston Ng                                       */                                      
/*                                                                 */
/*******************************************************************/

#include <iostream>

bool findCandidate(int array[],int& candidate, int sz);
bool majorityElement(const int arr[], int& majority, int sz);


//This function returns true if an integer called majority is present in more than 50 percent of the array
//let arr[] be the array of integers we are searching through
//let majority be a reference to an integer that will contain the majority candidate
//let sz, be the size of the array being passed to the function
bool majorityElement(const int arr[], int& majority, int sz){
    int* copy = new int[sz];    //copy is a dynamically allocated array of size sz that is an exact copy of arr[]        //2
    int count = 0;              //let count be the number of times the majority candidate shows up in the passed array   //1

    for (int i = 0; i < sz; i++)   // 1+n+n
    {
        copy[i] = arr[i];   //n
    }

    findCandidate(copy, majority, sz);  //find a candidate T(n) = O(n log n)

    for (int i = 0; i < sz; i++)        //1 + n + n
    {
        if (arr[i] == majority)         //n
        {
            count++;                    //n
        }
    }

    delete[] copy;      //1

    if (count > sz / 2) //2
    {
        return true;    //1
    }
    else
    {
        return false;   //1
    }
}

//Majority element Analysis
// T(n) = 2 + 3 + 1 + 2n + n + O(n log n) + 1 + 2n + 2n + 1 + 2 + 1
//      = 7n + O(n log n) 11 
//Because the time complexity of findCandidate is O(n log n), this means the time complexity of
//majorityElement is O(n log n)

//This function finds a majority candidate for the function above.

bool findCandidate(int array[],int& candidate, int sz){
    int j = 0;      //let j be the location of the numbers to be compared in the passed array   1
    int i = 0;      //let i be the location of the kept numbers     1
    bool odd = false;   //let odd be true if int sz is an odd number        1
    int holder = 0;     //let holder location of the eligible majority candidate        1

    if (sz % 2 == 1)    //2
    {
        holder = array[sz - 1]; //2
        odd = true;     //1
        sz -= 1;        //1
    }

    for (j = 0; j < sz; j += 2)     //if odd is true n = n-1; 1+(n/2) + (n/2) = 1 +(2n/2) = 1 + n
    {
        if (sz > 1)                          //1
        {
            if (array[j] == array[j + 1])   // (n/2)
            {
                array[i++] = array[j];  // (n/2)
            }
        }
    }

    if (i == 1) //1
    {
        candidate = array[0];   //1
        return true;    //1
    }
    else if (i == 0 && odd)     //2
    {
        candidate = holder;     //1
        return odd;     //1
    }
    else if (i==0 && !odd)  //3
    {
        return false;       //1
    }
    
    if (i && findCandidate(array, candidate, i))    //1 + T(n/2)
    {
        return true;    //1
    }
    else
    {
        candidate = holder; //1
        return odd; //1
    }
}

//Analysis of findCandidate
// T(0) = 15
// T(1) = 17
// T(2) = 19
// T(3) = 23
// T(4) = 24 + T(2)
//      = 24 + 19
//      = 43
// T(5) = 27 + T(2)
//      = 27 + 19
//      = 46
// T(6) = 26 + T(3)
//      = 26 + 23
//      = 49
// T(7) = 31 + T(3)
//      = 31 +23
//      = 54
// T(8) = 31 + T(4)
//      = 31 + 43
//      = 74
//      = 2(12) + 2 + 25
// T(12)= 38 + T(6)
//      = 38 + 26 + 25
//      = 3(12) + 2 + 2(12) + 2 + 25
//      = 5(12) + 2(2) + 25          2(12) + 1(2)
//T(24) = 62 + T(12)
//      = 62 + 38 + 26 + 25
//      = 5(12) + 2 + 3(12) + 2 + 2(12) + 2 + 25 
//      = 10(12) +3(2) + 25           4(12) + 1(2)
//T(48) = 110 + T(24)  
//      = 9(12) + 5(12) + 3(12) + 2(12) + 4(2) + 25
//      = 19(12) + 4(2) + 25          8(12) + 1(2)
//T(96) = 206 + T(24)
//      = 17(12) + 9(12) + 5(12) + 3(12) + 2(12) + 5(2) + 25
//      = 36(12) 5(2) +25
//T(n) = O(n logn) This is due to the fact that the line has more erratic jumps in value at lower values but continues to trend upward