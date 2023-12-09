// Saya [Ardyn Rezky Fahreza]
// NIM [2103551]
// mengerjakan soal TMD dalam mata kuliah Struktur Data
// untuk keberkahanNya maka saya tidak melakukan kecurangan seperti yang telah dispesifikasikan.
// Aamiin

#include <stdio.h>
#include <malloc.h>
#include <string.h>

// alamat simpul/node
typedef struct smp *alamatsimpul;

// bahan produk
typedef struct
{
    char ing[300][300];
} b;

// simpul/node
typedef struct smp
{
    char nama[300];       // data dlm simpul untuk nama produk
    char ortu[300];       // data dlm simpul untuk root produk
    int harga;            // data dlm simpul untuk harga produk(integer)
    char price[300];      // data dlm simpul untuk harga produk(string)
    int n;                // data dlm simpul untuk banyaknya bahan produk
    b mie;                // penampung bahan produk
    alamatsimpul sibling; // penunjuk saudara
    alamatsimpul child;   // penunjuk anak
} simpul;

// tree
typedef struct
{
    simpul *root;
} tree;

// variabel global
extern int biggest[999]; // array penampung string terpanjang
extern int z;            // banyaknya array biggest

// Prosedur dan Fungsi

void makeTree(char nama[], char o[], char p[], int prc, b nood, int bahan, tree *T);      // membuat tree
void addChild(char nama[], char o[], char p[], int prc, b nood, int bahan, simpul *root); // menambah anak
void delAll(simpul **root);                                                               // menghapus seluruh tree
void delChild(simpul *del, simpul *root);                                                 // menghapus anak
simpul *findSimpul(char cari[], simpul *root);                                            // mencari node
void printTreePreOrder(simpul *root, int n);                                              // mencetak node
void printTreePostOrder(simpul *root, simpul *almtRoot);                                  // mencetak node
void copyTree(simpul *root1, simpul **root2);                                             // menyalin tree
int isEqual(simpul *root1, simpul *root2);                                                // mengecek kesamaan dua buah tree
void checkPanjang(simpul *root, int n);                                                   // mengecek string terpanjang dari setiap tingkatan