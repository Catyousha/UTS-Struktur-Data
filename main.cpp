#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

#define NAMA_FILE_CSV "dataSurveyPemilu.csv"
using namespace std;

struct NodePemilih{
    string data[6];
    struct NodePemilih *next;
    struct NodePemilih *prev;
};
struct NodeID{
    string id;
    struct NodePemilih *dataPemilih = NULL;
    struct NodePemilih *dataAkhir = NULL;
    struct NodeID *next;
};

NodeID *kumpulanID = NULL; //Kumpulan NodeID
NodeID *IDAkhir = NULL; //tail pada node kumpulanID

int cekKosong(NodePemilih *h){
    if(h == NULL){
        return 1;
    }
    return 0;
}

//tampilkan SEMUA data
void tampilkan(){
    if(kumpulanID == NULL){
        cout<<"Tidak ada data untuk ditampilkan!"<<endl;
    }
    else{

        NodeID *showID = kumpulanID;
        cout<<"+"<<setfill('-')<<setw(16)<<"+"<<setw(15)<<"+"<<setw(29)<<"+"<<setw(5)<<"+"<<setw(15)<<"+"<<setw(23)<<"+"<<endl;
        cout<<"| ID"<<setfill(' ')<<setw(13)
            <<"|"<<" Nama"<<setw(10)
            <<"|"<<" Asal Kota"<<setw(19)
            <<"|"<<" JK"<<setw(2)
            <<"|"<<" Pil. Capres"<<setw(3)
            <<"|"<<" Donasi"<<setw(16)<<"|"<<endl;
        cout<<"+"<<setfill('-')<<setw(16)<<"+"<<setw(15)<<"+"<<setw(29)<<"+"<<setw(5)<<"+"<<setw(15)<<"+"<<setw(23)<<"+"<<endl;
        while(showID!=NULL){
            NodePemilih *show = showID->dataPemilih;
            while(show!=NULL){
                cout<<setfill(' ');
                cout<<"| "<<show->data[0]<<setw(15-show->data[0].length())
                    <<"|"<<show->data[1]<<setw(15-show->data[1].length())
                    <<"|"<<show->data[2]<<setw(30-show->data[2].length())
                    <<"| "<<show->data[3]<<setw(4-show->data[3].length())
                    <<"|"<<setw(8)<<show->data[4]<<setw(8-show->data[4].length())
                    <<"|"<<"Rp."<<show->data[5]<<setw(20-show->data[5].length())<<"|";
                cout<<endl;
                show = show->next;
            }
            showID = showID->next;
        }
        
        cout<<"+"<<setfill('-')<<setw(16)<<"+"<<setw(15)<<"+"<<setw(29)<<"+"<<setw(5)<<"+"<<setw(15)<<"+"<<setw(23)<<"+"<<endl;
    }
}


//////////////--------KELOLA NodeID--------//////////////
//mengambil tipe id dari id pemilih, misal: ambil DKI dari DKI01234, ambil JB dari JB02341
string ambilTipeID(string id){

    string tipeid;
    int i=0;
    while(id[i]!='0'){
        tipeid+=id[i];
        i++;
    }
    return tipeid;

}

//tambah data di depan NodeID
void tambahIDDepan(string idname){
    NodeID *idbaru = new NodeID;
    idbaru->id = idname;
    idbaru->next = NULL;

    if(kumpulanID == NULL){
        kumpulanID = idbaru;
        IDAkhir = kumpulanID;    
    }
    else{
        idbaru->next = kumpulanID;
        kumpulanID = idbaru;
    }
}

//id baru akan ditambahkan sebelum id acuan, dengan anggapan id acuan sudah ada
void tambahIDTengah(string idname, string acuan){
    NodeID *idbaru = new NodeID;
    idbaru->id = idname;
    idbaru->next = NULL;

    if(idbaru == kumpulanID){
        tambahIDDepan(idname);
        return;
    }
    NodeID *cari = kumpulanID;
    while(cari->next->id != acuan){
        cari = cari->next;
    }
    cout<<"p"<<endl;
    NodeID *bantu = cari->next;
    idbaru->next = cari->next;
    cari->next = idbaru;
    
}

//tambah data di belakang NodeID
void tambahIDBelakang(string idname){
    NodeID *idbaru = new NodeID;
    idbaru->id = idname;
    idbaru->next = NULL;

    if(kumpulanID == NULL){
        kumpulanID = idbaru;
        IDAkhir = kumpulanID;    
    }
    else{
        IDAkhir->next = idbaru;
        IDAkhir = idbaru;
    }
}

//pencarian ID
//cari suatu ID, jika tidak ketemu maka kembalikan false
int temukanID(string idname){
    NodeID *d = kumpulanID;
    while(d!=NULL){
        if(d->id == idname){
            return 1;
        }
        d = d->next;
    }
    return 0;
}

//cari suatu ID, jika ketemu maka kembalikan node id tersebut (anggapan yang dicari ada)
NodeID *dapatkanNodeID(string idname){
    NodeID *d = kumpulanID;
    while(d!=NULL){
        if(d->id == idname){
            return d;
        }
        d = d->next;
    }
}

