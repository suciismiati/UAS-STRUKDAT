#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#define RESI_LEN 10

// Struktur data untuk menyimpan informasi paket
typedef struct {
  char nama_pengirim[100]; // Nama Pengirim paket
  char nama_penerima[100]; // Nama penerima paket
  char telp_penerima[100]; // Nomer Telp Penerima
  char resi[50]; // Nomor resi paket
  float berat; // Berat paket dalam kg
  char alamat[100]; // Alamat tujuan paket
} Package;

typedef struct package_node {
  Package paket;
  struct package_node *next;
} PackageNode;

typedef struct {
  PackageNode *top;
  int count;  // jumlah paket di dalam stack
  int max_size;  // maksimal tumpukan yang diinginkan
} PackageStack;

typedef struct {
  PackageNode *front;
  PackageNode *rear;
} PackageQueue;

PackageQueue* create_queue() {
   PackageQueue *queue = (PackageQueue*) malloc(sizeof(PackageQueue));
  queue->front = NULL;
  queue->rear = NULL;
  return queue;
}

int is_empty(PackageQueue *queue) {
  return queue->front == NULL;
}

PackageStack* create_stack(int max_size) {
  PackageStack *stack = (PackageStack*) malloc(sizeof(PackageStack));
  stack->top = NULL;
  stack->count = 0;
  stack->max_size = max_size;
  return stack;
}

int is_empty(PackageStack *stack) {
  return stack->top == NULL;
}

int is_full(PackageStack *stack) {
  return stack->count == stack->max_size;
}

void push(PackageStack *stack, Package paket) {
  if (is_full(stack)) {
    printf("Gudang sudah penuh!\n");
  } else {
    PackageNode *node = (PackageNode*) malloc(sizeof(PackageNode));
    node->paket = paket;
    node->next = stack->top;
    stack->top = node;
    stack->count++;
    
     // Menyortir paket di dalam stack menurut beratnya
    PackageNode *curr = stack->top;
    while (curr->next != NULL) {
      if (curr->paket.berat > curr->next->paket.berat) {
        // Menukar elemen saat terdeteksi paket yang lebih ringan
        Package temp = curr->paket;
        curr->paket = curr->next->paket;
        curr->next->paket = temp;
      }
      curr = curr->next;
    }
  }
}

Package pop(PackageStack *stack) {
	  if (is_empty(stack)) {
	    printf("Gudang kosong!\n");
	  } else {
	    PackageNode *node = stack->top;
	    Package paket = node->paket;
	stack->top = node->next;
	free(node);
	stack->count--;
	return paket;
	}
}

Package peek(PackageStack *stack) {
	if (is_empty(stack)) {
	printf("Gudang kosong!\n");
	} 	else {
	return stack->top->paket;
	}
}

char* generate_resi() {
  static char resi[RESI_LEN + 1];  // membuat array char statis untuk menyimpan nilai resi

  srand(time(NULL));  // menginisialisasi generator bilangan acak dengan waktu saat ini

  // mengenerate karakter acak untuk string resi
  for (int i = 0; i < RESI_LEN; i++) {
    // mengenerate bilangan acak atau huruf
    if (rand() % 2 == 0) {
      resi[i] = '0' + rand() % 10;  // mengenerate bilangan acak
    } else {
      resi[i] = 'A' + rand() % 26;  // mengenerate huruf acak
    }
  }
  resi[RESI_LEN] = '\0';  // menandai akhir dari string resi dengan karakter '\0'

  return resi;  // mengembalikan string resi yang telah dihasilkan
}

void enqueue(PackageQueue *queue, PackageStack *stack) {
  if (is_empty(stack)) {
    printf("gudang kosong! Tidak dapat menambahkan paket ke dalam antrian.\n");
  } else {
    Package paket = pop(stack);  // mengambil paket di puncak stack

    PackageNode *node = (PackageNode*) malloc(sizeof(PackageNode));
    node->paket = paket;
    node->next = NULL;

    if (is_empty(queue)) {
      queue->front = node;
      queue->rear = node;
    } else {
      queue->rear->next = node;
      queue->rear = node;
    }
    printf("Paket masuk ke antrian untuk dikirim:\n");
    printf("Nama pengirim: %s\n", paket.nama_pengirim);
    printf("Nama penerima: %s\n", paket.nama_penerima);
    printf("Nomor telepon penerima: %s\n", paket.telp_penerima);
    printf("Nomor resi: %s\n", paket.resi);
    printf("Berat paket: %.2f kg\n", paket.berat);
    printf("Alamat tujuan: %s\n", paket.alamat);
  }
}

