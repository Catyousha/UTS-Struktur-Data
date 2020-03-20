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
        while(showID!=NULL){
            NodePemilih *show = showID->dataPemilih;
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
            showID = showID->next;
        }
        
        cout<<"+"<<setfill('-')<<setw(7)<<"+"<<setw(15)<<"+"<<setw(15)<<"+"<<setw(6)<<"+"<<setw(23)<<"+"<<setw(20)<<"+"<<endl;
    }
}


//KELOLA NodeID
//tambah data di belakang NodeID
void tambahID(string idname){
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

//pencarian
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

//cari suatu ID, jika ketemu maka kembalikan node id tersebut
NodeID *dapatkanNodeID(string idname){
    NodeID *d = kumpulanID;
    while(d!=NULL){
        if(d->id == idname){
            return d;
        }
        d = d->next;
    }
}

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

//hapus ID
//temukan idname kemudian hapus node yang mengandung idname tersebut
void hapusID(string idname){
    if(temukanID(idname) == 1){
        
        //jika id yang dihapus ialah id pertama
        if(kumpulanID->id == idname){
            NodeID *hapus = kumpulanID;
            kumpulanID = kumpulanID->next;
            delete hapus;
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
        return;
    }
}

//KELOLA NodePemilih
//fungsi pencarian dengan asumsi id ada.
int cariData(string caridata, string idname){
    NodeID *ID = dapatkanNodeID(idname);
    while(ID->dataPemilih->data[0]!=caridata and ID->dataPemilih!=NULL){
        ID->dataPemilih = ID->dataPemilih->next;
    }
    if(ID->dataPemilih==NULL){
        return 0;
    }
    else{
        return 1;
    }
}

//fungsi penambahan
void tambahDataDepan(string row[]){

    NodePemilih *baru = new NodePemilih;
    NodeID *pemilihID = kumpulanID;
    baru->data[0] = row[0];
    baru->data[1] = row[1];
    baru->data[2] = row[2];
    baru->data[3] = row[3];
    baru->data[4] = row[4];
    baru->data[5] = row[5]; //asal

    baru->prev = NULL;
    baru->next = NULL;
    
    if(temukanID(row[5]) == 0){
        tambahID(row[5]);
    }
    pemilihID = dapatkanNodeID(row[5]);
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

//dataid = data yang menjadi acuan user
//idname = id dimana data tersebut berada
//data akan disisipkan sebelum data dengan id 'dataid'
void tambahDataTengah(string row[], string dataid, string idname){
    if(cariData(dataid,idname)==0){
        cout<<"Data pemilih dengan id "<<dataid<<" tidak ditemukan!"<<endl;
        return;
    }
    else{
        NodeID *ID = dapatkanNodeID(idname);
        //kalau data acuan berada didepan, maka alihkan ke fungsi tambah depan
        if(dataid == ID->dataPemilih->data[0]){
            tambahDataDepan(row);
            return;
        }

        NodePemilih *baru = new NodePemilih;
        baru->data[0] = row[0];
        baru->data[1] = row[1];
        baru->data[2] = row[2];
        baru->data[3] = row[3];
        baru->data[4] = row[4];
        baru->data[5] = row[5]; //asal

        baru->prev = NULL;
        baru->next = NULL;

        while(ID->dataPemilih->data[0]!=dataid){
            ID->dataPemilih = ID->dataPemilih->next;
        }
        ID->dataPemilih->prev->next = baru;
        baru->next = ID->dataPemilih;
        ID->dataPemilih->prev = baru;
    }
}

void tambahDataBelakang(string row[]){
    NodePemilih *baru = new NodePemilih;
    NodeID *pemilihID = kumpulanID;
    baru->data[0] = row[0];
    baru->data[1] = row[1];
    baru->data[2] = row[2];
    baru->data[3] = row[3];
    baru->data[4] = row[4];
    baru->data[5] = string(row[5]);
    baru->prev = NULL;
    baru->next = NULL;
    
    if(temukanID(row[5]) == 0){
        tambahID(row[5]);
    }
    pemilihID = dapatkanNodeID(row[5]);
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

//hapus SEMUA data
void hapusSemua(){
    while(kumpulanID!=NULL){
        hapusID(kumpulanID->id);
    }
}

void baca_file(){
    fstream report;
    report.open("contohdatauts.csv", ios::in);
    
    string line, word;

    while(getline(report, line)){
        string row[7]; int rowIndex=0;
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
    
    
    tampilkanDataId("Inggris");
}