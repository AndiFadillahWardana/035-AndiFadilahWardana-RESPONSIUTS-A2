#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Parkir {
private:
    string nama[100], jenis[100], nomor[100], metode[100];
    double lama[100], biaya[100];
    bool sudahBayar[100];
    int jumlah = 0;

public:
    bool login() {
        string username, password;

        cout << "===== LOGIN PETUGAS PARKIR =====" << endl;
        cout << "Username : ";
        cin >> username;
        cout << "Password : ";
        cin >> password;

        if (username == "admin" && password == "2500018035") {
            cout << "\nLogin berhasil!\n";
            return true;
        } else {
            cout << "\nLogin gagal! Username atau password salah.\n";
            return false;
        }
    }

    int hitungBiayaRekursif(int jam) {
        if (jam <= 0) {
            return 0;
        }
        return 3000 + hitungBiayaRekursif(jam - 1);
    }

    string statusParkir(int jam) {
        if (jam > 5) {
            return "Parkir Lama";
        } else {
            return "Parkir Biasa";
        }
    }

    string statusPembayaran(bool status) {
        if (status) {
            return "Sudah Bayar";
        } else {
            return "Belum Bayar";
        }
    }

    void tambahData() {
        if (jumlah >= 100) {
            cout << "\nData parkir sudah penuh!\n";
            return;
        }

        cout << "\n===== TAMBAH DATA KENDARAAN =====" << endl;

        cin.ignore();

        cout << "Nama Pemilik      : ";
        getline(cin, nama[jumlah]);

        cout << "Jenis Kendaraan   : ";
        getline(cin, jenis[jumlah]);

        cout << "Nomor Kendaraan   : ";
        getline(cin, nomor[jumlah]);

        cout << "Lama Parkir (jam) : ";
        cin >> lama[jumlah];

        biaya[jumlah] = hitungBiayaRekursif(lama[jumlah]);
        sudahBayar[jumlah] = false;
        metode[jumlah] = "-";

        jumlah++;

        cout << "\nData kendaraan berhasil ditambahkan!\n";
    }

    void tampilData() {
        if (jumlah == 0) {
            cout << "\nBelum ada kendaraan yang sedang parkir.\n";
            return;
        }

        cout << "\n===== DATA KENDARAAN PARKIR =====" << endl;
        cout << left << setw(5) << "No"
             << setw(20) << "Nama"
             << setw(15) << "Jenis"
             << setw(15) << "Nomor"
             << setw(10) << "Jam"
             << setw(15) << "Biaya"
             << setw(15) << "Parkir"
             << setw(15) << "Bayar" 
             << setw(15) << "Metode" << endl;

        cout << string(125, '-') << endl;

        for (int i = 0; i < jumlah; i++) {
            cout << left << setw(5) << i + 1
                 << setw(20) << nama[i]
                 << setw(15) << jenis[i]
                 << setw(15) << nomor[i]
                 << setw(10) << lama[i]
                 << "Rp" << setw(13) << biaya[i]
                 << setw(15) << statusParkir(lama[i])
                 << setw(15) << statusPembayaran(sudahBayar[i])
                 << setw(15) << metode[i]
                 << endl;
        }
    }

void hapusData() {
    string cari;

    tampilData();

    if (jumlah == 0)
        return;

    cout << "\nMasukkan nomor kendaraan yang keluar : ";
    cin >> cari;

    int indeks = -1;

    for (int i = 0; i < jumlah; i++) {
        if (nomor[i] == cari) {
            indeks = i;
            break;
        }
    }

    if (indeks == -1) {
        cout << "\nData kendaraan tidak ditemukan!\n";
        return;
    }

    for (int i = indeks; i < jumlah - 1; i++) {
        nama[i] = nama[i + 1];
        jenis[i] = jenis[i + 1];
        nomor[i] = nomor[i + 1];
        lama[i] = lama[i + 1];
        biaya[i] = biaya[i + 1];
        sudahBayar[i] = sudahBayar[i + 1];
        metode[i] = metode[i + 1];
    }

    jumlah--;

    cout << "\nData kendaraan berhasil dihapus!\n";
}

