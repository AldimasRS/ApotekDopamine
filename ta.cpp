#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <fstream>
using namespace std;

struct dataobat{
	char kodeobat[6], namaobat[20], jenisobat[20];
	int hargaobat, jumlahobat;
};

struct tempobat{
	char kodeobat[6], namaobat[20], jenisobat[20];
	int hargaobat, jumlahobat;
	tempobat *next;
}*head, *tail, *curr, *entry;

struct nodeantri{
	int no, keterangan;	
	nodeantri *nexta;
}*heada, *taila, *entrya, *curra, *dela;

void gotoxy(short x, short y);
int getdatasize(fstream &data, int *size);
void writedataob(fstream &ob, int posisi, dataobat &inputob);
dataobat readdataob(fstream &ob, int posisi);
void menulogin();
void tambahdata(fstream &ob);
void sortdata(fstream &ob);
int searchdata(string cari, string dicari);
void searchob(fstream &ob);
void cetakdatao(fstream &ob, int posisi);
void searchdataob(fstream &ob);
void hapusdata(fstream &ob, int posisi);
void judul();
void admin();
void pelanggan();
void keluar();
void siapa();
int checkwheredataobat(fstream &ob, string kodeobat);
void insertantri(int no, int pcc);
void init();
void hapus();
void clear();
void show();

int a, i, ukuran, size, finded, noantri;
string user, pass;
char searchthem[20], pilih, kodeobat[6], pilihan;

fstream ob, so;

int main()
{
	system("cls");
	system("color 0A");
	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	ob.open("dataobat.bin", ios::out | ios::in | ios::binary);
	if(!ob.is_open()){
		ob.close();
		ob.open("dataobat.bin", ios::trunc | ios::out | ios::in | ios::binary);
	}
	getch();
	ukuran = sizeof(dataobat);
	size = getdatasize(ob, &ukuran);
	judul();
	siapa();	
	getch();
}

void gotoxy(short x, short y){
	COORD k = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), k);
}

int getdatasize(fstream &data, int *size){
	int start, end;
	data.seekg(0, ios::beg);
	start = data.tellg();
	data.seekg(0, ios::end);
	end = data.tellg();
	return (end - start) / *size;
}

void writedataob(fstream &ob, int posisi, dataobat &inputob){
	ob.seekp(posisi * sizeof(dataobat), ios::beg);
	ob.write(reinterpret_cast<char*>(&inputob), sizeof(dataobat));
}

dataobat readdataob(fstream &ob, int posisi){
	dataobat readobat;
	ob.seekg(posisi * sizeof(dataobat), ios::beg);
	ob.read(reinterpret_cast<char*>(&readobat), sizeof(dataobat));
	return readobat;
}

void menulogin(){
	menulogin:
	system("cls");
	string hp;
	char hpass;
	gotoxy(67, 13); cout << "Laman Login";
	gotoxy(65, 14); cout << "Username : ";
	gotoxy(76, 14); cin >> user;
	gotoxy(65, 15); cout << "Password : ";
	gotoxy(76, 15); hpass = getch();
	while(hpass != 13){
		hp.push_back(hpass);
		cout << "*";
		hpass = getch();
	}
	pass = hp;
	if((user == "admin") && (pass == "admin")){
		gotoxy(68, 16); cout << "Benar";
		Sleep(500);
	}else{
		gotoxy(68, 16); cout << "Salah";
		Sleep(500);
		goto menulogin;
	}
}

void tambahdata(fstream &ob){
	dataobat inputo;
	gotoxy(65, 13);cout << "Kode obat   : ";
	cin >> inputo.kodeobat;
	gotoxy(65, 14);cout << "Nama obat   : ";
	gets(inputo.namaobat);gets(inputo.namaobat);
	gotoxy(65, 15);cout << "Jenis obat  : ";
	gets(inputo.jenisobat);
	gotoxy(65, 16);cout << "Harga obat  : ";
	cin >> inputo.hargaobat;
	gotoxy(65, 17);cout << "Jumlah obat : ";
	cin >> inputo.jumlahobat;
	gotoxy(65, 18);cout << "Yakin (Y/N)? ";
	gotoxy(77, 18);cin >> pilih;
	if (pilih == 'y' && 'Y'){
		writedataob(ob, size, inputo);
	}else if(pilih == 'n' && 'N'){
	}else{
		cout << "Error";
		getch();
	}
	
}

