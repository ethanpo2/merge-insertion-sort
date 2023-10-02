#pragma warning(disable : 4996)

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <limits>
#include "sorts.h"

using namespace std;

void print_usage();
int correctTest(int argc, char** argv);
int timeTest();


int main(int argc, char** argv) {
    if (argc >= 2 && argv[1][0] == 't') {
        return timeTest();
    }
    return correctTest(argc, argv);
}

void print_usage()
{
    cout << "Usage:\n\n" << 
        "intro.exe k #...\n" <<
        "Where k is the array length the progam will switch from merge to insertion\n" <<
        "and #... is a list of space-separated integer(s)\n\n" <<
        "intro.exe t\n" <<
        "Runs the program in test mode where it outputs a table of test results " <<
        "and generates a csv file of the same results.\n";
}

int correctTest(int argc, char** argv)
{
    int i, k;
    long extr;
    char* p;
    vector<int> data;

    if (argc < 3) {
        print_usage();
        return -1;
    }
    
    k = (int)strtol(argv[1], &p, 10);
    if (*p) {
        cout << "k (input param #1) cannot be converted to a long.\n\n";
        print_usage();
        return -2;
    }
    if (k == 0) {
        k = 1;
        cout << "k less than 1 set to 1";
    }

    for (i = 2; i < argc; ++i) {
        char* conv;
        extr = strtol(argv[i], &conv, 10);
        if (*conv) {
            cout << "Input param #" << i << " cannot be converted to a long.\n\n";
            print_usage();
            return -2;
        }
        data.push_back((int)extr);
    }

    mergeSort(data, 0, (int)data.size(), k);

    for (vector<int>::const_iterator cit = data.cbegin(); cit != data.cend(); cit++) {
        cout << *cit << " ";
    }

    return 0;

}

int timeTest()
{
    ofstream fout("introStats.csv", ofstream::trunc);
    int n = 5000, fastest;
    double min = numeric_limits<double>::max();
    random_device rd;

    fout << "n = " << n << "\n"
        << "k,1st runtime (s), 2nd runtime (s), 3rd runtime (s), avg runtime (s)\n";

    cout << "Time Test Started\n";
    for (int k = 1; k <= 20; ++k) {
        int j, m;
        std::chrono::duration<double> elapsed_seconds = chrono::steady_clock::duration::zero();

        fout << k << ",";
        cout << "\rWorking on k " << k << "/20...";
        for (m = 0; m < 3; ++m) {
            vector<int> a;

            for (j = 0; j < n; ++j) {
                a.push_back(rd());
            }

            const auto start = chrono::steady_clock::now();
            mergeSort(a, 0, (int)a.size(), k);
            const auto end = chrono::steady_clock::now();
            elapsed_seconds += (chrono::duration<double>)(end - start);
            fout << ((chrono::duration<double>)(end - start)).count() << ",";
        }

        elapsed_seconds /= 3;
        if (min > elapsed_seconds.count()) {
            min = elapsed_seconds.count();
            fastest = k;
        }
        fout << elapsed_seconds.count() << "\n";
    }

    fout << "\nBest k: " << fastest << "\n";
    cout << "\rFinishing up (about 10s)...              ";

    //n = 50000 makes the final insertion sort take 20 min
    vector<int> sorted;
    for (int i = 0; i < n; ++i) {
        sorted.push_back(i);
    }
    const auto start1 = chrono::steady_clock::now();
    mergeSort(sorted, 0, (int)sorted.size(), 1);
    const auto end1 = chrono::steady_clock::now();
    fout << "k=1 Ordered List time in seconds: " << ((chrono::duration<double>)(end1 - start1)).count() << "\n";

    const auto start2 = chrono::steady_clock::now();
    mergeSort(sorted, 0, (int)sorted.size(), n);
    const auto end2 = chrono::steady_clock::now();
    fout << "k=n Ordered List time in seconds: " << ((chrono::duration<double>)(end2 - start2)).count() << "\n";


    vector<int> unsorted;
    for (int i = 0; i < n; ++i) {
        unsorted.push_back(rd());
    }
    const auto start3 = chrono::steady_clock::now();
    mergeSort(unsorted, 0, (int)unsorted.size(), 1);
    const auto end3 = chrono::steady_clock::now();
    fout << "k=1 Unordered List time in seconds: " << ((chrono::duration<double>)(end3 - start3)).count() << "\n";

    unsorted.clear();
    for (int i = 0; i < n; ++i) {
        unsorted.push_back(rd());
    }
    const auto start4 = chrono::steady_clock::now();
    mergeSort(unsorted, 0, (int)unsorted.size(), n);
    const auto end4 = chrono::steady_clock::now();
    fout << "k=n Ordered List time in seconds: " << ((chrono::duration<double>)(end4 - start4)).count() << "\n";




    fout.close();
    cout << "\rComplete                     \n";
    return 0;
}

