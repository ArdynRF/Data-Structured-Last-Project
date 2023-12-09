// Saya [Ardyn Rezky Fahreza]
// NIM [2103551]
// mengerjakan soal TMD dalam mata kuliah Struktur Data
// untuk keberkahanNya maka saya tidak melakukan kecurangan seperti yang telah dispesifikasikan.
// Aamiin

#include "TMD.h"

int biggest[999];
int z;

/* Prosedur Membuat Tree */
void makeTree(char nama[], char o[], char p[], int prc, b nood, int bahan, tree *T)
{
    // membuat node
    simpul *node;
    node = (simpul *)malloc(sizeof(simpul));
    // mengisi data
    strcpy(node->nama, nama);
    strcpy(node->ortu, o);
    strcpy(node->price, p);
    node->harga = prc;
    node->n = bahan;
    node->mie = nood;
    // membuat pointer anak dan saudara
    node->sibling = NULL;
    node->child = NULL;
    // memasang node ke root
    (*T).root = node;
}

/* Prosedur Menambah Child */
void addChild(char nama[], char o[], char p[], int prc, b nood, int bahan, simpul *root)
{
    if (root != NULL)
    {
        /* jika simpul root tidak kosong,
        berarti dapat ditambahkan simpul anak */
        simpul *baru;
        baru = (simpul *)malloc(sizeof(simpul));
        strcpy(baru->nama, nama);
        strcpy(baru->ortu, o);
        strcpy(baru->price, p);
        baru->harga = prc;
        baru->n = bahan;
        baru->mie = nood;
        baru->child = NULL;

        if (root->child == NULL)
        {
            /* jika simpul root belum memiliki simpul
            anak maka simpul baru menjadi anak pertama */
            baru->sibling = NULL;
            root->child = baru;
        }
        else
        {
            if (root->child->sibling == NULL)
            {
                /* jika simpul root memiliki anak yang belum
                memiliki saudara, maka simpul baru menjadi anak kedua */
                baru->sibling = root->child;
                root->child->sibling = baru;
            }
            else
            {
                simpul *last = root->child;
                /* mencari simpul anak terakhir karena akan
                dikaitkan dengan simpul baru sebagai simpul
                anak terakhir yang baru, simpul anak terakhir
                adalah yang memiliki sibling simpul anak pertama,
                maka selama belum sampai pada simpul anak terakhir,
                penunjuk last akan berjalan ke simpul anak berikutnya */
                while (last->sibling != root->child)
                {
                    last = last->sibling;
                }
                baru->sibling = root->child;
                last->sibling = baru;
            }
        }
    }
}

/* Prosedur Menghapus Seluruh Anak */
void delAll(simpul **root)
{
    if ((*root) != NULL)
    {
        /* jika simpul root tidak kosong */
        if ((*root)->child != NULL)
        {
            if ((*root)->child->sibling == NULL)
            {
                /* jika hanya memiliki satu simpul anak */
                delAll(&(*root)->child);
            }
            else
            {
                simpul *bantu;
                simpul *proses;
                bantu = (*root)->child;
                while (bantu->sibling != (*root)->child)
                {
                    proses = bantu;
                    bantu = bantu->sibling;
                    delAll(&proses);
                }
                delAll(&bantu);
            }
            free((*root)->child);
            (*root)->child = NULL;
        }
        free(*root);
        *root = NULL;
    }
}

