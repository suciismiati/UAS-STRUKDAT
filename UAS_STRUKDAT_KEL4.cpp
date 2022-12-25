#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_PACKAGES 100

// Struktur data untuk menyimpan informasi paket
typedef struct {
  char nama_pengirim[100]; // Nama Pengirim paket
  char nama_penerima[100]; // Nama penerima paket
  char telp_penerima[100]; // Nomer Telp Penerima
  char resi[50]; // Nomor resi paket
  float berat; // Berat paket dalam kg
  char alamat[100]; // Alamat tujuan paket
} Package;

Package gudang[MAX_PACKAGES]; // Gudang untuk menyimpan paket
int awal = 0; // Indeks awal dari queue gudang
int akhir = -1; // Indeks akhir dari queue gudang
int brg;

// Fungsi untuk menambah paket ke gudang
void tambah_paket(Package paket) {
  // Pengecekan apakah sudah ada paket dengan nomor resi yang sama
  for (int i = awal; i <= akhir; i++) {
    if (strcmp(gudang[i].resi, paket.resi) == 0) {
      printf("Gagal menambah paket. Nomor resi %s sudah ada.\n", paket.resi);
      return;
    }
  }

  // Penambahan paket dengan susunan stack paling berat di bawah
  if (akhir < MAX_PACKAGES - 1) {
    akhir++;
    int i = akhir;
    while (i > awal && gudang[i-1].berat < paket.berat) {
      gudang[i] = gudang[i-1];
      i--;
    }
    gudang[i] = paket;
  } else {
    printf("Gudang penuh! Tidak dapat menambah paket lagi.\n");
  }
}

// Fungsi untuk mengeluarkan paket dari gudang
Package keluarkan_paket() {
  Package paket;
  if (awal <= akhir) {
    // Paket hanya dapat dikirim jika sudah di keluarkan dari gudang
    brg = 1;
    paket = gudang[awal];
    awal++;
    return paket;
  } else {
    printf("Gudang kosong! Tidak ada paket yang dapat dikirim.");
    brg = 0;
    return paket;
  }
}

// Fungsi untuk mencetak informasi paket
void cetak_paket(Package paket) {
printf("\xB2============== Paket No Resi - %s ==============\xB2\n", paket.resi); 
printf("Nama Pengirim: %s\n", paket.nama_pengirim);
printf("Nama Penerima: %s\n", paket.nama_penerima);
printf("Nomer Telp Penerima: %s\n", paket.telp_penerima);
printf("Nomor Resi: %s\n", paket.resi);
printf("Berat: %.2f kg\n", paket.berat);
printf("Alamat tujuan: %s\n", paket.alamat);
printf("\xB2=================================================\xB2\n\n"); 
}

// Fungsi untuk mengeluarkan paket dari gudang dengan prinsip stack
void keluarkan_paket_stack() {
  if (awal <= akhir) {
    int top = akhir;
    Package paket = gudang[top];
    akhir--;
    printf("Paket yang dikeluarkan:\n");
    cetak_paket(paket);
  } else {
    printf("Gudang kosong! Tidak ada paket yang dapat dikeluarkan.\n");
  }
}

void lihat_semua_paket_stack() {
	if (awal <= akhir) {
		printf("Seluruh paket di gudang (stack):\n");
		for (int i = akhir; i >= awal; i--){
		cetak_paket(gudang[i]);
		}
	} else {
		printf("Gudang kosong! Tidak ada paket yang dapat dilihat.\n");
	}
}

int main()
{
  int pilihan;
  printf("21081010003 - Volem Alvaro Azira\n");
  printf("20081010239 - Rifqi Alvian Ardhiansyah\n\n");
  

  do {
  	printf("        <( PROGRAM G4 LOGISTIC )>\n");
    printf("\n================( Menu )================\n");
    printf(" 1. Masukkan Paket Ke Gudang\n");
    printf(" 2. Kirim Paket (queue)\n");
    printf(" 3. Lihat Paket Teratas (stack)\n");
    printf(" 4. Lihat Semua Paket Di Gudang (stack)\n");
    printf(" 5. Keluar\n");
    printf("========================================\n");
    printf("Pilihan : ");
    scanf("%d", &pilihan);
    system("cls");

    switch (pilihan) {
      case 1: {
      	printf("Tidak Boleh Nomor Seri Yang Sudah Ada atau Sama.\n\n");
        Package paket;
	printf("Nama Pengirim: ");
        scanf("%s", paket.nama_pengirim);
        printf("Nama Penerima: ");
        scanf("%s", paket.nama_penerima);
        printf("Nomor Telp Penerima: ");
        scanf("%s", paket.telp_penerima);
        printf("Nomor Resi: ");
        scanf("%s", paket.resi);
        printf("Berat (kg): ");
        scanf("%f", &paket.berat);
        printf("Kota Tujuan: ");
        scanf("%s", paket.alamat);
        tambah_paket(paket);
        break;
      }
      case 2: {
      	printf("Paket Dikirim Sesuai Antrean!!\n\n");
        Package paket = keluarkan_paket();
        if (brg == 1){
        	printf("Paket yang dikirim:\n");
        	cetak_paket(paket);
		}
        break;
      }
      case 3: {
        Package paket = gudang[akhir];
        printf("Paket teratas:\n");
        cetak_paket(paket);
        break;
      }
      case 4: {
      	printf("Paket Paling Atas Teringan\n\n");
        lihat_semua_paket_stack();
        break;
      }
      case 5: {
      	printf("Terima kasih telah menggunakan program ini.\n");
        break;
      }
      default: {
        printf("Pilihan tidak valid. Silakan pilih menu yang tersedia.\n");
        break;
	  }
	}
	printf("\n\nTekan ENTER Untuk Lanjut...");
	getch();
	system("cls");	
	} while (pilihan != 5);
  	return 0;
}
