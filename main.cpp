#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Node{
    string data[6];
    struct Node *next;
    struct Node *prev;
};

Node *list = NULL; //NODE UTAMA
Node *tail = NULL; //ekor

int cekKosong(Node *h){
    if(h == NULL){
        return 1;
    }
    return 0;
}
void tampilkan(Node *h){
    if(cekKosong(h)){
        cout<<"Tidak ada data untuk ditampilkan!"<<endl;
    }
    else{
        Node *show = h;
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
    Node *baru = new Node;
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
    Node *baru = new Node;
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

void baca_file(){
    fstream report;
    report.open("contohdatauts.csv", ios::in);
    
    //vector<string>row;
    string line, word, temp;

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
    tampilkan(list);
}