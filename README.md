# UTS-Struktur-Data

Jaka Asa Baldan Ahmad (190535646020)

Syahrieza Ilham Noor Fauzi (190535646058)

Winaldo Dwi Putra Laua (190535646057)

 Tentang Program
----------------
                                                  
   Survey Corps adalah kelompok yang bertugas untuk mensurvei pilihan masyarakat menjelang pemilu. Anggotanya tersebar ke seluruh pelosok negeri demi mendapatkan data. Oleh karena kelompok ini masih cukup kecil, dalam penyurveiannya mereka meminta donasi seikhlasnya. Setelah berbulan-bulan lamanya, akhirnya mereka mendapat banyak data yang terangkum dalam file csv. Adapun tujuan dari program ini ialah untuk mengelola hasil survey dari kelompok Survey Corps.
   
  
  Struktur Data Program
-----------------------

   Program ini kami buat dengan memanfaatkan struktur data array dan linked list. Kami mencoba menerapkan dua linked list dalam satu program di mana terdiri dari singly linked list dan doubly linked list. Singly linked list kami gunakan untuk alat bantu loncatan, sehingga ketika program menelusuri data tidak harus melakukan looping dari head sampai dengan tail. Sementara doubly linked list kami gunakan sebagai untaian data utama. Array digunakan sebagai field dalam kolom.


   Data pemilih yang dikelola dalam program ini dibagi berdasarkan jenisnya yang kemudian akan disebut sebagai ID. Contohnya, pemilih dengan asal Jakarta diberikan ID DKI sementara pemilih dengan asal provinsi Jawa Timur diberikan ID JT. Oleh karena data ID saling berurutan, kami implementasikan struktur data Singly Linked List yang tiap node-nya memiliki data-data pemilih. Data-data pemilih dengan ID yang sama akan saling dikaitkan dalam struktur data Doubly Linked List. Sedangkan untuk field yang ada seperti id pemilih, nama pemilih, asal kota, jenis kelamin, pilihan paslon, dan jumlah donasi akan disimpan dalam sebuah struktur data array.
   
Secara garis besar, arsitektur dari program ini dapat digambarkan sebagai berikut:
![Gambar dapat dilihat di [https://i.imgur.com/8DtyAnn.png](https://i.imgur.com/8DtyAnn.png)](https://i.imgur.com/8DtyAnn.png)
Gambar dengan resolusi lebih jelas dapat dilihat di https://i.imgur.com/8DtyAnn.png
