
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_PRODUK 50
#define PANJANG_NAMA 100

// Array untuk menyimpan data produk
char namaProduk[MAX_PRODUK][PANJANG_NAMA];
long long harga[MAX_PRODUK];
int stok[MAX_PRODUK];
int jumlahTerjual[MAX_PRODUK];

int jumlahProduk = 0;
long long totalPendapatan = 0;

// Fungsi membaca angka
long long bacaAngka(const char *pesan) {
    char buffer[100];
    char *akhir;
    long long nilai;

    while (1) {
        printf("%s", pesan);
        fgets(buffer, sizeof(buffer), stdin);

        nilai = strtoll(buffer, &akhir, 10);

        while (*akhir == ' ' || *akhir == '\t' ||
               *akhir == '\n' || *akhir == '\r') {
            akhir++;
        }

        if (akhir == buffer || *akhir != '\0') {
            printf("Input harus berupa angka!\n");
        } else {
            return nilai;
        }
    }
}

// Fungsi membaca nama produk
void bacaTeks(const char *pesan, char teks[], int ukuran) {
    while (1) {
        printf("%s", pesan);
        fgets(teks, ukuran, stdin);
        teks[strcspn(teks, "\n")] = '\0';

        if (strlen(teks) > 0) {
            return;
        }

        printf("Nama tidak boleh kosong!\n");
    }
}

// Data awal produk
void dataAwal() {
    strcpy(namaProduk[0], "Nasi Goreng");
    harga[0] = 12000;
    stok[0] = 15;
    jumlahTerjual[0] = 0;

    strcpy(namaProduk[1], "Mie Ayam");
    harga[1] = 10000;
    stok[1] = 12;
    jumlahTerjual[1] = 0;

    strcpy(namaProduk[2], "Es Teh");
    harga[2] = 4000;
    stok[2] = 25;
    jumlahTerjual[2] = 0;

    strcpy(namaProduk[3], "Roti Bakar");
    harga[3] = 8000;
    stok[3] = 10;
    jumlahTerjual[3] = 0;

    strcpy(namaProduk[4], "Air Mineral");
    harga[4] = 3000;
    stok[4] = 20;
    jumlahTerjual[4] = 0;

    jumlahProduk = 5;
}

// Menampilkan seluruh produk
void tampilkanProduk() {
    int i;

    printf("\n========== DAFTAR PRODUK ==========\n");
    printf("%-5s %-20s %-12s %-8s %-10s\n",
           "No", "Nama", "Harga", "Stok", "Terjual");

    for (i = 0; i < jumlahProduk; i++) {
        printf("%-5d %-20s %-12lld %-8d %-10d\n",
               i + 1, namaProduk[i], harga[i],
               stok[i], jumlahTerjual[i]);
    }
}

// Menambahkan produk
void tambahProduk() {
    long long h, s;

    if (jumlahProduk >= MAX_PRODUK) {
        printf("Kapasitas produk sudah penuh!\n");
        return;
    }

    bacaTeks("Nama produk: ",
             namaProduk[jumlahProduk], PANJANG_NAMA);

    h = bacaAngka("Harga produk: ");

    while (h < 0) {
        printf("Harga tidak boleh negatif!\n");
        h = bacaAngka("Harga produk: ");
    }

    s = bacaAngka("Jumlah stok: ");

    while (s < 0 || s > 2147483647LL) {
        printf("Stok tidak valid!\n");
        s = bacaAngka("Jumlah stok: ");
    }

    harga[jumlahProduk] = h;
    stok[jumlahProduk] = (int)s;
    jumlahTerjual[jumlahProduk] = 0;

    jumlahProduk++;

    printf("Produk berhasil ditambahkan!\n");
}

// Memilih produk
int pilihProduk() {
    long long nomor;

    tampilkanProduk();

    nomor = bacaAngka("Masukkan nomor produk: ");

    if (nomor < 1 || nomor > jumlahProduk) {
        printf("Produk tidak ditemukan!\n");
        return -1;
    }

    return (int)nomor - 1;
}

