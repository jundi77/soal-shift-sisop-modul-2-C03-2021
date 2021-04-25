# Penjelasan Soal Shift SISOP Modul 2
## Anggota Kelompok
1. Ega Prabu Pamungkas (05111940000014)
2. A. Zidan Abdillah Majid (05111940000070)
3. Jundullah Hanif Robbani (05111940000144)

## Soal 1

## Soal 2

## Soal 3
Pada soal ini terdapat 5 permasalahan yang perlu dikerjakan. Sebelum itu, soal nomor 3 ini harus dikerjakan dengan mengubah proses menjadi daemon terlebih dahulu karena program ini akan dikerjakan menggunakan 2 metode dimana program akan berjalan di latar belakang.
1. Membuat direktori dengan nama waktu saat itu juga **[tahun-bulan-tanggal_jam:menit:detik]** dengan selang 40 detik.
⋅⋅⋅Waktu saat membuat direktori dapat diambil dengan menggunakan library `**time.h**`. Setelah itu, dapat membuat direktori dengan membuat sub-proses terlebih dahulu dan menggunakan `execv` untuk memanggil `mkdir`. Program utama lalu melakukan `sleep(40)` agar directory selanjutnya dibuat tepat 40 detik setelahnya.

[Gambar mengambil waktu saat ini]
[Gambar membuat direktori]

2. Mendownload 10 gambar di https://picsum.photos/ dengan bentuk foto persegi dan ukurannya `**(n%1000)+50**` dimana **n** adalah waktu Epoch Unix dalam detik saat itu dengan selang 5 detik.
⋅⋅⋅Untuk membuat bentuk foto persegi cukup menambahkan satu bilangan setelah url sesuai dengan petunjuk di website tersebut. Mengambil waktu Epoch Unix dalam detik dapat menggunakan library `**time.h**` seperti pada gambar di bawah. Looping untuk mendownload juga dapat dilakukan menggunakan lopping biasa dan memanggil sub-proses di dalam looping tersebut. Mendownload juga dilakukan dengan `execv` memanggil `wget` dengan option `-O (nama_file)` dimana nama filenya **[tahun-bulan-tanggal_jam:menit:detik]** saat mendownload gambar tersebut, nama itu juga dapat dibuat dengan cara yang sama seperti nomor 1. Sebelum loop berlanjut, dilakukan `sleep(5)` agar foto yang didownload akan tepat 5 detik setelah foto sebelumnya terdownload.

[Gambar mengambil waktu saat ini]
[Gambar Looping]

3. Membuat file **status.txt** berisi kalimat _Download Success_ lalu dilakukan Caesar Chiper +5. Yang terakhir meletakkan folder tersebut di sebuah zip dan menghapus folder sehingga yang tersisa tinggal file zip.
⋅⋅⋅Untuk membuat file **status.txt** memakai tipe data `FILE` lalu `fopen` dengan opsi `w+` untuk membuat file baru dan menuliskan ke file baru tersebut. Caesar cipher dapat dilakukan dengan menggunakan kode seperti gambar dibawah. Setelah dienkripsi, dapat dituliskan ke dalam file menggunakan `fputs` dan jangan lupa di-close dengan `fclose`. Untuk melakukan kompress zip dengan membuat sub-proses `execv` dan `zip` lalu menghapus folder dengan `execv` dan `rm -r`.

[Gambar Caesar Cipher]
[Gambar membuat file txt]
[Gambar zip folder]

4. Membuat program **Killer** untuk mematikan program yang berjalan di latar belakang.
5. Membuat program berjalan dua mode `-z` atau `-x` dimana `-z` membuat program **Killer** untuk mematikan seluruh proses sekaligus, sedangkan `-x` membuat program **Killer** menunggu hasil download selesai terlebih dahulu lalu dimatikan prosesnya.
⋅⋅⋅Membuat program **Killer** dilakukan dengan menggunakn `FILE` sama seperti membuat **status.txt**. Untuk program **Killer** `-z` dilakukan dengan memanfaatkan `killall` dan dilanjuti nama program yang berjalan, untuk kasus ini adalah `soal3`. Sedangkan `-x` dapat dilakukan dengan memanggil `kill -9` lalu diikuti pid dari proses yang didapat dengan memanggil `getpid()`. Untuk pembuatan **Killer** dilakukan sebelum proses utama berjalan.

[Gambar mengecek mode]
[Gambar membuat killer]

#### Kendala saat mengerjakan
Sempat tidak berjalan `execv` untuk memanggil `wget` dimana file yang terdownload tidak lengkap. Menduga karena semua STD ditutup makanya mengalihkan STD ke `/dev/null` dengan menggunakan `fd` dan `dup2`, dengan begitu program utama dapat berjalan dengan lancar.