//tampilkan ID
//tampilkan data hanya berdasarkan id
void tampilkanDataId(string idname){
    if(temukanID(idname) == 0){
        cout<<"ID tidak ditemukan!"<<endl;
        return;
    }
    NodeID *id = dapatkanNodeID(idname);
    NodePemilih *show = id->dataPemilih;
        cout<<"+"<<setfill('-')<<setw(16)<<"+"<<setw(15)<<"+"<<setw(29)<<"+"<<setw(5)<<"+"<<setw(15)<<"+"<<setw(23)<<"+"<<endl;
        cout<<"| ID"<<setfill(' ')<<setw(13)
            <<"|"<<" Nama"<<setw(10)
            <<"|"<<" Asal Kota"<<setw(19)
            <<"|"<<" JK"<<setw(2)
            <<"|"<<" Pil. Capres"<<setw(3)
            <<"|"<<" Donasi"<<setw(16)<<"|"<<endl;
        cout<<"+"<<setfill('-')<<setw(16)<<"+"<<setw(15)<<"+"<<setw(29)<<"+"<<setw(5)<<"+"<<setw(15)<<"+"<<setw(23)<<"+"<<endl;
    while(show!=NULL){
                cout<<setfill(' ');
                cout<<"| "<<show->data[0]<<setw(15-show->data[0].length())
                    <<"|"<<show->data[1]<<setw(15-show->data[1].length())
                    <<"|"<<show->data[2]<<setw(30-show->data[2].length())
                    <<"| "<<show->data[3]<<setw(4-show->data[3].length())
                    <<"|"<<setw(8)<<show->data[4]<<setw(8-show->data[4].length())
                    <<"|"<<"Rp."<<show->data[5]<<setw(20-show->data[5].length())<<"|";
                cout<<endl;
        show = show->next;
    }
    cout<<"+"<<setfill('-')<<setw(16)<<"+"<<setw(15)<<"+"<<setw(29)<<"+"<<setw(5)<<"+"<<setw(15)<<"+"<<setw(23)<<"+"<<endl;
}

//tampilkan  ID yang ada
void tampilkanID(){
    if(kumpulanID == 0){
        cout<<"Tidak ditemukan ID yang terdaftar!"<<endl;
        return;
    }
    cout<<"+"<<setfill('-')<<setw(35)<<"+"<<endl;
    cout<<"| Berikut ID yang sudah terdaftar: |"<<endl;
    cout<<"+"<<setfill('-')<<setw(35)<<"+"<<endl;

    cout<<setfill(' ');
    NodeID *show = kumpulanID;
    while(show!=NULL){
        cout<<"| "<<show->id<<setw(34-show->id.length())<<"|"<<endl;
        show = show->next;
    }
    cout<<"+"<<setfill('-')<<setw(35)<<"+"<<endl;
}
//hapus ID
//temukan idname kemudian hapus node yang mengandung idname tersebut
void hapusIDDepan(){
    if(kumpulanID = NULL){
        cout<<"Tidak ada ID untuk dihapus!"<<endl;
        return;
    }

    NodeID *hapus = kumpulanID;
    kumpulanID = kumpulanID->next;
    delete hapus;
    
}
void hapusID(string idname){
    if(temukanID(idname) == 1){
        
        //jika id yang dihapus ialah id pertama, alihkan ke fungsi hapusIdDepan
        if(kumpulanID->id == idname){
            hapusIDDepan();
            return;
        }
        else{
            NodeID *d = kumpulanID;
            while(d->next->id!=idname){
                d=d->next;
            }
            NodeID *hapus = d->next;
            d->next = d->next->next;
            delete hapus;
        }
    }
    else{
        cout<<"ID tidak ditemukan!"<<endl;
        return;
    }
}

//////////////--------End Of KELOLA NodeID--------//////////////

//////////////--------KELOLA NodePemilih--------//////////////
//fungsi pencarian dengan asumsi id ada.
int adaDataPemilih(string caridata, string idname){
    
    if(temukanID(idname) == 0){
        return 0;
    }
    NodeID *ID = dapatkanNodeID(idname);
    NodePemilih *cari = ID->dataPemilih;
    while(cari!=NULL){
        if(cari->data[0] == caridata){
            return 1;
        }
        cari = cari->next;
    }
    return 0;
}

//tampilkan data pemilih
void tampilkanDataPemilih(string caridata){
    string tipeid = ambilTipeID(caridata);
    if(adaDataPemilih(caridata, tipeid) == 0){
        cout<<caridata<<" tidak terdaftar sebagai pemilih!"<<endl;
        return;
    }

    NodeID *cari = dapatkanNodeID(tipeid);
    while(cari->dataPemilih->data[0] != caridata){
        cari->dataPemilih = cari->dataPemilih->next;
    }
    cout<<"++++============++++Data Pemilih++++============++++"<<endl;
    cout<<"| ID Pemilih   :"<<cari->dataPemilih->data[0]<<endl;
    cout<<"| Nama Pemilih : "<<cari->dataPemilih->data[1]<<endl;
    cout<<"| Asal Kota Pemilih : "<<cari->dataPemilih->data[2]<<endl;
    cout<<"| Jenis Kelamin Pemilih : "<<cari->dataPemilih->data[3]<<endl;
    cout<<"| Dukungan Capres : "<<cari->dataPemilih->data[4]<<endl;
    cout<<"| Jumlah Donasi : Rp."<<cari->dataPemilih->data[5]<<endl;
    cout<<"++++============++++++++++++++++++++============++++"<<endl;
}



