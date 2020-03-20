#include <iostream>
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

void tampilkan(){
    if(kumpulanID == NULL){
        cout<<"Tidak ada data untuk ditampilkan!"<<endl;
    }
    else{

        NodeID *showID = kumpulanID;
        while(showID!=NULL){
            NodePemilih *show = showID->dataPemilih;
             while(show!=NULL){
                
                cout<<"Pasien No."<<show->data[0]<<endl;
                cout<<"Nama: "<<show->data[1]<<endl;
                cout<<"Diagnosa: "<<show->data[2]<<endl;
                cout<<"Usia: "<<show->data[3]<<endl;
                cout<<"Biaya Pengobatan: Rp."<<show->data[4]<<endl;
                cout<<"Negara Kunjungan: "<<show->data[5]<<endl;
                cout<<endl;
                show = show->next;
            }
            showID = showID->next;
        }
    }
}

//kelola NodeID

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

void tambahDataBelakang(string row[]){
    NodePemilih *baru = new NodePemilih;
    NodeID *pemilihID = kumpulanID;
    baru->data[0] = row[0];
    baru->data[1] = row[1];
    baru->data[2] = row[2];
    baru->data[3] = row[3];
    baru->data[4] = row[4];
    baru->data[5] = row[5];
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
        string row[6]; int rowIndex=0;
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
    
    hapusSemua();
    tampilkan();
}