void sortdata(fstream &ob){
	dataobat sorto1, sorto2, temp;
	char tempkodeobat[6], tempnamaobat[20], tempjenisobat[20];
	int temphargaobat, tempjumlahobat;
	bool swap;
	
	
	do{
		swap = false;	
		for(i = 0; i < (size - 1); i++){
			sorto1 = readdataob(ob, i);
			sorto2 = readdataob(ob, i + 1);
			if(strcmp(sorto1.kodeobat, sorto2.kodeobat) == 1){
				strcpy(tempkodeobat, sorto1.kodeobat);
				strcpy(tempnamaobat, sorto1.namaobat);
				strcpy(tempjenisobat, sorto1.jenisobat);
				temphargaobat = sorto1.hargaobat;
				tempjumlahobat = sorto1.jumlahobat;

				writedataob(ob, i, sorto2);

				strcpy(temp.kodeobat, tempkodeobat);
				strcpy(temp.namaobat, tempnamaobat);
				strcpy(temp.jenisobat, tempjenisobat);
				temp.hargaobat = temphargaobat;
				temp.jumlahobat = tempjumlahobat;

				writedataob(ob, i + 1, temp);
				swap = true;
			}
		}
	}while(swap == true);	
}

int searchdata(string cari, string dicari){ 
	size_t found = cari.find(dicari);
	int tanda = 0;
  	if(found != string::npos){
    	tanda = 1;
  	}
  	return tanda;
}

void searchob(fstream &ob){
	dataobat searcho;
	string temp;
	finded = -1;
	for(i = 0; i < size; i++){
		searcho = readdataob(ob, i);
		strlwr(searcho.namaobat);
		temp = searcho.namaobat;
		strlwr(searchthem);
		if(searchdata(temp, searchthem) == 1){
			finded++;
		}
	}
}

void cetakdatao(fstream &ob, int posisi){
	sortdata(ob);
	dataobat outputo;	
	if(posisi == -1){
	cout << "\n                           +============================================================================================================+";
	cout << "\n                           |                                                                                                            |";
	cout << "\n                           |   +====================================================================================================+   |";
	cout << "\n                           |   ||  Kode Obat  ||     Nama Obat     ||     Jenis Obat     ||     Harga Obat     ||    Jumlah Obat   ||   |";
	cout << "\n                           |   +====================================================================================================+   |";
		if(size != 0){
			for(i = 0; i < size; i++){
				outputo = readdataob(ob, i);
				cout << "\n                           |   || " << setiosflags(ios::left) << setw(12) << outputo.kodeobat << "||  " << setw(17) << outputo.namaobat << "||  " << setw(18) << outputo.jenisobat << "||  " << resetiosflags(ios::left) << setw(16) << outputo.hargaobat << "  ||" << setw(16) << outputo.jumlahobat << "  ||   |";		
			}
		}else{
			cout << "\n                           |   ||                                        Data masih kosong                                         ||   |";
		}	
		cout << "\n                           |   +====================================================================================================+   |";
		cout << "\n                           |                                                                                                            |";
		cout << "\n                           +============================================================================================================+";
	}else{
		i = posisi;
		outputo = readdataob(ob, posisi);
		cout << "\n                           |   || " << setiosflags(ios::left) << setw(12) << outputo.kodeobat << "||  " << setw(17) << outputo.namaobat << "||  " << setw(18) << outputo.jenisobat << "||  " << resetiosflags(ios::left) << setw(16) << outputo.hargaobat << "  ||" << setw(16) << outputo.jumlahobat << "  ||   |";
	}
}

void searchdataob(fstream &ob){
	dataobat searcho;
	string temp;
	if(finded != -1){
		for(i = 0; i < size; i++){
			searcho = readdataob(ob, i);
			strlwr(searcho.namaobat);
			temp = searcho.namaobat;
			strlwr(searchthem);
			if(searchdata(temp, searchthem) == 1){				
				cetakdatao(ob, i);
				finded++;
			}
		}
	}
}

