// Read and Write Conflicts.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <atlstr.h>
#include <cstdlib>
#include <iostream>
using namespace std;
const int MAX = 1e5;
int* pointerNoAtomic = new int;         //writer and writer pointer noAtomic
int valueNoAtomic;                      //writer and writer value noAtomic
atomic<int> valueAtomic;                //writer and writer value Atomic
atomic<int>* pointerAtomic = new atomic<int>;   //writer and writer value Atomic


// case 1
DWORD WINAPI writer_vn(LPVOID lpParam) {
for (int i = 0; i < MAX; ++i) {
    ++valueNoAtomic;
}
printf("finish\n");
//cout << "finish" << endl;
return 1;
}



// case 2
DWORD WINAPI writer_pn(LPVOID lpParam) {
int* p = (int*)lpParam;
for (int i = 0; i < MAX; ++i) {
    ++* p;
}
printf("finish\n");
//cout << "finish" << endl;
return 1;
}

// case 3
DWORD WINAPI writer_va(LPVOID lpParam) {
for (int i = 0; i < MAX; ++i) {
    ++valueAtomic;
}
printf("finish\n");
//cout << "finish" << endl;
return 1;
}


// case 4
DWORD WINAPI writer_pa(LPVOID lpParam) {
 atomic<int>* p = (atomic<int>*)lpParam;
for (int i = 0; i < MAX; ++i) {
    ++* p;
}
printf("finish\n");
//cout << "finish" << endl;
return 1;
}



int main()
{
HANDLE hThread1, hThread2;

DWORD dwThreadId1, dwThreadId2;

cout << "==============================================================" << endl;
cout<<"writer and writer value without atomic"<<endl;
    valueNoAtomic = 0;
    hThread1 = CreateThread(NULL
        , NULL
        , writer_vn
        , NULL
        , 0	
        , &dwThreadId1
    );

    hThread2 = CreateThread(NULL
        , NULL
        , writer_vn
        , NULL
        , 0
        , &dwThreadId2
    );
    Sleep(3);
    if (hThread1 == NULL) return 0;
    else CloseHandle(hThread1);

    if (hThread2 == NULL) return 0;
    else CloseHandle(hThread2);

    cout << "valueNoAtomic should be: " << MAX + MAX << " valueNoAtomic finally is: " << valueNoAtomic << endl;
    cout << "==============================================================" << endl;
    cout << "writer and writer pointer without atomic" << endl;
    *pointerNoAtomic = 0;
    hThread1 = CreateThread(NULL
        , NULL
        , writer_pn
        , pointerNoAtomic
        , 0
        , &dwThreadId1
    );

    hThread2 = CreateThread(NULL
        , NULL
        , writer_pn
        , pointerNoAtomic
        , 0
        , &dwThreadId2
    );
    Sleep(3);
    if (hThread1 == NULL) return 0;
    else CloseHandle(hThread1);

    if (hThread2 == NULL) return 0;
    else CloseHandle(hThread2);

    cout << "*pointerNoAtomic should be: " << MAX + MAX << " *pointerNoAtomic finally is: " << *pointerNoAtomic << endl;
    cout << "==============================================================" << endl;
    cout << "writer and writer value with atomic" << endl;
    valueAtomic = 0;
    hThread1 = CreateThread(NULL
        , NULL
        , writer_va
        , NULL
        , 0
        , &dwThreadId1
    );

    hThread2 = CreateThread(NULL
        , NULL
        , writer_va
        , NULL
        , 0
        , &dwThreadId2
    );
    Sleep(3);
    if (hThread1 == NULL) return 0;
    else CloseHandle(hThread1);

    if (hThread2 == NULL) return 0;
    else CloseHandle(hThread2);

    cout << "valueAtomic should be: " << MAX + MAX << " valueAtomic finally is: " << valueAtomic << endl;


    cout<<"==============================================================" << endl;
    cout << "writer and writer pointer with atomic" << endl;
    *pointerAtomic = 0;
    hThread1 = CreateThread(NULL
        , NULL
        , writer_pa
        , pointerAtomic
        , 0
        , &dwThreadId1
    );

    hThread2 = CreateThread(NULL
        , NULL
        , writer_pa
        , pointerAtomic
        , 0
        , &dwThreadId2
    );
    Sleep(3);
    if (hThread1 == NULL) return 0;
    else CloseHandle(hThread1);

    if (hThread2 == NULL) return 0;
    else CloseHandle(hThread2);

    cout << "*pointerAtomic should be: " << MAX + MAX << " *pointerAtomic finally is: " << *pointerAtomic << endl;



return 0;
}