//fungsi penambahan
void tambahDataDepan(string row[]){
    NodePemilih *baru = new NodePemilih;
    NodeID *pemilihID = kumpulanID;

    baru->data[0] = row[0]; //id misal: DKI01234
    string tipeid = ambilTipeID(row[0]); //DKI, JT, JB, dsb
    if(adaDataPemilih(row[0], tipeid)){
        cout<<row[0]<<" sudah terdaftar, data gagal ditambahkan."<<endl;
        return;
    }
    baru->data[1] = row[1]; //nama
    baru->data[2] = row[2]; //askot
    baru->data[3] = row[3]; //jenis kelamin
    baru->data[4] = row[4]; //pilihan capres
    baru->data[5] = row[5]; //donasi

    baru->prev = NULL;
    baru->next = NULL;
    

    if(temukanID(tipeid) == 0){
        tambahIDBelakang(tipeid);
    }
    pemilihID = dapatkanNodeID(tipeid);
    if(cekKosong(pemilihID->dataPemilih)){

        pemilihID->dataPemilih = baru;
        pemilihID->dataAkhir = pemilihID->dataPemilih;
        pemilihID->dataPemilih->next = NULL;

    }
    else{
        baru->next = pemilihID->dataPemilih;
        
        pemilihID->dataPemilih = baru;
        pemilihID->dataPemilih->prev = NULL;
    }
    cout<<"Data Pemilih Berhasil Ditambahkan!"<<endl;

}

void tambahDataTengah(string row[], string acuan, string idname){
    //dataid = data yang menjadi acuan user
    //idname = id dimana data tersebut berada
    //data akan disisipkan sebelum data dengan id 'dataid'
    if(adaDataPemilih(acuan,idname)==0){
        cout<<"Data pemilih dengan id "<<acuan<<" tidak ditemukan!"<<endl;
        return;
    }
    else{
        NodePemilih *baru = new NodePemilih;
        baru->data[0] = row[0]; //id misal: DKI01234
        string tipeid = ambilTipeID(row[0]); //DKI, JT, JB, dsb

        if(adaDataPemilih(row[0], tipeid)){
            cout<<row[0]<<" sudah terdaftar, data gagal ditambahkan."<<endl;
            return;
    }
        baru->data[1] = row[1]; //nama
        baru->data[2] = row[2]; //askot
        baru->data[3] = row[3]; //jenis kelamin
        baru->data[4] = row[4]; //pilihan capres
        baru->data[5] = row[5]; //donasi

        baru->prev = NULL;
        baru->next = NULL;

        if(temukanID(tipeid) == 0){
            tambahIDBelakang(tipeid);
        }

        NodeID *ID = dapatkanNodeID(tipeid);

        //kalau data acuan berada didepan, maka alihkan ke fungsi tambah depan
        if(acuan == ID->dataPemilih->data[0]){
            tambahDataDepan(row);
            return;
        }

        NodePemilih *bantu = ID->dataPemilih;
        while(bantu->next->data[0]!=acuan){
            bantu = bantu->next;
        }
        bantu->prev->next = baru;
        baru->next = bantu;
        bantu->prev = baru;
        bantu->next->prev = baru;

        //jika yang menjadi data acuan adalah tail
        //maka sambungkan tail dengan data baru
        if(bantu = ID->dataAkhir){
            ID->dataAkhir->prev = baru;
            baru->next = ID->dataAkhir;
        }
        cout<<"Data Pemilih Berhasil Ditambahkan!"<<endl;
    }
}

void tambahDataBelakang(string row[]){
    NodePemilih *baru = new NodePemilih;
    NodeID *pemilihID = kumpulanID;
    baru->data[0] = row[0]; //id misal: DKI01234
    string tipeid = ambilTipeID(row[0]); //DKI, JT, JB, dsb

    if(adaDataPemilih(row[0], tipeid)){
        cout<<row[0]<<" sudah terdaftar, data gagal ditambahkan."<<endl;
        return;
    }

    baru->data[1] = row[1]; //nama
    baru->data[2] = row[2]; //askot
    baru->data[3] = row[3]; //jenis kelamin
    baru->data[4] = row[4]; //pilihan capres
    baru->data[5] = row[5]; //donasi

    baru->prev = NULL;
    baru->next = NULL;
    

    if(temukanID(tipeid) == 0){
        tambahIDBelakang(tipeid);
    }
    pemilihID = dapatkanNodeID(tipeid);
    if(cekKosong(pemilihID->dataPemilih)){
        
        pemilihID->dataPemilih = baru;
        pemilihID->dataAkhir = pemilihID->dataPemilih;
        

    }
    else{
        pemilihID->dataAkhir->next = baru;
        baru->prev = pemilihID->dataAkhir;
        pemilihID->dataAkhir = baru;
    }
    cout<<"Data Pemilih Berhasil Ditambahkan!"<<endl;
}

