#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Node{
    string data[4];
    struct Node *next;
    struct Node *prev;
};

Node *tail = NULL;

void tambahDataDepan(Node *h, vector<string>&row){
    Node *baru = new Node;
    baru->data[0] = row[0];
    baru->data[1] = row[1];
    baru->data[2] = row[2];
    baru->data[3] = row[3];
    baru->data[4] = row[4];
    baru->prev = NULL;
    baru->next = NULL;

}

void baca_file(){
    fstream report;
    report.open("contohdatauts.csv", ios::in);
    
    vector<string>row;
    string line, word, temp;

    while(getline(report, line)){
        row.clear();
        istringstream iss(line);

        while(getline(iss, word, ';')){
            row.push_back(word);
        }
        string biaya = row[4];
        biaya.erase(std::remove(biaya.begin(),biaya.end(),'\"'),biaya.end()); //hapus tanda kutip di data bapaknya
            cout<<"Pasien No."<<stoi(row[0])<<endl;
            cout<<"Nama: "<<row[1]<<endl;
            cout<<"Diagnosa: "<<row[2]<<endl;
            cout<<"Usia: "<<stoi(row[3])<<endl;
            cout<<"Biaya Pengobatan: Rp."<<biaya<<endl;
            cout<<"Negara Kunjungan: "<<row[5]<<endl;
            cout<<endl;
        
    }
}

int main(){
    Node *list = NULL;
    baca_file();
}