#include <iostream>
#include <cctype>
#include <sstream> // manipulasi string
#include <fstream> // manipulasi file
#include <vector> // array dinamis
#include <algorithm> // Erase, Remove
#include <iomanip> // setw

using namespace std;

// Struct
// Data User
struct user_data{
    string username;
    string password;
    string telepon;
    string address;
};
// Data Motor
struct motor_data{
    string owner;
    string nama_motor;
    string warna_motor;
    string transmisi;
    string plat;
    int jarak_tempuh;
    bool servis;
};
struct kondisi_manual{
    string plat;
    int ban_belakang;
    int ban_depan;
    int busi;
    int gear;
    int kampas_kopling;
    int kampas_rem;
    int minyak_rem;
    int oli_mesin;
    int rantai;
};
struct kondisi_automatic{
    string plat;
    int ban_belakang;
    int ban_depan;
    int busi;
    int kampas_rem;
    int minyak_rem;
    int oli_gardan;
    int oli_mesin;
    int roller;
    int van_belt;
};

// Data Servis dan Struk
struct servis_data{
    string nama_servis;
    int harga_servis;
};
struct struk_servis{
    int id;
    string username;
    string plat;
    string status_servis;
    string status_akun;
    vector<servis_data> servis;
};

// Data Sparepart dan Struk
struct sparepart_data{
    string nama_sparepart;
    string tipe_transmisi;
    int harga_sparepart;
    int kilometer;
    int stok_sparepart;
};
struct sparepart_pesanan{
    string nama_sparepart;
    int jumlah;
    int harga;
};
struct struk_sparepart{
    int id;
    string username;
    string telepon;
    string address;
    string status_akun;
    vector<sparepart_pesanan> pesanan;
};

// Variabel Global:
vector<user_data> data_user;
vector<motor_data> data_motor;
vector<kondisi_manual> data_kondisi_manual;
vector<kondisi_automatic> data_kondisi_automatic;
vector<struk_servis> data_struk_servis;
vector<struk_sparepart> data_struk_sparepart;
vector<sparepart_data> data_list_sparepart;

void clear(){ // Membersihkan layar
    system("cls");
    return;
}
void pause(){ // Program lanjut setelah user menekan tombol apapun
    system("pause");
    return;
}


// Pengelolaan CSV <-> Vektor
void read_csv_user(){ // membersihkan data vektor dan membaca data csv user ke dalam vektor
    data_user.clear();
    ifstream file;
    file.open("Database/user_log.csv");
    if (!file) {
        cout << "Gagal membaca data user (user_log.csv)" << endl;
        pause();
        return;
    }
    string baris, data;
    getline(file, baris); // skip header
    while(getline(file, baris)){
        stringstream ss(baris);
        user_data temp;
        getline(ss, temp.username, ',');
        getline(ss, temp.password, ',');
        getline(ss, temp.telepon, ',');
        getline(ss, temp.address, '\n');
        data_user.push_back(temp);
    }
    file.close();
    return;
}
void write_csv_user(){ // menulis data user kembali ke file user_log.csv
    ofstream file;
    file.open("Database/user_log.csv");
    if (!file) {
        cout << "Gagal membaca data user (user_log.csv)" << endl;
        pause();
        return;
    }
    file << "Username,Password,nomor telepon,Address" << endl;
    for (int i = 0; i < data_user.size(); i++){
        file << data_user[i].username << "," << data_user[i].password << "," << data_user[i].telepon << "," << data_user[i].address << endl;
    }
    file.close();
    return;
}

void read_csv_motor(){// Membaca csv motor, list_motor.csv, kondisi_motor_manual.csv, kondisi_motor_automatic.csv
    data_motor.clear();
    ifstream file;
    file.open("Database/list_motor.csv");
    if (!file) {
        cout << "Gagal membaca data motor (list_motor.csv)" << endl;
        pause();
        return;
    }
    string baris, data, servis;
    getline(file, baris); // skip header
    // membaca data motor dari csv ke vektor
    while(getline(file, baris)){
        stringstream ss(baris);
        motor_data temp;
        // Data motor bertipe data string
        getline(ss, temp.owner, ',');
        getline(ss, temp.nama_motor, ',');
        getline(ss, temp.warna_motor, ',');
        getline(ss, temp.transmisi, ',');
        getline(ss, temp.plat, ',');
        // Jarak tempuh tipe data integer
        ss >> temp.jarak_tempuh;
        ss.ignore();
        // servis tipe data boolean
        getline(ss, servis, '\n');
        if (servis == "true"){
            temp.servis = true;
        }
        else{
            temp.servis = false;
        }
        data_motor.push_back(temp);
    }
    file.close();

    // membaca data csv kondisi motor manual ke vektor
    data_kondisi_manual.clear();
    file.open("Database/kondisi_motor_manual.csv");
    if (!file) {
        cout << "Gagal membaca data kondisi motor manual (kondisi_motor_manual.csv)" << endl;
        pause();
        return;
    }
    getline(file, baris); // skip header
    // membaca data kondisi motor manual dari csv ke vektor
    while(getline(file, baris)){
        stringstream ss(baris);
        kondisi_manual temp;
        // memisahkan data dengan pembatas koma
        getline(ss, temp.plat, ',');
        ss >> temp.ban_belakang; // memasukkan data ke dalam struct
        ss.ignore(); // ignore koma
        ss >> temp.ban_depan;
        ss.ignore();
        ss >> temp.busi;
        ss.ignore();
        ss >> temp.gear;
        ss.ignore();
        ss >> temp.kampas_kopling;
        ss.ignore();
        ss >> temp.kampas_rem;
        ss.ignore();
        ss >> temp.minyak_rem;
        ss.ignore();
        ss >> temp.oli_mesin;
        ss.ignore();
        ss >> temp.rantai;
        data_kondisi_manual.push_back(temp);
    }
    file.close();

    // membaca data csv kondisi motor automatic ke vektor
    data_kondisi_automatic.clear();
    file.open("Database/kondisi_motor_automatic.csv");
    if (!file) {
        cout << "Gagal membaca data kondisi motor automatic (kondisi_motor_automatic.csv)" << endl;
        pause();
        return;
    }
    getline(file, baris); // skip header
    while(getline(file, baris)){
        stringstream ss(baris);
        kondisi_automatic temp;
        getline(ss, temp.plat, ',');
        ss >> temp.ban_belakang;
        ss.ignore();
        ss >> temp.ban_depan;
        ss.ignore();
        ss >> temp.busi;
        ss.ignore();
        ss >> temp.kampas_rem;
        ss.ignore();
        ss >> temp.minyak_rem;
        ss.ignore();
        ss >> temp.oli_gardan;
        ss.ignore();
        ss >> temp.oli_mesin;
        ss.ignore();
        ss >> temp.roller;
        ss.ignore();
        ss >> temp.van_belt;
        data_kondisi_automatic.push_back(temp);
    } 
    file.close();
    return;
}
void write_csv_motor(){// Menulis dari vektor list_motor.csv, kondisi_motor_manual.csv, kondisi_motor_automatic.csv
    // Membuka file csv data motor
    ofstream file;
    file.open("Database/list_motor.csv");
    if (!file) {
        cout << "Gagal membaca data motor (list_motor.csv)" << endl;
        pause();
        return;
    }
    // Menulis data motor ke dalam file csv
    file << "Owner,Nama Motor,Warna,Transmisi,Plat,Jarak Tempuh(KM),servis" << endl;
    for (int i = 0; i < data_motor.size(); i++){
        file << data_motor[i].owner << "," << data_motor[i].nama_motor << "," << data_motor[i].warna_motor << "," << data_motor[i].transmisi << "," << data_motor[i].plat << "," << data_motor[i].jarak_tempuh << ",";
        if (data_motor[i].servis){
            file << "true" << endl;
        }
        else{
            file << "false" << endl;
        }
    }
    file.close();

    // Membuka file csv data kondisi motor manual
    file.open("Database/kondisi_motor_manual.csv");
    if (!file) {
        cout << "Gagal membaca data kondisi motor manual (kondisi_motor_manual.csv)" << endl;
        pause();
        return;
    }
    // Menulis data kondisi motor manual ke dalam file csv
    file << "Plat,Ban Belakang,Ban Depan,Busi,Gear,Kampas Kopling,Kampas Rem,Minyak Rem,Oli Mesin,Rantai" << endl;
    for (int i = 0; i < data_kondisi_manual.size(); i++){
        file << data_kondisi_manual[i].plat << "," << data_kondisi_manual[i].ban_belakang << "," << data_kondisi_manual[i].ban_depan << "," 
        << data_kondisi_manual[i].busi << "," << data_kondisi_manual[i].gear << "," << data_kondisi_manual[i].kampas_kopling << "," 
        << data_kondisi_manual[i].kampas_rem << "," << data_kondisi_manual[i].minyak_rem << "," << data_kondisi_manual[i].oli_mesin << "," << data_kondisi_manual[i].rantai << endl;
    }
    file.close();

    // Membuka file csv data kondisi motor automatic
    file.open("Database/kondisi_motor_automatic.csv");
    if (!file) {
        cout << "Gagal membaca data kondisi motor automatic (kondisi_motor_automatic.csv)" << endl;
        pause();
        return;
    }
    // Menulis data kondisi motor automatic ke dalam file csv
    file << "Plat,Ban Belakang,Ban Depan,Busi,Kampas Rem,Minyak Rem,Oli Gardan,Oli Mesin,Roller,Van Belt" << endl;
    for (int i = 0; i < data_kondisi_automatic.size(); i++){
        file << data_kondisi_automatic[i].plat << "," << data_kondisi_automatic[i].ban_belakang << "," << data_kondisi_automatic[i].ban_depan << "," 
        << data_kondisi_automatic[i].busi << "," << data_kondisi_automatic[i].kampas_rem << "," << data_kondisi_automatic[i].minyak_rem << "," 
        << data_kondisi_automatic[i].oli_gardan << "," << data_kondisi_automatic[i].oli_mesin << "," << data_kondisi_automatic[i].roller << "," << data_kondisi_automatic[i].van_belt << endl;
    }
    file.close();
    return;
}

void read_csv_list_sparepart(){ // Membaca csv list_sparepart.csv
    // Membaca list pendataan sparepart
    data_list_sparepart.clear();
    ifstream file;
    file.open("Database/list_sparepart.csv");
    if (!file) {
        cout << "Gagal membaca data sparepart (list_sparepart.csv)" << endl;
        pause();
        return;
    }
    string baris, data;
    getline(file, baris); // skip header
    while(getline(file, baris)){
        stringstream ss(baris);
        sparepart_data temp;
        getline(ss, temp.nama_sparepart, ',');
        getline(ss, temp.tipe_transmisi, ',');
        ss >> temp.harga_sparepart;
        ss.ignore();
        ss >> temp.kilometer;
        ss.ignore();
        ss >> temp.stok_sparepart;
        ss.ignore();
        data_list_sparepart.push_back(temp);
    }
    file.close();
    return;
}
void write_csv_list_sparepart(){ // Menulis data sparepart ke dalam file list_sparepart.csv
    ofstream file;
    file.open("Database/list_sparepart.csv");
    if (!file) {
        cout << "Gagal membaca data sparepart (list_sparepart.csv)" << endl;
        pause();
        return;
    }
    file << "Nama Sparepart,Tipe Transmisi,Harga,Kilometer,Stok" << endl;
    for (int i = 0; i < data_list_sparepart.size(); i++){
        file << data_list_sparepart[i].nama_sparepart << "," << data_list_sparepart[i].tipe_transmisi << "," 
        << data_list_sparepart[i].harga_sparepart << "," << data_list_sparepart[i].kilometer << "," << data_list_sparepart[i].stok_sparepart << endl;
    }
    file.close();
    return;

}

void read_csv_struk_servis(){
    // Membaca data "pesanan_servis.csv"
    data_struk_servis.clear();
    ifstream file;
    file.open("Database/pesanan_servis.csv");
    if (!file) {
        cout << "Gagal membaca data pesanan servis (pesanan_servis.csv)" << endl;
        pause();
        return;
    }
    string baris, data, baris_struk, data_struk;
    struk_servis temp_struk;
    vector<servis_data> temp_servis_vector;
    // skip header
    getline(file, baris);
    // membaca data pesanan servis dari csv ke vektor
    while(getline(file, baris)){
        stringstream ss(baris);
        ss >> temp_struk.id; // id struk
        ss.ignore();
        getline(ss, temp_struk.username, ','); // username
        getline(ss, temp_struk.plat, ','); // plat kendaraan
        getline(ss, temp_struk.status_servis, ','); // status servis
        getline(ss, temp_struk.status_akun, '\n'); // status akun
        // vector<servis_data> servis

        // jika status servis belum selesai, buat vektor detail servis kosong
        if (temp_struk.status_servis != "done"){
            temp_struk.servis = temp_servis_vector;
            data_struk_servis.push_back(temp_struk);
            continue;
        }
        // baca csv detail servis yang dipesan
        ifstream file_struk;
        file_struk.open("Database/Struk/Servis/" + to_string(temp_struk.id) + ".csv");
        if (!file_struk) {
            cout << "Gagal membaca data servis (Database/Struk/Servis/" + to_string(temp_struk.id) + ".csv)" << endl;
            pause();
            file.close();
            return;
        }
        getline(file_struk, baris_struk); // skip header
        while(getline(file_struk, baris_struk)){
            stringstream ss_struk(baris_struk);
            servis_data temp_servis;
            getline(ss_struk, temp_servis.nama_servis, ','); // nama servis
            ss_struk >> temp_servis.harga_servis; // harga servis
            temp_servis_vector.push_back(temp_servis);
        }
        file_struk.close();
        temp_struk.servis = temp_servis_vector;

        // Menyimpan data ke dalam vektor
        data_struk_servis.push_back(temp_struk);
        
        //clear temp_servis_vector
        temp_servis_vector.clear();
    }
    file.close();
    return;
}   
void write_csv_struk_servis(){
    // Hapus folder Database/Struk/Servis
    system("rmdir /s /q Database\\Struk\\Servis");
    // Buat folder Database/Struk/Servis
    system("mkdir Database\\Struk\\Servis");

    // Menulis data pesanan_servis.csv
    ofstream file;
    file.open("Database/pesanan_servis.csv");
    if (!file) {
        cout << "Gagal membaca data pesanan servis (pesanan_servis.csv)" << endl;
        return;
    }

    file << "ID,Username,Plat,Status Servis,Status Akun" << endl; // Menulis header
    for (int i = 0; i < data_struk_servis.size(); i++){
        file << data_struk_servis[i].id << ","  // id struk
        << data_struk_servis[i].username << "," // username
        << data_struk_servis[i].plat << "," // plat
        << data_struk_servis[i].status_servis << "," // status servis
        << data_struk_servis[i].status_akun << endl; // status akun
    }
    file.close();
    
    // Membuat file berisi data detail servis = "Database/Struk/Servis/{id}.csv"
    for (int i = 0; i < data_struk_servis.size(); i++){
        if (data_struk_servis[i].status_servis != "done"){
            continue;
        }
        file.open("Database/Struk/Servis/" + to_string(data_struk_servis[i].id) + ".csv"); 
        if (!file) {
            cout << "Gagal membaca data servis (Database/Struk/Servis/" + to_string(data_struk_servis[i].id) + ".csv)" << endl;
            return;
        }
        file << "Nama Servis,Harga Servis" << endl; // Menulis header
        for (int j = 0; j < data_struk_servis[i].servis.size(); j++){
            file << data_struk_servis[i].servis[j].nama_servis << "," << data_struk_servis[i].servis[j].harga_servis << endl;
        }
        file.close();
    }
    return;
}

void read_csv_struk_sparepart(){
    // Membaca data "pesanan_sparepart.csv"
    data_struk_sparepart.clear();
    ifstream file;
    file.open("Database/pesanan_sparepart.csv");
    if (!file) {
        cout << "Gagal membaca data pesanan sparepart (pesanan_sparepart.csv)" << endl;
        pause();
        return;
    }
    string baris, data, baris_struk, data_struk;
    struk_sparepart temp_struk;
    vector<sparepart_pesanan> temp_sparepart_vector;
    // skip header
    getline(file, baris);
    while(getline(file, baris)){
        stringstream ss(baris);
        ss >> temp_struk.id; // id struk
        ss.ignore();
        getline(ss, temp_struk.username, ','); // username
        getline(ss, temp_struk.telepon, ','); // telepon
        getline(ss, temp_struk.address, ','); // alamat
        getline(ss, temp_struk.status_akun, '\n'); // status akun
        // vector<sparepart_pesanan> pesanan
        // baca csv detail sparepart yang dipesan
        ifstream file_struk;
        file_struk.open("Database/Struk/Sparepart/" + to_string(temp_struk.id) + ".csv");
        if (!file_struk) {
            cout << "Gagal membaca data sparepart (Database/Struk/Sparepart/" + to_string(temp_struk.id) + ".csv)" << endl;
            pause();
            file.close();
            return;
        }
        getline(file_struk, baris_struk); // skip header
        while(getline(file_struk, baris_struk)){
            stringstream ss_struk(baris_struk);
            sparepart_pesanan temp_sparepart;
            getline(ss_struk, temp_sparepart.nama_sparepart, ','); // nama sparepart
            ss_struk >> temp_sparepart.jumlah; // jumlah
            ss_struk.ignore();
            ss_struk >> temp_sparepart.harga; // harga
            temp_sparepart_vector.push_back(temp_sparepart);
        }
        file_struk.close();
        temp_struk.pesanan = temp_sparepart_vector;
        
        // Menyimpan data ke dalam vektor
        data_struk_sparepart.push_back(temp_struk);

        //clear temp_sparepart_vector
        temp_sparepart_vector.clear();
    }
    file.close();
    return;
}
void write_csv_struk_sparepart(){
    // Hapus folder Database/Struk/Sparepart
    system("rmdir /s /q Database\\Struk\\Sparepart");
    // Buat folder Database/Struk/Sparepart
    system("mkdir Database\\Struk\\Sparepart");

    // Menulis data pesanan_sparepart.csv
    ofstream file;
    file.open("Database/pesanan_sparepart.csv");
    if (!file) {
        cout << "Gagal membaca data pesanan sparepart (pesanan_sparepart.csv)" << endl;
        return;
    }
    file << "ID,Username,Telepon,Address,Status Akun" << endl; // Menulis header
    for (int i = 0; i < data_struk_sparepart.size(); i++){
        file << data_struk_sparepart[i].id << ","  // id struk
        << data_struk_sparepart[i].username << "," // username
        << data_struk_sparepart[i].telepon << "," // telepon
        << data_struk_sparepart[i].address << "," // alamat
        << data_struk_sparepart[i].status_akun << endl;
    }
    file.close();
    // vector<sparepart_pesanan> pesanan
    // Membuat file berisi data detail sparepart = "Database/Struk/Sparepart/{id}.csv"
    for (int i = 0; i < data_struk_sparepart.size(); i++){
        file.open("Database/Struk/Sparepart/" + to_string(data_struk_sparepart[i].id) + ".csv");
        if (!file) {
            cout << "Gagal membaca data sparepart (Database/Struk/Sparepart/" + to_string(data_struk_sparepart[i].id) + ".csv)" << endl;
            return;
        }
        file << "Nama Sparepart,Jumlah,Harga" << endl; // Menulis header
        for (int j = 0; j < data_struk_sparepart[i].pesanan.size(); j++){
            file << data_struk_sparepart[i].pesanan[j].nama_sparepart << "," 
            << data_struk_sparepart[i].pesanan[j].jumlah << "," 
            << data_struk_sparepart[i].pesanan[j].harga << endl;
        }
        file.close();
    }
    return;
}