void hapusdata(fstream &ob, int posisi){
	int tanda;
	dataobat deleteob;
	for(i = 0; i < size; i++){
		deleteob = readdataob(ob, i);
		entry = new tempobat;
		strcpy(entry->kodeobat, deleteob.kodeobat);
		strcpy(entry->namaobat, deleteob.namaobat);
		strcpy(entry->jenisobat, deleteob.jenisobat);
		entry->hargaobat = deleteob.hargaobat;
		entry->jumlahobat = deleteob.jumlahobat;
		entry->next = NULL;
		if((head == NULL) || (head == 0)){
			head = tail = entry;
		}else{
			tail->next = entry;
			tail = tail->next;
		}
	}

	ob.close();
	ob.open("dataobat.bin", ios::trunc | ios::out | ios::in | ios::binary);
	curr = head;
	for(i = 0; i < size; i++){
		if(posisi != i){
			strcpy(deleteob.kodeobat, curr->kodeobat);
			strcpy(deleteob.namaobat, curr->namaobat);
			strcpy(deleteob.jenisobat, curr->jenisobat);			
			deleteob.hargaobat = curr->hargaobat;
			deleteob.jumlahobat = curr->jumlahobat;
			writedataob(ob, tanda, deleteob);
			tanda++;
		}
		curr = curr->next;
	}

	head = 0;
	head = NULL;
	tail = head;
}

void judul(){
	gotoxy(65, 13);cout << "+=============================================+\n";
	gotoxy(65, 14);cout << "|           PROGRAM APOTEK DOPAMINE           |\n";
	gotoxy(65, 15);cout << "|     Disusun untuk Memenunuhi Tugas Akhir    |\n";
	gotoxy(65, 16);cout << "|   Mata Kuliah Algoritma dan Struktur Data   |\n";
	gotoxy(65, 17);cout << "+=============================================+\n";
	gotoxy(65, 18);cout << "|                 KELOMPOK 3                  |\n";
	gotoxy(65, 19);cout << "|       S1 PENDIDIKAN TEKNIK INFORMATIKA      |\n";
	gotoxy(65, 20);cout << "+=============================================+\n";
	getch();
	system("cls");
}