//fungsi penghapusan
void hapusDataDepan(string idname){
    
    if(temukanID(idname) == 0){
        cout<<"ID tidak ditemukan!"<<endl;
        return;
    }
    NodeID *pemilihID = dapatkanNodeID(idname);
        
    if(cekKosong(pemilihID->dataPemilih)){
        cout<<"Tidak ditemukan data pemilih untuk dihapus!"<<endl;
        return;
    }

    if(pemilihID->dataPemilih->next == NULL){
        pemilihID->dataPemilih = NULL;
        pemilihID->dataAkhir = NULL;
    }
    else{
        NodePemilih *hapus = new NodePemilih;
        hapus = pemilihID->dataPemilih;
        pemilihID->dataPemilih = pemilihID->dataPemilih->next;
        delete hapus;
    }
}

void hapusDataBelakang(string idname){
    if(temukanID(idname) == 0){
        cout<<"ID tidak ditemukan!"<<endl;
        return;
    }
    NodeID *pemilihID = dapatkanNodeID(idname);

    if(pemilihID->dataPemilih->next == NULL){
        pemilihID->dataPemilih = NULL;
        pemilihID->dataAkhir = NULL;
    }
    else{
        NodePemilih *hapus = new NodePemilih;
        hapus = pemilihID->dataAkhir;
        pemilihID->dataAkhir = pemilihID->dataAkhir->prev;
        pemilihID->dataAkhir->next = NULL;
        delete hapus;
    }
}

void hapusDataTengah(string idname, string acuan){
    if(adaDataPemilih(acuan, idname)== 0){
        cout<<"Data pemilih dengan id "<<acuan<<" tidak ditemukan!"<<endl;
        return;        
    }
    else{
        NodeID *ID = dapatkanNodeID(idname);
        //kalau data yang ingin dihapus ada di depan, alihkan ke fungsi hapusDataDepan
        if(acuan == ID->dataPemilih->data[0]){
            hapusDataDepan(idname);
            cout<<"Data berhasil dihapus!"<<endl;
            return;
        }

        //kalau data yang ingin dihapus ada di belakang, alihkan ke fungsi hapusDataBelakang
        if(acuan == ID->dataAkhir->data[0]){
            hapusDataBelakang(idname);
            cout<<"Data berhasil dihapus!"<<endl;
            return;
        }

        NodePemilih *bantu = ID->dataPemilih;
        while(bantu->next->data[0]!=acuan){
            bantu = bantu->next;
        }

        NodePemilih *hapus = bantu->next;
        bantu->next->next->prev = bantu;
        bantu->next = bantu->next->next;
        delete hapus;
        
        //kaitkan tail dengan data sebelumnya jika tail berada setelah data yang akan dihapus
        if(bantu->next == ID->dataAkhir){
            bantu->next = ID->dataAkhir;
            ID->dataAkhir->prev = bantu;
        }
        cout<<"Data berhasil dihapus!"<<endl;
    }
}
void hapusSemuaDataPemilih(string idname){
    NodeID *ID = dapatkanNodeID(idname);
    NodePemilih *hapus = ID->dataPemilih;
    while(ID->dataPemilih != NULL){
        NodePemilih *hapus = ID->dataPemilih;
        ID->dataPemilih = ID->dataPemilih->next;
        delete hapus;
    }
}
//////////////--------End Of KELOLA NodePemilih--------//////////////

//hapus SEMUA data
void hapusSemua(){
    while(kumpulanID!=NULL){
        NodeID *hapus = kumpulanID;
        kumpulanID = kumpulanID->next;
        delete hapus;
    }
}