// Fungsi Login dan Registrasi
int login(int try_left, string *global_username, string *global_password){ // Binary Search
/*
return 0 = login admin
return 1 = login user
return 2 = gagal login 
*/
    // Batas upaya input login 3 kali
    if (try_left == 0){
        return 2;
    }
    string username_inp, password_inp, baris, data;
    ifstream file;
    bool pass = true;
    cout << "=============================" << endl;
    cout << "         MENU LOGIN" << endl;
    cout << "=============================" << endl;
    cout << "Kesempatan login tersisa: " << try_left << endl;
    cout << "-----------------------------" << endl;
    // Input Username
    cout << "Username : ";
    getline(cin, username_inp);
    if (username_inp.find(",") != string::npos){
        cout << "Username tidak boleh mengandung koma" << endl;
        pass = false;
    }
    else if(username_inp.find_first_not_of(' ') == string::npos){
        cout << "Username tidak boleh kosong" << endl;
        pass = false;
    }
    else if(username_inp.length() < 8){
        cout << "Username minimal 8 karakter" << endl;
        pass = false;
    }
    if (!pass){
        pause();
        clear();
        return login(try_left-1, global_username, global_password);
    }
    // Input Password
    cout << "Password : ";
    getline(cin, password_inp);
    if (password_inp.find(",") != string::npos){
        cout << "Password tidak boleh mengandung koma" << endl;
        pass = false;
    }
    else if(password_inp.find_first_not_of(' ') == string::npos){
        cout << "Password tidak boleh kosong" << endl;
        pass = false;
    }
    else if(password_inp.length() < 8){
        cout << "Password minimal 8 karakter" << endl;
        pass = false;
    }
    if (!pass){
        pause();
        clear();
        return login(try_left-1, global_username, global_password);
    }


    // Cek Data Login Admin
    file.open("Database/admin_log.csv");
    if (!file) {
        cout << "Gagal membaca data admin (admin_log.csv)" << endl;
        pause(); clear();
        return 2;
    }
    getline(file,baris); // skip header
    while(getline(file, baris)){
        stringstream ss(baris);
        getline(ss, data, ',');
        if (data == username_inp){
            getline(ss, data, '\n');
            cout << data << endl;
            if (data == password_inp){
                clear();
                cout << "LOGIN BERHASIL (ADMIN)" << endl;
                *global_username = username_inp;
                *global_password = password_inp;
                pause(); clear();
                return 0;
            }
        }
    }
    file.close();

    // Cek Data Login User dengan binary search
    file.open("Database/user_log.csv");
    int jumlah_user = data_user.size();
    int kiri = 0, kanan = jumlah_user-1, tengah;
    if (!file) {
        clear();
        cout << "Gagal membaca data user (user_log.csv)" << endl;
        pause(); clear();
        return 2;
    } 
    // Binary Search
    while (kiri <= kanan){ // selama index kiri masih lebih kecil atau sama dengan index kanan
        tengah = (kiri+kanan)/2;
        if (data_user[tengah].username == username_inp){ // cek username
            if (data_user[tengah].password == password_inp){ // cek password
                clear();
                cout << "LOGIN BERHASIL (USER)" << endl;
                *global_username = username_inp;
                *global_password = password_inp;
                pause(); clear();
                return 1;
            }
            else{
                break;
            }
        }
        else if (data_user[tengah].username < username_inp){
            kiri = tengah+1;
        }
        else{
            kanan = tengah-1;
        }
    }
    file.close();

    // Login gagal
    cout << "Username atau password salah" << endl;
    pause();
    clear();
    return login(try_left-1, global_username, global_password);
}
void regist(){ // setelah regist, data ditambahkan ke file user_log.csv dan di sort dengan bubble sort berdasarkan username
    string username_inp, password_inp, telepon_inp, address_inp;

    cout << "=============================" << endl;
    cout << "        MENU REGISTER" << endl;
    cout << "=============================" << endl;
    // Input Username
    cout << "Username: ";
    getline(cin, username_inp);
    if (username_inp.find(",") != string::npos){
        cout << "Username tidak boleh mengandung koma" << endl;
        pause();
        clear();
        return;
    }
    else if(username_inp.find_first_not_of(' ') == string::npos){
        cout << "Username tidak boleh kosong" << endl;
        pause();
        clear();
        return;
    }
    else if(username_inp.length() < 8){
        cout << "Username minimal 8 karakter" << endl;
        pause();
        clear();
        return;
    }
    // Cek keunikan username dengan data user
    for (int i = 0; i < data_user.size(); i++){
        if (data_user[i].username == username_inp){
            cout << "Username sudah terdaftar" << endl;
            pause();
            clear();
            return;
        }
    }

    // Cek keunikan username dengan data admin
    ifstream file;
    file.open("Database/admin_log.csv");
    if (!file) {
        cout << "Gagal membaca data admin (admin_log.csv)" << endl;
        pause();
        clear();
        return;
    }
    string baris, data;
    getline(file, baris); // skip header
    while(getline(file, baris)){
        stringstream ss(baris);
        getline(ss, data, ',');
        if (data == username_inp){
            cout << "Username sudah terdaftar" << endl;
            pause();
            clear();
            return;
        }
    }
    file.close();

    // Input Password
    cout << "Password: ";
    getline(cin, password_inp);
    if (password_inp.find(",") != string::npos){
        cout << "Password tidak boleh mengandung koma" << endl;
        pause();
        clear();
        return;
    }
    else if(password_inp.find_first_not_of(' ') == string::npos){
        cout << "Password tidak boleh kosong" << endl;
        pause();
        clear();
        return;
    }
    else if(password_inp.length() < 8){
        cout << "Password minimal 8 karakter" << endl;
        pause();
        clear();
        return;
    }

    // Input Nomor Telepon
    cout << "Nomor telepon: ";
    getline(cin, telepon_inp);
    // Error check nomor telepon
    if (telepon_inp.find_first_not_of("0123456789") != string::npos){
        cout << "Nomor telepon hanya boleh angka" << endl;
        pause();
        clear();
        return;
    }
    else if (telepon_inp.length() < 10){
        cout << "Nomor telepon minimal 10 digit" << endl;
        pause();
        clear();
        return;
    }
    else if (telepon_inp.length() > 13){
        cout << "Nomor telepon maksimal 13 digit" << endl;
        pause();
        clear();
        return;
    }

    // Cek keunikan nomor telepon dengan data user
    for (int i = 0; i < data_user.size(); i++){
        if (data_user[i].telepon == telepon_inp){
            cout << "Nomor telepon sudah terdaftar" << endl;
            pause();
            clear();
            return;
        }
    }

    // Input Alamat
    cout << "Alamat: ";
    getline(cin, address_inp);
    // Mengecek input supaya tidak memililki koma
    if (address_inp.find(",") != string::npos){
        cout << "Alamat tidak boleh mengandung koma" << endl;
        pause();
        clear();
        return;
    }
    else if(address_inp.find_first_not_of(' ') == string::npos){
        cout << "Alamat tidak boleh kosong" << endl;
        pause();
        clear();
        return;
    }



    // Menyimpan data ke dalam vector
    user_data temp;
    temp.username = username_inp;
    temp.password = password_inp;
    temp.telepon = telepon_inp;
    temp.address = address_inp;
    data_user.push_back(temp);

    // sort data user dengan bubble sort - username
    for (int i = 0; i < data_user.size(); i++){
        for (int j = 0; j < data_user.size()-1; j++){
            if (data_user[j].username > data_user[j+1].username){
                user_data temp = data_user[j];
                data_user[j] = data_user[j+1];
                data_user[j+1] = temp;
            }
        }
    }

    // update file user_log.csv
    write_csv_user();
    read_csv_user();

    cout << "Registrasi berhasil" << endl;
    pause();
    clear();
    return;
}


/* Bagian Menu User */
void add_motor(string username){
    string nama_motor, warna_motor, transmisi_motor, plat_motor;
    bool servis;
    cout << "=============================" << endl;
    cout << "    TAMBAH DATA MOTOR" << endl;
    cout << "=============================" << endl;
    // Input nama motor getline
    cout << "Nama Motor: ";
    while (true){
        getline(cin, nama_motor);
        // Mengecek input nama motor
        if (nama_motor.find(",") != string::npos){
            cout << "Nama motor tidak boleh mengandung koma" << endl;
            cout << "Nama Motor: ";
        }
        // Nama motor cuma spasi
        else if(nama_motor.find_first_not_of(' ') == string::npos){
            cout << "Nama motor tidak boleh kosong" << endl;
            cout << "Nama Motor: ";
        }
        else{
            break;
        }
        }
    // Input warna motor
    cout << "Warna Motor: ";
    while (true){
        getline(cin, warna_motor);
        // Mengecek input warna motor
        if (warna_motor.find(",") != string::npos){
            cout << "Warna motor tidak boleh mengandung koma" << endl;
            cout << "Warna Motor: ";
        }
        else if(warna_motor.find_first_not_of(' ') == string::npos){
            cout << "Warna motor tidak boleh kosong" << endl;
            cout << "Warna Motor: ";
        }
        else{
            break;
        }
    }

    // Input transmisi, "manual" atau "automatic"
    cout << "Transmisi Motor: ";
    while (true){
        getline(cin, transmisi_motor);
        // Mengubah input transmisi menjadi lowercase
        for (int i = 0; i < transmisi_motor.length(); i++){
            transmisi_motor[i] = tolower(transmisi_motor[i]);
        }
        if (transmisi_motor == "manual" || transmisi_motor == "automatic"){
            break;
        }
        else{
            cout << "Transmisi motor hanya bisa manual atau automatic" << endl;
            cout << "Transmisi Motor: ";
        }
    }

    // Input plat motor
    string data_plat_temp;
    string inp_plat_temp;
    bool pass;
    while (true){
        pass = true;
        cout << "Plat Motor: ";
        getline(cin, plat_motor);
        // Input tidak boleh kosong
        if (plat_motor.find_first_not_of(' ') == string::npos){
            cout << "Plat motor tidak boleh kosong" << endl;
            continue;
        }
        // Mengecek input plat motor tidak mengandung koma
        if (plat_motor.find(",") != string::npos){
            cout << "Plat motor tidak boleh mengandung koma" << endl;
            continue;
        }
        // Ubah Input Plat jadi kapital
        for (int j = 0; j < plat_motor.length(); j++){
            plat_motor[j] = toupper(plat_motor[j]);
        }
        // Cek keunikan tanpa spasi
        for (int i = 0; i < data_motor.size(); i++){
            data_plat_temp = data_motor[i].plat;
            inp_plat_temp = plat_motor;
            inp_plat_temp.erase(remove(inp_plat_temp.begin(), inp_plat_temp.end(), ' '), inp_plat_temp.end());
            data_plat_temp.erase(remove(data_plat_temp.begin(), data_plat_temp.end(), ' '), data_plat_temp.end());
            if (data_plat_temp == inp_plat_temp){
                cout << "Plat motor sudah terdaftar" << endl;
                pass = false;
                break;
            }
        }
        if (pass){
            break;
        }
    }
    // input jarak tempuh
    string str_jarak_tempuh;
    int jarak_tempuh;
    cout << "Jarak Tempuh (KM): ";
    while (true){
        getline(cin, str_jarak_tempuh);
        // Mengecek input jarak tempuh
        if (str_jarak_tempuh.find_first_not_of(' ') == string::npos){
            cout << "Jarak tempuh tidak boleh kosong" << endl;
            cout << "Jarak Tempuh (KM): ";
        }
        else if (str_jarak_tempuh.find_first_not_of("0123456789") != string::npos){
            cout << "Jarak tempuh harus berupa angka" << endl;
            cout << "Jarak Tempuh (KM): ";
        }
        else if (stoi(str_jarak_tempuh) < 0){
            cout << "Jarak tempuh tidak boleh negatif" << endl;
            cout << "Jarak Tempuh (KM): ";
        }
        else{
            jarak_tempuh = stoi(str_jarak_tempuh);
            break;
        }
    }

    // menambahkan data motor ke vektor
    motor_data temp;
    temp.owner = username;
    temp.nama_motor = nama_motor;
    temp.warna_motor = warna_motor;
    temp.transmisi = transmisi_motor;
    temp.plat = plat_motor;
    temp.jarak_tempuh = jarak_tempuh;
    temp.servis = false; // servis default = false
    data_motor.push_back(temp);

    // Input kondisi motor
    string kondisi_motor;
    cout << "=============================" << endl;
    cout << "    Terakhir Servis(Km)" << endl;
    cout << "=============================" << endl;
    // Input kondisi motor jika transmisi adalah automatic
    if (transmisi_motor == "automatic") {
        kondisi_automatic kondisi;
        kondisi.plat = plat_motor;
        // Input kondisi ban belakang
        cout << "Ban Belakang: ";
        while (true){
            getline(cin, kondisi_motor);
            if (kondisi_motor.find_first_not_of(' ') == string::npos){
                cout << "Kondisi motor tidak boleh kosong" << endl;
                cout << "Ban Belakang: ";
            }
            else if (kondisi_motor.find_first_not_of("0123456789") != string::npos){
                cout << "Kondisi motor harus berupa angka" << endl;
                cout << "Ban Belakang: ";
            }
            else if (stoi(kondisi_motor) < 0 || stoi(kondisi_motor) > jarak_tempuh){
                cout << "Kondisi motor tidak boleh negatif atau melebihi jarak tempuh" << endl;
                cout << "Ban Belakang: ";
            }
            else{
                kondisi.ban_belakang = stoi(kondisi_motor);
                break;
            }
        }
        // Input kondisi ban depan
        cout << "Ban Depan: ";
        while (true){
            getline(cin, kondisi_motor);
            if (kondisi_motor.find_first_not_of(' ') == string::npos){
                cout << "Kondisi motor tidak boleh kosong" << endl;
                cout << "Ban Depan: ";
            }
            else if (kondisi_motor.find_first_not_of("0123456789") != string::npos){
                cout << "Kondisi motor harus berupa angka" << endl;
                cout << "Ban Depan: ";
            }
            else if (stoi(kondisi_motor) < 0 || stoi(kondisi_motor) > jarak_tempuh){
                cout << "Kondisi motor tidak boleh negatif atau melebihi jarak tempuh" << endl;
                cout << "Ban Depan: ";
            }
            else{
                kondisi.ban_depan = stoi(kondisi_motor);
                break;
            }
        }
        // Input kondisi busi
        cout << "Busi: ";
        while (true){
            getline(cin, kondisi_motor);
            if (kondisi_motor.find_first_not_of(' ') == string::npos){
                cout << "Kondisi motor tidak boleh kosong" << endl;
                cout << "Busi: ";
            }
            else if (kondisi_motor.find_first_not_of("0123456789") != string::npos){
                cout << "Kondisi motor harus berupa angka" << endl;
                cout << "Busi: ";
            }
            else if (stoi(kondisi_motor) < 0 || stoi(kondisi_motor) > jarak_tempuh){
                cout << "Kondisi motor tidak boleh negatif atau melebihi jarak tempuh" << endl;
                cout << "Busi: ";
            }
            else{
                kondisi.busi = stoi(kondisi_motor);
                break;
            }
        }
        // Input kondisi kampas rem
        cout << "Kampas Rem: ";
        while (true){
            getline(cin, kondisi_motor);
            if (kondisi_motor.find_first_not_of(' ') == string::npos){
                cout << "Kondisi motor tidak boleh kosong" << endl;
                cout << "Kampas Rem: ";
            }
            else if (kondisi_motor.find_first_not_of("0123456789") != string::npos){
                cout << "Kondisi motor harus berupa angka" << endl;
                cout << "Kampas Rem: ";
            }
            else if (stoi(kondisi_motor) < 0 || stoi(kondisi_motor) > jarak_tempuh){
                cout << "Kondisi motor tidak boleh negatif atau melebihi jarak tempuh" << endl;
                cout << "Kampas Rem: ";
            }
            else{
                kondisi.kampas_rem = stoi(kondisi_motor);
                break;
            }
        }
        // Input kondisi minyak rem
        cout << "Minyak Rem: ";
        while (true){
            getline(cin, kondisi_motor);
            if (kondisi_motor.find_first_not_of(' ') == string::npos){
                cout << "Kondisi motor tidak boleh kosong" << endl;
                cout << "Minyak Rem: ";
            }
            else if (kondisi_motor.find_first_not_of("0123456789") != string::npos){
                cout << "Kondisi motor harus berupa angka" << endl;
                cout << "Minyak Rem: ";
            }
            else if (stoi(kondisi_motor) < 0 || stoi(kondisi_motor) > jarak_tempuh){
                cout << "Kondisi motor tidak boleh negatif atau melebihi jarak tempuh" << endl;
                cout << "Minyak Rem: ";
            }
            else{
                kondisi.minyak_rem = stoi(kondisi_motor);
                break;
            }
        }
        // Input kondisi oli gardan
        cout << "Oli Gardan: ";
        while (true){
            getline(cin, kondisi_motor);
            if (kondisi_motor.find_first_not_of(' ') == string::npos){
                cout << "Kondisi motor tidak boleh kosong" << endl;
                cout << "Oli Gardan: ";
            }
            else if (kondisi_motor.find_first_not_of("0123456789") != string::npos){
                cout << "Kondisi motor harus berupa angka" << endl;
                cout << "Oli Gardan: ";
            }
            else if (stoi(kondisi_motor) < 0 || stoi(kondisi_motor) > jarak_tempuh){
                cout << "Kondisi motor tidak boleh negatif atau melebihi jarak tempuh" << endl;
                cout << "Oli Gardan: ";
            }
            else{
                kondisi.oli_gardan = stoi(kondisi_motor);
                break;
            }
        }
        // Input kondisi oli mesin
        cout << "Oli Mesin: ";
        while (true){
            getline(cin, kondisi_motor);
            if (kondisi_motor.find_first_not_of(' ') == string::npos){
                cout << "Kondisi motor tidak boleh kosong" << endl;
                cout << "Oli Mesin: ";
            }
            else if (kondisi_motor.find_first_not_of("0123456789") != string::npos){
                cout << "Kondisi motor harus berupa angka" << endl;
                cout << "Oli Mesin: ";
            }
            else if (stoi(kondisi_motor) < 0 || stoi(kondisi_motor) > jarak_tempuh){
                cout << "Kondisi motor tidak boleh negatif atau melebihi jarak tempuh" << endl;
                cout << "Oli Mesin: ";
            }
            else{
                kondisi.oli_mesin = stoi(kondisi_motor);
                break;
            }
        }
        // Input kondisi roller
        cout << "Roller: ";
        while (true){
            getline(cin, kondisi_motor);
            if (kondisi_motor.find_first_not_of(' ') == string::npos){
                cout << "Kondisi motor tidak boleh kosong" << endl;
                cout << "Roller: ";
            }
            else if (kondisi_motor.find_first_not_of("0123456789") != string::npos){
                cout << "Kondisi motor harus berupa angka" << endl;
                cout << "Roller: ";
            }
            else if (stoi(kondisi_motor) < 0 || stoi(kondisi_motor) > jarak_tempuh){
                cout << "Kondisi motor tidak boleh negatif atau melebihi jarak tempuh" << endl;
                cout << "Roller: ";
            }
            else{
                kondisi.roller = stoi(kondisi_motor);
                break;
            }
        }
        // Input kondisi van belt
        cout << "Van Belt: ";
        while (true){
            getline(cin, kondisi_motor);
            if (kondisi_motor.find_first_not_of(' ') == string::npos){
                cout << "Kondisi motor tidak boleh kosong" << endl;
                cout << "Van Belt: ";
            }
            else if (kondisi_motor.find_first_not_of("0123456789") != string::npos){
                cout << "Kondisi motor harus berupa angka" << endl;
                cout << "Van Belt: ";
            }
            else if (stoi(kondisi_motor) < 0 || stoi(kondisi_motor) > jarak_tempuh){
                cout << "Kondisi motor tidak boleh negatif atau melebihi jarak tempuh" << endl;
                cout << "Van Belt: ";
            }
            else{
                kondisi.van_belt = stoi(kondisi_motor);
                break;
            }
        }
        // Simpan data ke vektor
        data_kondisi_automatic.push_back(kondisi);
        // Sort data kondisi automatic  dengan bubble sort, ascending berdasarkan plat
        for (int i = 0; i < data_kondisi_automatic.size(); i++){
            for (int j = 0; j < data_kondisi_automatic.size()-1; j++){
                if (data_kondisi_automatic[j].plat > data_kondisi_automatic[j+1].plat){
                    kondisi_automatic temp = data_kondisi_automatic[j];
                    data_kondisi_automatic[j] = data_kondisi_automatic[j+1];
                    data_kondisi_automatic[j+1] = temp;
                }
            }
        }
    }
    
    // Input kondisi motor jika transmisi adalah manual
    if (transmisi_motor == "manual") {
        kondisi_manual kondisi;
        kondisi.plat = plat_motor;
        // Input kondisi ban belakang
        cout << "Ban Belakang: ";
        while (true){
            getline(cin, kondisi_motor);
            if (kondisi_motor.find_first_not_of(' ') == string::npos){
                cout << "Kondisi motor tidak boleh kosong" << endl;
                cout << "Ban Belakang: ";
            }
            else if (kondisi_motor.find_first_not_of("0123456789") != string::npos){
                cout << "Kondisi motor harus berupa angka" << endl;
                cout << "Ban Belakang: ";
            }
            else if (stoi(kondisi_motor) < 0 || stoi(kondisi_motor) > jarak_tempuh){
                cout << "Kondisi motor tidak boleh negatif atau melebihi jarak tempuh" << endl;
                cout << "Ban Belakang: ";
            }
            else{
                kondisi.ban_belakang = stoi(kondisi_motor);
                break;
            }
        }
        // Input kondisi ban depan
        cout << "Ban Depan: ";
        while (true){
            getline(cin, kondisi_motor);
            if (kondisi_motor.find_first_not_of(' ') == string::npos){
                cout << "Kondisi motor tidak boleh kosong" << endl;
                cout << "Ban Depan: ";
            }
            else if (kondisi_motor.find_first_not_of("0123456789") != string::npos){
                cout << "Kondisi motor harus berupa angka" << endl;
                cout << "Ban Depan: ";
            }
            else if (stoi(kondisi_motor) < 0 || stoi(kondisi_motor) > jarak_tempuh){
                cout << "Kondisi motor tidak boleh negatif atau melebihi jarak tempuh" << endl;
                cout << "Ban Depan: ";
            }
            else{
                kondisi.ban_depan = stoi(kondisi_motor);
                break;
            }
        }
        // Input kondisi busi
        cout << "Busi: ";
        while (true){
            getline(cin, kondisi_motor);
            if (kondisi_motor.find_first_not_of(' ') == string::npos){
                cout << "Kondisi motor tidak boleh kosong" << endl;
                cout << "Busi: ";
            }
            else if (kondisi_motor.find_first_not_of("0123456789") != string::npos){
                cout << "Kondisi motor harus berupa angka" << endl;
                cout << "Busi: ";
            }
            else if (stoi(kondisi_motor) < 0 || stoi(kondisi_motor) > jarak_tempuh){
                cout << "Kondisi motor tidak boleh negatif atau melebihi jarak tempuh" << endl;
                cout << "Busi: ";
            }
            else{
                kondisi.busi = stoi(kondisi_motor);
                break;
            }
        }  
        // Input kondisi gear
        cout << "Gear: ";
        while (true){
            getline(cin, kondisi_motor);
            if (kondisi_motor.find_first_not_of(' ') == string::npos){
                cout << "Kondisi motor tidak boleh kosong" << endl;
                cout << "Gear: ";
            }
            else if (kondisi_motor.find_first_not_of("0123456789") != string::npos){
                cout << "Kondisi motor harus berupa angka" << endl;
                cout << "Gear: ";
            }
            else if (stoi(kondisi_motor) < 0 || stoi(kondisi_motor) > jarak_tempuh){
                cout << "Kondisi motor tidak boleh negatif atau melebihi jarak tempuh" << endl;
                cout << "Gear: ";
            }
            else{
                kondisi.gear = stoi(kondisi_motor);
                break;
            }
        }
        // Input kondisi kampas kopling
        cout << "Kampas Kopling: ";
        while (true){
            getline(cin, kondisi_motor);
            if (kondisi_motor.find_first_not_of(' ') == string::npos){
                cout << "Kondisi motor tidak boleh kosong" << endl;
                cout << "Kampas Kopling: ";
            }
            else if (kondisi_motor.find_first_not_of("0123456789") != string::npos){
                cout << "Kondisi motor harus berupa angka" << endl;
                cout << "Kampas Kopling: ";
            }
            else if (stoi(kondisi_motor) < 0 || stoi(kondisi_motor) > jarak_tempuh){
                cout << "Kondisi motor tidak boleh negatif atau melebihi jarak tempuh" << endl;
                cout << "Kampas Kopling: ";
            }
            else{
                kondisi.kampas_kopling = stoi(kondisi_motor);
                break;
            }
        }
        // Input kondisi kampas rem
        cout << "Kampas Rem: ";
        while (true){
            getline(cin, kondisi_motor);
            if (kondisi_motor.find_first_not_of(' ') == string::npos){
                cout << "Kondisi motor tidak boleh kosong" << endl;
                cout << "Kampas Rem: ";
            }
            else if (kondisi_motor.find_first_not_of("0123456789") != string::npos){
                cout << "Kondisi motor harus berupa angka" << endl;
                cout << "Kampas Rem: ";
            }
            else if (stoi(kondisi_motor) < 0 || stoi(kondisi_motor) > jarak_tempuh){
                cout << "Kondisi motor tidak boleh negatif atau melebihi jarak tempuh" << endl;
                cout << "Kampas Rem: ";
            }
            else{
                kondisi.kampas_rem = stoi(kondisi_motor);
                break;
            }
        }
        // Input kondisi minyak rem
        cout << "Minyak Rem: ";
        while (true){
            getline(cin, kondisi_motor);
            if (kondisi_motor.find_first_not_of(' ') == string::npos){
                cout << "Kondisi motor tidak boleh kosong" << endl;
                cout << "Minyak Rem: ";
            }
            else if (kondisi_motor.find_first_not_of("0123456789") != string::npos){
                cout << "Kondisi motor harus berupa angka" << endl;
                cout << "Minyak Rem: ";
            }
            else if (stoi(kondisi_motor) < 0 || stoi(kondisi_motor) > jarak_tempuh){
                cout << "Kondisi motor tidak boleh negatif atau melebihi jarak tempuh" << endl;
                cout << "Minyak Rem: ";
            }
            else{
                kondisi.minyak_rem = stoi(kondisi_motor);
                break;
            }
        }
        // Input kondisi oli gardan
        cout << "Oli Mesin: ";
        while (true){
            getline(cin, kondisi_motor);
            if (kondisi_motor.find_first_not_of(' ') == string::npos){
                cout << "Kondisi motor tidak boleh kosong" << endl;
                cout << "Oli Mesin: ";
            }
            else if (kondisi_motor.find_first_not_of("0123456789") != string::npos){
                cout << "Kondisi motor harus berupa angka" << endl;
                cout << "Oli Mesin: ";
            }
            else if (stoi(kondisi_motor) < 0 || stoi(kondisi_motor) > jarak_tempuh){
                cout << "Kondisi motor tidak boleh negatif atau melebihi jarak tempuh" << endl;
                cout << "Oli Mesin: ";
            }
            else{
                kondisi.oli_mesin = stoi(kondisi_motor);
                break;
            }
        }
        // Input kondisi roller
        cout << "Rantai: ";
        while (true){
            getline(cin, kondisi_motor);
            if (kondisi_motor.find_first_not_of(' ') == string::npos){
                cout << "Kondisi motor tidak boleh kosong" << endl;
                cout << "Rantai: ";
            }
            else if (kondisi_motor.find_first_not_of("0123456789") != string::npos){
                cout << "Kondisi motor harus berupa angka" << endl;
                cout << "Rantai: ";
            }
            else if (stoi(kondisi_motor) < 0 || stoi(kondisi_motor) > jarak_tempuh){
                cout << "Kondisi motor tidak boleh negatif atau melebihi jarak tempuh" << endl;
                cout << "Rantai: ";
            }
            else{
                kondisi.rantai = stoi(kondisi_motor);
                break;
            }
        }
        // Simpan data ke vektor
        data_kondisi_manual.push_back(kondisi);
        // Sort data kondisi manual dengan bubble sort, ascending berdasarkan plat
        for (int i = 0; i < data_kondisi_manual.size(); i++){
            for (int j = 0; j < data_kondisi_manual.size()-1; j++){
                if (data_kondisi_manual[j].plat > data_kondisi_manual[j+1].plat){
                    kondisi_manual temp = data_kondisi_manual[j];
                    data_kondisi_manual[j] = data_kondisi_manual[j+1];
                    data_kondisi_manual[j+1] = temp;
                }
            }
        }
    }

    // Sort data motor dengan bubble sort, ascending berdasarkan plat
    for (int i = 0; i < data_motor.size(); i++){
        for (int j = 0; j < data_motor.size()-1; j++){
            if (data_motor[j].plat > data_motor[j+1].plat){
                motor_data temp = data_motor[j];
                data_motor[j] = data_motor[j+1];
                data_motor[j+1] = temp;
            }
        }
    }

    // update csv motor
    write_csv_motor();
    cout << "Data motor berhasil ditambahkan" << endl;
    pause();
    clear();
    return;
}