/* Prosedur Menghapus Anak */
void delChild(simpul *del, simpul *root)
{
    if (root != NULL)
    {
        simpul *hapus = root->child;
        if (hapus != NULL)
        {
            if (hapus->sibling == NULL)
            {
                /*jika hanya mempunyai satu anak*/
                if ((root->child == del))
                {
                    delAll(&root->child);
                    root->child = NULL;
                }
                else
                {
                    printf("tidak ada simpul anak dengan kontainer karakter masukan\n");
                }
            }
            else
            {
                /*jika memiliki lebih dari satu simpul anak*/
                simpul *prev = NULL;
                /*mencari simpul yang akan dihapus*/
                int ketemu = 0;
                while ((hapus->sibling != root->child) && (ketemu == 0))
                {
                    if (hapus == del)
                    {
                        ketemu = 1;
                    }
                    else
                    {
                        prev = hapus;
                        hapus = hapus->sibling;
                    }
                }
                /* memproses simpul anak terakhir karena
                belum terproses dalam pengulangan */
                if ((ketemu == 0) && (hapus == del))
                {
                    ketemu = 1;
                }
                if (ketemu == 1)
                {
                    simpul *last = root->child;
                    /* mencari simpul anak terakhir untuk
                    membantu proses atau pemeriksaan jika yang
                    dihapus nantinya anak terakhir */
                    while (last->sibling != root->child)
                    {
                        last = last->sibling;
                    }
                    if (prev == NULL)
                    {
                        /*jika simpul yang dihapus anak pertama*/
                        if ((hapus->sibling == last) && (last->sibling == root->child))
                        {
                            /*jika hanya ada dua anak*/
                            root->child = last;
                            last->sibling = NULL;
                        }
                        else
                        {
                            /* jika memiliki simpul anak lebih dari dua simpul */
                            root->child = hapus->sibling;
                            last->sibling = root->child;
                        }
                    }
                    else
                    {
                        if ((prev == root->child) && (last == hapus))
                        {
                            /* jika hanya ada dua simpul anak dan
                            yang dihapus adalah simpul anak kedua */
                            root->child->sibling = NULL;
                        }
                        else
                        {
                            /* jika yang dihapus bukan simpul anak
                            pertama dan simpul root memiliki simpul
                            anak lebih dari dua simpul */
                            prev->sibling = hapus->sibling;
                            hapus->sibling = NULL;
                        }
                    }
                    delAll(&hapus);
                }
                else
                {
                    printf("tidak ada simpul anak dengan kontainer karakter masukan\n");
                }
            }
        }
    }
}

/* Prosedur Mencari Node */
simpul *findSimpul(char cari[], simpul *root)
{
    simpul *hasil = NULL;
    if (root != NULL)
    {
        if ((strcmp(root->nama, cari) == 0))
        {
            hasil = root;
        }
        else
        {
            simpul *bantu = root->child;
            if (bantu != NULL)
            {
                if (bantu->sibling == NULL)
                {
                    /*jika memiliki satu simpul anak*/
                    if ((strcmp(bantu->nama, cari) == 0))
                    {
                        hasil = bantu;
                    }
                    else
                    {
                        hasil = findSimpul(cari, bantu);
                    }
                }
                else
                {
                    /*jika memiliki banyak simpul anak*/
                    int ketemu = 0;
                    while ((bantu->sibling != root->child) && (ketemu == 0))
                    {
                        if ((strcmp(bantu->nama, cari) == 0))
                        {
                            hasil = bantu;
                            ketemu = 1;
                        }
                        else
                        {
                            hasil = findSimpul(cari, bantu);
                            bantu = bantu->sibling;
                            if (hasil != 0)
                            {
                                ketemu = 1;
                            }
                        }
                    }
                    /*memproses simpul anak terakhir karena belum
                    terproses dalam pengulangan*/
                    if (ketemu == 0)
                    {
                        if ((strcmp(bantu->nama, cari) == 0))
                        {
                            hasil = bantu;
                        }
                        else
                        {
                            hasil = findSimpul(cari, bantu);
                        }
                    }
                }
            }
        }
    }
    return hasil;
}

/* Prosedur Mencetak Node */
void printTreePreOrder(simpul *root, int n)
{
    if (root != NULL)
    {
        // mencetak spasi sesuai tingkatan
        if (n > 0)
        {
            printf("\n");
            for (int i = 0; i < biggest[n - 1]; i++)
            {
                printf(" ");
            }
            printf("|%s - %d", root->nama, root->harga);
        }
        else
        {
            printf("|%s - %d\n", root->nama, root->harga);
        }

        for (int i = 0; i < root->n; i++)
        {
            if (n > 0)
            {
                printf("\n");
                for (int j = 0; j < biggest[n - 1]; j++)
                {
                    printf(" ");
                }
                printf(" - %s", root->mie.ing[i]);

                if (i == root->n - 1)
                {
                    printf("\n");
                }
            }
            else
            {
                printf(" - %s\n", root->mie.ing[i]);
            }
        }

        simpul *bantu = root->child;
        if (bantu != NULL)
        {
            if (bantu->sibling == NULL)
            {
                /* jika memiliki satu simpul anak */
                printTreePreOrder(bantu, ++n);
                --n;
            }
            else
            {
                /* jika memiliki banyak simpul anak */
                /* mencetak simpul anak */
                while (bantu->sibling != root->child)
                {
                    printTreePreOrder(bantu, ++n);
                    --n;
                    bantu = bantu->sibling;
                }
                /* memproses simpul anak terakhir karena belum
                terproses dalam pengulangan */
                printTreePreOrder(bantu, ++n);
                --n;
            }
        }
    }
    else
    {
        printf("Kosong\n");
    }
}

