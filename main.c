#include "convention.h"
#include "kota.h"
#include "linked.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kota *pickWhichKota(kota k[], int kotaCount);
void addOrang(kota k[], int *kotaCount);
void addKota(kota k[], int *kotaCount);
void printAllkota(kota k[], int *kotaCount);
void deleteKota(kota k[], int *kotaCount);
void deleteOrang(kota k[], int *kotaCount);
void exitApp(kota k[], int *kotaCount);
void printMenu();
address pickWhichOrang(kota k);
void clearTerminal();

int main() {
  int n = 10, kotaCount = 0;
  kota k[n];
  bool isRunning = true;
  void (*tab[])(kota k[], int *kotaCount) = {
      addKota, addOrang, deleteKota, deleteOrang, printAllkota, exitApp};
  while (isRunning) {
    printMenu();
    int a;
    printf("\nPilih menu: ");
    scanf("%d", &a);
    tab[a - 1](k, &kotaCount);
  }
  return 0;
}
address pickWhichOrang(kota k) {

  clearTerminal();
  Tampil_List(k.p);
  int count = NbElmt(k.p);
  printf("Pilih orang yang mana? (1-%d)", count);
  int a;
  scanf("%d", &a);
  address b = k.p;
  for (int i = 1; i < a; i++) {
    b = (*b).next;
  }
  return b;
}

kota *pickWhichKota(kota k[], int kotaCount) {

  clearTerminal();
  for (int i = 0; i < kotaCount; i++) {
    printf("%d. %s\n", i + 1, k[i].kt);
  }
  printf("\nPilih kota yang mana? (1-%d): ", kotaCount);
  int a;
  scanf("%d", &a);
  return &k[a - 1];
}

void deleteOrang(kota k[], int *kotaCount) {

  clearTerminal();
  kota *kt = pickWhichKota(k, *kotaCount);
  infotype X;
  deleteByAddress(&(kt->p), pickWhichOrang(*kt), &X);
}

void addKota(kota k[], int *kotaCount) {
  clearTerminal();
  char kt[MAX_STRING_LENGTH];
  printf("Nama kota (Maksimal 100 char): ");
  scanf("%s", kt);
  strcpy(k[*kotaCount].kt, kt);
  createList(&(k[*kotaCount].p));
  *kotaCount += 1;
}

void deleteKota(kota k[], int *kotaCount) {

  clearTerminal();
  kota *kt = pickWhichKota(k, *kotaCount);
  int deleted = -1;
  for (int i = 0; i < *kotaCount; i++) {
    if (k[i].kt == kt->kt) {
      DeAlokasi(&(k[i].p));
      strcpy(k[i].kt, "");
      deleted = i;
    }
  }
  if (deleted != -1) {
    for (int i = deleted + 1; i < *kotaCount; i++) {
      strcpy(k[i - 1].kt, k[i].kt);
      k[i - 1].p = k[i].p;
      strcpy(k[i].kt, "");
      k[i].p = NULL;
    }
    *kotaCount -= 1;
  }
}

void addOrang(kota k[], int *kotaCount) {
  clearTerminal();
  address newNode;
  // for (int i = 0; i < kotaCount; i++) {
  //   printf("%d. %s\n", i + 1, k[i].kt);
  // }
  kota *selected = pickWhichKota(k, *kotaCount);
  // printf("%d, %d", selected, q[0]);
  char orang[MAX_STRING_LENGTH];
  printf("Nama orang (Max 100 chars): ");
  scanf("%s", orang);
  Create_Node(&newNode);
  Isi_Node_Str(&newNode, orang);
  Ins_Akhir(&(*selected).p, newNode);
}

void printAllkota(kota k[], int *kotaCount) {
  bool isRunning = true;
  while (isRunning) {
    clearTerminal();
    int sumOrang = 0;
    for (int i = 0; i < *kotaCount; i++) {
      sumOrang += NbElmt(k[i].p);
      printf("%d. %s (Jml orang %d): ", i + 1, k[i].kt, NbElmt(k[i].p));
      Tampil_List(k[i].p);
    }
    printf("Jumlah orang semua: %d\nJumlah kota: %d\n", sumOrang, *kotaCount);
    char a;
    printf("\nInput q untuk keluar... \n");
    getchar();
    scanf("%c", &a);
    if (a == 'q') {
      isRunning = false;
    }
  }
}
void exitApp(kota k[], int *kotaCount) {
  clearTerminal();
  for (int i = 0; i < *kotaCount; i++) {
    DeAlokasi(&k[i].p);
  }
  exit(0);
}
void clearTerminal() { system("clear"); }
void printMenu() {
  clearTerminal();
  printf("[APLIKASI KOTA DAN WARGA]\n");
  printf("(Maksimal 10 kota)\n");
  printf("1. Tambah kota\n");
  printf("2. Tambah orang\n");
  printf("3. Delete kota\n");
  printf("4. Delete orang\n");
  printf("5. Cetak data (kota dan orang2 nya, sama jumlah kota dan orang)\n");
  printf("6. Exit Aplikasi\n");
}