Package dequeue(PackageQueue *queue) {
   if (is_empty(queue)) {
    printf("tidak ada antrian! Tidak ada paket yang bisa dikirim.\n");
    // Kembalikan paket kosong jika queue kosong
    Package paket;
    return paket;
  } else {
    PackageNode *node = queue->front;
    Package paket = node->paket;
    queue->front = queue->front->next;
    free(node);
    return paket;
  }
}

 void keluarkan_paket(PackageQueue *queue) {
  Package paket = dequeue(queue);
  if (strlen(paket.resi) > 0) {  // Periksa apakah paket kosong
    printf("\xB2============= Paket Yang Terkirim ===============\xB2\n");
    printf("Nama pengirim: %s\n", paket.nama_pengirim);
    printf("Nama penerima: %s\n", paket.nama_penerima);
    printf("Nomor telepon penerima: %s\n", paket.telp_penerima);
    printf("Nomor resi: %s\n", paket.resi);
    printf("Berat paket: %.2f kg\n", paket.berat);
    printf("Alamat tujuan: %s\n", paket.alamat);
    printf("\xB2=================================================\xB2\n\n"); 
  } else {
  }
}

void cetak_paket(PackageStack *stack) {
  if (is_empty(stack)) {
    printf("Tidak ada paket yang dapat dicetak.\n");
  } else {
    Package paket = peek(stack);  // mengakses paket di puncak stack
    printf("\xB2============== Paket No Resi - %s ==============\xB2\n", paket.resi); 
	printf("Nama Pengirim: %s\n", paket.nama_pengirim);
	printf("Nama Penerima: %s\n", paket.nama_penerima);
	printf("Nomer Telp Penerima: %s\n", paket.telp_penerima);
	printf("Nomor Resi: %s\n", paket.resi);
	printf("Berat: %.2f kg\n", paket.berat);
	printf("Alamat tujuan: %s\n", paket.alamat);
	printf("\xB2=================================================\xB2\n\n"); 
  }
}
void lihat_semua_paket(PackageStack *stack) {
  if (is_empty(stack)) {
    printf("Stack kosong! Tidak ada paket yang bisa ditampilkan.\n");
  } else {
    printf("Paket di dalam stack:\n");
    PackageNode *curr = stack->top;
    while (curr != NULL) {
      Package paket = curr->paket;
      printf("\xB2============== Paket No Resi - %s ==============\xB2\n", paket.resi); 
      printf("Nama Pengirim: %s\n", paket.nama_pengirim);
      printf("Nama Penerima: %s\n", paket.nama_penerima);
      printf("Nomor Telepon Penerima: %s\n", paket.telp_penerima);
      printf("Nomor Resi: %s\n", paket.resi);
      printf("Berat Paket: %.2f kg\n", paket.berat);
      printf("Alamat Tujuan: %s\n", paket.alamat);
      printf("\xB2=================================================\xB2\n\n"); 
      curr = curr->next;
    }
  }
}

int main()
{
  int pilihan;
  printf("21081010003 - Volem Alvaro Azira\n");
  printf("20081010239 - Rifqi Alvian Ardhiansyah\n");
  printf("20081010167 - Candra Kusuma Muhammad Bimantara\n");
  printf("20081018261 - Ali Muhammad Saleh Baaboud\n");
  printf("20081010162 - Suci Ismiati\n\n");
  
  PackageQueue *queue = create_queue();
  int max_size = 20; 
  PackageStack *stack = create_stack(max_size); // membuat stack baru
  
  do {
  	printf("        <( PROGRAM G4 LOGISTIC )>\n");
    printf("\n================( Menu )================\n");
    printf(" 1. Masukkan Paket Ke Gudang\n");
    printf(" 2. Masukkan Paket Keantrian\n");
    printf(" 3. Kirim Paket \n");
    printf(" 4. Lihat Paket Teratas (stack)\n");
    printf(" 5. Lihat Semua Paket Di Gudang (stack)\n");
    printf(" 6. Keluar\n");
    printf("========================================\n");
    printf("Pilihan : ");
    scanf("%d", &pilihan);
    system("cls");

    switch (pilihan) {
      case 1: {
        Package paket;
        printf("\xB2============== Data Paket ==============\xB2\n"); 
	printf("  Nama Pengirim: ");
        scanf("%s", paket.nama_pengirim);
        printf("  Nama Penerima: ");
        scanf("%s", paket.nama_penerima);
        printf("  Nomor Telp Penerima: ");
        scanf("%s", paket.telp_penerima);
        printf("  Berat (kg): ");
        scanf("%f", &paket.berat);
        printf("  Kota Tujuan: ");
        scanf("%s", paket.alamat);
        printf("\xB2========================================\xB2\n");
        strcpy(paket.resi, generate_resi());
        push(stack, paket);;
        break;
      }
      case 2: {
      	enqueue(queue, stack);
        break;
      }
      case 3: {
       keluarkan_paket(queue);
       break;
      }
      case 4: {
    	 printf("Paket teratas:\n");
     	 cetak_paket(stack);
      break;
      }
     case 5: {
     	lihat_semua_paket(stack);
        break;
      }
     case 6: {
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
	} while (pilihan != 6);
  	return 0;
}