//////////////--------Fungsi tambahan + Agregat--------//////////////
void baca_file(){
    fstream report;
    report.open(NAMA_FILE_CSV, ios::in);
    
    string line, word;

    while(getline(report, line)){
        string row[100]; int rowIndex=0;
        istringstream iss(line);

        while(getline(iss, word, ';')){
            row[rowIndex]=word;
            rowIndex++;
        }
        tambahDataBelakang(row);
    }
}
void tampilkanDataPendukungPaslon(string paslon){
    if(kumpulanID == NULL){
        cout<<"Tidak ada data untuk ditampilkan!"<<endl;
    }
    else{

        NodeID *showID = kumpulanID;
        cout<<"+"<<setfill('-')<<setw(16)<<"+"<<setw(15)<<"+"<<setw(29)<<"+"<<setw(5)<<"+"<<setw(15)<<"+"<<setw(23)<<"+"<<endl;
        cout<<"| ID"<<setfill(' ')<<setw(13)
            <<"|"<<" Nama"<<setw(10)
            <<"|"<<" Asal Kota"<<setw(19)
            <<"|"<<" JK"<<setw(2)
            <<"|"<<" Pil. Capres"<<setw(3)
            <<"|"<<" Donasi"<<setw(16)<<"|"<<endl;
        cout<<"+"<<setfill('-')<<setw(16)<<"+"<<setw(15)<<"+"<<setw(29)<<"+"<<setw(5)<<"+"<<setw(15)<<"+"<<setw(23)<<"+"<<endl;
        while(showID!=NULL){
            NodePemilih *show = showID->dataPemilih;

            while(show!=NULL){
                //kalau pil capres tidak sesuai dengan parameter paslon, skip
                if(show->data[4] != paslon){
                    show = show->next;
                }
                else{
                    cout<<setfill(' ');
                    cout<<"| "<<show->data[0]<<setw(15-show->data[0].length())
                        <<"|"<<show->data[1]<<setw(15-show->data[1].length())
                        <<"|"<<show->data[2]<<setw(30-show->data[2].length())
                        <<"| "<<show->data[3]<<setw(4-show->data[3].length())
                        <<"|"<<setw(8)<<show->data[4]<<setw(8-show->data[4].length())
                        <<"|"<<"Rp."<<show->data[5]<<setw(20-show->data[5].length())<<"|";
                    cout<<endl;
                    show = show->next;
                }
            }
            showID = showID->next;
        }
        
        cout<<"+"<<setfill('-')<<setw(16)<<"+"<<setw(15)<<"+"<<setw(29)<<"+"<<setw(5)<<"+"<<setw(15)<<"+"<<setw(23)<<"+"<<endl;
    } 
}

int hitungJumlahPendukung(string paslon){
    int count = 0;
    NodeID *showID = kumpulanID;
    while(showID!=NULL){
        NodePemilih *show = showID->dataPemilih;
        while(show!=NULL){
            if(show->data[4] == paslon){
                count++;
            }
            show = show->next;
        }
        showID = showID->next;
    }
    return count;
}
int hitungJumlahDonasi(){
    int sum=0;
    NodeID *showID = kumpulanID;
    while(showID!=NULL){
        NodePemilih *show = showID->dataPemilih;
        while(show!=NULL){
            string uangdonasi = show->data[5];
            stringstream geek(uangdonasi);
            
            int nominal;
            geek >> nominal;
            sum+=nominal;
            show = show->next;
        }
        showID = showID->next;
    }
    return sum;
}
void simpan_file(){
    ofstream report;
    report.open(NAMA_FILE_CSV);
    NodeID *ID = kumpulanID;
    while(ID != NULL){
        NodePemilih *save = ID->dataPemilih;
        while(save != NULL){
            report<<save->data[0]<<";"
            <<save->data[1]<<";"
            <<save->data[2]<<";"
            <<save->data[3]<<";"
            <<save->data[4]<<";"
            <<save->data[5]<<";"<<endl;
            save = save->next;
        }
        ID = ID->next;
    }
    report.close();
}
//////////////--------End Of Fungsi tambahan + Agregat--------//////////////
void menuKelolaID();
void menuKelolaPemilih(string idname);
void menuDataSpesifik();
void menuCountOf();
void menuSumOf();
void menuSimpanDanKeluar();

int main(){
    baca_file();
    mainmenu: //checkpoint
    //system("cls"); //windows
    system("clear"); //linux
    cout<<"++++============++++SURVEY CORPS++++============++++"<<endl; //referensi attack on titan
    cout<<"|                                                  |"<<endl;
    cout<<"| 1. Tampilkan Data Hasil Survey                   |"<<endl; //show all data
    cout<<"| 2. Kelola ID Pemilih                             |"<<endl; //CRUD node ID
    cout<<"| 3. Kelola Data Pemilih                           |"<<endl; //CRUD node Pemilih
    cout<<"|                                                  |"<<endl;
    cout<<"| 4. Tampilkan Pendukung Capres                    |"<<endl; //data spesifik
    cout<<"| 5. Tampilkan Statistik Dukungan                  |"<<endl; //count of
    cout<<"| 6. Tampilkan Perolehan Donasi                    |"<<endl; //sum of
    cout<<"| 7. Keluar                                        |"<<endl; //exit
    cout<<"=================++++++++++++++++++++==============="<<endl;
    cout<<"* Pilih opsi...                                   | ";
    int opsi; cin>>opsi;
    //system("cls");
    system("clear");

    if(opsi == 1){
        tampilkan();
        cout<<"Tekan Tombol Apapun Untuk Kembali..."<<endl;
        cin.ignore();
        cin.get();
        goto mainmenu;
    }
    else if(opsi == 2){
        menuKelolaID();
        goto mainmenu;
    }
    else if(opsi == 3){
        cout<<"Data Pemilih Dikelompokkan Berdasarkan ID."<<endl;
        cout<<"Masukkan Tipe ID untuk mengelola data pemilih: "<<endl;
        string idname; cin>>idname;
        if(temukanID(idname)){
            menuKelolaPemilih(idname);
        }
        else{
            cout<<"ID tidak terdaftar!"<<endl;
            cin.ignore();
            cin.get();
            goto mainmenu;
        }
        goto mainmenu;
    }
    else if(opsi == 4){
        menuDataSpesifik();
        goto mainmenu;
    }
    else if(opsi == 5){
        menuCountOf();
        goto mainmenu;
    }
    else if(opsi == 6){
        menuSumOf();
        goto mainmenu;
    }
    else if(opsi == 7){
        menuSimpanDanKeluar();
    }
    else{
        cout<<"Opsi tidak ditemukan!"<<endl;
        cin.ignore();
        cin.get();
        goto mainmenu;
    }
}

