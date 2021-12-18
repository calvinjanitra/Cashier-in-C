//STRUCT BARANG
struct item{
    char code[5];
    char name[100];
    int price;
};
struct item belanja[];
//STRUCT MASTER BARANG
struct clientData {                              
    int id;        
    char namaBarang[ 15 ]; 
    unsigned long long stok;
    unsigned long long hargabeli;
    unsigned long long hargajual;
    int jumlah;
    int jumlahTotal;
}; 

struct clientData listBarang[];

//interface
void interface(){
    printf("=================================================\n");
    printf("                                                 \n");
    printf("                                                 \n");
    printf("           SELAMAT DATANG DI INDOMARET           \n");
    printf("                                                 \n");
    printf("                                                 \n");
    printf("=================================================\n");
}
void intStruk(){
    printf("=================================================\n");
    printf("                                                 \n");
    printf("                                                 \n");
    printf("                   STRUK BELANJA                 \n");
    printf("                                                 \n");
    printf("                                                 \n");
    printf("=================================================\n");
}
int option(){
    int input = 0;
    printf("(1). Input Item\n");
    printf("(2). Show Item\n");
    printf("(3). Kasir\n");
    printf("(4). Riwayat Pembelanjaan\n");
    printf("(5). Laporan Keuangan\n");
    printf("(6). Exit\n");
    printf("=================================================\n");
    printf("Pilihan (1-6) : ");
    scanf("%d", &input);
    return input;
}
//line
void line(){
    printf("=================================================\n");
}
//list Item
int listItem(){
    char ch;
    FILE *start;
    start = fopen("listbelanja.txt", "r");
    int jumlah=0;

    while( ( fscanf(start,"%s",belanja[jumlah].code) ) != EOF ){
        fscanf(start,"%s",belanja[jumlah].name);
        fscanf(start,"%d",&belanja[jumlah].price);
        jumlah++;
    }
    fclose(start);
    return jumlah;
}

//NGEPRINT ITEM DI MENU
void printItem(int index){
    printf("LIST ITEM : \n");
    for(int i = 0;i<index;i++){
        printf("%s %s %d\n",belanja[i].code,belanja[i].name,belanja[i].price);
    }
}

//nulis di databese
int masterBarang(){ 
    FILE *fp; /* credit.dat file pointer */
    struct clientData client = { 0, "",0, 0, 0,0,0,0};

    if ( ( fp = fopen( "MasterBarang.dat", "rb+" ) ) == NULL ) {
        printf( "File could not be opened.\n" );
        return 0;
    }

    while ( 1 ) { 
        printf( "Enter id?\n" );
        scanf( "%d", &client.id );
        if(client.id== 0) break;

        printf( "Enter nama barang, harga beli, stock, harga jual?\n");
        /* set record namaBarang, firstName and balance value */
        scanf( "%s%llu%llu%llu", client.namaBarang, &client.hargabeli,&client.stok,&client.hargajual);

        if(client.id == 0) break;
        /* seek position in file to user-specified record */
        fseek( fp, ( client.id - 1 ) * sizeof( struct clientData ), SEEK_SET );         

        /* write user-specified information in file */           
        fwrite( &client, sizeof( struct clientData ), 1, fp );
    }
    fclose( fp ); /* fclose closes the file */
}
int readMaster()
{ 
    int banyakBarang=0;
    int tanda=0;
    FILE *fp; /* credit.dat file pointer */
    struct clientData client = { 0, "", 0, 0,0,0,0,0};

    if ( ( fp = fopen( "MasterBarang.dat", "rb" ) ) == NULL ) {
        printf( "File could not be opened.\n" );
    } /* end if */
    else { 
      /* read all records from file (until eof) */
    while ( !feof( fp ) ) { 
        fread( &client, sizeof( struct clientData ), 1, fp );
        if(client.id==tanda){
            continue;
        }
        tanda=client.id;
         /* display record */
        if ( client.id != 0 ) {
            listBarang[banyakBarang].id = client.id;
            strcpy( listBarang[banyakBarang].namaBarang,client.namaBarang);
            listBarang[banyakBarang].hargabeli = client.hargabeli;
            listBarang[banyakBarang].stok = client.stok;
            listBarang[banyakBarang].hargajual = client.hargajual;
            listBarang[banyakBarang].jumlahTotal = client.jumlahTotal;
            banyakBarang++;
        }
    }
    fclose( fp ); /* fclose closes the file */
    return banyakBarang;
}
}


//menulis struk
void writeStruk(int jumlahBarang){
    intStruk();
    char ch;
    FILE *start;
    start = fopen("strukbelanja.txt", "w");

    for(int i = 0;i<jumlahBarang;i++){
        printf("%s %s %d\n",belanja[i].code,belanja[i].name,belanja[i].price);
    }
    fclose(start);
}