void view_motor(string username){
    read_csv_motor();
    // Cek apakah user memiliki data motor
    bool kosong = true;
    for (int i = 0; i < data_motor.size(); i++){
        if (data_motor[i].owner == username){
            kosong = false;
            break;
        }
    }
    if (kosong){
        cout << "Anda belum memiliki data motor" << endl;
        pause();
        clear();
        return;
    }

    vector<string> plat_vector;
    while(true){
        cout << "=====================================================================================================================" << endl;
        cout << "                                                 VIEW MOTOR" << endl;
        cout << "=====================================================================================================================" << endl;
        cout << "                                              Username: " << username << endl;
        cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
        // tampilkan list motor yang dimiliki user, hanya nama motor(plat) saja
        // Simpan plat motor yang dimiliki user ke dalam vector
        int count = 1;
        // Header Setw
        cout << left << setw(5) << "No" << setw(20) << "Nama Motor" << setw(14) << "Warna" << setw(14) << "Transmisi" << setw(20) 
            << "Plat" << setw(16) << "Jarak Tempuh" << "Diservis" << endl;
        for (int i = 0; i < data_motor.size(); i++){
            if (data_motor[i].owner == username){
                // Tampilkan data motor yang dimiliki user
                cout << setw(5) << count << setw(20) << data_motor[i].nama_motor << setw(14) << data_motor[i].warna_motor << setw(14)
                    << data_motor[i].transmisi << setw(20) << data_motor[i].plat << setw(16) << data_motor[i].jarak_tempuh;
                if (data_motor[i].servis){
                    cout << "Yes" << endl;
                }
                else{
                    cout << "No" << endl;
                }
                count++;
                plat_vector.push_back(data_motor[i].plat);
            }
        }
        cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
            
        // View Menu
        string str_pilih;
        int pilih;
        cout << "MENU VIEW :" << endl;
        cout << "1. Tampilkan Data Detail" << endl;
        cout << "2. Kembali (Menu Motor)" << endl;
        cout << "Pilih menu: ";
        getline(cin, str_pilih);
        // Mengecek error inputan
        if (str_pilih.find_first_not_of("0123456789") != string::npos){
            cout << "Input tidak valid. Silahkan masukkan angka." << endl;
            pause();
            clear();
            continue;
        }
        else if (str_pilih.find_first_not_of(' ') == string::npos){
            cout << "Input tidak boleh kosong" << endl;
            pause();
            clear();
            continue; // ke atas menu view 
        }
        else if(str_pilih.find_first_not_of("12") != string::npos){
            cout << "Input tidak valid. Silahkan pilih 1-2." << endl;
            pause();
            clear();
            continue; // ke atas menu view
        }
        pilih = stoi(str_pilih);
        // Tampilkan data detail motor
        if (pilih == 1){
            int pilih_motor;
            cout << "Pilih nomor motor : ";
            getline(cin, str_pilih);
            // Mengecek error inputan
            if (str_pilih.find_first_not_of("0123456789") != string::npos){
                cout << "Input tidak valid. Silahkan masukkan angka." << endl;
                pause();
                clear();
                continue;
            }
            else if (str_pilih.find_first_not_of(' ') == string::npos){
                cout << "Input tidak boleh kosong" << endl;
                pause();
                clear();
                continue; // ke atas menu view
            }
            else if(stoi(str_pilih) < 1 || stoi(str_pilih) > plat_vector.size()){
                cout << "Nomor motor tidak valid" << endl;
                pause();
                clear();
                continue;
            }
            pilih_motor = stoi(str_pilih);

            // Tampilkan data detail motor
            clear();
            cout << "==========================================" << endl;
            cout << "               VIEW MOTOR" << endl;
            cout << "==========================================" << endl;
            cout << "------------------------------------------" << endl;
            // Tampilkan data motor yang dipilih
            for (int i = 0; i < data_motor.size(); i++){ // cari data motor yang sesuai
                // jika data motor sesuai dengan username dan plat dari motor yang dipilih
                if (data_motor[i].owner == username && data_motor[i].plat == plat_vector[pilih_motor-1]){
                    cout << setw(15) << "Nama Motor" << " : "<< data_motor[i].nama_motor << endl;
                    cout << setw(15) << "Warna Motor" << " : " << data_motor[i].warna_motor << endl;
                    cout << setw(15) << "Transmisi" << " : "<< data_motor[i].transmisi << endl;
                    cout << setw(15) << "Plat" << " : "<< data_motor[i].plat << endl;
                    cout << setw(15) << "Jarak Tempuh" << " : "<< data_motor[i].jarak_tempuh << " KM" << endl;
                    cout << setw(15) << "Diservis" << " : ";
                    if (data_motor[i].servis){
                        cout << setw(20) << "Yes" << endl;
                    }
                    else{
                        cout << setw(20) << "No" << endl;
                    }
                    // Tampilkan kondisi sparepart motor yang dipilih
                    // di csv kondisi motor, dicari berdasarkan plat
                    if (data_motor[i].transmisi == "manual"){
                        for (int j = 0; j < data_kondisi_manual.size(); j++){
                            if (data_kondisi_manual[j].plat == data_motor[i].plat){
                                // Tampilkan dalam bentuk tabel 
                                cout << "------------------------------------------" << endl;
                                cout << "           KONDISI SPAREPART" << endl;
                                cout << "------------------------------------------" << endl;
                                cout << setw(15) << "Nama Sparepart" << setw(24) << "Terakhir Servis(KM)" << endl;
                                cout << setw(15) << "Ban Belakang" << setw(24) << data_kondisi_manual[j].ban_belakang << endl;
                                cout << setw(15) << "Ban Depan" << setw(24) << data_kondisi_manual[j].ban_depan << endl;
                                cout << setw(15) << "Busi" << setw(24) << data_kondisi_manual[j].busi << endl;
                                cout << setw(15) << "Gear" << setw(24) << data_kondisi_manual[j].gear << endl;
                                cout << setw(15) << "Kampas Kopling" << setw(24) << data_kondisi_manual[j].kampas_kopling << endl;
                                cout << setw(15) << "Kampas Rem" << setw(24) << data_kondisi_manual[j].kampas_rem << endl;
                                cout << setw(15) << "Minyak Rem" << setw(24) << data_kondisi_manual[j].minyak_rem << endl;
                                cout << setw(15) << "Oli Mesin" << setw(24) << data_kondisi_manual[j].oli_mesin << endl;
                                cout << setw(15) << "Rantai" << setw(24) << data_kondisi_manual[j].rantai << endl;
                                cout << "------------------------------------------" << endl;
                            }
                        }
                    }
                    if (data_motor[i].transmisi == "automatic"){
                        for (int j = 0; j < data_kondisi_automatic.size(); j++){
                            if (data_kondisi_automatic[j].plat == data_motor[i].plat){
                                // Tampilkan dalam bentuk tabel 
                                cout << "------------------------------------------" << endl;
                                cout << "             KONDISI SPAREPART" << endl;
                                cout << "------------------------------------------" << endl;
                                cout << setw(15) << "Ban Belakang" << " :  "<< data_kondisi_automatic[j].ban_belakang << " KM" << endl;
                                cout << setw(15) << "Ban Depan" << " :  "<< data_kondisi_automatic[j].ban_depan << " KM" << endl;
                                cout << setw(15) << "Busi" << " : "<< data_kondisi_automatic[j].busi << " KM" << endl;
                                cout << setw(15) << "Kampas Rem" << " :  "<< data_kondisi_automatic[j].kampas_rem << " KM" << endl;
                                cout << setw(15) << "Minyak Rem" << " :  "<< data_kondisi_automatic[j].minyak_rem << " KM" << endl;
                                cout << setw(15) << "Oli Gardan" << " :  "<< data_kondisi_automatic[j].oli_gardan << " KM" << endl;
                                cout << setw(15) << "Oli Mesin" << " :  "<< data_kondisi_automatic[j].oli_mesin << " KM" << endl;
                                cout << setw(15) << "Roller" << " :  "<< data_kondisi_automatic[j].roller << " KM" << endl;
                                cout << setw(15) << "Van Belt" << " :  "<< data_kondisi_automatic[j].van_belt << " KM" << endl;
                                cout << "------------------------------------------" << " KM" << endl;
                            
                            }
                        }
                    }
                    pause();
                    clear();   
                    return;
                }
            }
            
        }
        // Kembali ke menu user
        if(pilih == 2){
            clear();
            return;
        }
        // Input tidak sesuai
        else {
            cout << "Menu tidak tersedia. Silahkan masukkan angka 1-2." << endl;
        }
    }
        pause();
        clear();
        return;
}