//////////////--------fungsi tampilkan menu--------//////////////
void menuKelolaID(){

    menukelolaID:
    //system("cls");
    system("clear");
    cout<<"++++============+++++Kelola ID+++++=============++++"<<endl;
    cout<<"|                                                  |"<<endl;
    cout<<"| 1. Tampilkan ID Yang Terdaftar                   |"<<endl; //show all data
    cout<<"| 2. Tambah ID Depan                               |"<<endl; //CRUD node ID
    cout<<"| 3. Tambah ID Tengah                              |"<<endl;
    cout<<"| 4. Tambah ID Belakang                            |"<<endl;
    cout<<"| 5. Hapus ID                                      |"<<endl;
    cout<<"| 6. Hapus Semua ID                                |"<<endl;
    cout<<"| 7. Kembali ke Menu Awal                          |"<<endl;
    cout<<"|                                                  |"<<endl;
    cout<<"=================++++++++++++++++++++==============="<<endl;
    cout<<"* Pilih opsi...                                   | ";
    int opsiid; cin>>opsiid;
    //system("cls");
    system("clear");
    if(opsiid == 1){
        tampilkanID();
        cin.ignore();
        cin.get();
        goto menukelolaID;
    }
    else if(opsiid == 2){
        cout<<"Format ID adalah huruf kapital [Misal: DKI, JB, JT]"<<endl;
        cout<<"Masukkan ID yang ingin di daftarkan:"<<endl;
        string idname; cin>>idname;
        if(temukanID(idname) == 1){
            cout<<"ID sudah terdaftar!"<<endl;
            cin.ignore();
            cin.get();
            goto menukelolaID;
        }
        tambahIDDepan(idname);
        cout<<"ID berhasil ditambahkan!"<<endl;
        cin.ignore();
        cin.get();
        goto menukelolaID;
    }
    else if(opsiid == 3){
        cout<<"Format ID adalah huruf kapital [Misal: DKI, JB, JT]"<<endl;
        cout<<"Masukkan ID yang ingin di daftarkan:"<<endl;
        string idname; cin>>idname;
        if(temukanID(idname) == 1){
            cout<<"ID sudah terdaftar!"<<endl;
            cin.ignore();
            cin.get();
            goto menukelolaID;
        }

        tampilkanID();
        cout<<"ID Baru akan ditambahkan sebelum ID acuan."<<endl;
        cout<<"Masukkan ID yang menjadi acuan:"<<endl;
        string idacuan; cin>>idacuan;
        if(temukanID(idacuan) == 0){
            cout<<"ID tidak ditemukan!"<<endl;
            cin.ignore();
            cin.get();
            goto menukelolaID;
        }
        tambahIDTengah(idname, idacuan);
        cout<<"ID Berhasil ditambahkan!"<<endl;
        cin.ignore();
        cin.get();
        goto menukelolaID;
    }
    else if(opsiid == 4){
        cout<<"Format ID adalah huruf kapital [Misal: DKI, JB, JT]"<<endl;
        cout<<"Masukkan ID yang ingin di daftarkan:"<<endl;
        string idname; cin>>idname;
        if(temukanID(idname) == 1){
            cout<<"ID sudah terdaftar!"<<endl;
            cin.ignore();
            cin.get();
            goto menukelolaID;
        }
        tambahIDBelakang(idname);
        cout<<"ID berhasil ditambahkan!"<<endl;
        cin.ignore();
        cin.get();
        goto menukelolaID;
    }
    else if(opsiid == 5){
        tampilkanID();
        cout<<"Masukkan ID yang ingin dihapus!"<<endl;
        string idname; cin>>idname;
        if(temukanID(idname) == 0){
            cout<<"ID tidak ditemukan!"<<endl;
            cin.ignore();
            cin.get();
            goto menukelolaID;
        }
        hapusID(idname);
        cout<<"ID berhasil dihapus!"<<endl;
        cin.ignore();
        cin.get();
        goto menukelolaID;

    }
    else if(opsiid == 6){
        cout<<"Dengan menghapus semua ID, maka anda juga menghapus keseluruhan data yang ada."<<endl;
        cout<<"Ketik 'YaSemuanyaAkanSayaHapus' untuk menghapus semua ID"<<endl;
        string konfirm; cin>>konfirm;
        if(konfirm == "YaSemuanyaAkanSayaHapus"){
            hapusSemua();
            cout<<"Data Berhasil dihapus!"<<endl;
        }
        else{
            cout<<"Penghapusan Dibatalkan."<<endl;
        }
        cin.ignore();
        cin.get();
        goto menukelolaID;
    }
    else if(opsiid == 7){
        return;
    }
    else{
        cout<<"Opsi tidak ditemukan!"<<endl;
        cin.ignore();
        cin.get();
        goto menukelolaID;
    }
}

