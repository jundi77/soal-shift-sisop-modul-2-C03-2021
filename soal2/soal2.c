#include <string.h> // untuk strtok


#define DEBUG
#define HOMEDIR ~
#define zipdir pets.zip

int main()
{
    /**
     * - extract zip
     * - hapus folder yang tidak dipakai
     * - ambil semua nama file, simpan di array
     * - simpan banyak file, inisialisasi variabel untuk counter file yang berhasil diparse
     * - loop semua nama file, per loop deploy child untuk memparsing namanya, simpan banyak file yang akan diparse di parent
     *   (child)
     *   - pakai strtok dengan delimiter '_' untuk setiap nama agar dapat
     *     memparse string yang berkaitan dengan peliharaan lain, lalu pakai
     *     strtok dengan delimiter ':', lalu sesuaikan format
     *     [jenis peliharaan]:[nama peliharaan]:[umur peliharaan dalam tahun]
     *     untuk diambil datanya
     *   - copy file ke folder jenis peliharaan, lalu rename jadi nama peliharaan
     *   - hapus file
     *   - masukkan nama peliharaan dan umurnya ke file keterangan.txt di setiap folder jenis peliharaan sesuai format di docs
     *   - increment counter file
     * - (parent, setelah loop, child async) while(counter belum sampai banyak file), infinite loop nunggu sampai childnya selesai semua
     * - exit
     * 
     * menggunakan fork dan exec
     * tidak boleh pakai system(), mkdir(), dan rename()
     */
}