// Mengubah harga dan stok
void ubahProduk() {
    int i = pilihProduk();
    long long h, s;

    if (i == -1) return;

    h = bacaAngka("Masukkan harga baru: ");

    while (h < 0) {
        printf("Harga tidak boleh negatif!\n");
        h = bacaAngka("Masukkan harga baru: ");
    }

    s = bacaAngka("Masukkan stok baru: ");

    while (s < 0 || s > 2147483647LL) {
        printf("Stok tidak valid!\n");
        s = bacaAngka("Masukkan stok baru: ");
    }

    harga[i] = h;
    stok[i] = (int)s;

    printf("Data produk berhasil diubah!\n");
}

// Menambahkan stok
void tambahStok() {
    int i = pilihProduk();
    long long tambahan;

    if (i == -1) return;

    tambahan = bacaAngka("Jumlah stok tambahan: ");

    while (tambahan <= 0 ||
           tambahan > 2147483647LL - stok[i]) {
        printf("Jumlah stok tidak valid!\n");
        tambahan = bacaAngka("Jumlah stok tambahan: ");
    }

    stok[i] += (int)tambahan;

    printf("Stok berhasil ditambahkan!\n");
}

// Mencari produk
void cariProduk() {
    char kataKunci[100];
    char namaKecil[100], kunciKecil[100];
    int i, ditemukan = 0;
    size_t j;

    bacaTeks("Masukkan nama produk: ",
             kataKunci, sizeof(kataKunci));

    strcpy(kunciKecil, kataKunci);

    for (j = 0; kunciKecil[j]; j++)
        kunciKecil[j] = tolower((unsigned char)kunciKecil[j]);

    for (i = 0; i < jumlahProduk; i++) {
        strcpy(namaKecil, namaProduk[i]);

        for (j = 0; namaKecil[j]; j++)
            namaKecil[j] = tolower((unsigned char)namaKecil[j]);

        if (strstr(namaKecil, kunciKecil) != NULL) {
            printf("%s | Harga: Rp%lld | Stok: %d\n",
                   namaProduk[i], harga[i], stok[i]);
            ditemukan = 1;
        }
    }

    if (!ditemukan)
        printf("Produk tidak ditemukan!\n");
}

// Transaksi penjualan beberapa produk
void transaksiPenjualan() {
    int keranjang[MAX_PRODUK] = {0};
    int i, adaPembelian = 0;
    long long nomor, jumlah, total = 0;

    printf("\n===== TRANSAKSI PENJUALAN =====\n");
    printf("Masukkan 0 untuk menyelesaikan transaksi.\n");

    while (1) {
        tampilkanProduk();

        nomor = bacaAngka("Nomor produk (0 selesai): ");

        if (nomor == 0) break;

        if (nomor < 1 || nomor > jumlahProduk) {
            printf("Produk tidak ditemukan!\n");
            continue;
        }

        i = (int)nomor - 1;

        jumlah = bacaAngka("Jumlah pembelian: ");

        if (jumlah <= 0) {
            printf("Jumlah harus lebih dari 0!\n");
            continue;
        }

        if (jumlah > stok[i] - keranjang[i]) {
            printf("Stok tidak mencukupi!\n");
            continue;
        }

        keranjang[i] += (int)jumlah;
        adaPembelian = 1;

        printf("Produk berhasil dimasukkan ke keranjang!\n");
    }

    if (!adaPembelian) {
        printf("Transaksi dibatalkan!\n");
        return;
    }

    printf("\n======= RINCIAN TRANSAKSI =======\n");

    for (i = 0; i < jumlahProduk; i++) {
        if (keranjang[i] > 0) {
            long long subtotal = harga[i] * keranjang[i];

            printf("%s x %d = Rp%lld\n",
                   namaProduk[i], keranjang[i], subtotal);

            total += subtotal;
        }
    }

    printf("Total pembayaran: Rp%lld\n", total);

    if (bacaAngka("Konfirmasi? (1=Ya, 0=Tidak): ") != 1) {
        printf("Transaksi dibatalkan!\n");
        return;
    }

    for (i = 0; i < jumlahProduk; i++) {
        stok[i] -= keranjang[i];
        jumlahTerjual[i] += keranjang[i];
    }

    totalPendapatan += total;

    printf("Transaksi berhasil!\n");
}