void edit_motor(string username){
    // Cek apakah user memiliki data motor
    bool kosong = true;
    for (int i = 0; i < data_motor.size(); i++){
        if (data_motor[i].owner == username){
            kosong = false;
            break;
        }
    }
    if (kosong){
        cout << "Anda belum memiliki data motor" << endl;
        pause();
        clear();
        return;
    }

    // vektor plat motor yang dimiliki user
    vector<string> plat_vector;
    // Tampilkan list motor yang dimiliki user
    cout << "=====================================================================================================================" << endl;
    cout << "                                                EDIT DATA MOTOR" << endl;
    cout << "=====================================================================================================================" << endl;
    cout << "                                              Username: " << username << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    // Menghitung jumlah motor yang dimiliki user
    int count = 1;
    // Header tabel
    cout << left << setw(5) << "No" << setw(20) << "Nama Motor" << setw(20) << "Warna" << setw(20) << "Transmisi" << setw(20) 
        << "Plat" << setw(20) << "Jarak Tempuh" << setw(10) << "Diservis" << endl;
    for (int i = 0; i < data_motor.size(); i++){
        if (data_motor[i].owner == username){
            // Tampilkan data motor yang dimiliki user
            cout << setw(5) << count << setw(20) << data_motor[i].nama_motor << setw(20) << data_motor[i].warna_motor << setw(20)
                << data_motor[i].transmisi << setw(20) << data_motor[i].plat << setw(20) << data_motor[i].jarak_tempuh << setw(10);
            if (data_motor[i].servis){
                cout << "Yes" << endl;
            }
            else{
                cout << "No" << endl;
            }
            count++;
            plat_vector.push_back(data_motor[i].plat);
        }
    }
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    // Pilih Nomor Motor yang akan diedit
    int pilih_motor;
    while (true) {
        cout << "Pilih nomor motor untuk diedit: ";
        // jika input tidak sesuai, bukan angka, lebih dari 1 kata, ulangi input
        if (!(cin >> pilih_motor) || cin.peek() != '\n'){
            cin.clear();
            cin.ignore(999, '\n');
            cout << "Input tidak valid. Silahkan input ulang." << endl;
            continue;
        }

        // Jika nomor yang dipilih sesuai dengan jumlah motor
        if (pilih_motor >= 1 && pilih_motor <= count-1){ 
            clear();
            // Simpan plat saat ini dari motor yang dipilih
            string plat_motor_temp = plat_vector[pilih_motor-1];

            // Jika nomor yang dipilih sedang diservis, tidak boleh diedit
            for (int i = 0; i < data_motor.size(); i++){
                if (data_motor[i].owner == username && data_motor[i].plat == plat_motor_temp){
                    if (data_motor[i].servis){
                        clear();
                        cout << "Motor sedang diservis, tidak bisa diedit" << endl;
                        pause();
                        clear();
                        return;
                    }
                }
            }

            cout << "=============================" << endl;
            cout << "       EDIT DATA MOTOR" << endl;
            cout << "=============================" << endl;
            cout << "Username: " << username << endl;
            cout << "----------------------------" << endl;
            // Tampilkan data singkat motor yang dipilih
            for (int i = 0; i < data_motor.size(); i++){
                if (data_motor[i].owner == username && data_motor[i].plat == plat_motor_temp){
                    // gunakan setw
                    cout << left << setw(15) << "Nama Motor" << ": " << data_motor[i].nama_motor << endl;
                    cout << left << setw(15) << "Warna Motor" << ": " << data_motor[i].warna_motor << endl;
                    cout << left << setw(15) << "Transmisi" << ": " << data_motor[i].transmisi << endl;
                    cout << left << setw(15) << "Plat" << ": " << data_motor[i].plat << endl;
                    cout << left << setw(15) << "Jarak Tempuh" << ": " << data_motor[i].jarak_tempuh << " KM" << endl;
                    cout << left << setw(15) << "Diservis" << ": ";
                    if (data_motor[i].servis){
                        cout << "Yes" << endl;
                    }
                    else{
                        cout << "No" << endl;
                    }
                }
            }
            cout << "=============================" << endl;
            // Input data baru
            cout <<  "         Data Baru" << endl;
            cout << "----------------------------" << endl;
            for (int i = 0; i < data_motor.size(); i++){
                // Jika data motor sesuai dengan username dan plat motor yang dipilih
                if (data_motor[i].owner == username && data_motor[i].plat == plat_motor_temp){
                    string nama_motor, warna_motor, transmisi_motor, plat_motor;
                    int jarak_tempuh;
                    // Input nama motor
                    cout << "Nama Motor: ";
                    cin.ignore();
                    while (true){
                        getline(cin, nama_motor);
                        // Mengecek input nama motor tidak mengandung koma
                        if (nama_motor.find(",") != string::npos){
                            cout << "Nama motor tidak boleh mengandung koma" << endl;
                            cout << "Nama Motor: ";
                        }
                        // Mengecek input nama motortidak boleh kosong
                        else if (nama_motor.length() <= 0){
                            cout << "Nama motor tidak boleh kosong" << endl;
                            cout << "Nama Motor: ";
                        }
                        else{
                            break;
                        }
                    }

                    // Input warna motor
                    cout << "Warna Motor: ";
                    while (true){
                        getline(cin, warna_motor);
                        // Mengecek input warna motor tidak mengandung koma
                        if (warna_motor.find(",") != string::npos){
                            cout << "Warna motor tidak boleh mengandung koma" << endl;
                            cout << "Warna Motor: ";
                        }
                        // Mengecek input tidak boleh kosong
                        else if (warna_motor.length() <= 0){
                            cout << "Warna motor tidak boleh kosong" << endl;
                            cout << "Warna Motor: ";
                        }
                        else{
                            break;
                        }
                    }

                    // Input transmisi, "manual" atau "automatic"
                    cout << "Transmisi Motor: ";
                    while (true){
                        getline(cin, transmisi_motor);
                        // mengubah input transmisi menjadi lowercase
                        for (int i = 0; i < transmisi_motor.length(); i++){
                            transmisi_motor[i] = tolower(transmisi_motor[i]);
                        }

                        if (transmisi_motor == "manual" || transmisi_motor == "automatic"){
                            break;
                        }
                        else{
                            cout << "Transmisi motor hanya bisa manual atau automatic" << endl;
                            cout << "Transmisi Motor: ";
                        }
                    }

                    // Input plat motor
                    string data_plat_temp;
                    string inp_plat_temp;
                    bool pass;
                    while (true){
                        pass = true;
                        cout << "Plat Motor: ";
                        getline(cin, plat_motor);
                        // Input plat motor tidak boleh kosong
                        if (plat_motor.find_first_not_of(' ') == string::npos){
                            cout << "Plat motor tidak boleh kosong" << endl;
                            continue;
                        }
                        // Input plat motor tidak boleh mengandung koma
                        if (plat_motor.find(",") != string::npos){
                            cout << "Plat motor tidak boleh mengandung koma" << endl;
                            continue;
                        }
                        // Ubah input plat jadi kapital
                        for (int i = 0; i < plat_motor.length(); i++){
                            plat_motor[i] = toupper(plat_motor[i]);
                        }
                        // Cek keunikan tanpa spasi, boleh sama dengan yang sebelumnya
                        for (int i = 0; i < data_motor.size(); i++){
                            data_plat_temp = data_motor[i].plat;
                            inp_plat_temp = plat_motor;
                            // Hapus spasi
                            data_plat_temp.erase(remove(data_plat_temp.begin(), data_plat_temp.end(), ' '), data_plat_temp.end());
                            inp_plat_temp.erase(remove(inp_plat_temp.begin(), inp_plat_temp.end(), ' '), inp_plat_temp.end());
                            // Jika plat motor sudah ada atau sama dengan yang sebelumnya
                            if (data_plat_temp == inp_plat_temp && data_motor[i].plat != plat_motor){
                                cout << "Plat motor sudah ada" << endl;
                                pass = false;
                                break;
                            }
                        }
                        if (pass){
                            break;
                        }
                    }

                    // Input jarak tempuh
                    cout << "Jarak Tempuh (KM): ";
                    while (!(cin >> jarak_tempuh) || cin.peek() != '\n' || jarak_tempuh < 0) {
                        cout << "Invalid input. Silahkan masukkan angka yang benar." << endl;
                        cin.clear();
                        cin.ignore(999, '\n');
                        cout << "Jarak Tempuh (KM): ";
                    }

                    // Simpan editan motor ke vektor sementara
                    motor_data new_motor;
                    new_motor.owner = username;
                    new_motor.nama_motor = nama_motor;
                    new_motor.warna_motor = warna_motor;
                    new_motor.transmisi = transmisi_motor;
                    new_motor.plat = plat_motor;
                    new_motor.jarak_tempuh = jarak_tempuh;
                    new_motor.servis = false;

                    // Hapus data motor yang sebelumnya
                    data_motor.erase(data_motor.begin() + i);
                    // Hapus data kondisi motor yang sebelumnya
                    if (transmisi_motor == "manual"){
                        for (int i = 0; i < data_kondisi_manual.size(); i++){
                            if (data_kondisi_manual[i].plat == plat_motor_temp){
                                data_kondisi_manual.erase(data_kondisi_manual.begin() + i);
                            }
                        }
                    }
                    if (transmisi_motor == "automatic"){
                        for (int i = 0; i < data_kondisi_automatic.size(); i++){
                            if (data_kondisi_automatic[i].plat == plat_motor_temp){
                                data_kondisi_automatic.erase(data_kondisi_automatic.begin() + i);
                            }
                        }
                    }
                    // Tambahkan data vektor yang baru
                    data_motor.push_back(new_motor);

                    // Sort data motor dengan bubble sort, ascending berdasarkan plat
                    for (int i = 0; i < data_motor.size(); i++){
                        for (int j = 0; j < data_motor.size()-1; j++){
                            if (data_motor[j].plat > data_motor[j+1].plat){
                                motor_data temp = data_motor[j];
                                data_motor[j] = data_motor[j+1];
                                data_motor[j+1] = temp;
                            }
                        }
                    }

                    // Input kondisi motor
                    cout << "=============================" << endl;
                    cout << "    Terakhir Servis(Km)" << endl;
                    cout << "=============================" << endl;

                    // Jika transmisi adalah automatic
                    if (transmisi_motor == "automatic") {
                        kondisi_automatic kondisi;
                        kondisi.plat = plat_motor;
                        // Input kondisi motor automatic, harus angka > 0, dan jika lebih dari 1 kata ulangi
                        cout << "Ban Belakang: ";
                        // Input harus angka lebih dari 0 tapi kurang dari jarak tempuh motor, dan jika lebih dari 1 kata ulangi
                        while (!(cin >> kondisi.ban_belakang) || cin.peek() != '\n' 
                        || kondisi.ban_belakang < 0 || kondisi.ban_belakang > jarak_tempuh) {
                            cout << "Input Invalid, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                            cout << "Ban Belakang: ";
                        }
                        cout << "Ban Depan: ";
                        while (!(cin >> kondisi.ban_depan) || cin.peek() != '\n' 
                        || kondisi.ban_depan < 0 || kondisi.ban_depan > jarak_tempuh) {
                            cout << "Input Invalid, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                            cout << "Ban Depan: ";
                        }
                        cout << "Busi: ";
                        while (!(cin >> kondisi.busi) || cin.peek() != '\n' 
                        || kondisi.busi < 0 || kondisi.busi > jarak_tempuh) {
                            cout << "Input Invalid, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                            cout << "Busi: ";
                        }
                        cout << "Kampas Rem: ";
                        while (!(cin >> kondisi.kampas_rem) || cin.peek() != '\n'
                        || kondisi.kampas_rem < 0 || kondisi.kampas_rem > jarak_tempuh) {
                            cout << "Input Invalid, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                            cout << "Kampas Rem: ";
                        }
                        cout << "Minyak Rem: ";
                        while (!(cin >> kondisi.minyak_rem) || cin.peek() != '\n'
                        || kondisi.minyak_rem < 0 || kondisi.minyak_rem > jarak_tempuh) {
                            cout << "Input Invalid, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                            cout << "Minyak Rem: ";
                        }
                        cout << "Oli Gardan: ";
                        while (!(cin >> kondisi.oli_gardan) || cin.peek() != '\n'
                        || kondisi.oli_gardan < 0 || kondisi.oli_gardan > jarak_tempuh) {
                            cout << "Input Invalid, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                            cout << "Oli Gardan: ";
                        }
                        cout << "Oli Mesin: ";
                        while (!(cin >> kondisi.oli_mesin) || cin.peek() != '\n'
                        || kondisi.oli_mesin < 0 || kondisi.oli_mesin > jarak_tempuh) {
                            cout << "Input Invalid, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                            cout << "Oli Mesin: ";
                        }
                        cout << "Roller: ";
                        while (!(cin >> kondisi.roller) || cin.peek() != '\n'
                        || kondisi.roller < 0 || kondisi.roller > jarak_tempuh) {
                            cout << "Input Invalid, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                            cout << "Roller: ";
                        }
                        cout << "Van Belt: ";
                        while (!(cin >> kondisi.van_belt) || cin.peek() != '\n'
                        || kondisi.van_belt < 0 || kondisi.van_belt > jarak_tempuh) {
                            cout << "Input Invalid, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                            cout << "Van Belt: ";
                        }

                        // Tambahkan data vektor yang baru
                        data_kondisi_automatic.push_back(kondisi);
                        // Sort data kondisi automatic  dengan bubble sort, ascending berdasarkan plat
                        for (int i = 0; i < data_kondisi_automatic.size(); i++){
                            for (int j = 0; j < data_kondisi_automatic.size()-1; j++){
                                if (data_kondisi_automatic[j].plat > data_kondisi_automatic[j+1].plat){
                                    kondisi_automatic temp = data_kondisi_automatic[j];
                                    data_kondisi_automatic[j] = data_kondisi_automatic[j+1];
                                    data_kondisi_automatic[j+1] = temp;
                                }
                            }
                        }
                    }

                    // Jika transmisi adalah manual
                    if (transmisi_motor == "manual") {
                        kondisi_manual kondisi;
                        kondisi.plat = plat_motor;
                        cout << "Ban Belakang: ";
                        // Input kondisi motor manual, harus angka, dan jika lebih dari 1 kata ulangi
                        while (!(cin >> kondisi.ban_belakang) || cin.peek() != '\n' 
                        || kondisi.ban_belakang < 0 || kondisi.ban_belakang > jarak_tempuh) {
                            cout << "Input Invalid, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                            cout << "Ban Belakang :";
                        }
                        cout << "Ban Depan: ";
                        while (!(cin >> kondisi.ban_depan) || cin.peek() != '\n'
                        || kondisi.ban_depan < 0 || kondisi.ban_depan > jarak_tempuh) {
                            cout << "Input Invalid, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                            cout << "Ban Depan: ";
                        }
                        cout << "Busi: ";
                        while (!(cin >> kondisi.busi) || cin.peek() != '\n'
                        || kondisi.busi < 0 || kondisi.busi > jarak_tempuh) {
                            cout << "Input Invalid, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                            cout << "Busi: ";
                        }
                        cout << "Gear: ";
                        while (!(cin >> kondisi.gear) || cin.peek() != '\n'
                        || kondisi.gear < 0 || kondisi.gear > jarak_tempuh) {
                            cout << "Input Invalid, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                            cout << "Gear: ";
                        }
                        cout << "Kampas Kopling: ";
                        while (!(cin >> kondisi.kampas_kopling) || cin.peek() != '\n'
                        || kondisi.kampas_kopling < 0 || kondisi.kampas_kopling > jarak_tempuh) {
                            cout << "Input Invalid, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                            cout << "Kampas Kopling: ";
                        }
                        cout << "Kampas Rem: ";
                        while (!(cin >> kondisi.kampas_rem) || cin.peek() != '\n'
                        || kondisi.kampas_rem < 0 || kondisi.kampas_rem > jarak_tempuh) {
                            cout << "Input Invalid, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                            cout << "Kampas Rem: ";
                        }
                        cout << "Minyak Rem: ";
                        while (!(cin >> kondisi.minyak_rem) || cin.peek() != '\n'
                        || kondisi.minyak_rem < 0 || kondisi.minyak_rem > jarak_tempuh) {
                            cout << "Input Invalid, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                            cout << "Minyak Rem: ";
                        }
                        cout << "Oli Mesin: ";
                        while (!(cin >> kondisi.oli_mesin) || cin.peek() != '\n'
                        || kondisi.oli_mesin < 0 || kondisi.oli_mesin > jarak_tempuh) {
                            cout << "Input Invalid, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                            cout << "Oli Mesin: ";
                        }
                        cout << "Rantai: ";
                        while (!(cin >> kondisi.rantai) || cin.peek() != '\n'
                        || kondisi.rantai < 0 || kondisi.rantai > jarak_tempuh) {
                            cout << "Input Invalid, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();  
                            cin.ignore(999, '\n');
                            cout << "Rantai: ";
                        }
                        // Tambahkan data vektor yang baru
                        data_kondisi_manual.push_back(kondisi);
                        // Sort data kondisi manual dengan bubble sort, ascending berdasarkan plat
                        for (int i = 0; i < data_kondisi_manual.size(); i++){
                            for (int j = 0; j < data_kondisi_manual.size()-1; j++){
                                if (data_kondisi_manual[j].plat > data_kondisi_manual[j+1].plat){
                                    kondisi_manual temp = data_kondisi_manual[j];
                                    data_kondisi_manual[j] = data_kondisi_manual[j+1];
                                    data_kondisi_manual[j+1] = temp;
                                }
                            }
                        }
                    }

                    // Sort data motor dengan bubble sort, ascending berdasarkan plat
                    for (int i = 0; i < data_motor.size(); i++){
                        for (int j = 0; j < data_motor.size()-1; j++){
                            if (data_motor[j].plat > data_motor[j+1].plat){
                                motor_data temp = data_motor[j];
                                data_motor[j] = data_motor[j+1];
                                data_motor[j+1] = temp;
                            }
                        }
                    }

                    // Update vektor data_struk_servis
                    for (int i = 0; i < data_struk_servis.size(); i++){
                        if (data_struk_servis[i].plat == plat_motor_temp && data_struk_servis[i].status_akun == "active"){
                            data_struk_servis[i].plat = plat_motor;
                        }
                    }

                    // Update csv data motor & pesanan servis
                    write_csv_motor();
                    read_csv_motor();
                    write_csv_struk_servis();
                    read_csv_struk_servis();
                    cout << "Data motor berhasil diubah!" << endl;
                    pause();
                    clear();
                    return;
                }
            }
        }
        // Input tidak sesuai
        else {
            cout << "Pilihan tidak tersedia. Silahkan masukkan nomor yang sesuai" << endl;
        }
    }
}

void hapus_motor(string username){
    // Cek apakah user memiliki data motor
    bool kosong = true;
    for (int i = 0; i < data_motor.size(); i++){
        if (data_motor[i].owner == username){
            kosong = false;
            break;
        }
    }
    if (kosong){
        cout << "Anda belum memiliki data motor" << endl;
        pause();
        clear();
        return;
    }

    vector<string> plat_vector;
    // Tampilkan list motor yang dimiliki user
    while (true){
        cout << "=====================================================================================================================" << endl;
        cout << "                                                  HAPUS MOTOR" << endl;
        cout << "=====================================================================================================================" << endl;
        cout << "                                              Username: " << username << endl;
        cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
        // Menghitung jumlah motor yang dimiliki user
        int count = 1;
        // Tampilkan data motor yang dimiliki user
        // Header
        cout << left << setw(5) << "No" << setw(20) << "Nama Motor" << setw(20) << "Warna" << setw(20) << "Transmisi" << setw(20) 
            << "Plat" << setw(20) << "Jarak Tempuh" << setw(10) << "Diservis" << endl;
        for (int i = 0; i < data_motor.size(); i++){
            if (data_motor[i].owner == username){
                // Gunakan tabel setw, untuk menampilkan
                // Header, Pastikan nilai set w sudah sesuai
                // tampilkan data motor yang dimiliki user
                cout << setw(5) << count << setw(20) << data_motor[i].nama_motor << setw(20) << data_motor[i].warna_motor << setw(20)
                    << data_motor[i].transmisi << setw(20) << data_motor[i].plat << setw(20) << data_motor[i].jarak_tempuh << setw(10);
                if (data_motor[i].servis){
                    cout << "Yes" << endl;
                }
                else{
                    cout << "No" << endl;
                }
                plat_vector.push_back(data_motor[i].plat);
                count++;
            }
        }
        cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
        // Pilih Nomor Motor yang akan dihapus
        string str_pilih_motor;
        int pilih_motor;
        cout << "Pilih nomor motor untuk dihapus: ";
        getline(cin, str_pilih_motor);
        // Error Check
        if (str_pilih_motor.find_first_not_of("0123456789") != string::npos){
            cout << "Input tidak valid. Silahkan input ulang." << endl;
            pause();
            clear();
            continue;
        }
        else if(str_pilih_motor.length() == 0){
            cout << "Input tidak valid. Silahkan input ulang." << endl;
            pause();
            clear();
            continue;
        }
        else if(stoi(str_pilih_motor) < 1 || stoi(str_pilih_motor) > count-1){
            cout << "Input tidak valid. Silahkan input ulang." << endl;
            pause();
            clear();
            continue;
        }
        else if (str_pilih_motor.find(" ") != string::npos){
            cout << "Input tidak valid. Silahkan input ulang." << endl;
            pause();
            clear();
            continue;
        }
        else{
            pilih_motor = stoi(str_pilih_motor);
        }
        
        clear();
        // Simpan plat dari motor yang dipilih
        string plat_motor_temp = plat_vector[pilih_motor-1];

        // Jika nomor yang dipilih sedang diservis, tidak boleh dihapus, return
        for (int i = 0; i < data_motor.size(); i++){
            if (data_motor[i].owner == username && data_motor[i].plat == plat_motor_temp){
                if (data_motor[i].servis){
                    clear();
                    cout << "Motor sedang diservis, tidak bisa dihapus" << endl;
                    pause();
                    clear();
                    return;
                }
            }
        }
        // Hapus data motor yang dipilih dari vektor
        for (int i = 0; i < data_motor.size(); i++){
            if (data_motor[i].owner == username && data_motor[i].plat == plat_motor_temp){
                data_motor.erase(data_motor.begin() + i);
            }
        }
        // Hapus data kondisi motor
        for (int i = 0; i < data_kondisi_manual.size(); i++){
            if (data_kondisi_manual[i].plat == plat_motor_temp){
                data_kondisi_manual.erase(data_kondisi_manual.begin() + i);
            }
        }
        for (int i = 0; i < data_kondisi_automatic.size(); i++){
            if (data_kondisi_automatic[i].plat == plat_motor_temp){
                data_kondisi_automatic.erase(data_kondisi_automatic.begin() + i);
            }
        }

        // Update csv data motor
        write_csv_motor();
        read_csv_motor();
        cout << "Data motor berhasil dihapus!" << endl;
        pause();
        clear();
        return;
    }
}