void menuKelolaPemilih(string idname){
    menukelolaPemilih:
    //system("cls");
    system("clear");
    cout<<"++++============++++Kelola Pemilih++++============++++"<<endl;
    cout<<"|                          "<<idname<<setfill(' ')<<setw(27-idname.length())<<"|"<<endl;
    cout<<"| 1. Tampilkan Pemilih Yang Terdaftar                |"<<endl; //show all data
    cout<<"| 2. Tambah Data Pemilih Depan                       |"<<endl; //CRUD node ID
    cout<<"| 3. Tambah Data Pemilih Tengah                      |"<<endl;
    cout<<"| 4. Tambah Data Pemilih Belakang                    |"<<endl;
    cout<<"|                                                    |"<<endl;
    cout<<"| 5. Hapus Data Pemilih                              |"<<endl;
    cout<<"| 6. Hapus Semua Data Pemilih                        |"<<endl;
    cout<<"| 7. Cari Data Pemilih                               |"<<endl;
    cout<<"|                                                    |"<<endl;
    cout<<"| 8. Kembali ke Menu Awal                            |"<<endl;
    cout<<"|                                                    |"<<endl;
    cout<<"=================++++++++++++++++++++++==============="<<endl;
    cout<<"* Pilih opsi...                                   | ";
    int opsipem; cin>>opsipem;
    //system("cls");
    system("clear");

    if(opsipem == 1){
        tampilkanDataId(idname);
        cin.ignore();
        cin.get();
        goto menukelolaPemilih;
    }
    else if(opsipem == 2){
        string row[6];
        cout<<"++++============++++Tambah Data Depan++++============++++"<<endl;
        cout<<"* Masukkan ID ["<<idname<<"0xxxxx] :"; cin>>row[0];
            
        //kalau id yang didaftarkan user tidak sesuai, maka ID tidak valid.
        string cekid =ambilTipeID(row[0]);
        if(cekid != idname){
            cout<<"ID tidak valid!"<<endl;
            cin.ignore();
            cin.get();
            goto menukelolaPemilih;            
        }

        cout<<"* Masukkan Nama: "; cin>>row[1];
        cout<<"* Masukkan Jenis Kelamin [L/P]: "; cin>>row[2];
        cout<<"* Masukkan Asal Kota: "; cin>>row[3];
        cout<<"* Masukkan No. Dukungan [1/2]: "; cin>>row[4];
        cout<<"* Masukkan Jumlah Donasi: Rp."; cin>>row[5];
        cout<<"++++============++++++++++++++++++++++++============++++"<<endl;
        cout<<"Sedang Memproses..."<<endl;
        tambahDataDepan(row);
        cin.ignore();
        cin.get();
        goto menukelolaPemilih; 
    }
    else if(opsipem == 3){
        string row[6];
        cout<<"++++============++++Tambah Data Tengah++++============++++"<<endl;
        cout<<"* Masukkan ID ["<<idname<<"0xxxxx] :"; cin>>row[0];
            
        //kalau id yang didaftarkan user tidak sesuai, maka ID tidak valid.
        string cekid =ambilTipeID(row[0]);
        if(cekid != idname){
            cout<<"ID tidak valid!"<<endl;
            cin.ignore();
            cin.get();
            goto menukelolaPemilih;            
        }

        cout<<"* Masukkan Nama: "; cin>>row[1];
        cout<<"* Masukkan Jenis Kelamin [L/P]: "; cin>>row[2];
        cout<<"* Masukkan Asal Kota: "; cin>>row[3];
        cout<<"* Masukkan No. Dukungan [1/2]: "; cin>>row[4];
        cout<<"* Masukkan Jumlah Donasi: Rp."; cin>>row[5];
        cout<<"++++============++++++++++++++++++++++++============++++"<<endl;
        cout<<"Sedang Memproses..."<<endl;
        
        tampilkanDataId(idname);
        cout<<"Data Pemilih Baru akan ditambahkan sebelum ID acuan."<<endl;
        cout<<"Masukkan ID yang menjadi acuan:"<<endl;
        string idacuan; cin>>idacuan;
        cout<<"Sedang Memproses..."<<endl;
        tambahDataTengah(row, idacuan, idname);
        cin.ignore();
        cin.get();
        goto menukelolaPemilih; 
    }
    else if(opsipem == 4){
        string row[6];
        cout<<"++++============++++Tambah Data Belakang++++============++++"<<endl;
        cout<<"* Masukkan ID ["<<idname<<"0xxxxx] :"; cin>>row[0];
            
        //kalau id yang didaftarkan user tidak sesuai, maka ID tidak valid.
        string cekid =ambilTipeID(row[0]);
        if(cekid != idname){
            cout<<"ID tidak valid!"<<endl;
            cin.ignore();
            cin.get();
            goto menukelolaPemilih;            
        }

        cout<<"* Masukkan Nama: "; cin>>row[1];
        cout<<"* Masukkan Jenis Kelamin [L/P]: "; cin>>row[2];
        cout<<"* Masukkan Asal Kota: "; cin>>row[3];
        cout<<"* Masukkan No. Dukungan [1/2]: "; cin>>row[4];
        cout<<"* Masukkan Jumlah Donasi: Rp."; cin>>row[5];
        cout<<"++++============++++++++++++++++++++++++============++++"<<endl;
        cout<<"Sedang Memproses..."<<endl;
        tambahDataBelakang(row);
        cin.ignore();
        cin.get();
        goto menukelolaPemilih; 
    }
    else if(opsipem == 5){
        tampilkanDataId(idname);
        cout<<"Masukkan ID Pemilih yang ingin dihapus: ";
        string idpem; cin>>idpem;
        hapusDataTengah(idname, idpem);
        cin.ignore();
        cin.get();
        goto menukelolaPemilih;
    }
    else if(opsipem == 6){
        cout<<"Seluruh data pada ID ini akan dihapus."<<endl;
        cout<<"Ketik 'YaHapusSemua' untuk menghapus seluruh data yang ada pada ID ini: "<<endl;
        string konfirm; cin>>konfirm;
        if(konfirm == "YaHapusSemua"){
            hapusSemuaDataPemilih(idname);
            cout<<"Penghapusan selesai!"<<endl;
        }
        else{
            cout<<"Penghapusan dibatalkan."<<endl;
        }
        cin.ignore();
        cin.get();
        goto menukelolaPemilih;
    }
    else if(opsipem == 7){
        cout<<"++++============++++Cari Data Pemilih++++============++++"<<endl;
        cout<<"* Masukkan ID Pemilih :"; string idpem; cin>>idpem;
        cout<<"++++============+++++++++++++++++++++++++============++++"<<endl;
        tampilkanDataPemilih(idpem);

        cout<<"Tekan tombol apapun untuk kembali..."<<endl;
        cin.ignore();
        cin.get();
        goto menukelolaPemilih;
    }
    else if(opsipem == 8){
        return;
    }
    else{
        cout<<"Opsi tidak ditemukan!"<<endl;
        cin.ignore();
        cin.get();
        goto menukelolaPemilih;
    }
}