void admin(){
	menu_admin:
	system("cls");
	gotoxy(65, 13);cout<<"Menu Admin : "<<endl;
	gotoxy(65, 14);cout<<"1. Masukkan Data Obat"<<endl;
	gotoxy(65, 15);cout<<"2. Tampilkan Daftar Obat "<<endl;
	gotoxy(65, 16);cout<<"3. Tambah Jumlah Obat "<<endl;
	gotoxy(65, 17);cout<<"4. Hapus Data Obat "<<endl;
	gotoxy(65, 18);cout<<"5. Menu Antrian "<<endl;
	gotoxy(65, 19);cout<<"6. Kembali ke Menu Sebelumnya"<<endl;
	gotoxy(65, 20);cout<<"7. Keluar"<<endl;
	gotoxy(65, 21);cout<<"Pilihan Anda (1/2/3/4/5/6/7): ";
	gotoxy(95, 21);cin>>pilihan;
	switch(pilihan){
		case '1':
			system("cls");
			tambahdata(ob);
		goto menu_admin;
		break;
		case '2':
			system("cls");
			ukuran = sizeof(dataobat);
			size = getdatasize(ob, &ukuran);
			cetakdatao(ob, -1);
			getch();
		goto menu_admin;
		break;
		case '3':
			system("cls");
			ukuran = sizeof(dataobat);
			size = getdatasize(ob, &ukuran);
			cetakdatao(ob, -1);
			int tobat, tanda;
			dataobat tambah;
			tanda = 0;
			cout << "\n                           Masukan Kode Obat: "; cin >> kodeobat;
			cout << "                           Tambah Jumlah Obat: "; cin >> tobat;
				for(i = 0; i < size; i++){
					tambah = readdataob(ob, i);
					if(strcmp(kodeobat, tambah.kodeobat)==0){
						tambah.jumlahobat += tobat;
						writedataob(ob, i, tambah);	
						tanda = 1;
					}
				}
				if(tanda == 1){
					system("cls");
					ukuran = sizeof(dataobat);
					size = getdatasize(ob, &ukuran);
					cetakdatao(ob, -1);
					cout << "\n                           Berhasil Ditambahkan";
					getch();
				}else if(tanda == 0){
					system("cls");
					ukuran = sizeof(dataobat);
					size = getdatasize(ob, &ukuran);
					cetakdatao(ob, -1);
					cout << "\n                           Kode tidak ada";
					getch();
				}
				goto menu_admin;
		break;
		case '4':
			system("cls");
			ukuran = sizeof(dataobat);
			size = getdatasize(ob, &ukuran);
			cetakdatao(ob, -1);
			dataobat cari;
			tanda = 0;
			cout << "\n                           Masukan kode obat: "; cin >> kodeobat;
			for (i = 0; i < size; i++){
				cari = readdataob(ob, i);
				if(strcmp(kodeobat, cari.kodeobat)==0){
					hapusdata(ob, i);
					tanda = 1;
				}	
			}
			if(tanda == 1){
					system("cls");
					ukuran = sizeof(dataobat);
					size = getdatasize(ob, &ukuran);
					cetakdatao(ob, -1);
					cout << "\n                           Berhasil Terhapus";
					getch();
				}else if(tanda == 0){
					system("cls");
					ukuran = sizeof(dataobat);
					size = getdatasize(ob, &ukuran);
					cetakdatao(ob, -1);
					cout << "\n                           Kode tidak ada";
					getch();
				}
			goto menu_admin;
		break;
		case '5':
			menu_antrian:
			system("cls");
			gotoxy(65, 13);cout << "Menu Antrian : "<<endl;
			gotoxy(65, 14);cout << "1. Ambil No. Antrian"<<endl;
			gotoxy(65, 15);cout << "2. Panggil Antrian Selanjutnya"<<endl;
			gotoxy(65, 16);cout << "3. Bersihkan Antrian"<<endl;
			gotoxy(65, 17);cout << "4. Kembali ke Menu Sebelumnya"<<endl;
			gotoxy(65, 18);cout << "Pilih : ";
			gotoxy(72, 18);cin >> pilih;
			switch(pilih){
				case'1':
					insertantri(++noantri, 19);
					goto menu_antrian;
				break;
				case'2':
					hapus();
					goto menu_antrian;
				break;
				case'3':
					clear();
					goto menu_antrian;
				break;
				case'4':
				goto menu_admin;
				break;
				default:
				gotoxy(65, 19);cout << "Kode yang anda inputkan salah";
				getch();
				goto menu_antrian;
				break;
			}
		break;
		case '6':
			system("cls");
			siapa();
		break;
		case '7':
			keluar();
		break;
		default:
			gotoxy(65, 22);cout << "Kode yang anda inputkan salah";
			getch();
			goto menu_admin;
		break;
	}
}