void edit_akun_user(string *username){

    /// Cuma bisa edit akun ketika tidak ada motor yang sedang servis
    for (int i = 0; i < data_motor.size(); i++){
        if (data_motor[i].owner == *username && data_motor[i].servis){
            cout << "Motor sedang diservis, tidak bisa mengedit akun" << endl;
            pause();
            clear();
            return;
        }
    }

    // Tampilkan data akun user
    string data_username_temp, data_telepon_temp;
    cout << "=============================" << endl;
    cout << "       EDIT DATA AKUN" << endl;
    cout << "=============================" << endl;
    for (int i = 0; i < data_user.size(); i++){
        if (data_user[i].username == *username){
            // tampilkan dalam bentuk tabel
            cout << left << setw(15) << "Username" << " : " << data_user[i].username << endl;
            cout << setw(15) << "Password" << " : " << data_user[i].password << endl;
            cout << setw(15) << "No. Telepon" << " : " << data_user[i].telepon << endl;
            cout << setw(15) << "Alamat" << " : " << data_user[i].address << endl;
            cout << "------------------------------------------" << endl;
            data_username_temp = data_user[i].username;
            data_telepon_temp = data_user[i].telepon;
        }
    }
    // Input data baru
    string inp_username_temp, inp_telepon_temp;
    for (int i = 0; i < data_user.size(); i++){
        if (data_user[i].username == *username){
            string new_username, new_password, new_telepon, new_address;
            
            // Input username
            cout << "Username baru: ";
            // Error checking username
            if (!(cin >> new_username) || cin.peek() != '\n' || new_username.find(" ") != string::npos 
            || new_username.find(",") != string::npos || new_username.length() < 8 ){
                cout << "Username tidak valid " << endl;
                pause();
                clear();
                cin.clear();
                cin.ignore(999 , '\n');
                return;
            }

            // Cek keunikan username dengan vektor data_user
            for (int i = 0; i < data_user.size(); i++){
                if (data_user[i].username == new_username && new_username != *username){
                    cout << "Username sudah terdaftar" << endl;
                    pause();
                    clear();
                    return;
                }
            }
            // Cek keunikan username dengan data admin
            ifstream file;
            file.open("Database/admin_log.csv");
            if (!file){
                cout << "Gagal membaca data admin (admin_log.csv)" << endl;
                pause();
                clear();
                return;
            }
            string baris, data;
            // skip header
            getline(file, baris);
            while (getline(file, baris)){
                stringstream ss(baris);
                getline(ss, data, ',');
                if (data == new_username){
                    cout << "Username sudah terdaftar" << endl;
                    pause();
                    clear();
                    return;
                }
            }
            file.close();


            // Input password
            cout << "Password baru: ";
            // Error checking password
            if (!(cin >> new_password) || cin.peek() != '\n' || new_password.find(" ") != string::npos
            || new_password.find(",") != string::npos || new_password.length() < 8){
                cout << "Password tidak valid " << endl;
                pause();
                clear();
                cin.clear();
                cin.ignore(999 , '\n');
                return;
            }

            // Input no telepon
            cout << "No. Telepon baru: ";
            // Error checking nomor telepon
            if(!(cin >> new_telepon) || cin.peek() != '\n' || new_telepon.length() < 10 || new_telepon.length() > 12){
                cout << "No. Telepon tidak valid " << endl;
                pause();
                clear();
                cin.clear();
                cin.ignore(999 , '\n');
                return;
            }
            // Nomor telepon harus numerik
            for (int i = 0; i < new_telepon.length(); i++){
                if (!isdigit(new_telepon[i])){
                    cout << "No. Telepon harus berupa angka " << endl;
                    pause();
                    clear();
                    return;
                }
            }
            // Mengecek keunikan nomor telepon
            for (int i = 0; i < data_user.size(); i++){
                if (data_user[i].telepon == new_telepon && new_telepon != data_telepon_temp){
                    cout << "No. Telepon sudah terdaftar" << endl;
                    pause();
                    clear();
                    return;
                }
            }

            // Input alamat
            cout << "Alamat baru: ";
            cin.ignore();
            getline(cin, new_address);
            // Mengecek input supaya tidak mengandung koma, dan tidak kosong
            if (new_address.find(",") != string::npos || new_address.length() == 0){
                cout << "Alamat tidak valid" << endl;
                pause();
                clear();
                return;
            }

            // Update Data Vektor User
            user_data new_user;
            new_user.username = new_username;
            new_user.password = new_password;
            new_user.telepon = new_telepon;
            new_user.address = new_address;
            // Hapus data user yang dipilih dari vektor
            data_user.erase(data_user.begin() + i);
            // Tambahkan data vektor yang baru ke csv
            data_user.push_back(new_user);

            // Sort data user dengan bubble sort, ascending berdasarkan username
            for (int i = 0; i < data_user.size(); i++){
                for (int j = 0; j < data_user.size()-1; j++){
                    if (data_user[j].username > data_user[j+1].username){
                        user_data temp = data_user[j];
                        data_user[j] = data_user[j+1];
                        data_user[j+1] = temp;
                    }
                }
            }

            // Update vektor list_motor dengan username lama menjadi username baru
            for (int i = 0; i < data_motor.size(); i++){
                if (data_motor[i].owner == *username){
                    data_motor[i].owner = new_username;
                }
            }

            // update username dari vektor struk servis dengan status_user = active
            for (int i = 0; i < data_struk_servis.size(); i++){
                if (data_struk_servis[i].username == *username && data_struk_servis[i].status_akun == "active"){
                    data_struk_servis[i].username = new_username;
                }
            }

            // update username dari vektor struk sparepart dengan status_user = active
            for (int i = 0; i < data_struk_sparepart.size(); i++){
                if (data_struk_sparepart[i].username == *username && data_struk_sparepart[i].status_akun == "active"){
                    data_struk_sparepart[i].username = new_username;
                }
            }

            // Update csv 
            write_csv_user();
            write_csv_motor();
            write_csv_struk_servis();
            write_csv_struk_sparepart();

            // Update username global
            *username = new_username;

            cout << "Data akun berhasil diubah!" << endl;
            pause();
            clear();
            return;
        }
    }

}

int hapus_akun_user(string username){
    // Cuma bisa hapus akun ketika tidak ada motor yang sedang servis
    for (int i = 0; i < data_motor.size(); i++){
        if (data_motor[i].owner == username){
            if (data_motor[i].servis){
                clear();
                cout << "Terdapat motor yang sedang diservis, tidak bisa hapus akun" << endl;
                pause();
                clear();
                return 0;
            }
        }
    }
    // Hapus data user yang dipilih dari vektor
    for (int i = 0; i < data_user.size(); i++){
        if (data_user[i].username == username){
            data_user.erase(data_user.begin() + i);
        }
    }
    // Hapus data motor yang dipilih dari vektor
    for (int i = 0; i < data_motor.size(); i++){
        // cari data motor yang dimiliki user
        if (data_motor[i].owner == username){
            /// Hapus  data kondisi motor
            if (data_motor[i].transmisi == "automatic"){
                for (int i = 0; i < data_kondisi_automatic.size(); i++){
                    if (data_kondisi_automatic[i].plat == data_motor[i].plat){
                        data_kondisi_automatic.erase(data_kondisi_automatic.begin() + i);
                    }
                }
            }
            if (data_motor[i].transmisi == "manual"){
                for (int i = 0; i < data_kondisi_manual.size(); i++){
                    if (data_kondisi_manual[i].plat == data_motor[i].plat){
                        data_kondisi_manual.erase(data_kondisi_manual.begin() + i);
                    }
                }
            }
            // Hapus data motor yang dimiliki user
            data_motor.erase(data_motor.begin() + i);
            // Supaya tidak melewati elemen selanjutnya, karena elemen saat ini sudah dihapus
            i--;
        }
    }

    // Ubah status akun (deleted) di vektor struk servis
    for (int i = 0; i < data_struk_servis.size(); i++){
        if (data_struk_servis[i].username == username && data_struk_servis[i].status_akun == "active"){
            data_struk_servis[i].status_akun = "deleted";
        }
    }
    // Ubah status akun (deleted) di vektor struk sparepart
    for (int i = 0; i < data_struk_sparepart.size(); i++){
        if (data_struk_sparepart[i].username == username && data_struk_sparepart[i].status_akun == "active"){
            data_struk_sparepart[i].status_akun = "deleted";
        }
    }

    // Update csv data user
    write_csv_user();
    write_csv_motor();
    write_csv_struk_servis();
    write_csv_struk_sparepart();
    clear();

    // "Akun {username} berhasil dihapus"
    cout << "Akun " << username << " berhasil dihapus" << endl;
    pause();
    clear();
    return 1;
}

// Fungsi-fungsi menu
int menu_awal(){
    string str_pilih;
    int pilih;
    while (true) {
        cout << "=============================" << endl;
        cout << "          MENU AWAL" << endl;
        cout << "=============================" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cout << "Pilih menu: ";
        // input pilhan menu
        getline(cin, str_pilih);
        // Error checking
        if (str_pilih.find_first_not_of("123") != string::npos || str_pilih.length() > 1){
            cout << "Input tidak valid. Silahkan masukkan angka 1-3." << endl;
            pause();
            clear();
            continue;
        }
        if (str_pilih.find_first_not_of(" ") == string::npos){
            cout << "Input tidak boleh kosong." << endl;
            pause();
            clear();
            continue;
        }
        // Konversi string ke integer
        pilih = stoi(str_pilih);
        return pilih;
    }
}

// Menu-menu user
void menu_motor(string global_username){
    string str_pilih;
    int pilih;
    while (true) {
        cout << "=============================" << endl;
        cout << "        MENU DATA MOTOR" << endl;
        cout << "=============================" << endl;
        cout << "Username: " << global_username << endl;
        cout << "----------------------------" << endl;
        cout << "1. Tambah Data Motor" << endl;
        cout << "2. Lihat Data Motor" << endl;
        cout << "3. Edit Data Motor" << endl;
        cout << "4. Hapus Data Motor" << endl;
        cout << "5. Kembali (Menu User)" << endl;
        cout << "----------------------------" << endl;
        cout << "Pilih menu: ";
        // input pilhan menu
        getline(cin, str_pilih);
        // Error checking
        if (str_pilih.find_first_not_of("12345") != string::npos || str_pilih.length() > 1){
            cout << "Input tidak valid. Silahkan masukkan angka 1-5." << endl;
            pause();
            clear();
            continue;
        }
        if (str_pilih.find_first_not_of(" ") == string::npos){
            cout << "Input tidak boleh kosong." << endl;
            pause();
            clear();
            continue;
        }
        // Konversi string ke integer
        pilih = stoi(str_pilih);
        switch (pilih)
        {
        case 1:
            // Tambah Data Motor
            clear();
            add_motor(global_username);
            break;
        case 2:
            // Lihat Data Motor
            clear();
            view_motor(global_username);
            break;
        case 3:
            // Edit Data Motor
            clear();
            edit_motor(global_username);
            break;
        case 4:
            // Hapus Data Motor
            clear();
            hapus_motor(global_username);
            break;
        case 5:
            // Kembali (Menu User)
            clear();
            return;
            break;
        }
    }
}

int menu_data_akun(string *global_username){
    int pilih;
    string str_pilih;
    while (true) {
        cout << "=============================" << endl;
        cout << "        MENU DATA AKUN" << endl;
        cout << "=============================" << endl;
        cout << "Username: " << *global_username << endl;
        cout << "----------------------------" << endl;
        cout << "1. Edit Data Akun" << endl;
        cout << "2. Hapus Akun" << endl;
        cout << "3. Kembali (Menu User)" << endl;
        cout << "----------------------------" << endl;
        cout << "Pilih menu: ";
        getline (cin, str_pilih);
        // Error checking
        if (str_pilih.find_first_not_of("123") != string::npos || str_pilih.length() > 1){
            cout << "Input tidak valid. Silahkan masukkan angka 1-3." << endl;
            pause();
            clear();
            continue;
        }
        if (str_pilih.find_first_not_of(" ") == string::npos){
            cout << "Input tidak boleh kosong." << endl;
            pause();
            clear();
            continue;
        }
        pilih = stoi(str_pilih);
        switch (pilih)
        {
        case 1:
            // Edit Data Akun
            clear();
            edit_akun_user(global_username);
            break;
        case 2:
            // Hapus Data Akun
            clear();
            if (hapus_akun_user(*global_username) == 1){
                return 1;
            }
            break;
        case 3:
            // Kembali (Menu User)
            clear();
            return 0; // Tidak Logout
            break;
        }
    }
}

