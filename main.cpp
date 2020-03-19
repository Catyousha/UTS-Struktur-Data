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
    struct NodePemilih *dataAkhir;
    struct NodeID *next;
};

NodeID *kumpulanID = NULL; //Kumpulan NodeID
NodeID *IDAkhir = NULL; //tail pada node kumpulanID

int cekKosong(NodeID *h){
    if(h == NULL){
        return 1;
    }
    return 0;
}

void tampilkan(NodeID *h){
    if(cekKosong(h)){
        cout<<"Tidak ada data untuk ditampilkan!"<<endl;
    }
    else{

        NodeID *showID = h;
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

//cari suatu ID
NodeID *temukanID(string idname){
    NodeID *d = kumpulanID;
    while(d!=NULL){
        if(d->id == idname){
            return d;
        }
        d = d->next;
    }
    tambahID(idname);
    return temukanID(idname);
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

    if(cekKosong(kumpulanID)){
        tambahID(row[5]);
        pemilihID = temukanID(row[5]);
        
        pemilihID->dataPemilih = baru;
        pemilihID->dataAkhir = pemilihID->dataPemilih;
        pemilihID->dataPemilih->next = NULL;

    }
    else{
        pemilihID = temukanID(row[5]);
//        pemilihID->dataPemilih->prev = baru;
        baru->next = pemilihID->dataPemilih;
        
        pemilihID->dataPemilih = baru;
        pemilihID->dataPemilih->prev = NULL;
    }

}
/*
void tambahDataBelakang(string row[]){
    NodePemilih *baru = new NodePemilih;
    baru->data[0] = row[0];
    baru->data[1] = row[1];
    baru->data[2] = row[2];
    baru->data[3] = row[3];
    baru->data[4] = row[4];
    baru->data[5] = row[5];
    baru->prev = NULL;
    baru->next = NULL;

    if(cekKosong(list)){
        list = baru;
        tail = list;
    }
    else{
        baru->prev = tail;
        tail->next = baru;
        tail = baru;
    }
}

void hapusDataDepan(){
    if(cekKosong(list)){
        cout<<"Tidak ada data untuk dihapus!"<<endl;
        return;
    }

    if(list->next == NULL){
        list = NULL;
        tail = NULL;
    }
    else{
        NodePemilih *hapus = new NodePemilih;
        hapus = list;
        list = list->next;
        delete hapus;
    }
}

void hapusDataBelakang(){
    if(cekKosong(list)){
        cout<<"Tidak ada data untuk dihapus!"<<endl;
    }

    if(list->next == NULL){
        list = NULL;
        tail = NULL;
    }
    else{
        NodePemilih *hapus = new NodePemilih;
        hapus = tail;
        tail = tail->prev;
        tail->next = NULL;
        delete hapus;
    }
}

void hapusSemua(){
    while(!cekKosong(list)){
        hapusDataDepan();
    }
}
*/
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
        tambahDataDepan(row);
    }
}

int main(){
    baca_file();
    
    tampilkan(kumpulanID);
}