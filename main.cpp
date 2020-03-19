#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Pemilih{
    string data[6];
    struct Pemilih *next;
    struct Pemilih *prev;
};
struct ID{
    string id;
    struct Pemilih *daftarOrang;
    struct ID *next;
};

Pemilih *list = NULL; //Pemilih UTAMA
Pemilih *tail = NULL; //ekor

int cekKosong(Pemilih *h){
    if(h == NULL){
        return 1;
    }
    return 0;
}
void tampilkan(Pemilih *h){
    if(cekKosong(h)){
        cout<<"Tidak ada data untuk ditampilkan!"<<endl;
    }
    else{
        Pemilih *show = h;
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
    }
}

void tambahDataDepan(string row[]){
    Pemilih *baru = new Pemilih;
    baru->data[0] = row[0];
    baru->data[1] = row[1];
    baru->data[2] = row[2];
    baru->data[3] = row[3];
    baru->data[4] = row[4];
    baru->data[5] = row[5];
    baru->prev = NULL;
    baru->next = NULL;

    if(cekKosong(list)){
        list=baru;
        tail=list;
    }
    else{
        baru->next = list;
        list = baru;
        list->prev = NULL;
    }

}

void tambahDataBelakang(string row[]){
    Pemilih *baru = new Pemilih;
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
        Pemilih *hapus = new Pemilih;
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
        Pemilih *hapus = new Pemilih;
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
    hapusDataDepan();
    hapusDataBelakang();
    tampilkan(list);
}