void menu_perawatan(string global_username){
    // Jika tidak ada motor
    bool kosong = true;
    for (int i = 0; i < data_motor.size(); i++){
        if (data_motor[i].owner == global_username){
            kosong = false;
            break;
        }
    }
    if (kosong){
        cout << "Anda belum memiliki data motor" << endl;
        pause();
        clear();
        return;
    }
    // 1. Tampilkan List Motor yang dimiliki user
    cout << "=====================================================================================================================" << endl;
    cout << "                                                 MENU PERAWATAN" << endl;
    cout << "=====================================================================================================================" << endl;
    cout << "                                              Username: " << global_username << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    // Menghitung jumlah motor yang dimiliki user
    int count = 1;
    // Tampilkan data motor yang dimiliki user
    // Header
    cout << setw(5) << "No" << setw(20) << "Nama Motor" << setw(20) << "Warna" << setw(20) << "Transmisi" << setw(20) 
        << "Plat" << setw(20) << "Jarak Tempuh" << endl;
    for (const auto& motor : data_motor) {
        if (motor.owner == global_username) {
            // Tampilkam data motor yang dimiliki user
            cout << setw(5) << count << setw(20) << motor.nama_motor << setw(20) << motor.warna_motor << setw(20)
                << motor.transmisi << setw(20) << motor.plat << setw(20) << motor.jarak_tempuh << endl;
            count++;
        }
    }
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;

    // 2. Pilih motor yang akan ditunjukkan jadwal perawatan
    string plat_motor;
    cout << "Pilih motor (plat): ";
    getline(cin,plat_motor);
    for (const auto& motor : data_motor) {
        if (motor.plat == plat_motor) {
            // 3. Tampilkan jadwal perawatan per sparepart
            clear();
            cout << "============================================" << endl;
            cout << "      MENU PERAWATAN MOTOR " << endl;
            cout << "============================================" << endl;
            cout << "        Username: " << global_username << endl;
            cout << "--------------------------------------------" << endl;
            //  tampilkan data singkat motor, setw
            cout << left << setw(15) << "Nama Motor" << " : " << setw(15) << motor.nama_motor << endl;
            cout << setw(15) << "Warna" << " : " << setw(15) << motor.warna_motor << endl;
            cout << setw(15) << "Transmisi" << " : " << setw(15) << motor.transmisi << endl;
            cout << setw(15) << "Plat" << " : " << setw(15) << motor.plat << endl;
            cout << setw(15) << "Jarak Tempuh" << " : " << setw(15) << motor.jarak_tempuh << endl;
            cout << "--------------------------------------------" << endl;
            // Header Jadwal Perawatan
            cout << setw(15) << "Sparepart" << setw(19) << "Keterangan" << endl;
            cout << "--------------------------------------------" << endl;
            // Pengeckkan jika transmisi motor manual
            if (motor.transmisi == "manual"){
                for (const auto& kondisi : data_kondisi_manual){
                    if (kondisi.plat == plat_motor){
                        // Pengecekan Ban Belakang
                        for (int i = 0; i < data_list_sparepart.size(); i++){
                            if (data_list_sparepart[i].nama_sparepart == "ban belakang"){

                                // Jika masih dalam batas waktu servis
                                if ((motor.jarak_tempuh - kondisi.ban_belakang) <= data_list_sparepart[i].kilometer){
                                    cout << setw(15) << "Ban Belakang" << "Servis Dalam " << (data_list_sparepart[i].kilometer - (motor.jarak_tempuh - kondisi.ban_belakang)) << " KM"<< endl;
                                }
                                // Jika telat servis
                                else {
                                    cout << setw(15) << "Ban Belakang" << " Telat  " << ((motor.jarak_tempuh - kondisi.ban_belakang) - data_list_sparepart[i].kilometer) << " KM"<< endl;
                                }
                            }
                        }
                        // Pengecekan Ban Depan
                        for (int i = 0; i < data_list_sparepart.size(); i++){
                            if (data_list_sparepart[i].nama_sparepart == "ban depan"){
                                // Jika masih dalam batas waktu servis
                                if (motor.jarak_tempuh - kondisi.ban_depan <= data_list_sparepart[i].kilometer){
                                    cout << setw(15) << "Ban Depan" << "Servis Dalam " << (data_list_sparepart[i].kilometer - (motor.jarak_tempuh - kondisi.ban_depan)) << " KM"<< endl;
                                }
                                // Jika telat servis
                                else {
                                    cout << setw(15) << "Ban Depan" << " Telat  " << ((motor.jarak_tempuh - kondisi.ban_depan) - data_list_sparepart[i].kilometer) << " KM"<< endl;
                                }
                            }
                        }               
                        // Pengecekan Busi
                        for (int i = 0; i < data_list_sparepart.size(); i++){
                            if (data_list_sparepart[i].nama_sparepart == "busi"){
                                // Jika masih dalam batas waktu servis
                                if (motor.jarak_tempuh - kondisi.busi <= data_list_sparepart[i].kilometer){
                                    cout << setw(15) << "Busi" << "Servis Dalam " << (data_list_sparepart[i].kilometer - (motor.jarak_tempuh - kondisi.busi)) << " KM"<< endl;
                                }
                                // Jika telat servis
                                else {
                                    cout << setw(15) << "Busi" << " Telat  " << ((motor.jarak_tempuh - kondisi.busi) - data_list_sparepart[i].kilometer) << " KM"<< endl;
                                }
                            }
                        }
                        // Pengecekan Kampas Kopling
                        for (int i = 0; i < data_list_sparepart.size(); i++){
                            if (data_list_sparepart[i].nama_sparepart == "kampas kopling"){
                                // Jika masih dalam batas waktu servis
                                if (motor.jarak_tempuh - kondisi.kampas_kopling <= data_list_sparepart[i].kilometer){
                                    cout << setw(15) << "Kampas Kopling" << "Servis Dalam " << (data_list_sparepart[i].kilometer - (motor.jarak_tempuh - kondisi.kampas_kopling)) << " KM"<< endl;
                                }
                                // Jika telat servis
                                else {
                                    cout << setw(15) << "Kampas Kopling" << " Telat  " << ((motor.jarak_tempuh - kondisi.kampas_kopling) - data_list_sparepart[i].kilometer) << " KM"<< endl;
                                }
                            }
                        }
                        // Pengecekan Kampas Rem
                        for (int i = 0; i < data_list_sparepart.size(); i++){
                            if (data_list_sparepart[i].nama_sparepart == "kampas rem"){
                                // Jika masih dalam batas waktu servis
                                if (motor.jarak_tempuh - kondisi.kampas_rem <= data_list_sparepart[i].kilometer){
                                    cout << setw(15) << "Kampas Rem" << "Servis Dalam " << (data_list_sparepart[i].kilometer - (motor.jarak_tempuh - kondisi.kampas_rem)) << " KM"<< endl;
                                }
                                // Jika telat servis
                                else {
                                    cout << setw(15) << "Kampas Rem" << " Telat  " << ((motor.jarak_tempuh - kondisi.kampas_rem) - data_list_sparepart[i].kilometer) << " KM"<< endl;
                                }
                            }
                        }                        
                        // Pengecekan Minyak Rem
                        for (int i = 0; i < data_list_sparepart.size(); i++){
                            if (data_list_sparepart[i].nama_sparepart == "minyak rem"){
                                // Jika masih dalam batas waktu servis
                                if (motor.jarak_tempuh - kondisi.minyak_rem <= data_list_sparepart[i].kilometer){
                                    cout << setw(15) << "Minyak Rem" << "Servis Dalam " << (data_list_sparepart[i].kilometer - (motor.jarak_tempuh - kondisi.minyak_rem)) << " KM"<< endl;
                                }
                                // Jika telat servis
                                else {
                                    cout << setw(15) << "Minyak Rem" << " Telat  " << ((motor.jarak_tempuh - kondisi.minyak_rem) - data_list_sparepart[i].kilometer) << " KM"<< endl;
                                }
                            }
                        }
                        // Pengecekan Oli Minyak
                        for (int i = 0; i < data_list_sparepart.size(); i++){
                            if (data_list_sparepart[i].nama_sparepart == "oli mesin"){
                                // Jika masih dalam batas waktu servis
                                if (motor.jarak_tempuh - kondisi.oli_mesin <= data_list_sparepart[i].kilometer){
                                    cout << setw(15) << "Oli Mesin" << "Servis Dalam " << (data_list_sparepart[i].kilometer - (motor.jarak_tempuh - kondisi.oli_mesin)) << " KM"<< endl;
                                }
                                // Jika telat servis
                                else {
                                    cout << setw(15) << "Oli Mesin" << " Telat  " << ((motor.jarak_tempuh - kondisi.oli_mesin) - data_list_sparepart[i].kilometer) << " KM"<< endl;
                                }
                            }
                        }
                        // Pengecekan Rantai
                        for (int i = 0; i < data_list_sparepart.size(); i++){
                            if (data_list_sparepart[i].nama_sparepart == "rantai"){
                                // Jika masih dalam batas waktu servis
                                if (motor.jarak_tempuh - kondisi.rantai <= data_list_sparepart[i].kilometer){
                                    cout << setw(15) << "Rantai" << "Servis Dalam " << (data_list_sparepart[i].kilometer - (motor.jarak_tempuh - kondisi.rantai)) << " KM"<< endl;
                                }
                                // Jika telat servis
                                else {
                                    cout << setw(15) << "Rantai" << " Telat  " << ((motor.jarak_tempuh - kondisi.rantai) - data_list_sparepart[i].kilometer) << " KM"<< endl;
                                }
                            }
                        }
                        pause();
                        clear();
                        return;
                    }
                }
            }
            // Pengecekkan kondisi motor jika transmisi adalah automatic
            if (motor.transmisi == "automatic") {
                for (const auto& kondisi : data_kondisi_automatic) {
                    if (kondisi.plat == plat_motor) {
                        // Pengecekan Ban Belakang
                        for (int i = 0; i < data_list_sparepart.size(); i++){
                            if (data_list_sparepart[i].nama_sparepart == "ban belakang"){
                                // Jika masih dalam batas waktu servis
                                if (motor.jarak_tempuh - kondisi.ban_belakang <= data_list_sparepart[i].kilometer){
                                    cout << setw(15) << "Ban Belakang" << "Servis Dalam " << (data_list_sparepart[i].kilometer - (motor.jarak_tempuh - kondisi.ban_belakang)) << " KM"<< endl;
                                }
                                // Jika telat servis
                                else {
                                    cout << setw(15) << "Ban Belakang" << " Telat  " << ((motor.jarak_tempuh - kondisi.ban_belakang) - data_list_sparepart[i].kilometer) << " KM"<< endl;
                                }
                            }
                        }
                        // Pengecekan Ban Depan
                        for (int i = 0; i < data_list_sparepart.size(); i++){
                            if (data_list_sparepart[i].nama_sparepart == "ban depan"){
                                // Jika masih dalam batas waktu servis
                                if (motor.jarak_tempuh - kondisi.ban_depan <= data_list_sparepart[i].kilometer){
                                    cout << setw(15) << "Ban Depan" << "Servis Dalam " << (data_list_sparepart[i].kilometer - (motor.jarak_tempuh - kondisi.ban_depan)) << " KM"<< endl;
                                }
                                // Jika telat servis
                                else {
                                    cout << setw(15) << "Ban Depan" << " Telat  " << ((motor.jarak_tempuh - kondisi.ban_depan) - data_list_sparepart[i].kilometer) << " KM"<< endl;
                                }
                            }
                        }
                        // Pengecekan Busi
                        for (int i = 0; i < data_list_sparepart.size(); i++){
                            if (data_list_sparepart[i].nama_sparepart == "busi"){
                                // Jika masih dalam batas waktu servis
                                if (motor.jarak_tempuh - kondisi.busi <= data_list_sparepart[i].kilometer){
                                    cout << setw(15) << "Busi" << "Servis Dalam " << (data_list_sparepart[i].kilometer - (motor.jarak_tempuh - kondisi.busi)) << " KM"<< endl;
                                }
                                // Jika telat servis
                                else {
                                    cout << setw(15) << "Busi" << " Telat  " << ((motor.jarak_tempuh - kondisi.busi) - data_list_sparepart[i].kilometer) << " KM"<< endl;
                                }
                            }
                        }
                        // Pengecekan Kampas Rem
                        for (int i = 0; i < data_list_sparepart.size(); i++){
                            if (data_list_sparepart[i].nama_sparepart == "kampas rem"){
                                // Jika masih dalam batas waktu servis
                                if (motor.jarak_tempuh - kondisi.kampas_rem <= data_list_sparepart[i].kilometer){
                                    cout << setw(15) << "Kampas Rem" << "Servis Dalam " << (data_list_sparepart[i].kilometer - (motor.jarak_tempuh - kondisi.kampas_rem)) << " KM"<< endl;
                                }
                                // Jika telat servis
                                else {
                                    cout << setw(15) << "Kampas Rem" << " Telat  " << ((motor.jarak_tempuh - kondisi.kampas_rem) - data_list_sparepart[i].kilometer) << " KM"<< endl;
                                }
                            }
                        }
                        // Pengecekan Minyak Rem
                        for (int i = 0; i < data_list_sparepart.size(); i++){
                            if (data_list_sparepart[i].nama_sparepart == "minyak rem"){
                                // Jika masih dalam batas waktu servis
                                if (motor.jarak_tempuh - kondisi.minyak_rem <= data_list_sparepart[i].kilometer){
                                    cout << setw(15) << "Minyak Rem" << "Servis Dalam " << (data_list_sparepart[i].kilometer - (motor.jarak_tempuh - kondisi.minyak_rem)) << " KM"<< endl;
                                }
                                // Jika telat servis
                                else {
                                    cout << setw(15) << "Minyak Rem" << " Telat  " << ((motor.jarak_tempuh - kondisi.minyak_rem) - data_list_sparepart[i].kilometer) << " KM"<< endl;
                                }
                            }
                        }
                        // Pengecekan Oli Gardan
                        for (int i = 0; i < data_list_sparepart.size(); i++){
                            if (data_list_sparepart[i].nama_sparepart == "oli gardan"){
                                // Jika masih dalam batas waktu servis
                                if (motor.jarak_tempuh - kondisi.oli_gardan <= data_list_sparepart[i].kilometer){
                                    cout << setw(15) << "Oli Gardan" << "Servis Dalam " << (data_list_sparepart[i].kilometer - (motor.jarak_tempuh - kondisi.oli_gardan)) << " KM"<< endl;
                                }
                                // Jika telat servis
                                else {
                                    cout << setw(15) << "Oli Gardan" << " Telat  " << ((motor.jarak_tempuh - kondisi.oli_gardan) - data_list_sparepart[i].kilometer) << " KM"<< endl;
                                }
                            }
                        }
                        // Pengecekan Oli Mesin
                        for (int i = 0; i < data_list_sparepart.size(); i++){
                            if (data_list_sparepart[i].nama_sparepart == "oli mesin"){
                                // Jika masih dalam batas waktu servis
                                if (motor.jarak_tempuh - kondisi.oli_mesin <= data_list_sparepart[i].kilometer){
                                    cout << setw(15) << "Oli Mesin" << "Servis Dalam " << (data_list_sparepart[i].kilometer - (motor.jarak_tempuh - kondisi.oli_mesin)) << " KM"<< endl;
                                }
                                // Jika telat servis
                                else {
                                    cout << setw(15) << "Oli Mesin" << " Telat  " << ((motor.jarak_tempuh - kondisi.oli_mesin) - data_list_sparepart[i].kilometer) << " KM"<< endl;
                                }
                            }
                        }
                        // Pengecekan roller
                        for (int i = 0; i < data_list_sparepart.size(); i++){
                            if (data_list_sparepart[i].nama_sparepart == "roller"){
                                // Jika masih dalam batas waktu servis
                                if (motor.jarak_tempuh - kondisi.roller <= data_list_sparepart[i].kilometer){
                                    cout << setw(15) << "Roller" << "Servis Dalam " << (data_list_sparepart[i].kilometer - (motor.jarak_tempuh - kondisi.roller)) << " KM"<< endl;
                                }
                                // Jika telat servis
                                else {
                                    cout << setw(15) << "Roller" << " Telat  " << ((motor.jarak_tempuh - kondisi.roller) - data_list_sparepart[i].kilometer) << " KM"<< endl;
                                }
                            }
                        }
                        // Pengecekan Van belt
                        for (int i = 0; i < data_list_sparepart.size(); i++){
                            if (data_list_sparepart[i].nama_sparepart == "van belt"){
                                // Jika masih dalam batas waktu servis
                                if (motor.jarak_tempuh - kondisi.van_belt <= data_list_sparepart[i].kilometer){
                                    cout << setw(15) << "Van Belt" << "Servis Dalam " << (data_list_sparepart[i].kilometer - (motor.jarak_tempuh - kondisi.van_belt)) << " KM"<< endl;
                                }
                                // Jika telat servis
                                else {
                                    cout << setw(15) << "Van Belt" << " Telat  " << ((motor.jarak_tempuh - kondisi.van_belt) - data_list_sparepart[i].kilometer) << " KM"<< endl;
                                }
                            }
                        }
                        pause();
                        clear();
                        return;
                    }
                }
            }
        }
    }
    // Jika plat motor tidak ditemukan
    cout << "Plat motor tidak ditemukan" << endl;
    pause();
    clear();

} 

void menu_user_servis(string global_username){
    // Variabel pilihan menu
    char pilih;
    while (true){
        cout << "====================================" << endl;
        cout << "          MENU JASA SERVIS" << endl;
        cout << "====================================" << endl;
        cout << "          Username: " << global_username << endl;
        cout << "------------------------------------" << endl;
        cout << "a. Pesan Jasa Servis Motor" << endl;
        cout << "b. Tampilkan History Servis" << endl;
        cout << "c. Kembali (Menu User)" << endl << endl;
        // Pilihan menu
        cout << "Pilih menu: ";
        cin >> pilih;
        // Pengecekkan input
        if (pilih == 'a' || pilih == 'b' || pilih == 'c'){
        } else {
            cout << "Input tidak valid" << endl;
            pause();
            clear();
            continue;
        }
        clear();
        // Pengecekkan input
        if (pilih == 'a'){
            clear();
            // Variabel hitung motor
            int hitung_motor = 0;
            // Tampilkan List Motor yang dimiliki user
            cout << "================================================================" << endl;
            cout << "                      PESAN JASA SERVIS" << endl;
            cout << "================================================================" << endl;
            cout << "                     Username: " << global_username << endl;
            cout << "----------------------------------------------------------------" << endl;
            cout << setw(5) << "No" << setw(14) << "Nama Motor" << setw(12) << "Warna" << setw(15) << "Transmisi" << setw(15)
                << "Plat" << setw(15) << "Jarak Tempuh" << endl;
            // Tampilkan List motor yang dimiliki user, yang belum diservis
            for (int i = 0; i < data_motor.size(); i++){
                if (data_motor[i].owner == global_username && data_motor[i].servis == false){
                    cout << setw(5) << hitung_motor+1 << setw(14) << data_motor[i].nama_motor << setw(12) << data_motor[i].warna_motor << setw(15)
                        << data_motor[i].transmisi << setw(15) << data_motor[i].plat << setw(15) << data_motor[i].jarak_tempuh << endl;
                    hitung_motor++;
                }
            }
            
            // Pengecekkan jika tidak ada motor yang bisa diservis
            if (hitung_motor == 0){
                clear();
                cout << "Tidak ada motor yang bisa diservis" << endl;
                pause();
                clear();
                continue;
            }
            // Pilih motor yang akan diservis
            int pilih_motor;
            cout << "----------------------------------------------------------------" << endl;
            cout << "Pilih nomor motor : ";
            cin >> pilih_motor;
            // Pengecekkan input
            if (pilih_motor < 1 || pilih_motor > hitung_motor){
                cout << "Input tidak valid" << endl;
                pause();
                clear();
                continue;
            } 
            // Mengubah servis motor menjadi true
            int no_motor = 0, no_motor_global;
            for (int i = 0; i < data_motor.size(); i++){
                if (data_motor[i].owner == global_username && data_motor[i].servis == false){
                    no_motor++;
                    if (no_motor == pilih_motor){
                        data_motor[i].servis = true;
                        no_motor_global = i;
                        break;
                    }
                }
            }
            // Menambahkan data baru ke dalam vektor struk_servis
            struk_servis new_struk_servis;
            new_struk_servis.id = data_struk_servis.size();
            new_struk_servis.username = global_username;
            new_struk_servis.plat = data_motor[no_motor_global].plat;
            new_struk_servis.status_servis = "ongoing";
            new_struk_servis.status_akun = "active";
            data_struk_servis.push_back(new_struk_servis);
            // Menulis data ke dalam file csv
            write_csv_motor();
            write_csv_struk_servis();

            // end massage
            cout << "Motor " << data_motor[no_motor_global].nama_motor << " akan segera diservis" << endl;
            pause();
            clear();


        } 
        if (pilih == 'b'){
            clear();
            // Tampilkan History servis Struk
            // Variabel nomor
            int no = 1;
            cout << "====================================" << endl;
            cout << "       RIWAYAT SERVIS STRUK" << endl;
            cout << "====================================" << endl;
            cout << "      Username: " << global_username << endl;
            cout << "------------------------------------" << endl;
            // Tampilkan data struk servis yang dimiliki user, setw
            // header setw
            cout << left << setw(5) << "ID" << setw(14) << "Plat" << "Status Servis" << endl;
            for (int i = 0; i < data_struk_servis.size(); i++){
                if (data_struk_servis[i].username == global_username && data_struk_servis[i].status_akun == "active"){
                    // tampilkan data struk servis
                    cout << left << setw(5) << data_struk_servis[i].id << setw(14) << data_struk_servis[i].plat 
                        << data_struk_servis[i].status_servis << endl;
                }
                no++;
            }
            // Menu Pilih Struk atau kembali ke menu user_servis
            int pilih_struk;
            cout << "------------------------------------" << endl;
            cout << "MENU :" << endl;
            cout << "1. Pilih Struk" << endl;
            cout << "2. Kembali (Menu User Servis)" << endl;
            cout << "Pilih menu: ";
            cin >> pilih;
            // Error checking, input huruf
            if (pilih == '1' || pilih == '2'){
                if (pilih == '2'){
                    clear();
                    continue;
                }
            } else {
                cout << "Input tidak valid" << endl;
                cin.ignore(9999, '\n');
                pause();
                clear();
                continue;
            }
            // Pilih Struk
            string str_pilih;
            cout << "Pilih ID Struk: ";
            cin.ignore();
            getline (cin, str_pilih);
            // Error checking
            if (str_pilih.find_first_not_of("1234567890") != string::npos){
                cout << "Input tidak valid" << endl;
                pause();
                clear();
                continue;
            }
            if (str_pilih.find_first_not_of(" ") == string::npos){
                cout << "Input tidak boleh kosong" << endl;
                pause();
                clear();
                continue;
            }
            // Konversi string ke integer
            pilih_struk = stoi(str_pilih);
            int index_strux;
            bool found = false;
            // Pengecekkan status servis, simpan index struk yang dipilih
            for (int i = 0; i < data_struk_servis.size(); i++){
                if (data_struk_servis[i].username == global_username && data_struk_servis[i].status_akun == "active" && data_struk_servis[i].id == pilih_struk){
                    if (data_struk_servis[i].status_servis == "ongoing"){
                        clear();
                        cout << "Motor masih dalam proses servis" << endl;
                        pause();
                        return;
                    }
                    index_strux = i;
                    found = true;
                }
            }
            // Pengecekkan jika struk tidak ditemukan
            if (!found){
                cout << "Struk tidak ditemukan" << endl;
                pause();
                clear();
                return;
            }

            // Tampilkan struk dengan id yang dipilih
            clear();
            // variabel nampung harga total
            int harga_total = 0;
            cout << "================================" << endl;
            cout << "          STRUK SERVIS "<< endl;
            cout << "================================" << endl;
            cout << "          Username: " << global_username << endl;
            cout << "--------------------------------" << endl;
            // Tampilkan data pesanan servis
            cout << left << setw(10) << "ID Struk" << " : " << data_struk_servis[index_strux].id << endl;
            cout << left << setw(10) << "Plat Motor" << " : " << data_struk_servis[index_strux].plat << endl;
            cout << "================================" << endl;
            // Tampilkan heder tabel
            cout << left << setw(16) << "Nama Servis" << "Harga Servis" << endl;
            cout << "--------------------------------" << endl;
            // Tampilkan data servis
            for (int i = 0; i < data_struk_servis.size(); i++){
                if (data_struk_servis[i].username == global_username && data_struk_servis[i].status_akun == "active" && data_struk_servis[i].id == pilih_struk){
                    // tampilkan detail struk vektor servis_data
                    for (int j = 0; j < data_struk_servis[i].servis.size(); j++){
                            cout << left << setw(16) << data_struk_servis[i].servis[j].nama_servis 
                                << data_struk_servis[i].servis[j].harga_servis << endl;
                            harga_total += data_struk_servis[i].servis[j].harga_servis;
                    }
                }
            }
            // tammpilkan harga total
            cout << "--------------------------------" << endl;
            cout << left << setw(14) << "Harga Total" << " : " << harga_total << endl;
            cout << "================================" << endl;
            pause();
            clear();
            continue;
        }
        if (pilih == 'c'){
            clear();
            cin.ignore();
            return;
        }
    }
}