void printTreePostOrder(simpul *root, simpul *almtRoot)
{
    if (root != NULL)
    {
        simpul *bantu = root->child;
        if (bantu != NULL)
        {
            if (bantu->sibling == NULL)
            {
                /*jika memiliki satu simpul anak*/
                printTreePostOrder(bantu, almtRoot);
            }
            else
            {
                /*jika memiliki banyak simpul anak*/
                /*mencetak simpul anak*/
                while (bantu->sibling != root->child)
                {
                    printTreePostOrder(bantu, almtRoot);
                    bantu = bantu->sibling;
                }
                /*memproses simpul anak terakhir karena
                belum terproses dalam pengulangan*/
                printTreePostOrder(bantu, almtRoot);
            }
        }
        printf("%s", root->nama);
        if (root != almtRoot)
        {
            // jika bukan elemen root utama
            printf("-");
        }
    }
    else
    {
        printf("Kosong\n");
    }
}

void copyTree(simpul *root1, simpul **root2)
{
    if (root1 != NULL)
    {
        (*root2) = (simpul *)malloc(sizeof(simpul));
        strcpy((*root2)->nama, root1->nama);
        (*root2)->sibling = NULL;
        (*root2)->child = NULL;
        if (root1->child != NULL)
        {
            if (root1->child->sibling == NULL)
            {
                /*jika memiliki satu simpul anak*/
                copyTree(root1->child, &(*root2)->child);
            }
            else
            {
                /*jika memiliki banyak simpul anak*/
                simpul *bantu1 = root1->child;
                simpul *bantu2 = (*root2)->child;
                while (bantu1->sibling != root1->child)
                {
                    copyTree(bantu1, &bantu2);
                    bantu1 = bantu1->sibling;
                    bantu2 = bantu2->sibling;
                }
                /*memproses simpul anak terakhir karena
                belum terproses dalam pengulangan*/
                copyTree(bantu1, &bantu2);
            }
        }
    }
}

int isEqual(simpul *root1, simpul *root2)
{
    int hasil = 1;
    if ((root1 != NULL) && (root2 != NULL))
    {
        if ((strcmp(root1->nama, root2->nama) != 0))
        {
            hasil = 0;
        }
        else
        {
            if ((root1->child != NULL) && (root2->child != NULL))
            {
                if (root1->child->sibling == NULL)
                {
                    /*jika memiliki satu simpul anak*/
                    hasil = isEqual(root1->child, root2->child);
                }
                else
                {
                    /*jika memiliki banyak simpul anak*/
                    simpul *bantu1 = root1->child;
                    simpul *bantu2 = root2->child;
                    while (bantu1->sibling != root1->child)
                    {
                        if ((bantu1 != NULL) && (bantu2 != NULL))
                        {
                            hasil = isEqual(bantu1, bantu2);
                            bantu1 = bantu1->sibling;
                            bantu2 = bantu2->sibling;
                        }
                        else
                        {
                            hasil = 0;
                            break;
                        }
                    }
                    /*memproses simpul anak terakhir karena belum terproses dalam pengulangan*/
                    hasil = isEqual(bantu1, bantu2);
                }
            }
        }
    }
    else
    {
        if ((root1 != NULL) || (root2 != NULL))
        {
            hasil = 0;
        }
    }
    return hasil;
}

// void untuk mengecek nilai terpanjang di setiap tingkat
void checkPanjang(simpul *root, int n)
{
    if (root != NULL)
    {
        // menampung nilai panjang inputan pertama
        int len;
        len = strlen(root->nama) + strlen(root->price) + 5;
        if (len > biggest[n])
        {
            biggest[n] = len;
        }
        // proses mencari nilai terpanjang di setiap tingkatan
        for (int i = 0; i < root->n; i++)
        {
            len = strlen(root->mie.ing[i]) + 4;
            if (len > biggest[n])
            {
                biggest[n] = len;
            }
        }
        // mengambil nilai tingkat tertinggi/terakhir
        if (n > z)
        {
            z = n;
        }

        simpul *bantu = root->child;
        if (bantu != NULL)
        {
            if (bantu->sibling == NULL)
            {
                /* jika memiliki satu simpul anak */
                checkPanjang(bantu, ++n);
                --n;
            }
            else
            {
                /* jika memiliki banyak simpul anak */
                /* mencetak simpul anak */
                while (bantu->sibling != root->child)
                {
                    checkPanjang(bantu, ++n);
                    --n;
                    bantu = bantu->sibling;
                }
                /* memproses simpul anak terakhir karena belum
                terproses dalam pengulangan */
                checkPanjang(bantu, ++n);
                --n;
            }
        }
    }
    else
    {
        printf("Kosong\n");
    }
}
