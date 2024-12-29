#include <iostream>
#include <cmath>
#include <chrono>
#include <string>
using namespace std;
const int nMax = 700;

struct toko {
    string namaToko;
    int jarak;
};

// Fungsi untuk membuat delay proporsional dengan ukuran dataset
void makeDelay(int size) {
    double result = 0;
    int iterations = 5000 + (size * 10);
    for(int i = 0; i < iterations; i++) {
        result += sqrt(i * 1.0);
        result = sin(result) + cos(result);
    }
}

int binarySearchNearest(toko arr[], int x, int size, long long &totalTime) {
    int left = 0;
    int right = size - 1;
    int best = -1;

    while (left <= right) {
        auto start = chrono::high_resolution_clock::now();

        int mid = (left + right) / 2;
        makeDelay(right - left + 1); // Delay proporsional terhadap ukuran dataset

        if (best == -1 || abs(arr[mid].jarak - x) < abs(arr[best].jarak - x)) {
            best = mid;
        }

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Durasi iterasi saat ini: " << totalTime << " mikrodetik" << endl;
        totalTime += duration.count();

        if (arr[mid].jarak < x) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return best;
}

void processDataset(toko arr[], int size, int target, const string& datasetName) {
    long long totalTime = 0;

    cout << "DATASET " << datasetName << " ELEMEN" << endl;
    int result = binarySearchNearest(arr, target, size, totalTime);
    cout << "Waktu total binary search: " << totalTime << " mikrodetik" << endl;
    cout << "Toko terdekat di dataset " << datasetName << " elemen: "
         << arr[result].namaToko << ", Jarak: " << arr[result].jarak << " km" << endl << endl;
}

int main() {
    cout << "ITERATIF" << endl;
    toko infoToko100[100];
    toko infoToko300[300];
    toko infoToko700[700];

    // Inisialisasi data toko
    for (int i = 0; i < 700; i++) {
        string nama = "Toko " + to_string(i + 1);
        int jarak = (i + 1) * 10;

        if (i < 100) infoToko100[i] = {nama, jarak};
        if (i < 300) infoToko300[i] = {nama, jarak};
        infoToko700[i] = {nama, jarak};
    }

    int posisi = 650;

    processDataset(infoToko100, 100, posisi, "100");
    processDataset(infoToko300, 300, posisi, "300");
    processDataset(infoToko700, 700, posisi, "700");

    return 0;
}