void menu_user_sparepart(string global_username){
    char pilih;
    while (true){
        clear();
        cout << "====================================" << endl;
        cout << "          MENU SPAREPART" << endl;
        cout << "====================================" << endl;
        cout << "Username: " << global_username << endl;
        cout << "------------------------------------" << endl;
        cout << "a. Pesan Sparepart" << endl;
        cout << "b. Tampilkan History Pesanan Sparepart" << endl;
        cout << "c. Kembali (Menu User)" << endl << endl;
        // Pilihan menu
        cout << "Pilih menu: ";
        cin >> pilih;
        // error checking
        if (pilih == 'a' || pilih == 'b' || pilih == 'c'){
        } else {
            cout << "Input tidak valid" << endl;
            pause();
            clear();
            continue;
        }
        clear();
        if (pilih == 'a'){
            int id = data_struk_sparepart.size();
            string address, telepon;
            // simpan alamat user , cari address di data_user
            for (int i = 0; i < data_user.size(); i++){
                if (data_user[i].username == global_username){
                    address = data_user[i].address;
                    telepon = data_user[i].telepon;
                }
            }

            // cek apakah masih ada stok yang tersedia untuk seluruh sparepart
            bool stok_tersedia = false;
            for (int i = 0; i < data_list_sparepart.size(); i++){
                if (data_list_sparepart[i].stok_sparepart > 0){
                    stok_tersedia = true;
                    break;
                }
            }
            // Jika stok tidak tersedia
            if (!stok_tersedia){
                cout << "Stok sparepart tidak tersedia" << endl;
                pause();
                clear();
                continue;
            }
            // Tambahkan Struk Pemesanan Sparepart baru
            data_struk_sparepart.push_back({id, global_username, telepon, address, "active", {}});
            
            // Pesan Sparepart
            // 1. Tampilkan List Sparepart yang tersedia menggunakan setrecision sehingga berbentuk table yang rapi
            while (true){
                clear();
                cout << "=========================================================" << endl;
                cout << "                    LIST SPAREPART\n";
                cout << "=========================================================" << endl;
                cout << left <<setw(5) << "No" << setw(20) << left << "Nama Sparepart" << setw(15) << "Harga" << setw(10) << "Stok" << endl;
                cout << "---------------------------------------------------------" << endl;
                for (int i = 0; i < data_list_sparepart.size(); i++){
                    cout << setw(5)  << i+1 << setw(20) << data_list_sparepart[i].nama_sparepart << setw(15) 
                        << data_list_sparepart[i].harga_sparepart << setw(10)  << data_list_sparepart[i].stok_sparepart << endl;
                }
                cout << "=========================================================" << endl;
                int pilih_sparepart;
                int jumlah_sparepart;
                bool retry = true;
                while(retry){
                    retry = true;
                    cout << "Pilih sparepart yang akan dipesan (nomor): ";
                    cin >> pilih_sparepart;
                    // error checking jika input tidak valid
                    if (cin.fail()){
                        cout << "Input tidak valid , Mohon Input Dengan Benar" << endl;
                        cin.clear();
                        cin.ignore(999, '\n');
                        continue;
                    }
                    if (pilih_sparepart < 1 || pilih_sparepart > data_list_sparepart.size()){
                        cout << "Input tidak valid , Mohon Input Dengan Benar" << endl;
                        continue;
                    }

                    while(true){
                        cout << "Jumlah sparepart yang akan dipesan: ";
                        cin >> jumlah_sparepart;
                        // Pengecekkan input
                        if (cin.fail()){
                            cout << "Input tidak valid , Mohon Input Dengan Benar" << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                            continue;
                        }
                        if (jumlah_sparepart < 1){
                            cout << "Input tidak valid , Mohon Input Dengan Benar" << endl;
                            continue;
                        }
                        if (jumlah_sparepart > data_list_sparepart[pilih_sparepart-1].stok_sparepart){
                            cout << "Stok sparepart tidak mencukupi" << endl;
                            break;
                        }
                        retry = false;
                        break;
                    }
                }
                // push back data sparepart ke dalam vektor servis
                data_struk_sparepart[id].pesanan.push_back({data_list_sparepart[pilih_sparepart-1].nama_sparepart, jumlah_sparepart, data_list_sparepart[pilih_sparepart-1].harga_sparepart});
                // Mengurangi stok sparepart
                data_list_sparepart[pilih_sparepart-1].stok_sparepart -= jumlah_sparepart;
                // Tampilkan Struk Pemesanan
                clear();
                cout << "====================================" << endl;
                cout << "        STRUK SPAREPART" << endl;
                cout << "====================================" << endl;
                cout << "ID Struk : " << id << endl;
                cout << "Username: " << global_username << endl;
                cout << "------------------------------------" << endl;
                cout<< left << setw (5) << "No" << setw(20) << "Nama Sparepart" << setw(15) << "Harga" << setw(10) << "Jumlah" << endl;
                cout << "------------------------------------" << endl;
                for (int i = 0; i < data_struk_sparepart[id].pesanan.size(); i++){
                    cout << setw(5) << i+1 << setw(20) << data_struk_sparepart[id].pesanan[i].nama_sparepart 
                        << setw(15) << data_struk_sparepart[id].pesanan[i].harga 
                        << setw(10) << data_struk_sparepart[id].pesanan[i].jumlah << endl;
                }
                cout << "------------------------------------" << endl;
                // Tampilkan Total Harga
                int total_harga = 0;
                for (int i = 0; i < data_struk_sparepart[id].pesanan.size(); i++){
                    total_harga += data_struk_sparepart[id].pesanan[i].harga * data_struk_sparepart[id].pesanan[i].jumlah;
                }
                cout << "Total Harga: " << total_harga << endl;
                cout << "====================================" << endl;
                // Pengecekkan apakah user ingin menambahkan sparepart lagi
                char tambah;

                // cek stok sparepart apakah masih di vektor
                stok_tersedia = false;
                for (int i = 0; i < data_list_sparepart.size(); i++){
                    if (data_list_sparepart[i].stok_sparepart > 0){
                        stok_tersedia = true;
                        break;
                    }
                }
                while (true){
                    cout << "Tambahkan sparepart lagi? (y/n): ";
                    cin >> tambah;
                    if (tambah == 'n' || tambah == 'N'|| !stok_tersedia){
                        if (!stok_tersedia){
                            cout << "Stok sparepart habis, Terimakasih Sodaraku MENYALA KALI LAH KAU INI" << endl;
                        }
                        else{
                            cout << "Pemesanan berhasil, Terimakasih Sodaraku MENYALA KALI LAH KAU INI" << endl;
                        }
                        pause();
                        // Menulis data ke dalam file csv
                        write_csv_struk_sparepart();
                        write_csv_list_sparepart();
                        cin.ignore();
                        return;
                    } else if (tambah == 'y' || tambah == 'Y'){
                        break;
                    } else {
                        cout << "Input tidak valid" << endl;
                        pause();
                    }
                }
            }
        } else if (pilih == 'b'){
            // Tampilkan History Pesanan Sparepart
            clear();
            cout << "====================================" << endl;
            cout << "         HISTORY SPAREPART" << endl;
            cout << "====================================" << endl;
            cout << "Username: " << global_username << endl;
            cout << "------------------------------------" << endl;
            // Variabel nomor
            int no = 1;
            int id_struk = 0;
            // Tampilkan Histoty pesanan dengan setw sehingga terbentuk table yang rapi hanya id dan harga pemesanan
            cout << setw(10) << left << "ID" << setw(10) << right << "Harga Pemesanan" << endl;
            cout << "------------------------------------" << endl;
            int harga_total = 0;
            for (int i = 0; i < data_struk_sparepart.size(); i++){
                if (data_struk_sparepart[i].username == global_username && data_struk_sparepart[i].status_akun == "active"){
                    // hitung harga total
                    for (int j = 0; j < data_struk_sparepart[i].pesanan.size(); j++){
                        harga_total += data_struk_sparepart[i].pesanan[j].harga * data_struk_sparepart[i].pesanan[j].jumlah;
                    }
                    cout << setw(10) << left << data_struk_sparepart[i].id << setw(10) << right << harga_total << endl;
                    no++;
                    harga_total = 0;

                }
            }
            // Pilih Struk atau kembali ke menu user_sparepart
            cout << "------------------------------------" << endl;
            cout << "a. Menampilkan Detail Pesanan" << endl;
            cout << "b. Kembali (Menu User Sparepart)" << endl;
            char pilih;
            cout << "Pilih menu: ";
            cin >> pilih;
            // memilih menu a atau b
            int pilihid_struk;
            if (pilih == 'a'){
                cout << "Pilih ID Struk: ";
                cin >> pilihid_struk;
                // Error checking jika bukan numerik
                if(cin.fail()){
                    cout << "Input tidak valid" << endl;
                    pause();
                    clear();
                    cin.clear();
                    cin.ignore();
                    continue;
                }
                // Pengecekkan input
                if (pilihid_struk < 0 || pilihid_struk > data_struk_sparepart.size()){
                    cout << "Input tidak valid" << endl;
                    pause();
                    clear();
                    cin.ignore();
                    continue;
                }
                // perulangan untuk pengecekan bahwa struk yang dipilih adalah struk yang dimiliki user
                bool found = false;
                for (int i = 0; i < data_struk_sparepart.size(); i++){
                    if (data_struk_sparepart[i].username == global_username && data_struk_sparepart[i].status_akun == "active" && data_struk_sparepart[i].id == pilihid_struk){
                        found = true;
                        cin.ignore();
                        break;
                    }
                }
                if (!found) {
                    cout << "ID Salah , Mohon Lebih Teliti" << endl;
                    cin.ignore();
                    pause();
                    continue;
                }
                // Tampilkan Struk yang dipilih
                clear();
                // variabel nampung harga total
                harga_total = 0;

                cout << "====================================" << endl;
                cout << "      STRUK PESANAN SPAREPART" << endl;
                cout << "====================================" << endl;
                cout << "Username: " << global_username << endl;
                cout << "ID Struk: " << data_struk_sparepart[pilihid_struk].id << endl;
                cout << "------------------------------------" << endl;
                cout << "No. " << setw(20) 
                    << left << "Nama Sparepart"
                << setw(10) << right << "Harga"
                << setw(10) << right << "Jumlah" << endl;
                cout << "------------------------------------" << endl;
                for (int i = 0; i < data_struk_sparepart[pilihid_struk].pesanan.size(); i++){
                    cout << right << i+1 << ". "
                        << " " << setw(20) << left << data_struk_sparepart[pilihid_struk].pesanan[i].nama_sparepart
                        << setw(10) << right << data_struk_sparepart[pilihid_struk].pesanan[i].harga
                        << setw(10) << right << data_struk_sparepart[pilihid_struk].pesanan[i].jumlah << endl;
                    harga_total += data_struk_sparepart[pilihid_struk].pesanan[i].harga * data_struk_sparepart[pilihid_struk].pesanan[i].jumlah;
                }
                cout << "------------------------------------" << endl;
                // Tampilkan Total Harga
                cout << "Total Harga: " << harga_total << endl;
                cout << "====================================" << endl;
                pause();
                continue;
            }
            else if (pilih == 'b'){
                clear();
                continue;
            }
            else{
                cout << "Menu tidak tersedia" << endl;
                pause();
                clear();
            }
        } else if (pilih == 'c'){
            clear();
            cin.ignore();
            return;
        }
    }
}

void menu_user(string global_username){
    int pilih, result;
    string str_pilih;
    while (true) {
        cout << "=============================" << endl;
        cout << "          MENU USER" << endl;
        cout << "=============================" << endl;
        cout << "Username : " << global_username << endl;
        cout << "----------------------------" << endl;
        cout << "1. Menu Data Motor" << endl;
        cout << "2. Menu Data Akun" << endl;
        cout << "3. Jadwal Perawatan Motor" << endl;
        cout << "4. Jasa servis Motor" << endl;
        cout << "5. Pemesanan Sparepart Motor" << endl;
        cout << "6. Log Out" << endl;
        cout << "----------------------------" << endl;
        cout << "Pilih menu: ";
        getline(cin, str_pilih);
        // error checking input
        if (str_pilih.find_first_of ("123456") == string::npos || str_pilih.length() > 1){
            cout << "Input tidak valid. Silahkan masukkan angka 1-6." << endl;
            pause();
            clear();
            continue;

        }
        else if (str_pilih.find_first_of (" ") != string::npos){
            cout << "Input tidak boleh kosong" << endl;
            pause();
            clear();
            continue;

        }
        pilih = stoi(str_pilih);
        cout << pilih;
        switch (pilih){
            case 1:
                // Menu Data Motor
                clear();
                menu_motor(global_username);
                break;
            case 2:
                // Menu Data Akun
                clear();
                result = menu_data_akun(&global_username);
                if (result == 1){ // Akun terhapus, logout
                    return;
                }
                break;
            case 3:
                // Jadwal Perawatan Motor
                clear();
                menu_perawatan(global_username);
                break;
            case 4:
                // Jasa servis Motor
                clear();
                menu_user_servis(global_username);
                break;
            case 5:
                // Pemesanan Sparepart Motor
                menu_user_sparepart(global_username);
                clear();
                break;
            case 6:
                // Log Out
                return;
                break;
        }
    }
}


// Menu-Menu Admin
void edit_data_admin(string *global_username){
    string new_username, new_password;
    cout << "=============================" << endl;
    cout << "     EDIT DATA ADMIN" << endl;
    cout << "=============================" << endl;
    cout << "Username: " << *global_username << endl;
    cout << "----------------------------" << endl;
    // Input username admin baru
    cout << "Masukkan Username Admin Baru: ";
    getline(cin, new_username);
    if(new_username.find(",") != string::npos){
        cout << "Username tidak boleh mengandung koma" << endl;
        pause();
        clear();
        return;
    }
    if (new_username.length() < 8){
        cout << "Username minimal 8 karakter" << endl;
        pause();
        clear();
        return;
    }
    if (new_username.find(" ") != string::npos){
        cout << "Username tidak boleh mengandung spasi" << endl;
        pause();
        clear();
        return;
    }
    if (new_username.find_first_of(" ") != string::npos){
        cout << "Username tidak boleh kosong" << endl;
        pause();
        clear();
        return;
    }
    // cek keunikan username dengan vektor data_user
    for (int i = 0; i < data_user.size(); i++){
        if (data_user[i].username == new_username){
            cout << "Username sudah digunakan" << endl;
            pause();
            clear();
            return;
        }
    }

    // Input password admin baru
    cout << "Masukkan Password Admin Baru: ";
    getline(cin, new_password);
    // error checking password
    if (new_password.length() < 8){
        cout << "Password minimal 8 karakter" << endl;
        pause();
        clear();
        return;
    }
    if (new_password.find(" ") != string::npos){
        cout << "Password tidak boleh mengandung spasi" << endl;
        pause();
        clear();
        return;
    }
    if (new_password.find_first_of(" ") != string::npos){
        cout << "Password tidak boleh kosong" << endl;
        pause();
        clear();
        return;
    }
    if(new_password.find(",") != string::npos){
        cout << "Password tidak boleh mengandung koma" << endl;
        pause();
        clear();
        return;
    }
    
    // Update admin data pada admin_log.csv
    ofstream file;
    file.open("Database/admin_log.csv");
    if(!file.is_open()){
        cout << "Gagal Membaca Data Admin" << endl;
        return;
    }
    file << "username,password\n";
    file << new_username << "," << new_password << "\n";
    file.close();

    // Update global username
    *global_username = new_username;

    cout << "Data Admin berhasil diupdate" << endl;
    pause();
    clear();
    return;
}

