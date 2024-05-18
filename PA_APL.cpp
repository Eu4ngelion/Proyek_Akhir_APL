#include <iostream>
#include <cctype>
#include <sstream> // manipulasi string
#include <fstream> // manipulasi file
#include <vector> // array dinamis
#include <algorithm> // Erase, Remove

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
    bool service;
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
vector<struk_servis> data_struk_service;
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
    string baris, data, service;
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
        // Service tipe data boolean
        getline(ss, service, '\n');
        if (service == "true"){
            temp.service = true;
        }
        else{
            temp.service = false;
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
    file << "Owner,Nama Motor,Warna,Transmisi,Plat,Jarak Tempuh(KM),Service" << endl;
    for (int i = 0; i < data_motor.size(); i++){
        file << data_motor[i].owner << "," << data_motor[i].nama_motor << "," << data_motor[i].warna_motor << "," << data_motor[i].transmisi << "," << data_motor[i].plat << "," << data_motor[i].jarak_tempuh << ",";
        if (data_motor[i].service){
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
    data_struk_service.clear();
    ifstream file;
    file.open("Database/pesanan_servis.csv");
    if (!file) {
        cout << "Gagal membaca data pesanan service (pesanan_servis.csv)" << endl;
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
        data_struk_service.push_back(temp_struk);
        
        //clear temp_servis_vector
        temp_servis_vector.clear();
    }
    file.close();
    return;
}   
void write_csv_struk_servis(){
    // Hapus folder Database/Struk/Servis
    system("rmdir /s /q Database/Struk/Servis");
    // Buat folder Database/Struk/Servis
    system("mkdir Database/Struk/Servis");

    // Menulis data pesanan_servis.csv
    ofstream file;
    file.open("Database/pesanan_servis.csv");
    if (!file) {
        cout << "Gagal membaca data pesanan service (pesanan_servis.csv)" << endl;
        pause();
        return;
    }
    file << "ID,Username,Plat,Status Servis, Status Akun" << endl; // Menulis header
    for (int i = 0; i < data_struk_service.size(); i++){
        file << data_struk_service[i].id << ","  // id struk
        << data_struk_service[i].username << "," // username
        << data_struk_service[i].plat << "," // plat
        << data_struk_service[i].status_servis // status servis
        << "," << data_struk_service[i].status_akun << endl;
    }
    file.close();
    // vector<servis_data> servis
    // Membuat file berisi data detail servis = "Database/Struk/Servis/{id}.csv"
    for (int i = 0; i < data_struk_service.size(); i++){
        file.open("Database/Struk/Servis/" + to_string(data_struk_service[i].id) + ".csv");
        if (!file) {
            cout << "Gagal membaca data servis (Database/Struk/Servis/" + to_string(data_struk_service[i].id) + ".csv)" << endl;
            pause();
            return;
        }
        file << "Nama Servis,Harga Servis" << endl; // Menulis header
        for (int j = 0; j < data_struk_service[i].servis.size(); j++){
            file << data_struk_service[i].servis[j].nama_servis << "," << data_struk_service[i].servis[j].harga_servis << endl;
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
    system("rmdir /s /q Database/Struk/Sparepart");
    // Buat folder Database/Struk/Sparepart
    system("mkdir Database/Struk/Sparepart");

    // Menulis data pesanan_sparepart.csv
    ofstream file;
    file.open("Database/pesanan_sparepart.csv");
    if (!file) {
        cout << "Gagal membaca data pesanan sparepart (pesanan_sparepart.csv)" << endl;
        pause();
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
            pause();
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
    cout << "=============================" << endl;
    cout << "         MENU LOGIN" << endl;
    cout << "=============================" << endl;
    cout << "Username: ";
    cin >> username_inp;
    cout << "Password: ";
    cin >> password_inp;

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
    cout << "Kesempatan tersisa: " << try_left-1 << endl;
    pause();
    clear();
    return login(try_left-1, global_username, global_password);
}
void regist(){ // setelah regist, data ditambahkan ke file user_log.csv dan di sort dengan bubble sort
    string username_inp, password_inp, telepon_inp, address_inp;

    cout << "=============================" << endl;
    cout << "        MENU REGISTER" << endl;
    cout << "=============================" << endl;
    // Input Username
    cout << "Username: ";
    cin >> username_inp;
    // memastikan username unik dan tidak mengandung spasi
    if (username_inp.find(",") != string::npos){
        cout << "Username tidak boleh mengandung spasi atau koma" << endl;
        pause();
        clear();
        return;
    }
    // Mengecek seluruh data vektor, username harus unik
    // Cek juga data csv admin_log.csv
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
    for (int i = 0; i < data_user.size(); i++){
        if (data_user[i].username == username_inp){
            cout << "Username sudah terdaftar" << endl;
            pause();
            clear();
            return;
        }
    }

    // Input Password
    cout << "Password: ";
    cin >> password_inp;
    // memastikan password tidak mengandung spasi atau koma
    if (password_inp.find(",") != string::npos){
        cout << "Password tidak boleh mengandung spasi atau koma" << endl;
        pause();
        clear();
        return;
    }

    // Input Nomor Telepon
    cout << "Nomor telepon: ";
    cin >> telepon_inp;
    // memastikan nomor telepon hanya berupa angka
    for (int i = 0; i < telepon_inp.length(); i++){
        if (!isdigit(telepon_inp[i])){
            cout << "nomor telepon harus berupa angka" << endl;
            pause();
            clear();
            return;
        }
    }
    // Mengecek seluruh data vektor, Data telepon harus unik
    for (int i = 0; i < data_user.size(); i++){
        if (data_user[i].telepon == telepon_inp){
            cout << "nomor telepon sudah terdaftar" << endl;
            pause();
            clear();
            return;
        }
    }

    // Input Alamat
    cout << "Alamat: ";
    cin.ignore();
    getline(cin, address_inp);
    // Mengecek input supaya tidak memililki koma
    if (address_inp.find(",") != string::npos){
        cout << "Alamat tidak boleh mengandung koma" << endl;
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

    // sort data user dengan bubble sort
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
    bool service;
    cout << "=============================" << endl;
    cout << "    TAMBAH DATA MOTOR" << endl;
    cout << "=============================" << endl;
    // Input nama motor getline
    cout << "Nama Motor: ";
    cin.ignore();
    getline(cin, nama_motor);
    // Input warna motor
    cout << "Warna Motor: ";
    getline(cin, warna_motor);
    cout << "Transmisi Motor: ";
    // Input transmisi, "manual" atau "automatic"
    while (true){
        getline(cin, transmisi_motor);
        if (transmisi_motor == "manual" || transmisi_motor == "automatic"){
            break;
        }
        else{
            cout << "Transmisi motor hanya bisa manual atau automatic" << endl;
            cout << "Transmisi Motor: ";
        }
    }
    // Input plat motor
    cout << "Plat Motor: ";
    getline(cin, plat_motor);
    // Memastikan plat motor yang diinput belum terdaftar
    string data_plat_temp;
    string inp_plat_temp = plat_motor;
    for (int i = 0; i < data_motor.size(); i++){
        // Bandingkan tanpa memperhatikan spasi
        data_plat_temp = data_motor[i].plat;
        // Hapus spasi dari string plat
        data_plat_temp.erase(remove(data_plat_temp.begin(), data_plat_temp.end(), ' '), data_plat_temp.end());
        inp_plat_temp.erase(remove(inp_plat_temp.begin(), inp_plat_temp.end(), ' '), inp_plat_temp.end());
        if (data_plat_temp.compare(inp_plat_temp) == 0){
            cout << "Plat motor sudah terdaftar" << endl;
            cout << "Plat Motor: ";
            getline(cin, plat_motor);
            inp_plat_temp = plat_motor;
            i = -1;
        }
    }
    // input jarak tempuh
    int jarak_tempuh;
    cout << "Jarak Tempuh (KM): ";
    while (!(cin >> jarak_tempuh)) {
        cout << "Invalid input. Silahkan masukkan angka." << endl;
        cin.clear();
        cin.ignore(999, '\n');
        cout << "Jarak Tempuh (KM): ";
    }

    // menambahkan data motor ke vektor
    motor_data temp;
    temp.owner = username;
    temp.nama_motor = nama_motor;
    temp.warna_motor = warna_motor;
    temp.transmisi = transmisi_motor;
    temp.plat = plat_motor;
    temp.jarak_tempuh = jarak_tempuh;
    temp.service = false; // service default = false
    data_motor.push_back(temp);

    // Input kondisi
    cout << "=============================" << endl;
    cout << "    Terakhir Servis(Km)" << endl;
    cout << "=============================" << endl;
    // Input kondisi motor jika transmisi adalah automatic
    if (transmisi_motor == "automatic") {
        kondisi_automatic kondisi;
        kondisi.plat = plat_motor;
        // Input kondisi motor automatic
        cout << "Ban Belakang: ";
        while (!(cin >> kondisi.ban_belakang)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(999, '\n');
        }
        cout << "Ban Depan: ";
        while (!(cin >> kondisi.ban_depan)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(999, '\n');
        }
        cout << "Busi: ";
        while (!(cin >> kondisi.busi)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(999, '\n');
        }
        cout << "Kampas Rem: ";
        while (!(cin >> kondisi.kampas_rem)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(999, '\n');
        }
        cout << "Minyak Rem: ";
        while (!(cin >> kondisi.minyak_rem)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(999, '\n');
        }
        cout << "Oli Gardan: ";
        while (!(cin >> kondisi.oli_gardan)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(999, '\n');
        }
        cout << "Oli Mesin: ";
        while (!(cin >> kondisi.oli_mesin)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(999, '\n');
        }
        cout << "Roller: ";
        while (!(cin >> kondisi.roller)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(999, '\n');
        }
        cout << "Van Belt: ";
        while (!(cin >> kondisi.van_belt)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(999, '\n');
        }
        // Simpan data ke vektor
        data_kondisi_automatic.push_back(kondisi);
    }
    // Input kondisi motor jika transmisi adalah manual
    if (transmisi_motor == "manual") {
        kondisi_manual kondisi;
        kondisi.plat = plat_motor;
        // Input kondisi motor manual
        cout << "Ban Belakang: ";
        while (!(cin >> kondisi.ban_belakang)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(999, '\n');
        }
        cout << "Ban Depan: ";
        while (!(cin >> kondisi.ban_depan)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(999, '\n');
        }
        cout << "Busi: ";
        while (!(cin >> kondisi.busi)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(999, '\n');
        }
        cout << "Gear: ";
        while (!(cin >> kondisi.gear)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(999, '\n');
        }
        cout << "Kampas Kopling: ";
        while (!(cin >> kondisi.kampas_kopling)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(999, '\n');
        }
        cout << "Kampas Rem: ";
        while (!(cin >> kondisi.kampas_rem)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(999, '\n');
        }
        cout << "Minyak Rem: ";
        while (!(cin >> kondisi.minyak_rem)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(999, '\n');
        }
        cout << "Oli Mesin: ";
        while (!(cin >> kondisi.oli_mesin)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(999, '\n');
        }
        cout << "Rantai: ";
        while (!(cin >> kondisi.rantai)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(999, '\n');
        }
        // Simpan data ke vektor
        data_kondisi_manual.push_back(kondisi);
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
    // Sort data kondisi manual  dengan bubble sort, ascending berdasarkan plat
    for (int i = 0; i < data_kondisi_manual.size(); i++){
        for (int j = 0; j < data_kondisi_manual.size()-1; j++){
            if (data_kondisi_manual[j].plat > data_kondisi_manual[j+1].plat){
                kondisi_manual temp = data_kondisi_manual[j];
                data_kondisi_manual[j] = data_kondisi_manual[j+1];
                data_kondisi_manual[j+1] = temp;
            }
        }
    }
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

    // update csv motor
    write_csv_motor();
    read_csv_motor();
    cout << "Data motor berhasil ditambahkan" << endl;
    pause();
    clear();
    return;
}

void view_motor(string username){
    cout << "=============================" << endl;
    cout << "        DATA MOTOR" << endl;
    cout << "=============================" << endl;
    cout << "Username: " << username << endl;
    cout << "----------------------------" << endl;
    // tampilkan list motor yang dimiliki user, hanya nama motor(plat) saja
    // Simpan plat motor yang dimiliki user ke dalam vector
    vector<string> plat_vector;
    int count = 1;
    for (int i = 0; i < data_motor.size(); i++){
        if (data_motor[i].owner == username){
            cout << count << ". "; count++;
            cout << "Nama Motor: " << data_motor[i].nama_motor;
            if (data_motor[i].service){
                cout << " (Service)";
            }
            cout << endl;
            cout << "Plat: " << data_motor[i].plat << endl;
            plat_vector.push_back(data_motor[i].plat);
            cout << "Warna: " << data_motor[i].warna_motor << endl;
            cout << "Transmisi: " << data_motor[i].transmisi << endl;
            cout << "Jarak Tempuh: " << data_motor[i].jarak_tempuh << " KM" << endl;
            cout <<"----------------------------"<< endl;
        }
    }
    // View Menu
    int pilih;
    while (true) {
        cout << "Menu View:" << endl;
        cout << "1. Tampilkan Data Detail" << endl;
        cout << "2. Back" << endl;
        cout << "Pilih menu: ";
        cin >> pilih;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(999, '\n');
            cout << "Input tidak valid. Silahkan masukkan angka 1-2." << endl;
            pause();
            clear();
            continue;
        } else if (pilih >= 1 && pilih <= 2) {
            // Tampilkan data detail motor
            if (pilih == 1){
                int pilih_motor;
                while (true) {
                    cout << "Pilih nomor motor untuk ditampilkan: ";
                    cin >> pilih_motor;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(999, '\n');
                        cout << "Input tidak valid. Silahkan masukkan angka." << endl;
                        pause();
                        clear();
                        continue;
                    }
                    break;
                }
                // Tampilkan data detail motor
                if (pilih_motor >= 1 && pilih_motor <= count-1){
                clear();
                cout << "=============================" << endl;
                cout << "     DATA MOTOR (DETAIL)" << endl;
                cout << "=============================" << endl;
                cout << "Username: " << username << endl;
                cout << "----------------------------" << endl;
                // Tampilkan data motor yang dipilih
                    for (int i = 0; i < data_motor.size(); i++){ // cari data motor yang sesuai
                        // jika data motor sesuai dengan username dan plat dari motor yang dipilih
                        if (data_motor[i].owner == username && data_motor[i].plat == plat_vector[pilih_motor-1]){
                            cout << "Nama Motor: " << data_motor[i].nama_motor << endl;
                            cout << "Plat: " << data_motor[i].plat << endl;
                            cout << "Warna: " << data_motor[i].warna_motor << endl;
                            cout << "Transmisi: " << data_motor[i].transmisi << endl;
                            cout << "Jarak Tempuh: " << data_motor[i].jarak_tempuh << " KM" << endl;
                            cout << "Service: ";
                            if (data_motor[i].service){
                                cout << "Yes" << endl;
                            }
                            else{
                                cout << "No" << endl;
                            }
                            cout << "----------------------------" << endl;
                            // Tampilkan kondisi sparepart motor yang dipilih
                            // di csv kondisi motor, dicari berdasarkan plat
                            if (data_motor[i].transmisi == "manual"){
                                for (int j = 0; j < data_kondisi_manual.size(); j++){
                                    if (data_kondisi_manual[j].plat == data_motor[i].plat){
                                        cout << "     Terakhir Servis(KM)" << endl;
                                        cout << "----------------------------" << endl;
                                        cout << "Ban Belakang: " << data_kondisi_manual[j].ban_belakang << endl;
                                        cout << "Ban Depan: " << data_kondisi_manual[j].ban_depan << endl;
                                        cout << "Busi: " << data_kondisi_manual[j].busi << endl;
                                        cout << "Gear: " << data_kondisi_manual[j].gear << endl;
                                        cout << "Kampas Kopling: " << data_kondisi_manual[j].kampas_kopling << endl;
                                        cout << "Kampas Rem: " << data_kondisi_manual[j].kampas_rem << endl;
                                        cout << "Minyak Rem: " << data_kondisi_manual[j].minyak_rem << endl;
                                        cout << "Oli Mesin: " << data_kondisi_manual[j].oli_mesin << endl;
                                        cout << "Rantai: " << data_kondisi_manual[j].rantai << endl;
                                        cout << "----------------------------" << endl;
                                    }
                                }
                            }
                            if (data_motor[i].transmisi == "automatic"){
                                for (int j = 0; j < data_kondisi_automatic.size(); j++){
                                    if (data_kondisi_automatic[j].plat == data_motor[i].plat){
                                        cout << "     Terakhir Servis(KM)" << endl;
                                        cout << "----------------------------" << endl;
                                        cout << "Ban Belakang: " << data_kondisi_automatic[j].ban_belakang << endl;
                                        cout << "Ban Depan: " << data_kondisi_automatic[j].ban_depan << endl;
                                        cout << "Busi: " << data_kondisi_automatic[j].busi << endl;
                                        cout << "Kampas Rem: " << data_kondisi_automatic[j].kampas_rem << endl;
                                        cout << "Minyak Rem: " << data_kondisi_automatic[j].minyak_rem << endl;
                                        cout << "Oli Gardan: " << data_kondisi_automatic[j].oli_gardan << endl;
                                        cout << "Oli Mesin: " << data_kondisi_automatic[j].oli_mesin << endl;
                                        cout << "Roller: " << data_kondisi_automatic[j].roller << endl;
                                        cout << "Van Belt: " << data_kondisi_automatic[j].van_belt << endl;
                                        cout << "----------------------------" << endl;
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
            // Kembali ke menu user
            if(pilih == 2){
                clear();
                return;
            }
        }
        // Input tidak sesuai
        else {
            cout << "Menu tidak tersedia. Silahkan masukkan angka 1-2." << endl;
            pause();
        }
    }
        pause();
        clear();
        return;
}

void edit_motor(string username){
    // vektor plat motor yang dimiliki user
    vector<string> plat_vector;
    // Tampilkan list motor yang dimiliki user
    cout << "=============================" << endl;
    cout << "       EDIT DATA MOTOR" << endl;
    cout << "=============================" << endl;
    cout << "Username: " << username << endl;
    cout << "----------------------------" << endl;
    // Menghitung jumlah motor yang dimiliki user
    int count = 1;
    for (int i = 0; i < data_motor.size(); i++){
        if (data_motor[i].owner == username){
            cout << count << ". "; count++;
            cout << "Nama Motor: " << data_motor[i].nama_motor;
            if (data_motor[i].service){
                cout << " (Service)";
            }
            cout << endl;
            cout << "Plat: " << data_motor[i].plat << endl;
            plat_vector.push_back(data_motor[i].plat);
            cout << "Warna: " << data_motor[i].warna_motor << endl;
            cout << "Transmisi: " << data_motor[i].transmisi << endl;
            cout << "Jarak Tempuh: " << data_motor[i].jarak_tempuh << " KM" << endl;
            cout <<"----------------------------"<< endl;
        }
    }
    // Pilih Nomor Motor yang akan diedit
    int pilih_motor;
    while (true) {
        cout << "Pilih nomor motor untuk diedit: ";
        cin >> pilih_motor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(999, '\n');
            cout << "Input tidak valid. Silahkan masukkan angka." << endl;
            pause();
            clear();
            continue;
        }
        // Jika nomor yang dipilih sesuai dengan jumlah motor
        if (pilih_motor >= 1 && pilih_motor <= count-1){ 
            clear();
            // Simpan plat dari motor yang dipilih
            string plat_motor_temp = plat_vector[pilih_motor-1];

            // Jika nomor yang dipilih sedang diservis, tidak boleh edit
            for (int i = 0; i < data_motor.size(); i++){
                if (data_motor[i].owner == username && data_motor[i].plat == plat_motor_temp){
                    if (data_motor[i].service){
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
                    cout << "Nama Motor: " << data_motor[i].nama_motor << endl;
                    cout << "Plat: " << data_motor[i].plat << endl;
                    cout << "Warna: " << data_motor[i].warna_motor << endl;
                    cout << "Transmisi: " << data_motor[i].transmisi << endl;
                    cout << "Jarak Tempuh: " << data_motor[i].jarak_tempuh << " KM" << endl;
                    cout << "Service: ";
                    if (data_motor[i].service){
                        cout << "Yes" << endl;
                    }
                    else{
                        cout << "No" << endl;
                    }
                    cout << "----------------------------" << endl;
                }
            }

            // Input data baru
            for (int i = 0; i < data_motor.size(); i++){
                if (data_motor[i].owner == username && data_motor[i].plat == plat_motor_temp){
                    string nama_motor, warna_motor, transmisi_motor, plat_motor;
                    int jarak_tempuh;
                    cout << "Nama Motor: ";
                    cin.ignore();
                    getline(cin, nama_motor);
                    // Input plat motor
                    cout << "Plat Motor: ";
                    getline(cin, plat_motor);
                    /* Inputan plat boleh sama dengan yang sebelumnya
                    tetapi tidak boleh sama dengan plat yang lain*/
                    string data_plat_temp;
                    string inp_plat_temp = plat_motor;
                    for (int i = 0; i < data_motor.size(); i++){
                        // Bandingkan tanpa memperhatikan spasi
                        data_plat_temp = data_motor[i].plat;
                        // Hapus spasi dari string plat
                        data_plat_temp.erase(remove(data_plat_temp.begin(), data_plat_temp.end(), ' '), data_plat_temp.end());
                        inp_plat_temp.erase(remove(inp_plat_temp.begin(), inp_plat_temp.end(), ' '), inp_plat_temp.end());
                        if (data_plat_temp.compare(inp_plat_temp) == 0 && data_motor[i].plat != plat_motor_temp){
                            cout << "Plat motor sudah terdaftar" << endl;
                            cout << "Plat Motor: ";
                            getline(cin, plat_motor);
                            inp_plat_temp = plat_motor;
                            i = -1;
                        }
                    }
                    cout << "Warna Motor: ";
                    getline(cin, warna_motor);
                    cout << "Transmisi Motor: ";
                    while (true){
                        getline(cin, transmisi_motor);
                        if (transmisi_motor == "manual" || transmisi_motor == "automatic"){
                            break;
                        }
                        else{
                            cout << "Transmisi motor hanya bisa manual atau automatic" << endl;
                            cout << "Transmisi Motor: ";
                        }
                    }
                    // Input jarak tempuh
                    cout << "Jarak Tempuh Motor (KM): ";
                    cin >> jarak_tempuh;
                    while (cin.fail()) {
                        cin.clear();
                        cin.ignore(999, '\n');
                        cout << "Input tidak valid. Silahkan masukkan angka." << endl;
                        cout << "Jarak Tempuh Motor (KM): ";
                        cin >> jarak_tempuh;
                    }

                    // Update Data Vektor Motor
                    motor_data new_motor;
                    new_motor.owner = username;
                    new_motor.nama_motor = nama_motor;
                    new_motor.warna_motor = warna_motor;
                    new_motor.transmisi = transmisi_motor;
                    new_motor.plat = plat_motor;
                    new_motor.jarak_tempuh = jarak_tempuh;
                    new_motor.service = false;
                    
                    // Hapus data motor yang dipilih dari vektor
                    data_motor.erase(data_motor.begin() + i);

                    // Hapus juga data kondisi motor 
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

                    // input kondisi motor jika transmisi adalah automatic
                    if (transmisi_motor == "automatic") {
                        kondisi_automatic kondisi;
                        kondisi.plat = plat_motor;
                        // Input kondisi motor automatic
                        cout << "Ban Belakang: ";
                        while (!(cin >> kondisi.ban_belakang)) {
                            cout << "Invalid Input, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                        }
                        cout << "Ban Depan: ";
                        while (!(cin >> kondisi.ban_depan)) {
                            cout << "Invalid Input, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                        }
                        cout << "Busi: ";
                        while (!(cin >> kondisi.busi)) {
                            cout << "Invalid Input, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                        }
                        cout << "Kampas Rem: ";
                        while (!(cin >> kondisi.kampas_rem)) {
                            cout << "Invalid Input, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                        }
                        cout << "Minyak Rem: ";
                        while (!(cin >> kondisi.minyak_rem)) {
                            cout << "Invalid Input, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                        }
                        cout << "Oli Gardan: ";
                        while (!(cin >> kondisi.oli_gardan)) {
                            cout << "Invalid Input, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                        }
                        cout << "Oli Mesin: ";
                        while (!(cin >> kondisi.oli_mesin)) {
                            cout << "Invalid Input, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                        }
                        cout << "Roller: ";
                        while (!(cin >> kondisi.roller)) {
                            cout << "Invalid Input, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                        }
                        cout << "Van Belt: ";
                        while (!(cin >> kondisi.van_belt)) {
                            cout << "Invalid Input, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
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

                    // Input kondisi motor jika transmisi adalah manual
                    if (transmisi_motor == "manual") {
                        kondisi_manual kondisi;
                        kondisi.plat = plat_motor;
                        // Input kondisi motor manual
                        cout << "Ban Belakang: ";
                        while (!(cin >> kondisi.ban_belakang)) {
                            cout << "Invalid Input, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                        }
                        cout << "Ban Depan: ";
                        while (!(cin >> kondisi.ban_depan)) {
                            cout << "Invalid Input, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                        }
                        cout << "Busi: ";
                        while (!(cin >> kondisi.busi)) {
                            cout << "Invalid Input, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                        }
                        cout << "Gear: ";
                        while (!(cin >> kondisi.gear)) {
                            cout << "Invalid Input, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                        }
                        cout << "Kampas Kopling: ";
                        while (!(cin >> kondisi.kampas_kopling)) {
                            cout << "Invalid Input, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                        }
                        cout << "Kampas Rem: ";
                        while (!(cin >> kondisi.kampas_rem)) {
                            cout << "Invalid Input, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                        }
                        cout << "Minyak Rem: ";
                        while (!(cin >> kondisi.minyak_rem)) {
                            cout << "Invalid Input, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                        }
                        cout << "Oli Mesin: ";
                        while (!(cin >> kondisi.oli_mesin)) {
                            cout << "Invalid Input, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                        }
                        cout << "Rantai: ";
                        while (!(cin >> kondisi.rantai)) {
                            cout << "Invalid Input, Tolong Masukkan Angka yang sesuai." << endl;
                            cin.clear();
                            cin.ignore(999, '\n');
                        }
                        // Tambahkan data vektor yang baru
                        data_kondisi_manual.push_back(kondisi);
                        // Sort data kondisi manual  dengan bubble sort, ascending berdasarkan plat
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

                    // Update csv data motor
                    write_csv_motor();
                    read_csv_motor();
                    cout << "Data motor berhasil ditambahkan!" << endl;
                    pause();
                    clear();
                    return;
                }
            }
        }
        // Input tidak sesuai
        else {
            cout << "Pilihan tidak tersedia. Silahkan masukkan nomor yang sesuai" << endl;
            pause();
            clear();
        }
    }
}

void hapus_motor(string username){
    vector<string> plat_vector;
    // Tampilkan list motor yang dimiliki user
    cout << "=============================" << endl;
    cout << "       HAPUS DATA MOTOR" << endl;
    cout << "=============================" << endl;
    cout << "Username: " << username << endl;
    cout << "----------------------------" << endl;
    // Menghitung jumlah motor yang dimiliki user
    int count = 1;
    for (int i = 0; i < data_motor.size(); i++){
        if (data_motor[i].owner == username){
            cout << count << ". "; count++;
            cout << "Nama Motor: " << data_motor[i].nama_motor;
            if (data_motor[i].service){
                cout << " (Service)";
            }
            cout << endl;
            cout << "Plat: " << data_motor[i].plat << endl;
            plat_vector.push_back(data_motor[i].plat);
            cout << "Warna: " << data_motor[i].warna_motor << endl;
            cout << "Transmisi: " << data_motor[i].transmisi << endl;
            cout << "Jarak Tempuh: " << data_motor[i].jarak_tempuh << " KM" << endl;
            cout <<"----------------------------"<< endl;
        }
    }
    // Pilih Nomor Motor yang akan dihapus
    int pilih_motor;
    while (true) {
        cout << "Pilih nomor motor untuk dihapus: ";
        cin >> pilih_motor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(999, '\n');
            cout << "Input tidak valid. Silahkan masukkan angka." << endl;
            pause();
            clear();
            continue;
        }
        // Jika nomor yang dipilih sesuai dengan jumlah motor
        if (pilih_motor >= 1 && pilih_motor <= count-1){ 
            clear();
            // Simpan plat dari motor yang dipilih
            string plat_motor_temp = plat_vector[pilih_motor-1];

            // Jika nomor yang dipilih sedang diservis, tidak boleh dihapus, return
            for (int i = 0; i < data_motor.size(); i++){
                if (data_motor[i].owner == username && data_motor[i].plat == plat_motor_temp){
                    if (data_motor[i].service){
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
}

void edit_akun_user(string *username){
    // Tampilkan data akun user
    cout << "=============================" << endl;
    cout << "       EDIT DATA AKUN" << endl;
    cout << "=============================" << endl;
    cout << "Username: " << *username << endl;
    cout << "----------------------------" << endl;
    for (int i = 0; i < data_user.size(); i++){
        if (data_user[i].username == *username){
            cout << "Username: " << data_user[i].username << endl;
            cout << "Password: " << data_user[i].password << endl;
            cout << "No. Telepon: " << data_user[i].telepon << endl;
            cout << "Alamat: " << data_user[i].address << endl;
            cout << "----------------------------" << endl;
        }
    }
    // Input data baru
    string data_username_temp, data_telepon_temp;
    string inp_username_temp, inp_telepon_temp;
    for (int i = 0; i < data_user.size(); i++){
        if (data_user[i].username == *username){
            string new_username, new_password, new_telepon, new_address;
            cout << "Username baru: ";
            // username tidak boleh sama dengan username lain, tapi boleh sama dengan username yang sebelumnya
            cin.ignore();
            getline(cin, new_username);
            inp_username_temp = new_username;
            for (int i = 0; i < data_user.size(); i++){
                // Bandingkan tanpa memperhatikan spasi
                data_username_temp = data_user[i].username;
                // Hapus spasi dari string username
                data_username_temp.erase(remove(data_username_temp.begin(), data_username_temp.end(), ' '), data_username_temp.end());
                inp_username_temp.erase(remove(inp_username_temp.begin(), inp_username_temp.end(), ' '), inp_username_temp.end());
                if (data_username_temp.compare(inp_username_temp) == 0 && data_user[i].username != *username){
                    cout << "Username sudah terdaftar" << endl;
                    cout << "Username baru: ";
                    getline(cin, new_username);
                    inp_username_temp = new_username;
                    i = -1;
                }
            }
            cout << "Password baru: ";
            getline(cin, new_password);
            cout << "No. Telepon baru: ";
            // telepon boleh sama dengan telepon yang sebelumnya, tapi tidak boleh sama dengan telepon yang lain
            getline(cin, new_telepon);
            for (int i = 0; i < data_user.size(); i++){
                if (data_user[i].telepon == new_telepon && data_user[i].username != *username){
                    cout << "No. Telepon sudah terdaftar" << endl;
                    cout << "No. Telepon baru: ";
                    getline(cin, new_telepon);
                    i = -1;
                }
            }
            cout << "Alamat baru: ";
            getline(cin, new_address);

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
            /* update username vektor sparepart status_user active*/
            for (int i = 0; i < data_struk_sparepart.size(); i++){
                if (data_struk_sparepart[i].username == *username && data_struk_sparepart[i].status_akun == "active"){
                    data_struk_sparepart[i].username = new_username;
                }
            }

            // Update csv 
            write_csv_user();
            read_csv_user();
            write_csv_motor();
            read_csv_motor();
            write_csv_struk_sparepart();
            read_csv_struk_sparepart();

            // Update username global
            *username = new_username;

            cout << "Data akun berhasil diubah!" << endl;
            pause();
            clear();
            return;
        }
    }

}

void hapus_akun_user(string username){
    // // Cuma bisa hapus akun ketika tidak ada motor yang sedang servis
    // for (int i = 0; i < data_motor.size(); i++){
    //     if (data_motor[i].owner == username){
    //         if (data_motor[i].service){
    //             clear();
    //             cout << "Terdapat motor yang sedang diservis, tidak bisa hapus akun" << endl;
    //             pause();
    //             clear();
    //             return;
    //         }
    //     }
    // }
    // // Hapus data user yang dipilih dari vektor
    // for (int i = 0; i < data_user.size(); i++){
    //     if (data_user[i].username == username){
    //         data_user.erase(data_user.begin() + i);
    //     }
    // }
    // // Hapus data motor yang dipilih dari vektor
    // for (int i = 0; i < data_motor.size(); i++){
    //     // cara  data motor yang dimiliki user
    //     if (data_motor[i].owner == username){
    //         /// Hapus  data kondisi motor
    //         if (data_motor[i].transmisi == "manual"){
    //             for (int i = 0; i < data_kondisi_manual.size(); i++){
    //                 if (data_kondisi_manual[i].plat == data_motor[i].plat){
    //                     data_kondisi_manual.erase(data_kondisi_manual.begin() + i);
    //                 }
    //             }
    //         }
    //         if (data_motor[i].transmisi == "automatic"){
    //             for (int i = 0; i < data_kondisi_automatic.size(); i++){
    //                 if (data_kondisi_automatic[i].plat == data_motor[i].plat){
    //                     data_kondisi_automatic.erase(data_kondisi_automatic.begin() + i);
    //                 }
    //             }
    //         }
    //         // Hapus data motor yang dimiliki user
    //         data_motor.erase(data_motor.begin() + i);
    //     }
    // }

    // // Hapus data struk sparepart dengan username sama
    // for (int i = 0; i < data_struk_sparepart.size(); i++){
    //     if (data_struk_sparepart[i].user == username){
    //         data_struk_sparepart.erase(data_struk_sparepart.begin() + i);
    //     }
    // }

    // // Update csv data user
    // write_csv_user();
    // read_csv_user();
    // write_csv_motor();
    // read_csv_motor();
    // write_csv_struk_servis();
    // read_csv_struk_servis();
    // write_csv_struk_sparepart();
    // read_csv_struk_sparepart();
}

// Fungsi-fungsi menu
int menu_awal(){
    int pilih;
    while (true) {
        cout << "=============================" << endl;
        cout << "          MENU AWAL" << endl;
        cout << "=============================" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cout << "Pilih menu: ";
        cin >> pilih;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(999, '\n');
            cout << "Input tidak valid. Silahkan masukkan angka 1-3." << endl;
            pause();
            clear();
        } else if (pilih >= 1 && pilih <= 3) {
            return pilih;
        } else {
            cout << "Menu tidak tersedia. Silahkan masukkan angka 1-3." << endl;
            pause();
            clear();
        }
    }
}

// Menu-menu user
void menu_motor(string global_username){
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
        cin >> pilih;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(999, '\n');
            cout << "Input tidak valid. Silahkan masukkan angka 1-5." << endl;
            pause();
            clear();
        } else if (pilih >= 1 && pilih <= 5) {
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
                return;
                break;
            }
        } else {
            cout << "Menu tidak tersedia. Silahkan masukkan angka 1-5." << endl;
            pause();
            clear();
        }
    }
}

int menu_data_akun(string global_username){
    int pilih;
    while (true) {
        cout << "=============================" << endl;
        cout << "        MENU DATA AKUN" << endl;
        cout << "=============================" << endl;
        cout << "Username: " << global_username << endl;
        cout << "----------------------------" << endl;
        cout << "1. Edit Data Akun" << endl;
        cout << "2. Hapus Data Akun" << endl;
        cout << "3. Kembali (Menu User)" << endl;
        cout << "----------------------------" << endl;
        cout << "Pilih menu: ";
        cin >> pilih;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(999, '\n');
            cout << "Input tidak valid. Silahkan masukkan angka 1-3." << endl;
            pause();
            clear();
        } else if (pilih >= 1 && pilih <= 3) {
            switch (pilih)
            {
            case 1:
                // Edit Data Akun
                clear();
                edit_akun_user(&global_username);
                break;
            case 2:
                // Hapus Data Akun
                clear();
                hapus_akun_user(global_username);
                return 1; // Logout akun
                break;
            case 3:
                // Kembali (Menu User)
                clear();
                return 0; // Tidak Logout
                break;
            }
        } else {
            cout << "Menu tidak tersedia. Silahkan masukkan angka 1-3." << endl;
            pause();
            clear();
        }
    }

}

void menu_perawatan(string global_username){
    /* 
    1. Tampilkan List Motor yang dimiliki user
    2. Pilih motor yang akan ditunjukkan jadwal perawatan
    3. Tampilkan jadwal perawatan per sparepart
    (jadwal perawatan ini dihitung dengan: 
    - jarak tempuh motor yang dimiliki
    - terakhir servir sparepart motor yang dimiliki
    - jadwal rutin servis untuk sparepart yang ada pada database)
    ex : 

    > Servis yang akan datang
    Ban Belakang harus disercis setelah 5000 KM
    > Servis yang telat
    Telat 2000 KM untuk servis oli mesin
         
    */
}  

void menu_user_servis(string global_username){
    /* 
    Menu :
    a. Pesan Jasa Servis Motor
    1. Tampilkan List Motor yang dimiliki user
    2. Pilih motor yang akan diservis
    3. Tunggu
    4. Admin akan melakukan servis (menu admin)
    5. Admin akan mengupdate data servis pada sparepart motor yang dipilih (menu admin)
    6. Struk servis akan disimpan di database
    7. Motor sudah selesai diservis

    b. tampilkan history servis struk
    1. Tampilkan List struk, ascended dari id terkecil
    2. Pilih untuk menampilkan detail struk, atau kembali (menu user_servis)
    */
}

void menu_user_sparepart(string global_username){
    /* 
    Menu :
    a. Pesan Sparepart
    1. Tampilkan List Sparepart yang tersedia
    2. Pilih sparepart yang akan dipesan
    3. Input jumlah sparepart yang akan dipesan
    4. Struk pemesanan ditampilkan dan disimpan di database
    5. kembali (menu user)

    b. tampilkan history pesanan sparepart
    1. Tampilkan List pesanan, ascended dari id terkecil
    2. Pilih untuk menampilkan detail pesanan, atau kembali (menu user_sparepart)
    */
}

void menu_user(string global_username){
    int pilih, result;
    while (true) {
        cout << "=============================" << endl;
        cout << "          MENU USER" << endl;
        cout << "=============================" << endl;
        cout << "Username : " << global_username << endl;
        cout << "----------------------------" << endl;
        cout << "1. Menu Data Motor" << endl;
        cout << "2. Menu Data Akun" << endl;
        cout << "3. Jadwal Perawatan Motor" << endl;
        cout << "4. Jasa Service Motor" << endl;
        cout << "5. Pemesanan Sparepart Motor" << endl;
        cout << "6. Log Out" << endl;
        cout << "----------------------------" << endl;
        cout << "Pilih menu: ";
        cin >> pilih;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(999, '\n');
            cout << "Input tidak valid. Silahkan masukkan angka 1-6." << endl;
            pause();
            clear();
        } else if (pilih >= 1 && pilih <= 6) {
            switch (pilih)
            {
            case 1:
                // Menu Data Motor
                clear();
                menu_motor(global_username);
                break;
            case 2:
                // Menu Data Akun
                clear();
                result = menu_data_akun(global_username);
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
                // Jasa Service Motor
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
        } else {
            cout << "Menu tidak tersedia. Silahkan masukkan angka 1-6." << endl;
            pause();
            clear();
        }
    }
}


// Menu-Menu Admin
void edit_data_admin(string global_username){
    string new_username, new_password;
    cout << "=============================" << endl;
    cout << "     EDIT DATA ADMIN" << endl;
    cout << "=============================" << endl;
    cout << "Username: " << global_username << endl;
    cout << "----------------------------" << endl;
    cout << "Masukkan Username Baru: ";
    cin >> new_username;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(999, '\n');
        cout << "Input tidak valid. Silahkan masukkan username baru." << endl;
        cout << "Masukkan Username Baru: ";
        cin >> new_username;
    }
    cout << "Masukkan Password Baru: ";
    cin >> new_password;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(999, '\n');
        cout << "Input tidak valid. Silahkan masukkan password baru." << endl;
        cout << "Masukkan Password Baru: ";
        cin >> new_password;
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

    cout << "Data Admin berhasil diupdate, Silahkan Login Ulang." << endl;
    pause();
    clear();
    return;
}

void admin_servis(string global_username){
    /* 
    1. Tampilkan List Motor yang dimiliki user
    2. Pilih motor yang akan diservis
    3. Tunggu
    4. Admin akan melakukan servis
    5. Admin akan mengupdate data servis pada sparepart motor yang dipilih
    6. Struk servis akan diberikan kepada user, dan disimpan di database
    7. Motor sudah selesai diservis
    */
}

void admin_sparepart(string global_username){
    /* 
    1. Tampilkan List Sparepart yang tersedia
    2. Tambah Sparepart
    3. Edit Sparepart
    4. Hapus Sparepart
    */
}

void menu_admin(string global_username){
    int pilih;
    while (true) {
        cout << "=============================" << endl;
        cout << "          MENU ADMIN" << endl;
        cout << "=============================" << endl;
        cout << "Username : " << global_username << endl;
        cout << "----------------------------" << endl;
        cout << "1. Edit Data Admin" << endl;
        cout << "2. Layanan Servis" << endl;
        cout << "3. Toko Sparepart" << endl;
        cout << "4. Log Out" << endl;
        cout << "Pilih menu: ";
        cin >> pilih;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(999, '\n');
            cout << "Input tidak valid. Silahkan masukkan angka 1-4." << endl;
            pause();
            clear();
        } else if (pilih >= 1 && pilih <= 4) {
            switch (pilih)
            {
            case 1:
                // Edit Data Admin
                clear();
                edit_data_admin(global_username);
                return;
                break;
            case 2:
                // Layanan Servis (Admin)
                break;
            case 3:
                // Toko Sparepart (Admin)
                break;
            }
        } else {
            cout << "Menu tidak tersedia. Silahkan masukkan angka 1-4." << endl;
            pause();
            clear();
        }
    }
}


// Fungsi Main
int main(){
    //tes write file
    write_csv_user();
    write_csv_motor();
    write_csv_struk_servis();
    write_csv_struk_sparepart();
    write_csv_list_sparepart();



    // Membaca data csv di awal
    read_csv_user();
    read_csv_motor();
    read_csv_struk_servis();
    read_csv_struk_sparepart();
    read_csv_list_sparepart();

    // tes output semua data vektor 
    // cout << "Data User:" << endl;
    // for (const auto& user : data_user) {
    //     cout << "Username: " << user.username << endl;
    //     cout << "Password: " << user.password << endl;
    //     cout << "Telepon: " << user.telepon << endl;
    //     cout << "Alamat: " << user.address << endl;
    //     cout << "------------------------" << endl;
    // }
    // cout << "Data Motor:" << endl;
    // for (const auto& motor : data_motor) {
    //     cout << "Pemilik: " << motor.owner << endl;
    //     cout << "Nama Motor: " << motor.nama_motor << endl;
    //     cout << "Warna Motor: " << motor.warna_motor << endl;
    //     cout << "Transmisi: " << motor.transmisi << endl;
    //     cout << "Plat: " << motor.plat << endl;
    //     cout << "Jarak Tempuh: " << motor.jarak_tempuh << endl;
    //     cout << "Service: " << (motor.service ? "Yes" : "No") << endl;
    //     cout << "------------------------" << endl;
    // }
    // cout << "Data Kondisi Manual:" << endl;
    // for (const auto& kondisi : data_kondisi_manual) {
    //     cout << "Plat: " << kondisi.plat << endl;
    //     cout << "Ban Belakang: " << kondisi.ban_belakang << endl;
    //     cout << "Ban Depan: " << kondisi.ban_depan << endl;
    //     cout << "Busi: " << kondisi.busi << endl;
    //     cout << "Gear: " << kondisi.gear << endl;
    //     cout << "Kampas Kopling: " << kondisi.kampas_kopling << endl;
    //     cout << "Kampas Rem: " << kondisi.kampas_rem << endl;
    //     cout << "Minyak Rem: " << kondisi.minyak_rem << endl;
    //     cout << "Oli Mesin: " << kondisi.oli_mesin << endl;
    //     cout << "Rantai: " << kondisi.rantai << endl;
    //     cout << "------------------------" << endl;
    // }
    // cout << "Data Kondisi Automatic:" << endl;
    // for (const auto& kondisi : data_kondisi_automatic) {
    //     cout << "Plat: " << kondisi.plat << endl;
    //     cout << "Ban Belakang: " << kondisi.ban_belakang << endl;
    //     cout << "Ban Depan: " << kondisi.ban_depan << endl;
    //     cout << "Busi: " << kondisi.busi << endl;
    //     cout << "Kampas Rem: " << kondisi.kampas_rem << endl;
    //     cout << "Minyak Rem: " << kondisi.minyak_rem << endl;
    //     cout << "Oli Gardan: " << kondisi.oli_gardan << endl;
    //     cout << "Oli Mesin: " << kondisi.oli_mesin << endl;
    //     cout << "Roller: " << kondisi.roller << endl;
    //     cout << "Van Belt: " << kondisi.van_belt << endl;
    //     cout << "------------------------" << endl;
    // }
    // cout << "Data Struk Service:" << endl;
    // for (const auto& struk : data_struk_service) {
    //     cout << "ID: " << struk.id << endl;
    //     cout << "Plat: " << struk.plat << endl;
    //     cout << "Status: " << struk.status << endl;
    //     cout << "Servis:" << endl;
    //     for (const auto& servis : struk.servis) {
    //         cout << "Nama Servis: " << servis.nama_servis << endl;
    //         cout << "Harga Servis: " << servis.harga_servis << endl;
    //     }
    //     cout << "------------------------" << endl;
    // }
    // cout << "Data Struk Sparepart:" << endl;
    // for (const auto& struk : data_struk_sparepart) {
    //     cout << "ID: " << struk.id << endl;
    //     cout << "User: " << struk.user << endl;
    //     cout << "Pesanan:" << endl;
    //     for (const auto& pesanan : struk.pesanan) {
    //         cout << "Nama Sparepart: " << pesanan.nama_sparepart << endl;
    //         cout << "Jumlah: " << pesanan.jumlah << endl;
    //         cout << "Harga: " << pesanan.harga << endl;
    //     }
    //     cout << "------------------------" << endl;
    // }
    // cout << "Data List Sparepart:" << endl;
    // for (const auto& sparepart : data_list_sparepart) {
    //     cout << "Nama Sparepart: " << sparepart.nama_sparepart << endl;
    //     cout << "Tipe Transmisi: " << sparepart.tipe_transmisi << endl;
    //     cout << "Harga Sparepart: " << sparepart.harga_sparepart << endl;
    //     cout << "Kilometer: " << sparepart.kilometer << endl;
    //     cout << "Stok Sparepart: " << sparepart.stok_sparepart << endl;
    //     cout << "------------------------" << endl;
    // }
    // pause();

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
