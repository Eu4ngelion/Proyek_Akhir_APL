#include <iostream>
#include <cctype>
#include <sstream> // manipulasi string
#include <fstream> // manipulasi file
#include <vector> // array dinamis

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
struct struk_service{
    int id;
    vector<servis_data> servis;
    int harga_jasa;
};

// Data Sparepart
struct sparepart_data{
    string nama_sparepart;
    string tipe_transmisi;
    int harga_sparepart;
    int kilometer;
    int stok_sparepart;
};

// Variabel Global:
vector<user_data> data_user;
vector<motor_data> data_motor;
vector<kondisi_manual> data_kondisi_manual;
vector<kondisi_automatic> data_kondisi_automatic;
vector<struk_service> data_struk_service;
vector<sparepart_data> data_sparepart;

void clear(){
    system("cls");
    return;
}
void pause(){
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
void update_csv_user(){ // mengupdate data user kembali ke file user_log.csv
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
void read_csv_motor(){// read csv motor, list_motor.csv, kondisi_motor_manual.csv, kondisi_motor_automatic.csv
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
void update_csv_motor(){// update_csv_motor dari vektor kembalikan ke csv, list_motor.csv, kondisi_motor_manual.csv, kondisi_motor_automatic.csv
    ofstream file;
    file.open("Database/list_motor.csv");
    if (!file) {
        cout << "Gagal membaca data motor (list_motor.csv)" << endl;
        pause();
        return;
    }
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

    file.open("Database/kondisi_motor_manual.csv");
    if (!file) {
        cout << "Gagal membaca data kondisi motor manual (kondisi_motor_manual.csv)" << endl;
        pause();
        return;
    }
    file << "Plat,Ban Belakang,Ban Depan,Busi,Gear,Kampas Kopling,Kampas Rem,Minyak Rem,Oli Mesin,Rantai" << endl;
    for (int i = 0; i < data_kondisi_manual.size(); i++){
        file << data_kondisi_manual[i].plat << "," << data_kondisi_manual[i].ban_belakang << "," << data_kondisi_manual[i].ban_depan << "," 
        << data_kondisi_manual[i].busi << "," << data_kondisi_manual[i].gear << "," << data_kondisi_manual[i].kampas_kopling << "," 
        << data_kondisi_manual[i].kampas_rem << "," << data_kondisi_manual[i].minyak_rem << "," << data_kondisi_manual[i].oli_mesin << "," << data_kondisi_manual[i].rantai << endl;
    }
    file.close();

    file.open("Database/kondisi_motor_automatic.csv");
    if (!file) {
        cout << "Gagal membaca data kondisi motor automatic (kondisi_motor_automatic.csv)" << endl;
        pause();
        return;
    }
    file << "Plat,Ban Belakang,Ban Depan,Busi,Kampas Rem,Minyak Rem,Oli Gardan,Oli Mesin,Roller,Van Belt" << endl;
    for (int i = 0; i < data_kondisi_automatic.size(); i++){
        file << data_kondisi_automatic[i].plat << "," << data_kondisi_automatic[i].ban_belakang << "," << data_kondisi_automatic[i].ban_depan << "," 
        << data_kondisi_automatic[i].busi << "," << data_kondisi_automatic[i].kampas_rem << "," << data_kondisi_automatic[i].minyak_rem << "," 
        << data_kondisi_automatic[i].oli_gardan << "," << data_kondisi_automatic[i].oli_mesin << "," << data_kondisi_automatic[i].roller << "," << data_kondisi_automatic[i].van_belt << endl;
    }
    file.close();
    return;
}


// Fungsi Login dan Register
int login(int try_left, string *global_username, string *global_password){
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
void regist(){ // setelah register, data ditambahkan ke file user_log.csv dan di sort dengan bubble sort
    string username_inp, password_inp, telepon_inp, address_inp;

    cout << "=============================" << endl;
    cout << "        MENU REGISTER" << endl;
    cout << "=============================" << endl;
    // Input Username
    cout << "Username: ";
    cin >> username_inp;
    // memastikan username unik dan tidak mengandung spasi
    if (password_inp.find(",") != string::npos){ 
        cout << "Username tidak boleh mengandung spasi" << endl;
        pause();
        clear();
        return;
    }
    // Mengecek seluruh data vektor, username harus unik
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
    update_csv_user();
    read_csv_user();

    cout << "Registrasi berhasil" << endl;
    pause();
    clear();
    return;
}


// Bagian Menu User
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
    // Memastikan plat motor belum terdaftar
    for (int i = 0; i < data_motor.size(); i++){
        if (data_motor[i].plat == plat_motor){
            cout << "Plat motor sudah terdaftar" << endl;
            cout << "Plat Motor: ";
            getline(cin, plat_motor);
            i = 0;
        }
    }
    // input jarak tempuh
    int jarak_tempuh;
    cout << "Jarak Tempuh (KM): ";
    while (!(cin >> jarak_tempuh)) {
        cout << "Invalid input. Silahkan masukkan angka." << endl;
        cin.clear();
        cin.ignore(999, '\n');
    }
    // menambahkan data motor ke vektor
    motor_data temp;
    temp.owner = username;
    temp.nama_motor = nama_motor;
    temp.warna_motor = warna_motor;
    temp.transmisi = transmisi_motor;
    temp.plat = plat_motor;
    temp.service = false; // service default = false
    data_motor.push_back(temp);

    // Input kondisi
    cout << "=============================" << endl;
    cout << "      Terakhir Servis(Km)" << endl;
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
    else if (transmisi_motor == "manual") {
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

    // update csv motor
    update_csv_motor();
    read_csv_motor();
    cout << "Data motor berhasil ditambahkan" << endl;
    pause();
    clear();
    return;
}
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
void menu_user(string global_username){
    int pilih;
    while (true) {
        cout << "=============================" << endl;
        cout << "          MENU USER" << endl;
        // Tampilkan username saat ini
        cout << "=============================" << endl;
        cout << "Username : " << global_username << endl;
        cout << "1. Tambah Data Motor" << endl;
        cout << "2. Tampilkan Data Motor" << endl;
        cout << "3. Edit Data Motor" << endl;
        cout << "4. Edit Data Akun" << endl;
        cout << "5. Jadwal Perawatan Motor" << endl;
        cout << "6. Pelayanan Service Motor" << endl;
        cout << "7. Pemesanan Sparepart Motor" << endl;
        cout << "8. Log Out" << endl;
        cout << "Pilih menu: ";
        cin >> pilih;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(999, '\n');
            cout << "Input tidak valid. Silahkan masukkan angka 1-8." << endl;
            pause();
            clear();
        } else if (pilih >= 1 && pilih <= 8) {
            switch (pilih)
            {
            case 1:
                // Tambah Data Motor
                clear();
                add_motor(global_username);
                break;
            case 2:
                // Tampilkan Data Motor
                break;
            case 3:
                // Edit Data Motor
                break;
            case 4:
                // Edit Data Akun
                break;
            case 5:
                // Jadwal Perawatan Motor
                break;
            case 6:
                // Pelayanan Service Motor
                break;
            case 7:
                // Pemesanan Sparepart Motor
                break;
            case 8:
                // Log Out
                return;
                break;
            }
        } else {
            cout << "Menu tidak tersedia. Silahkan masukkan angka 1-8." << endl;
            pause();
            clear();
        }
    }
}

// Bagian menu Admin

void menu_admin(string global_username){
    int pilih;
    while (true) {
        cout << "=============================" << endl;
        cout << "          MENU ADMIN" << endl;
        cout << "=============================" << endl;

        cout << "1. Edit Data Admin" << endl;
        cout << "2. Layanan Servis" << endl;
        cout << "3. Toko Sparepart" << endl;
        cout << "4. Log Out" << endl;
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
                // Edit Data Admin
                break;
            case 2:
                // Layanan Servis
                break;
            case 3:
                // Toko Sparepart
                break;
            }
        } else {
            cout << "Menu tidak tersedia. Silahkan masukkan angka 1-3." << endl;
            pause();
            clear();
        }
    }
}

int main(){
    // Membacca data csv di awal
    read_csv_user();
    read_csv_motor();

    // Variabel lokal main
    string global_username, global_password;
    int log_result;
    while(true){
        clear();
        int pilih = menu_awal();
        switch(pilih){
            case 1: // Login
                clear();
                // Menu Admin
                log_result = login(3, &global_username, &global_password);
                if (log_result == 0){
                    cout << "Menu Admin" << endl;
                }
                // Menu User
                else if (log_result == 1){
                    menu_user(global_username);
                }
                else if (log_result == 2){
                    clear();
                    continue;
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