void admin_servis(string global_username){
    while(true){
        string str_pilih;
        int pilih;
        cout << "=============================" << endl;
        cout << "        MENU SERVIS" << endl;
        cout << "=============================" << endl;
        cout << "Username: " << global_username << endl;
        cout << "----------------------------" << endl;
        cout << "1. Konfirmasi Pesanan Servis" << endl;
        cout << "2. Tampilkan Riwayat Servis" << endl;
        cout << "3. Kembali " << endl;
        cout << "----------------------------" << endl;
        cout << "Pilih menu: ";
        getline(cin, str_pilih);
        if (str_pilih.find_first_not_of ("123") != string::npos || str_pilih.length() > 1){
            cout << "Input tidak valid. Silahkan masukkan angka 1-3." << endl;
            pause();
            clear();
            continue;
        }
        if (str_pilih.find_first_of (" ") != string::npos || str_pilih == ""){
            cout << "Input tidak boleh kosong" << endl;
            pause();
            clear();
            continue;
        }
        pilih = stoi(str_pilih);
        if(pilih == 1){
            while(true){
                clear();
                // Buat 2 menu untuk admin memilih kendaraan mana yang akan diservis dan menu kembali
                cout << "=============================" << endl;
                cout << "    MENU KONFIRMASI SERVIS" << endl;
                cout << "=============================" << endl;
                cout << "Username: " << global_username << endl;
                cout << "----------------------------" << endl;
                cout << "1. Pilih Kendaraan Untuk Diservis" << endl;
                cout << "2. Kembali" << endl;
                cout << "----------------------------" << endl;
                cout << "Pilih menu: ";
                int pilih;
                cin >> pilih;
                clear();
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(999, '\n');
                    cout << "Input tidak valid. Silahkan masukkan angka 1-2." << endl;
                    pause();
                    clear();
                }
                else if (pilih >= 1 && pilih <= 2){
                    if (pilih == 1){
                        // Pilih kendaraan yang akan diservis
                        int hitung_ongoing = 0;
                        cout << "======================================================" << endl;
                        cout << "                   PESANAN SERVIS" << endl;
                        cout << "======================================================" << endl;
                        cout << left << setw(3) << "ID" << " | " << setw(10) << "Username" << " | " 
                            << setw(6) << "Plat" << " | " << setw(7) << "Status" << endl;
                        cout << "------------------------------------------------------" << endl;
                        // print data pesanan servis yang berstatus ongoing pada pesanan_servis.csv
                        for (int i = 0; i < data_struk_servis.size(); i++){
                            if (data_struk_servis[i].status_servis == "ongoing"){
                                cout << setw(3) << data_struk_servis[i].id << " | "
                                    << setw(10) << data_struk_servis[i].username << " | " 
                                    << setw(6) << data_struk_servis[i].plat << " | " 
                                    << setw(7) << data_struk_servis[i].status_servis << endl;
                                hitung_ongoing++;
                            }
                        }
                        cout << "------------------------------------------------------" << endl;
                        // Jika tidak ada pesanan servis yang berstatus ongoing
                        if (hitung_ongoing == 0){
                            clear();
                            cout << "Tidak ada pesanan servis yang tersedia" << endl;
                            pause();
                            clear();
                            break;
                        }
                        cout << "Pilih ID Servis: ";
                        int id_servis;
                        cin >> id_servis;
                        // Jika id servis tidak ada di dalam pesanan servis maka akan kembali ke menu sebelumnya. Id servis hanya mendeteksi status ongoing, jika id servis sesuai dengan id kendaraan berstatus done, maka input tidak valid
                        bool found = false;
                        for (int i = 0; i < data_struk_servis.size(); i++){
                            if (data_struk_servis[i].id == id_servis && data_struk_servis[i].status_servis == "ongoing"){
                                found = true;
                            }
                        }
                        if (!found){
                            cout << "ID Servis tidak ditemukan" << endl;
                            pause();
                            clear();
                            continue;
                        }
                        clear();
                        // vektor yang nyimpan data struk servis
                        vector<servis_data> temp_detail_servis;
                        cin.ignore();
                        while(true){
                            cout << "=========================================================" << endl;
                            cout << "                    LIST SPAREPART" << endl;
                            cout << "=========================================================" << endl;
                            cout << setw (20) << "Nama Sparepart" << setw(15) << "Harga" << setw(10) << endl;
                            cout << "---------------------------------------------------------" << endl;
                            // Sparepart yang ditampilkan hanya yang memiliki kesamaan tipe transmisi dengan motor yang dipilih ID nya untuk diservis
                            for (int i = 0; i < data_list_sparepart.size(); i++){
                                if (data_list_sparepart[i].tipe_transmisi == data_motor[id_servis].transmisi){
                                    cout << setw(20) << data_list_sparepart[i].nama_sparepart << setw(15) << data_list_sparepart[i].harga_sparepart << endl;
                                }
                            }
                            // Tampilkan sparepart bertipe transmisi "keduanya"
                            for (int i = 0; i < data_list_sparepart.size(); i++){
                                if (data_list_sparepart[i].tipe_transmisi == "keduanya"){
                                    cout << setw(20) << data_list_sparepart[i].nama_sparepart << setw(15) << data_list_sparepart[i].harga_sparepart << endl;
                                }
                            }
                            cout << "---------------------------------------------------------" << endl;
                            cout << "Masukkan Nama Sparepart: ";
                            string nama_sparepart;
                            getline(cin, nama_sparepart);
                            clear();
                            // Jika nama sparepart tidak sesuai dengan yang ada di list sparepart, maka akan kembali ke menu sebelumnya
                            found = false;
                            for (int i = 0; i < data_list_sparepart.size(); i++){
                                if (data_list_sparepart[i].nama_sparepart == nama_sparepart){
                                    found = true;
                                    // Tambahkan sparepart yang dipilih ke vektor temp_detail_servis
                                    servis_data temp_detail;
                                    temp_detail.nama_servis = nama_sparepart;
                                    // Harga sparepart
                                    for (int j = 0; j < data_list_sparepart.size(); j++){
                                        if (data_list_sparepart[j].nama_sparepart == nama_sparepart){
                                            temp_detail.harga_servis = data_list_sparepart[j].harga_sparepart;
                                        }
                                    }
                                    temp_detail_servis.push_back(temp_detail);
                                }
                            }
                            if (!found){
                                cout << "Sparepart tidak ditemukan" << endl;
                                pause();
                                clear();
                                continue;
                            }
                            // Buat opsi untuk admin, apakah ingin menambah sparepart untuk servis atau tidak. Jika, iya maka sparepart yang digunakan akan bertambah
                            bool next = false;
                            while(true){
                                cout << "=============================" << endl;
                                cout << "        DETAIL SERVIS" << endl;
                                cout << "=============================" << endl;
                                cout << "1. Tambah Servis" << endl;
                                cout << "2. Selanjutnya" << endl;
                                cout << "-----------------------------" << endl;
                                cout << "Pilih menu: ";
                                int pilih;
                                cin >> pilih;
                                cin.ignore();
                                if (cin.fail()) {
                                    cout << "Input tidak valid. Masukkan angka 1-2." << endl;
                                    cin.clear();
                                    cin.ignore(999, '\n');
                                    clear();
                                    continue;
                                }
                                if (pilih == 1){
                                    clear();
                                    break;
                                }
                                else if (pilih == 2){
                                    clear();
                                    next = true;
                                    break;
                                }
                                else{
                                    cout << "Menu tidak tersedia. Silahkan masukkan angka 1-2." << endl;
                                    pause();
                                    clear();
                                }
                            }
                            if (next){
                                break;
                            }
                        }
                        clear();
                        // Update csv data struk servis
                        // Tampilkan detail servis yang dipilih, kemudian admin dapat menentukan apakah servis sudah selesai atau belum
                        cout << "=========================================================" << endl;
                        cout << "                    DETAIL SERVIS" << endl;
                        cout << "=========================================================" << endl;
                        // print data pesanan servis yang berstatus ongoing pada pesanan_servis.csv
                        for (int i = 0; i < data_struk_servis.size(); i++){
                            if (data_struk_servis[i].id == id_servis){
                                cout << "ID Struk: " << data_struk_servis[i].id << endl;
                                cout << "Username: " << data_struk_servis[i].username << endl;
                                cout << "Plat: " << data_struk_servis[i].plat << endl;
                                cout << "Status Servis: " << data_struk_servis[i].status_servis << endl;
                                cout << "Status Akun: " << data_struk_servis[i].status_akun << endl;
                            }
                        }
                        cout << "------------------------------------------------------" << endl;
                        // Menampilkan sparepart apa saja yang diinput admin
                        cout << "                 SERVIS & SPAREPART : " << endl;
                        cout << "------------------------------------------------------" << endl;
                        // header
                        cout << left << setw(20) << "Nama Servis" << setw(10) << "Harga Servis" << endl;
                        for (int i = 0; i < temp_detail_servis.size(); i++){
                            cout << left << setw(20) << temp_detail_servis[i].nama_servis 
                                << setw(10) << temp_detail_servis[i].harga_servis << endl;
                        }
                        cout << "-------------------------------------------------------" << endl;
                        cout << "1. Servis Selesai" << endl;
                        cout << "2. Batalkan Servis" << endl;
                        cout << "----------------------------" << endl;
                        cout << "Pilih menu: ";
                        int pilih;
                        cin >> pilih;
                        clear();
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(999, '\n');
                            cout << "Input tidak valid. Silahkan masukkan angka 1-2." << endl;
                            pause();
                        } 
                        else if (pilih >= 1 && pilih <= 2){
                            if (pilih == 1){
                                // Update kondisi motor yang dipilih, berdasarkan id struk
                                for (int i = 0; i < data_motor.size(); i++){
                                    if (data_motor[i].plat == data_struk_servis[id_servis].plat){
                                        // Simpan tipe transmisi motor yang dipilih
                                        string transmisi_motor = data_motor[i].transmisi;
                                        // Update kondisi motor
                                        if (transmisi_motor == "manual"){
                                            for (int j = 0; j < data_kondisi_manual.size(); j++){
                                                if (data_kondisi_manual[j].plat == data_motor[i].plat){
                                                    // Cek sparepart yang diservis
                                                    for (int k = 0; k < temp_detail_servis.size(); k++){
                                                        // Buat pointer null dengan tipe data kondisi_manual
                                                        int kondisi_manual::*ptr = nullptr;
                                                        // Cek nama sparepart yang diservis
                                                        if (temp_detail_servis[k].nama_servis == "ban belakang"){
                                                            ptr = &kondisi_manual::ban_belakang;
                                                        }
                                                        else if (temp_detail_servis[k].nama_servis == "ban depan"){
                                                            ptr = &kondisi_manual::ban_depan;
                                                        }
                                                        else if (temp_detail_servis[k].nama_servis == "busi"){
                                                            ptr = &kondisi_manual::busi;
                                                        }
                                                        else if (temp_detail_servis[k].nama_servis == "gear"){
                                                            ptr = &kondisi_manual::gear;
                                                        }
                                                        else if (temp_detail_servis[k].nama_servis == "kampas kopling"){
                                                            ptr = &kondisi_manual::kampas_kopling;
                                                        }
                                                        else if (temp_detail_servis[k].nama_servis == "kampas rem"){
                                                            ptr = &kondisi_manual::kampas_rem;
                                                        }
                                                        else if (temp_detail_servis[k].nama_servis == "minyak rem"){
                                                            ptr = &kondisi_manual::minyak_rem;
                                                        }
                                                        else if (temp_detail_servis[k].nama_servis == "oli mesin"){
                                                            ptr = &kondisi_manual::oli_mesin;
                                                        }
                                                        else if (temp_detail_servis[k].nama_servis == "rantai"){
                                                            ptr = &kondisi_manual::rantai;
                                                        }
                                                        // Update kondisi motor, menjadi sama dengan jarak tempuh motor
                                                        if (ptr != nullptr){
                                                            data_kondisi_manual[j].*ptr = data_motor[i].jarak_tempuh;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        else if (transmisi_motor == "automatic"){
                                            // Buat sama seperti motor manual dibedakan dengan sparepart motor untuk automatic
                                            for (int j = 0; j < data_kondisi_automatic.size(); j++){
                                                if (data_kondisi_automatic[j].plat == data_motor[i].plat){
                                                    // Cek sparepart yang diservis
                                                    for (int k = 0; k < temp_detail_servis.size(); k++){
                                                        // Buat pointer null dengan tipe data kondisi_automatic
                                                        int kondisi_automatic::*ptr = nullptr;
                                                        // Cek nama sparepart yang diservis
                                                        if (temp_detail_servis[k].nama_servis == "ban belakang"){
                                                            ptr = &kondisi_automatic::ban_belakang;
                                                        }
                                                        else if (temp_detail_servis[k].nama_servis == "ban depan"){
                                                            ptr = &kondisi_automatic::ban_depan;
                                                        }
                                                        else if (temp_detail_servis[k].nama_servis == "busi"){
                                                            ptr = &kondisi_automatic::busi;
                                                        }
                                                        else if (temp_detail_servis[k].nama_servis == "kampas rem"){
                                                            ptr = &kondisi_automatic::kampas_rem;
                                                        }
                                                        else if (temp_detail_servis[k].nama_servis == "minyak rem"){
                                                            ptr = &kondisi_automatic::minyak_rem;
                                                        }
                                                        else if (temp_detail_servis[k].nama_servis == "oli mesin"){
                                                            ptr = &kondisi_automatic::oli_mesin;
                                                        }
                                                        else if (temp_detail_servis[k].nama_servis == "roller"){
                                                            ptr = &kondisi_automatic::roller;
                                                        }
                                                        else if (temp_detail_servis[k].nama_servis == "van belt"){
                                                            ptr = &kondisi_automatic::van_belt;
                                                        }
                                                        // Update kondisi motor, menjadi sama dengan jarak tempuh motor
                                                        if (ptr != nullptr){
                                                            data_kondisi_automatic[j].*ptr = data_motor[i].jarak_tempuh;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }

                                // Update status servis motor jadi false
                                for (int i = 0; i < data_motor.size(); i++){
                                    if (data_motor[i].plat == data_struk_servis[id_servis].plat){
                                        data_motor[i].servis = false;
                                    }
                                }
                                // Update csv kondisi motor
                                write_csv_motor();
                                read_csv_motor();
                                // Update csv data sparepart
                                write_csv_list_sparepart();
                                read_csv_list_sparepart();
                                // Ubah status servis menjadi done
                                for (int i = 0; i < data_struk_servis.size(); i++){
                                    if (data_struk_servis[i].id == id_servis){
                                        data_struk_servis[i].status_servis = "done";
                                        data_struk_servis[i].servis = temp_detail_servis;
                                    }
                                }
                                // Update struk servis pada csv
                                write_csv_struk_servis();
                                read_csv_struk_servis();
                                cout << "Servis berhasil selesai!" << endl;
                                pause();
                                clear();
                            }
                            else if (pilih == 2){
                                // Kembali
                                clear();
                                return;
                                break;
                            }
                        }
                        else{
                            clear();
                            cout << "Menu tidak tersedia. Silahkan masukkan angka 1-2." << endl;
                            pause();
                        }
                    }
                    else if (pilih == 2){
                        // Kembali
                        clear();
                        break;
                    }
                }
                else{
                    clear();
                    cout << "Menu tidak tersedia. Silahkan masukkan angka 1-2." << endl;
                    pause();
                }
            }
        }
        else if (pilih == 2){
            clear();
            // Tamplikan riwayat servis yang sudah selesai (dari struk_servis.csv)
            cout << "======================================================" << endl;
            cout << "                 RIWAYAT SERVIS" << endl;
            cout << "======================================================" << endl;
            cout << "    Username: " << global_username << endl;
            cout << "------------------------------------------------------" << endl;
            // gunakan setw
            cout << setw(3) << "ID" << " | " << setw(10) << "Username" << " | " << setw(6) << "Plat"  << endl;
            cout << "------------------------------------------------------" << endl;
            // print semua data struk servis pada struk_servis.csv
            for (int i = 0; i < data_struk_servis.size(); i++){
                if (data_struk_servis[i].status_servis == "done"){
                    cout << setw(3) << data_struk_servis[i].id << " | " << setw(10) << data_struk_servis[i].username << " | " << setw(6) << data_struk_servis[i].plat << endl;
                }                
            }
            cout << "------------------------------------------------------" << endl;
            pause();
            clear();
        }
        else if (pilih == 3){    
            // Kembali
            clear();
            return;
            break;
        }
    }
}
    
void admin_sparepart(string global_username){
    // Tampilkan list sparepart yang tersedia
    while(true){
        cout << "=============================" << endl;
        cout << "        MENU SPAREPART" << endl;
        cout << "=============================" << endl;
        cout << "Username: " << global_username << endl;
        cout << "----------------------------" << endl;
        cout << "1. Tampilkan List Sparepart" << endl;
        cout << "2. Edit Sparepart" << endl;
        cout << "3. Kembali" << endl;
        cout << "----------------------------" << endl;
        cout << "Pilih menu: ";
        int pilih;
        cin >> pilih; // stoi
        clear();
        if (cin.fail()) {
            cin.clear();
            cin.ignore(999, '\n');
            cout << "Input tidak valid. Silahkan masukkan angka 1-3." << endl;
            pause();
            clear();
        } 
        else if (pilih >= 1 && pilih <= 3){
            if(pilih == 1){
                // Tampilkan List Sparepart
                cout << "=============================" << endl;
                cout << "        LIST SPAREPART" << endl;
                cout << "=============================" << endl;
                cout << "Username: " << global_username << endl;
                cout << "----------------------------" << endl;
                cout << left << setw(20) << "Nama Sparepart" << setw(12) << "Harga" << setw(16) << "Jarak Max (KM)" << setw(8) << "Stok" << endl;
                cout << "----------------------------" << endl;
                // print semua data sparepart pada list_sparepart.csv
                for (int i = 0; i < data_list_sparepart.size(); i++){
                    cout << left << setw(20) << data_list_sparepart[i].nama_sparepart << setw(12) << data_list_sparepart[i].harga_sparepart 
                        << setw(16) << data_list_sparepart[i].kilometer << setw(8) << data_list_sparepart[i].stok_sparepart << endl;
                }
                cout << "----------------------------" << endl;
                pause();
                clear();
            }
            else if (pilih == 2){
                // Edit sparepart, dengan menyesuaikan nama sparepart dengan isi list_sparepart.csv. Jika nama sparepart tidak sesuai dengan yang ada di list_sparepart.csv, maka tidak bisa diedit
                cout << "=============================" << endl;
                cout << "        EDIT SPAREPART" << endl;
                cout << "=============================" << endl;
                cout << "Username: " << global_username << endl;
                cout << "----------------------------" << endl;
                // tampilkan list sparepart
                cout << left << setw(20) << "Nama Sparepart" << setw(12) << "Harga" << setw(16) << "Jarak Max(KM)" << setw(8) << "Stok" << endl; 
                cout << "----------------------------" << endl;
                for (int i = 0; i < data_list_sparepart.size(); i++){
                    cout << left << setw(20) << data_list_sparepart[i].nama_sparepart << setw(12) << data_list_sparepart[i].harga_sparepart 
                        << setw(16) << data_list_sparepart[i].kilometer << setw(8) << data_list_sparepart[i].stok_sparepart << endl;
                }
                cout << "----------------------------" << endl;
                // Input nama sparepart yang akan diubah
                cout << "Nama Sparepart: ";
                string nama_sparepart;
                cin.ignore();
                getline(cin, nama_sparepart);
                // Cek apakah nama sparepart ada di list_sparepart.csv
                bool found = false;
                for (int i = 0; i < data_list_sparepart.size(); i++){
                    if (data_list_sparepart[i].nama_sparepart == nama_sparepart){
                        found = true;
                        string str_input;
                        int harga_sparepart, kilometer, stok_sparepart;
                        // Input harga, kilometer, dan stok sparepart yang baru
                        cout << "Harga Sparepart: ";
                        // input & Error Handling
                        getline(cin, str_input);
                        if (str_input.find_first_not_of("0123456789") != string::npos){
                            cout << "Input tidak valid. Harga harus berupa angka." << endl;
                            i--;
                            continue;
                        }
                        // Batasi 12 digit harga
                        if (str_input.length() > 12){
                            cout << "Input tidak valid. Harga maksimal 12 digit." << endl;
                            i--;
                            continue;
                        }
                        // Jika input kosong
                        if (str_input == ""){
                            cout << "Input tidak boleh kosong" << endl;
                            i--;
                            continue;
                        }
                        harga_sparepart = stoi(str_input);

                        while(true){
                            cout << "Kilometer Servis: ";
                            getline(cin, str_input);
                            // Error Handling
                            if (str_input.find_first_not_of("0123456789") != string::npos){
                                cout << "Input tidak valid. Kilometer harus berupa angka." << endl;
                                continue;
                            }
                            // Batasi 12 digit kilometer
                            if (str_input.length() > 12){
                                cout << "Input tidak valid. Kilometer maksimal 12 digit." << endl;
                                continue;
                            }
                            if (str_input == ""){
                                cout << "Input tidak boleh kosong" << endl;
                                continue;
                            }
                            kilometer = stoi(str_input);
                            break;
                        }

                        while(true){
                            cout << "Stok Sparepart: ";
                            getline(cin, str_input);
                            // Error Handling
                            if (str_input.find_first_not_of("0123456789") != string::npos){
                                cout << "Input tidak valid. Stok harus berupa angka." << endl;
                                continue;
                            }
                            // Batasi 12 digit stok
                            if (str_input.length() > 12){
                                cout << "Input tidak valid. Stok maksimal 12 digit." << endl;
                                continue;
                            }
                            if (str_input == ""){
                                cout << "Input tidak boleh kosong" << endl;
                                continue;
                            }
                            stok_sparepart = stoi(str_input);
                            break;
                        }
                        // Update data sparepart yang dipilih
                        data_list_sparepart[i].harga_sparepart = harga_sparepart;
                        data_list_sparepart[i].kilometer = kilometer;
                        data_list_sparepart[i].stok_sparepart = stok_sparepart;
                        // Update csv list_sparepart
                        write_csv_list_sparepart();
                        read_csv_list_sparepart();
                        clear();
                        cout << "Sparepart berhasil diubah!" << endl;
                        pause();
                        clear();
                        break;
                    }
                }
                if (!found){
                    cout << "Sparepart tidak ditemukan" << endl;
                    pause();
                    clear();
                }
            }
            else if (pilih == 3){
                // Kembali
                cin.ignore();
                return;
            }
        }
        else{
            clear();
            cout << "Menu tidak tersedia. Silahkan masukkan angka 1-3." << endl;
            pause();
            clear();
        }
    }
}

void menu_admin(string global_username){
    int pilih;
    string str_pilih;
    while (true) {
        cout << "=============================" << endl;
        cout << "          MENU ADMIN" << endl;
        cout << "=============================" << endl;
        cout << "Username : " <<global_username << endl;
        cout << "----------------------------" << endl;
        cout << "1. Edit Data Admin" << endl;
        cout << "2. Layanan Servis" << endl;
        cout << "3. Toko Sparepart" << endl;
        cout << "4. Log Out" << endl;
        cout << "Pilih menu: ";
        getline(cin, str_pilih);
        // error checking input
        if (str_pilih.find_first_not_of ("1234") != string::npos || str_pilih.length() > 1){
            cout << "Input tidak valid. Silahkan masukkan angka 1-4." << endl;
            pause();
            clear();
            continue;
        }
        if (str_pilih.find_first_of (" ") != string::npos){
            cout << "Input tidak boleh kosong" << endl;
            pause();
            clear();
            continue;
        }
        if (str_pilih == ""){
            cout << "Input tidak kosong" << endl;
            pause();
            clear();
            continue;
        }
        pause();
        pilih = stoi(str_pilih);
        switch (pilih){
            case 1:
                // Edit Data Admin
                clear();
                edit_data_admin(&global_username);
                break;
            case 2:
                // Layanan Servis (Admin)
                clear();
                admin_servis(global_username);
                break;
            case 3:
                // Toko Sparepart (Admin)
                clear();
                admin_sparepart(global_username);
                break;
            case 4:
                // Log Out
                clear();
                return;
                break;
        }
    }
}


// Fungsi Main
int main(){
    // Membaca data csv di awal
    read_csv_user();
    read_csv_motor();
    read_csv_struk_servis();
    read_csv_struk_sparepart();
    read_csv_list_sparepart();

    // Variabel lokal main
    string global_username, global_password;
    int log_result;

    while(true){
        clear();
        int pilih = menu_awal();
        switch(pilih){
            case 1: // Login
                clear();
                log_result = login(3, &global_username, &global_password);
                if (log_result == 0){ // Menu Admin
                    menu_admin(global_username);
                }
                else if (log_result == 1){ // Menu User
                    menu_user(global_username);
                }
                else if (log_result == 2){ // Gagal Login
                    clear();
                }
                break;
            case 2: // Register
                clear();
                regist();
                break;
            case 3:
                clear();
                cout << "Program Berhenti" << endl;
                return 0;
        }
    }
}