void bayarParkir() {
    string cari;
    int metodeBayar;

    tampilData();

    if (jumlah == 0)
        return;

    cout << "\nMasukkan nomor kendaraan yang akan membayar : ";
    cin >> cari;

    int indeks = -1;

    for (int i = 0; i < jumlah; i++) {
        if (nomor[i] == cari) {
            indeks = i;
            break;
        }
    }

    if (indeks == -1) {
        cout << "\nData kendaraan tidak ditemukan!\n";
        return;
    }

    if (sudahBayar[indeks]) {
        cout << "\nTransaksi pembayaran sudah dilakukan.\n";
        cout << "Status Pembayaran : Sudah Bayar\n";
        return;
    }

    cout << "\n===== PILIH METODE PEMBAYARAN =====" << endl;
    cout << "1. Tunai" << endl;
    cout << "2. Transfer Bank" << endl;
    cout << "3. E-Wallet" << endl;
    cout << "Pilih metode pembayaran: ";
    cin >> metodeBayar;

    if (metodeBayar == 1) {
        metode[indeks] = "Tunai";
    } else if (metodeBayar == 2) {
        metode[indeks] = "Transfer Bank";
    } else if (metodeBayar == 3) {
        metode[indeks] = "E-Wallet";
    } else {
        cout << "\nMetode pembayaran tidak valid!\n";
        return;
    }

    sudahBayar[indeks] = true;

    cout << "\nTransaksi pembayaran telah dilakukan.\n";
    cout << "Status Pembayaran : Sudah Bayar\n";
    cout << "Total Pembayaran  : Rp" << biaya[indeks] << endl;
    cout << "Metode Pembayaran : " << metode[indeks] << endl;

    cetakStruk(indeks);
}

    void cetakStruk(int i) {
        ofstream file("struk_parkir.txt", ios::app);

        file << "===== STRUK PARKIR =====" << endl;
        file << "Nama Pemilik    : " << nama[i] << endl;
        file << "Jenis Kendaraan : " << jenis[i] << endl;
        file << "Nomor Kendaraan : " << nomor[i] << endl;
        file << "Lama Parkir     : " << lama[i] << " jam" << endl;
        file << "Status Parkir   : " << statusParkir(lama[i]) << endl;
        file << "Total Biaya     : Rp" << biaya[i] << endl;
        file << "Metode Bayar    : " << metode[i] << endl;
        file << "Status Bayar    : " << statusPembayaran(sudahBayar[i]) << endl;
        file << "========================" << endl << endl;

        file.close();

        cout << "Struk berhasil dicetak ke file struk_parkir.txt\n";
    }

    void menu() {
        int pilihan;

        do {
            cout << "\n===== SISTEM INFORMASI PARKIR =====" << endl;
            cout << "1. Tambah Data Kendaraan" << endl;
            cout << "2. Tampilkan Data Kendaraan" << endl;
            cout << "3. Hapus Data Kendaraan Keluar" << endl;
            cout << "4. Pembayaran Parkir" << endl;
            cout << "5. Keluar" << endl;
            cout << "Pilih menu: ";
            cin >> pilihan;

            switch (pilihan) {
                case 1:
                    tambahData();
                    break;
                case 2:
                    tampilData();
                    break;
                case 3:
                    hapusData();
                    break;
                case 4:
                    bayarParkir();
                    break;
                case 5:
                    cout << "\nTerima kasih, program selesai.\n";
                    break;
                default:
                    cout << "\nPilihan menu tidak valid!\n";
            }

        } while (pilihan != 5);
    }
};

int main() {
    Parkir p;

    if (p.login()) {
        p.menu();
    }

    return 0;
}
