#include <stdio.h>
#include <string.h>
#include "header.h"

int search(int banyakBarang,int id);
void laporan(int banyakBarang);

int main(int argc, char const *argv[])
{
    int id;
    int index;
    char lanjut;

    int modal;
    int keuntungan;
    label : 
    interface();
    int pilihan = option();
    while(1){
        int banyakBarang = readMaster();
        switch(pilihan){
            case 1 :
                system("cls");
                interface();
                masterBarang();
                break;
            case 2 :
                system("cls");
                interface();
                printf("\t\t  ITEM LIST\n");
                line();
                printf( "%-6s%-16s%-11s%10s\n", "Id", "Name", "Price", "Stock" );
                for(int i=0; i<banyakBarang;i++){
                    printf( "%-6d%-16s%-11llu%10.llu\n", listBarang[i].id, listBarang[i].namaBarang, listBarang[i].hargajual, listBarang[i].stok);
                }
                line();
                break;
            case 3 :
                line();
                while(1){
                    printf("Enter item id\n");
                    scanf("%d",&id);
                    if(id==0){
                        break;
                    }
                    index = search(banyakBarang,id);
                    printf("Masukkan banyak barang (%s)\n",listBarang[index].namaBarang);
                    scanf("%d",&listBarang[index].jumlah);
                }
                laporan(banyakBarang);
                break; 
            case 4 : 
                printf("a");
                break;
            case 5 :
                system("cls");
                modal = 0;
                keuntungan = 0;
                printf("%-6s%-16s%-11s%-10s%-13s%-13s\n", "Id", "Name", "Harga Beli", "Stock", "Harga Jual","Total Barang");
                for(int i=0; i<banyakBarang;i++){
                    printf( "%-6d%-16s%-11llu%-10.llu%-13.llu%-13d\n", listBarang[i].id, listBarang[i].namaBarang, listBarang[i].hargabeli, listBarang[i].stok,listBarang[i].hargajual,listBarang[i].jumlahTotal);
                    modal = modal + ((listBarang[i].stok + listBarang[i].jumlahTotal)*listBarang[i].hargabeli);
                    keuntungan = keuntungan + (listBarang[i].hargajual * listBarang[i].jumlahTotal);
                }
                line();
                printf("Modal\t\t: %d\n",modal);
                printf("Keuntungan\t: %d\n",keuntungan);
                break;
            case 6 :
                system("cls");
                interface();
                printf("Terima kasih telah berbelanja\n");
                printf("Struk telah dicetak");
                return 0;
            default :
                printf("Pilihan tidak ditemukan");
                break;
        }
        printf("Lanjut? (y/n) : ");
        scanf(" %c",&lanjut);
        if(lanjut == 'y'){
            system("cls");
            goto label;
        }
        
    }
    return 0;
}
int search(int banyakBarang, int id){
    for(int i = 0; i < banyakBarang; i++){
        if(id == listBarang[i].id){
            return i;
        }
    }
    printf("Barang tidak ditemukan");
}
void laporan(int banyakBarang){
    FILE *fp; /* credit.dat file pointer */
    struct clientData client = { 0, "",0, 0, 0,0,0};

    if ( ( fp = fopen( "MasterBarang.dat", "rb+" ) ) == NULL ) {
        printf( "File could not be opened.\n" );
        return 0;
    }

    for(int i=0; i<banyakBarang;i++){
        client.id = listBarang[i].id;
        client.jumlah = listBarang[i].jumlah;
        strcpy(client.namaBarang,listBarang[i].namaBarang); 
        client.hargabeli = listBarang[i].hargabeli;
        client.hargajual = listBarang[i].hargajual;
        client.jumlahTotal = listBarang[i].jumlahTotal + listBarang[i].jumlah;
        client.stok = listBarang[i].stok - listBarang[i].jumlah;
        if(client.id == 0) break;
        /* seek position in file to user-specified record */
        fseek( fp, ( client.id - 1 ) * sizeof( struct clientData ), SEEK_SET );         

        /* write user-specified information in file */           
        fwrite( &client, sizeof( struct clientData ), 1, fp );
    }
    fclose( fp ); /* fclose closes the file */
}
