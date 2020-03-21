#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
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
void tambahIDDepan(string idname, string asal){
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
    cout<<"+"<<setfill('-')<<setw(7)<<"+"<<setw(15)<<"+"<<setw(15)<<"+"<<setw(6)<<"+"<<setw(23)<<"+"<<setw(20)<<"+"<<endl;
        cout<<"| No."<<setfill(' ')<<setw(3)
        <<"|"<<" Nama"<<setw(10)
        <<"|"<<" Diagnosa"<<setw(6)
        <<"|"<<"Usia"<<setw(2)
        <<"|"<<" Biaya"<<setw(17)
        <<"|"<<" Asal Negara"<<setw(8)<<"|"<<endl;
    cout<<"+"<<setfill('-')<<setw(7)<<"+"<<setw(15)<<"+"<<setw(15)<<"+"<<setw(6)<<"+"<<setw(23)<<"+"<<setw(20)<<"+"<<endl;
    while(show!=NULL){
        cout<<setfill(' ');
        cout<<"| "<<show->data[0]<<setw(6-show->data[0].length())
            <<"|"<<show->data[1]<<setw(15-show->data[1].length())
            <<"|"<<show->data[2]<<setw(15-show->data[2].length())
            <<"|"<<show->data[3]<<setw(6-show->data[3].length())
            <<"|"<<"Rp."<<show->data[4]<<setw(20-show->data[4].length())
            <<"|"<<show->data[5]<<setw(20-show->data[5].length())<<"|";
        cout<<endl;
        show = show->next;
    }
    cout<<"+"<<setfill('-')<<setw(7)<<"+"<<setw(15)<<"+"<<setw(15)<<"+"<<setw(6)<<"+"<<setw(23)<<"+"<<setw(20)<<"+"<<endl;
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
int cariData(string caridata, string idname){
    
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

//fungsi penambahan
void tambahDataDepan(string row[]){

    NodePemilih *baru = new NodePemilih;
    NodeID *pemilihID = kumpulanID;

    baru->data[0] = row[0]; //id misal: DKI01234
    string tipeid = ambilTipeID(row[0]); //DKI, JT, JB, dsb

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

}


void tambahDataTengah(string row[], string dataid, string idname){
    //dataid = data yang menjadi acuan user
    //idname = id dimana data tersebut berada
    //data akan disisipkan sebelum data dengan id 'dataid'
    if(cariData(dataid,idname)==0){
        cout<<"Data pemilih dengan id "<<dataid<<" tidak ditemukan!"<<endl;
        return;
    }
    else{
        NodePemilih *baru = new NodePemilih;
        baru->data[0] = row[0]; //id misal: DKI01234
        string tipeid = ambilTipeID(row[0]); //DKI, JT, JB, dsb

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
        if(dataid == ID->dataPemilih->data[0]){
            tambahDataDepan(row);
            return;
        }

        NodePemilih *bantu = ID->dataPemilih;
        while(bantu->data[0]!=dataid){
            bantu = bantu->next;
        }
        bantu->prev->next = baru;
        baru->next = bantu;
        bantu->prev = baru;

        //jika yang menjadi data acuan adalah tail
        //maka sambungkan tail dengan data baru
        if(bantu = ID->dataAkhir){
            ID->dataAkhir->prev = baru;
            baru->next = ID->dataAkhir;
        }
    }
}

void tambahDataBelakang(string row[]){
    NodePemilih *baru = new NodePemilih;
    NodeID *pemilihID = kumpulanID;
    baru->data[0] = row[0]; //id misal: DKI01234
    string tipeid = ambilTipeID(row[0]); //DKI, JT, JB, dsb

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

void hapusDataTengah(string idname, string dataid){
    if(cariData(dataid, idname)== 0){
        cout<<"Data pemilih dengan id "<<dataid<<" tidak ditemukan!"<<endl;
        return;        
    }
    else{
        NodeID *ID = dapatkanNodeID(idname);
        //kalau data yang ingin dihapus ada di depan, alihkan ke fungsi hapusDataDepan
        if(dataid == ID->dataPemilih->data[0]){
            hapusDataDepan(idname);
            return;
        }

        //kalau data yang ingin dihapus ada di belakang, alihkan ke fungsi hapusDataBelakang
        if(dataid == ID->dataAkhir->data[0]){
            hapusDataBelakang(idname);
            return;
        }

        NodePemilih *bantu = ID->dataPemilih;
        while(bantu->data[0]!=dataid){
            bantu = bantu->next;
        }

        NodePemilih *hapus = bantu;
        bantu->next->prev = bantu;
        bantu->prev->next = bantu->next;
        delete hapus;
        
        //kaitkan tail dengan data sebelumnya jika tail berada setelah data yang akan dihapus
        if(bantu->next == ID->dataAkhir){
            bantu->next = ID->dataAkhir;
            ID->dataAkhir->prev = bantu;
        }
    }
}
//////////////--------End Of KELOLA NodePemilih--------//////////////

//hapus SEMUA data
void hapusSemua(){
    while(kumpulanID!=NULL){
        hapusID(kumpulanID->id);
    }
}

void baca_file(){
    fstream report;
    report.open("dataSurveyPemilu.csv", ios::in);
    
    string line, word;

    while(getline(report, line)){
        string row[20]; int rowIndex=0;
        istringstream iss(line);

        while(getline(iss, word, ';')){
            row[rowIndex]=word;
            rowIndex++;
        }
        tambahDataBelakang(row);
    }
}

int main(){
    baca_file();
    
    
    tampilkan();

}