// Laporan penjualan
void laporanPenjualan() {
    int i, totalUnit = 0;
    int terlaris = -1;

    printf("\n======= LAPORAN PENJUALAN =======\n");

    for (i = 0; i < jumlahProduk; i++) {
        printf("%s: %d terjual\n",
               namaProduk[i], jumlahTerjual[i]);

        totalUnit += jumlahTerjual[i];

        if (terlaris == -1 ||
            jumlahTerjual[i] > jumlahTerjual[terlaris]) {
            terlaris = i;
        }
    }

    printf("Total unit terjual: %d\n", totalUnit);
    printf("Total pendapatan: Rp%lld\n", totalPendapatan);

    if (totalUnit > 0 && terlaris != -1) {
        printf("Produk terlaris: %s (%d unit)\n",
               namaProduk[terlaris],
               jumlahTerjual[terlaris]);
    } else {
        printf("Belum ada penjualan.\n");
    }
}

// Menukar data produk saat pengurutan
void tukarProduk(int a, int b) {
    char namaSementara[100];
    long long hargaSementara;
    int stokSementara, terjualSementara;

    strcpy(namaSementara, namaProduk[a]);
    strcpy(namaProduk[a], namaProduk[b]);
    strcpy(namaProduk[b], namaSementara);

    hargaSementara = harga[a];
    harga[a] = harga[b];
    harga[b] = hargaSementara;

    stokSementara = stok[a];
    stok[a] = stok[b];
    stok[b] = stokSementara;

    terjualSementara = jumlahTerjual[a];
    jumlahTerjual[a] = jumlahTerjual[b];
    jumlahTerjual[b] = terjualSementara;
}

// Mengurutkan produk
void urutkanProduk() {
    int pilihan, i, j;

    printf("\n1. Harga termurah\n");
    printf("2. Penjualan terbanyak\n");

    pilihan = (int)bacaAngka("Pilih pengurutan: ");

    if (pilihan != 1 && pilihan != 2) {
        printf("Pilihan tidak tersedia!\n");
        return;
    }

    for (i = 0; i < jumlahProduk - 1; i++) {
        for (j = 0; j < jumlahProduk - i - 1; j++) {

            int tukar = (pilihan == 1)
                ? harga[j] > harga[j + 1]
                : jumlahTerjual[j] < jumlahTerjual[j + 1];

            if (tukar)
                tukarProduk(j, j + 1);
        }
    }

    printf("Produk berhasil diurutkan!\n");
    tampilkanProduk();
}

// Mengecek stok menipis
void cekStokMenipis() {
    int i, ditemukan = 0;

    printf("\n===== STOK MENIPIS =====\n");

    for (i = 0; i < jumlahProduk; i++) {
        if (stok[i] < 5) {
            printf("%s - Stok: %d\n",
                   namaProduk[i], stok[i]);
            ditemukan = 1;
        }
    }

    if (!ditemukan)
        printf("Tidak ada stok yang menipis.\n");
}

// Program utama
int main() {
    long long pilihan;

    dataAwal();

    do {
        printf("\n====================================\n");
        printf(" SISTEM MONITORING KANTIN KAMPUS\n");
        printf("====================================\n");
        printf("1. Lihat Daftar Produk\n");
        printf("2. Tambah Produk\n");
        printf("3. Ubah Produk\n");
        printf("4. Transaksi Penjualan\n");
        printf("5. Tambah Stok\n");
        printf("6. Cari Produk\n");
        printf("7. Urutkan Produk\n");
        printf("8. Laporan Penjualan\n");
        printf("9. Cek Stok Menipis\n");
        printf("0. Keluar\n");

        pilihan = bacaAngka("Pilih menu: ");

        switch (pilihan) {
            case 1:
                tampilkanProduk();
                break;

            case 2:
                tambahProduk();
                break;

            case 3:
                ubahProduk();
                break;

            case 4:
                transaksiPenjualan();
                break;

            case 5:
                tambahStok();
                break;

            case 6:
                cariProduk();
                break;

            case 7:
                urutkanProduk();
                break;

            case 8:
                laporanPenjualan();
                break;

            case 9:
                cekStokMenipis();
                break;

            case 0:
                printf("Program selesai. Terima kasih!\n");
                break;

            default:
                printf("Menu tidak tersedia!\n");
        }

    } while (pilihan != 0);

    return 0;
}
