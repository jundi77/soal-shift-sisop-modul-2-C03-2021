# Penjelasan Soal Shift SISOP Modul 2
## Anggota Kelompok
1. Ega Prabu Pamungkas (05111940000014)
2. A. Zidan Abdillah Majid (05111940000070)
3. Jundullah Hanif Robbani (05111940000144)

## Soal 1
a. Dalam soal a kami menggunakan 'fork()' pada setiap variabel 'qid'. Kemudian Untuk membuat folder Musyik, Fylm, dan Pyoto kami menggunakan command mkdir dan fungsi execv() untuk menjalankannya

## Soal 2
Alur program yang dirancang untuk nomor 2 sebagai jawaban kami adalah:
1. Membuat folder `modul2` di `$HOME`, menggunakan `mkdir`, lalu `chdir` ke folder modul2.
2. `unzip` `pets.zip` ke folder `modul2`.
3. Hapus folder yang tidak diperlukan di folder `modul2` (hasil ekstrak `pets.zip`), , listing folder menggunakan `find` dengan argumen `-d`, dan penghapusan menggunakan `rm` dengan argumen `-rf`.
4. Membuat folder `petshop` di dalam folder `modul2` menggunakan `mkdir`.
5. Menyimpan list nama-nama file yang akan dipindah, listing file menggunakan `find` dengan argumen `-f`.
6. Nama file diparsing menggunakan `strtok`:
   1. Yang pertama adalah pemisahan string dengan karakter `_` yang menandakan terdapat hewan yang berbeda di dalam gambar, sebab file perlu disalin sebanyak banyak hewan yang ada di gambar.
   2. Untuk setiap string data hewan, lakukan:
      1. Pemisahan data-data string dengan karakter `;`, kemudian ambil data jenis, nama, dan umur hewan.
      2. Membuat folder jenis peliharaan di dalam folder `petshop`.
      3. Menambahkan nama dan umur peliharaan ke file `keterangan.txt` di dalam folder jenis peliharaan.
      4. Menyalin file gambar ke dalam folder jenis peliharaan dengan penamaan baru menggunakan `cp`.
   3. Hapus file gambar menggunakan `rm`.
7. Program selesai.

Dalam pengerjaan, `find` digunakan untuk listing direktori ketimbang `ls` disebabkan adanya error yang sulit dicari penyebabnya saat menggunakan `ls`. Untuk transfer data hasil output child ke parent, misal dalam transfer output `find`, digunakan fungsi `pipe` untuk menyambungkan antara child dan parent, lalu digunakan `dup2` untuk mengalihkan output ke `pipe`.