void pelanggan(){
	int total, subtotal, jml, tunai;
	menu_pelanggan:
	system("cls");
	gotoxy(65, 13);cout<<"Pilih Menu : "<<endl;
	gotoxy(65, 14);cout<<"1. Beli Obat "<<endl;
	gotoxy(65, 15);cout<<"2. Tampilkan Daftar Obat "<<endl;
	gotoxy(65, 16);cout<<"3. Cari "<<endl;
	gotoxy(65, 17);cout<<"4. Ambil No. Antrian"<<endl;
	gotoxy(65, 18);cout<<"5. Kembali ke Menu Sebelumnya "<<endl;
	gotoxy(65, 19);cout<<"6. Selesai"<<endl;
	gotoxy(65, 20);cout<<"Pilihan Anda (1/2/3/4/5/6): ";
	gotoxy(92, 20);cin>>pilihan;
		switch(pilihan){
		case '1':
			so.open("struk.txt", ios::trunc | ios::out | ios::in);
			system("cls");
			int tanda, kembali, totaljml;
			subtotal = 0;
			total = 0;
			totaljml = 0;
			char nama[50];
			ukuran = sizeof(dataobat);
			size = getdatasize(ob, &ukuran);
			cetakdatao(ob, -1);
			dataobat cari;
			cout << "\n                           Masukkan atas nama : "; gets(nama); gets(nama);
			so << "+=========================================================+" << endl;
			so << "|                     APOTEK DOPAMINE                     |" << endl;
			so << "|              Jl. Lurus Menuju Surga, Malang             |" << endl;
			so << "|                      (0341)-696969                      |" << endl;
			so << "+=========================================================+" << endl;			
			so << "| Atas Nama : " << setiosflags(ios::left) << setw(44) << nama << "|" << endl << resetiosflags(ios::left);
			so << "+=========================================================+" << endl;
			so << "| Nama Obat          |Jumlah|  Harga  |    Total Harga    |" << endl;
			belilagi:
			tanda = 0;
			cout << "                           Masukkan Kode Obat : "; cin >> kodeobat;
			for (i = 0; i < size; i++){
				cari = readdataob(ob, i);
				if(strcmp(kodeobat, cari.kodeobat)==0){
					cout << "                           Masukkan jumlah obat yang ingin dibeli : "; cin >> jml;
					subtotal = cari.hargaobat * jml;
					total += subtotal;
					cari.jumlahobat -= jml;
					totaljml += jml;
 					writedataob(ob, i, cari);
					tanda = 1;
					so << "| " << setiosflags(ios::left) << setw(19) << cari.namaobat << "|" << resetiosflags(ios::left) << setw(6) << jml << "|" << setw(9) << cari.hargaobat << "|" << setw(19) << subtotal << "|" << endl;
				}	
			}
			if(tanda == 1){
					system("cls");
					ukuran = sizeof(dataobat);
					size = getdatasize(ob, &ukuran);
					cetakdatao(ob, -1);
					cout << "\n                           Total Harga : Rp. " << total;
					cout << "\n                           Beli lagi?(Y/N)";cin >> pilih;
					if (pilih == 'y' && 'Y'){
						goto belilagi;
					}else if(pilih == 'n' && 'N'){
						cout << "\n                           Jumlah Obat      : " << totaljml;
						cout << "\n                           Total Harga      : " << total;
						cout << "\n                           Tunai            : "; cin >> tunai;
						cout << "\n                           Cetak (Y/N)?     : "; cin >> pilih;
						if (pilih == 'y' && 'Y'){
							if(tunai-total < 0){
								cout << "\n                           Uang anda tidak mencukupi!";
								getch();
								goto menu_pelanggan;
							}else
							so << "+=========================================================+" << endl;
							so << "|                              Total : " << setw(19) << total << "|" << endl;
							so << "|                              Tunai : " << setw(19) << tunai << "|" << endl;
							so << "|                            Kembali : " << setw(19) << tunai - total << "|" << endl;
							so << "+=========================================================+" << endl;
							system("cls");
							gotoxy(52, 5);cout << "+=========================================================+";
							gotoxy(52, 6);cout << "|                     APOTEK DOPAMINE                     |";
							gotoxy(52, 7);cout << "|              Jl. Lurus Menuju Surga, Malang             |";
							gotoxy(52, 8);cout << "|                      (0341)-696969                      |";
							gotoxy(52, 9);cout << "+=========================================================+";
							gotoxy(52, 10);cout << "| Atas Nama : " << setiosflags(ios::left) << setw(44) << nama << "|";
							gotoxy(52, 11);cout << "+=========================================================+";
							gotoxy(52, 12);cout << "| Nama Obat          |Jumlah|  Harga  |    Total Harga    |";
							gotoxy(52, 13);cout << "| " << setiosflags(ios::left) << setw(19) << cari.namaobat << "|" << resetiosflags(ios::left) << setw(6) << jml << "|" << setw(9) << cari.hargaobat << "|" << setw(19) << subtotal << "|" << endl;
							gotoxy(52, 14);cout << "+=========================================================+";
							gotoxy(52, 15);cout << "|                              Total : " << setw(19) << total << "|";
							gotoxy(52, 16);cout << "|                              Tunai : " << setw(19) << tunai << "|";
							gotoxy(52, 17);cout << "|                            Kembali : " << setw(19) << tunai - total << "|";
							gotoxy(52, 18);cout << "+=========================================================+"; 
						}else if(pilih == 'n' && 'N'){
							goto menu_pelanggan;
						}else{
							cout << "                           Error";
						}
					}else{
						cout << "                           Error";
					}
					getch();
				}else if(tanda == 0){
					system("cls");
					ukuran = sizeof(dataobat);
					size = getdatasize(ob, &ukuran);
					cetakdatao(ob, -1);
					cout << "\n                           Kode tidak ada";
					getch();
				}
			goto menu_pelanggan;
		break;
		case '2':
			system("cls");
			ukuran = sizeof(dataobat);
			size = getdatasize(ob, &ukuran);
			cetakdatao(ob, -1);
			getch();
			goto menu_pelanggan;
		break;
		case '3':
			system("cls");
			ukuran = sizeof(dataobat);
			size = getdatasize(ob, &ukuran);
			cetakdatao(ob, -1);
			cout << "\n                           Ketik Nama Obat: "; cin >> searchthem;
			searchob(ob);
			if (finded != -1){
				cout << "\n                           |   +====================================================================================================+   |";
				searchdataob(ob);
				cout << "\n                           |   +====================================================================================================+   |";
			}else{
				cout << "                           Nama obat tidak ditemukan";
			}
			getch();
			goto menu_pelanggan;
		break;
		case '4':
			insertantri(++noantri, 21);
			goto menu_pelanggan;
		break;
		case '5':
			system("cls");
			siapa();
		break;
		case '6':
			keluar();
		break;
		default:
			gotoxy(65, 21);cout << "Kode yang anda inputkan salah";
			getch();
			goto menu_pelanggan;
		break;
	}
}