void menuDataSpesifik(){
    cout<<"++++============++++Tampilkan Pendukung Capres++++============++++"<<endl;
    cout<<"* Masukkan Nomor Urut Paslon: "; string paslon; cin>>paslon;
    cout<<"++++============++++++++++++++++++++++++++++++++++============++++"<<endl;
    tampilkanDataPendukungPaslon(paslon);
    cout<<"Tekan tombol apapun untuk kembali...";
    cin.ignore();
    cin.get();
    return;
}

void menuCountOf(){
    int pendukungno1 = hitungJumlahPendukung("1");
    int pendukungno2 = hitungJumlahPendukung("2");

    cout<<"++++============++++Tampilkan Statistik Dukungan++++============++++"<<endl;
    cout<<"* Pendukung Paslon No.Urut 1: "<<pendukungno1<<setfill(' ')<<setw(36)<<"*"<<endl;
    cout<<"|                                                                   |"<<endl;
    cout<<"* Pendukung Paslon No.Urut 2: "<<pendukungno2<<setfill(' ')<<setw(36)<<"*"<<endl;
    cout<<"++++============++++++++++++++++++++++++++++++++++++============++++"<<endl;
    cout<<"Tekan tombol apapun untuk kembali...";
    cin.ignore();
    cin.get();
    return;
}

void menuSumOf(){
    int jumlahdonasi = hitungJumlahDonasi();
    string digit = to_string(jumlahdonasi);
    cout<<"++++============++++Jumlah Donasi Yang Sudah Terkumpul++++============++++"<<endl;
    cout<<"|                                                                        |"<<endl;
    cout<<"| Rp."<<jumlahdonasi<<setfill(' ')<<setw(69-digit.length())<<"|"<<endl;
    cout<<"|                                                                        |"<<endl;
    cout<<"=================++++++++++++++++++++++++++++++++++++++++++==============="<<endl;
    cout<<"Tekan tombol apapun untuk kembali..."<<endl;
    cin.ignore();
    cin.get();
    return;
}

void menuSimpanDanKeluar(){
    cout<<"Menyimpan data..."<<endl;
    simpan_file();
    cout<<"Penyimpanan berhasil!\n\n\n"<<endl;
    cout<<"++++==============++++Sampai Jumpa++++===============++++"<<endl;
    cout<<"++++                                                 ++++"<<endl;
    cout<<"++++ Jaka Asa Baldan Ahmad            (190535646020) ++++"<<endl;
    cout<<"++++ Syahrieza Ilham Noor Fauzi       (190535646058) ++++"<<endl;
    cout<<"++++ Winaldo Dwi Putra Laua           (190535646057) ++++"<<endl;
    cout<<"++++                                                 ++++"<<endl;
    cout<<"++++=============++++Selamat/Sukses++++==============++++"<<endl;
}