| ![image](https://user-images.githubusercontent.com/40772378/115982884-62872b80-a5c8-11eb-8869-434fedb0a53a.png) | 
|:--:| 
| *Program sedang berjalan, `mkdir` terlihat mengeluarkan pesan bahwa folder jenis hewan telah dibuat* |

Saat pengerjaan, debugging menggunakan visual studio code tidak memberikan cara debug child-child proses yang berjalan, sehingga memberikan tantangan tersendiri untuk debugging bug dan error yang ada.

| ![debugging dengan vscode](https://user-images.githubusercontent.com/40772378/115982729-77af8a80-a5c7-11eb-8854-accab7466900.png) | 
|:--:| 
| *Debugging menggunakan vscode* |

## Soal 3
Pada soal ini terdapat 5 permasalahan yang perlu dikerjakan. Sebelum itu, soal nomor 3 ini harus dikerjakan dengan mengubah proses menjadi daemon terlebih dahulu karena program ini akan dikerjakan menggunakan 2 metode dimana program akan berjalan di latar belakang.
1. Membuat direktori dengan nama waktu saat itu juga **[tahun-bulan-tanggal_jam:menit:detik]** dengan selang 40 detik.

   Waktu saat membuat direktori dapat diambil dengan menggunakan library `**time.h**`. Setelah itu, dapat membuat direktori dengan membuat sub-proses terlebih dahulu dan menggunakan `execv` untuk memanggil `mkdir`. Program utama lalu melakukan `sleep(40)` agar directory selanjutnya dibuat tepat 40 detik setelahnya.
   
   ![mkdir](https://user-images.githubusercontent.com/68368240/115980362-6742e400-a5b6-11eb-83af-559198b60e61.png "Membuat direktori")

2. Mendownload 10 gambar di https://picsum.photos/ dengan bentuk foto persegi dan ukurannya `**(n%1000)+50**` dimana **n** adalah waktu Epoch Unix dalam detik saat itu dengan selang 5 detik.

   Untuk membuat bentuk foto persegi cukup menambahkan satu bilangan setelah url sesuai dengan petunjuk di website tersebut. Mengambil waktu Epoch Unix dalam detik dapat menggunakan library `**time.h**` seperti pada gambar di bawah. Looping untuk mendownload juga dapat dilakukan menggunakan lopping biasa dan memanggil sub-proses di dalam looping tersebut. Mendownload juga dilakukan dengan `execv` memanggil `wget` dengan option `-O (nama_file)` dimana nama filenya **[tahun-bulan-tanggal_jam:menit:detik]** saat mendownload gambar tersebut, nama itu juga dapat dibuat dengan cara yang sama seperti nomor 1. Sebelum loop berlanjut, dilakukan `sleep(5)` agar foto yang didownload akan tepat 5 detik setelah foto sebelumnya terdownload.

   ![loop](https://user-images.githubusercontent.com/68368240/115980416-cbfe3e80-a5b6-11eb-8df4-702f8e8d3b47.png "Looping Download Foto")

3. Membuat file **status.txt** berisi kalimat _Download Success_ lalu dilakukan Caesar Chiper +5. Yang terakhir meletakkan folder tersebut di sebuah zip dan menghapus folder sehingga yang tersisa tinggal file zip.

   Untuk membuat file **status.txt** memakai tipe data `FILE` lalu `fopen` dengan opsi `w+` untuk membuat file baru dan menuliskan ke file baru tersebut. Caesar cipher dapat dilakukan dengan menggunakan kode seperti gambar dibawah. Setelah dienkripsi, dapat dituliskan ke dalam file menggunakan `fputs` dan jangan lupa di-close dengan `fclose`. Untuk melakukan kompress zip dengan membuat sub-proses `execv` dan `zip` lalu menghapus folder dengan `execv` dan `rm -r`.

   ![caesar_cipher](https://user-images.githubusercontent.com/68368240/115980426-dfa9a500-a5b6-11eb-85d4-0610b35aebdb.png "Caesar Cipher)
   
   ![status](https://user-images.githubusercontent.com/68368240/115980432-e3d5c280-a5b6-11eb-82f8-940cad921627.png "status.txt")
   
   ![zip](https://user-images.githubusercontent.com/68368240/115980436-e9cba380-a5b6-11eb-86f9-1ceffcab6ec2.png "zip folder")
   
   ![rm](https://user-images.githubusercontent.com/68368240/115980437-eb956700-a5b6-11eb-9caa-30c1e8c86025.png "menghapus folder")


4. Membuat program **Killer** untuk mematikan program yang berjalan di latar belakang.
5. Membuat program berjalan dua mode `-z` atau `-x` dimana `-z` membuat program **Killer** untuk mematikan seluruh proses sekaligus, sedangkan `-x` membuat program **Killer** menunggu hasil download selesai terlebih dahulu lalu dimatikan prosesnya.

   Membuat program **Killer** dilakukan dengan menggunakn `FILE` sama seperti membuat **status.txt**. Untuk program **Killer** `-z` dilakukan dengan memanfaatkan `killall` dan dilanjuti nama program yang berjalan, untuk kasus ini adalah `soal3`. Sedangkan `-x` dapat dilakukan dengan memanggil `kill -9` lalu diikuti pid dari proses yang didapat dengan memanggil `getpid()`. Untuk pembuatan **Killer** dilakukan sebelum proses utama berjalan.

   ![mode](https://user-images.githubusercontent.com/68368240/115980449-049e1800-a5b7-11eb-9de8-7a9de9a0e060.png "Mengecek Mode")
   
   ![mode2](https://user-images.githubusercontent.com/68368240/115980452-09fb6280-a5b7-11eb-8136-abf6398455aa.png "Mengecek Mode")
   
   ![make_killer](https://user-images.githubusercontent.com/68368240/115980454-0cf65300-a5b7-11eb-8a47-3afd41f131df.png "Membuat Killer.sh")

### Kendala saat mengerjakan
Sempat tidak berjalan `execv` untuk memanggil `wget` dimana file yang terdownload tidak lengkap. Menduga karena semua STD ditutup makanya mengalihkan STD ke `/dev/null` dengan menggunakan `fd` dan `dup2`, dengan begitu program utama dapat berjalan dengan lancar.

![fd](https://user-images.githubusercontent.com/68368240/115980487-59419300-a5b7-11eb-8e57-f25403009c2e.png "Mengalihkan STDs ke /dev/null")
