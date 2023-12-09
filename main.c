// Saya [Ardyn Rezky Fahreza]
// NIM [2103551]
// mengerjakan soal TMD dalam mata kuliah Struktur Data
// untuk keberkahanNya maka saya tidak melakukan kecurangan seperti yang telah dispesifikasikan.
// Aamiin

#include "TMD.h"

int main()
{
    tree T;
    int i, j;        // variabel untuk loopinh
    int n;           // variabel untuk inputan pertama
    scanf("%d", &n); // inputan pertama

    char inputan[300][300]; // array inputan kedua

    // array - array untuk penampung inputan yg dipisah
    char inp1[300][300], inp2[300][300], inp3[300][300], inp4[300][300];
    // variabel untuk penampung inputan yg dipisah
    int bahan[300];
    int harga[300];

    // inisialisasi struct untuk bahan produk
    b utama;

    // variabel untuk penanda
    int count = 1;

    // looping sebanyak inputan
    for (i = 0; i < n; i++)
    {
        // pointer untuk root awal
        simpul *nodeRoot;
        // inputan kedua
        scanf("%s", inputan[i]);

        // variabel menampung panjang inputan
        int len;
        len = strlen(inputan[i]);
        int flag = 0; // variabel untuk penanda
        int x = 0;    // inisialisasi menjadi 0

        // proses untuk memisahkan inputan
        for (j = 0; j < len; j++)
        {
            if (inputan[i][j] != '#')
            {
                if (flag == 0)
                {
                    inp1[i][x] = inputan[i][j]; // inputan pertama
                }
                else if (flag == 1)
                {
                    inp2[i][x] = inputan[i][j]; // inputan kedua
                }
                else if (flag == 2)
                {
                    inp3[i][x] = inputan[i][j]; // inputan ketiga
                }
                else if (flag == 3)
                {
                    inp4[i][x] = inputan[i][j]; // inputan keempat
                }
                x++;
            }
            else if (inputan[i][j] == '#')
            {
                flag++;
                x = 0;
            }
        }

        // proses untuk mengubah inp4 dari (string) ke (integer)
        len = 0;
        len = strlen(inp4[i]);
        for (j = 0; j < len; j++)
        {
            bahan[i] = bahan[i] * 10 + (inp4[i][j] - '0');
        }

        // proses untuk mengubah inp3 dari (string) ke (integer)
        len = 0;
        len = strlen(inp3[i]);
        for (j = 0; j < len; j++)
        {
            harga[i] = harga[i] * 10 + (inp3[i][j] - '0');
        }

        // array untuk inputan ketiga
        char ingredients[300][300];
        // inputan
        for (j = 0; j < bahan[i]; j++)
        {
            scanf("%s", utama.ing[j]);
        }

        // proses untuk membuat tree
        if (strcmp(inp2[i], "null") == 0)
        {
            makeTree(inp1[i], inp2[i], inp3[i], harga[i], utama, bahan[i], &T);
        }
        else
        {
            if (count == 1)
            {
                nodeRoot = T.root;
            }
            else
            {
                nodeRoot = findSimpul(inp2[i], T.root);
            }

            addChild(inp1[i], inp2[i], inp3[i], harga[i], utama, bahan[i], nodeRoot);
        }
        count++;
    }
    // variabel dan inputan keempat
    int del;
    scanf("%d", &del);

    // inisisalisasi nilai biggest
    for (i = 0; i < 300; i++)
    {
        biggest[i] = -1;
    }
    // inisialisasi nilai z
    z = -1;

    // memanggil void checkPanjang
    checkPanjang(T.root, 0);

    // menambahkan nilai biggest dengan nilai sebelumnya
    for (i = 0; i < z; i++)
    {
        biggest[i] = biggest[i] + biggest[i - 1];
    }

    // output pertama
    printTreePreOrder(T.root, 0);

    // proses menghapus simpul yang tidak memenuhi harga jual
    for (i = 0; i < n; i++)
    {
        if (harga[i] < del)
        {
            simpul *del = findSimpul(inp1[i], T.root);
            simpul *ortu = findSimpul(inp2[i], T.root);
            delChild(del, ortu);
        }
    }

    // memanggil void checkPanjang
    checkPanjang(T.root, 0);
    // output kedua
    printf("\n");
    printTreePreOrder(T.root, 0);

    return 0;
}