void keluar(){
	system("cls");
	gotoxy(65,13);cout << "Terima Kasih..";
}

void siapa(){
	menu_siapa:
	system("cls");
	gotoxy(65, 13);cout<<"Siapakah anda? : "<<endl;
	gotoxy(65, 14);cout<<"1. Admin"<<endl;
	gotoxy(65, 15);cout<<"2. Pelanggan"<<endl;
	gotoxy(65, 16);cout<<"3. Keluar"<<endl;
	gotoxy(65, 17);cout<<"Pilihan Anda (1/2/3) : ";
	gotoxy(87, 17);cin>>pilihan;
	switch(pilihan){
		case '1':
			menulogin();
			admin();
			getch();
			break;
		case '2':
			pelanggan();
			break;
		case '3':
			keluar();
			break;
		default:
			gotoxy(65, 18);cout << "Kode yang anda inputkan salah";
			getch();
			goto menu_siapa;
			break;
	}
}	

void insertantri(int no, int pcc){
	entrya = new nodeantri;
	entrya->no = no;
	entrya->nexta = NULL;
	if(heada == NULL){
		heada = entrya;
		taila = heada;
	}else{
		taila->nexta = entrya;
		taila = taila->nexta;
	}
	gotoxy (65, pcc); cout << "Antrian Anda: " << setw(2) << no;
	getch();
}

void init(){
	heada = taila = NULL;
}

void show(){
	if(heada == NULL){
		gotoxy(65, 19); cout << "Antrian Sekarang : Kosong ";
	}else{
		gotoxy(65, 19); cout << "Antrian Sekarang : ";
		gotoxy(91, 19); cout << setw(2) << heada->no;
	}
	getch();	
}

void hapus(){
	if(heada == NULL){
		gotoxy(65, 19); cout << "Antrian Sekarang : Kosong ";
	}else{
		gotoxy(65, 19); cout << "Antrian Sekarang : ";
		gotoxy(91, 19); cout << setw(2) << heada->no;		
		dela = heada;
		heada = heada->nexta;
		delete dela;
	}
	getch();
}

void clear(){
	curra = heada;
	while(curra != NULL){
		dela = curra;
		curra = curra->nexta;
		delete dela;
	}
	init();
	noantri = 0;
}