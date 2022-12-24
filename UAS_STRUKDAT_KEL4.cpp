#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_PACKAGES 100

// Struktur data untuk menyimpan informasi paket
typedef struct {
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
printf("Nomor resi: %s\n", paket.resi);
printf("Berat: %.2f kg\n", paket.berat);
printf("Alamat tujuan: %s\n", paket.alamat);
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
  printf("21081010003 - VOLEM ALVARO AZIRA\n\n");
  

  do {
  	printf("        <( PROGRAM G4 LOGISTIC )>\n");
    printf("\n================( Menu )================\n");
    printf(" 1. Masukkan paket ke gudang\n");
    printf(" 2. Kirim paket (queue)\n");
    printf(" 3. Lihat paket teratas (stack)\n");
    printf(" 4. Lihat semua paket di gudang (stack)\n");
    printf(" 5. Keluar\n");
    printf("========================================\n");
    printf("Pilihan : ");
    scanf("%d", &pilihan);
    system("cls");

    switch (pilihan) {
      case 1: {
      	printf("Tidak Boleh Nomor Seri Yang Sudah Ada atau Sama.\n\n");
        Package paket;
        printf("Nomor resi: ");
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
