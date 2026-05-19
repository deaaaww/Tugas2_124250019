#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Karyawan {
    int nip;
    string nama;
    string divisi;
    bool sedangCuti;
    Karyawan* anak_kiri;
    Karyawan* anak_kanan;
  
    Karyawan(int Newnip, string Newnama, string Newdivisi) {
        nip = Newnip;
        nama = Newnama;
        divisi = Newdivisi;
        sedangCuti = false;
        anak_kiri = NULL;
        anak_kanan = NULL;
        cout << "Data karyawan berhasil ditambahkan!\n";
    }
};

bool adaYangCuti(Karyawan* root);

struct queue {
    int nip;
    string nama;
    queue* next;
};

queue* depan = NULL;
queue* belakang = NULL;

int queuekosong() {
	return (depan == NULL);
}

void enqueue(int nip, string nama) {
    queue* baru = new queue();
    baru->nip = nip;
    baru->nama = nama;
    baru->next = NULL;
    if (depan == NULL) {
        depan = belakang = baru;
    } else {
        belakang->next = baru;
        belakang = baru;
    }
}

void dequeue() {
    if (queuekosong ()) {
		return;
	} 
	queue *hapus = depan;
	depan = depan->next;
	if (depan == NULL) {
        belakang = NULL;
    }
    delete hapus;
}

void tampilAntrian() {
	queue *bantu = depan;
    if (bantu == NULL) {
        cout << "Antrian kosong\n";
        return;
    }
    cout << "ANTRIAN CUTI\n";
    while (bantu != NULL) {
        cout << bantu->nama << " menunggu giliran cuti\n";
        bantu = bantu->next;
    }
}

struct stack {
    string jenis;
    int nip;
    string nama;
    stack* next;
};

stack *awal= NULL, *top=NULL;

bool stackkosong() {
	return awal == NULL;
}

void buatstack() {
	awal = top = NULL;
}

void pushUndo(string jenis, int nip, string nama) {
    stack* baru = new stack();
    baru->jenis = jenis;
    baru->nip = nip;
    baru->nama = nama;
    baru->next = NULL;
    
    if (stackkosong() ) {
		awal = top = baru;
	} else {
		baru->next = awal;
		awal = baru;
		top = baru;
	}
}

void popUndo() {
    if (stackkosong() ) {
		return;
	} else {
		stack *hapus = awal;
		awal = awal->next;
		delete hapus;
	}
}

bool adaYangCuti(Karyawan* root) {
    if (root == NULL) return false;
    if (root->sedangCuti) return true;
    return adaYangCuti(root->anak_kiri) || adaYangCuti(root->anak_kanan);
}

Karyawan* root = NULL;

void insert(Karyawan* &root, int nip_baru, string nama_baru, string divisi_baru) {
    if (root == NULL) {
        root = new Karyawan(nip_baru, nama_baru, divisi_baru);
        return;
    }
    
    if (nip_baru < root->nip) {
        insert(root->anak_kiri, nip_baru, nama_baru, divisi_baru);
    } 
    else if (nip_baru > root->nip) {
        insert(root->anak_kanan, nip_baru, nama_baru, divisi_baru);
    } 
    else {
        cout << "NIP sudah ada! Input gagal.\n";
    }
}

Karyawan* search(Karyawan* root, int nip_cari) {
	Karyawan *curr = root;
	while (curr) {
		if (curr->nip == nip_cari) {
			return curr;
		}
		curr = (nip_cari < curr->nip) ?
		curr->anak_kiri:
		curr->anak_kanan;
    }
    return nullptr;
}

void tampilInorder(Karyawan* root) {

    if (root == NULL) {
        return;
    }

    tampilInorder(root->anak_kiri);

    cout << setfill(' ') << left;
    cout << "| " << setw(12)  << root->nip
         << "| " << setw(18) << root->nama
         << "| " << setw(15) << root->divisi
         << "| " << setw(15)
         << (root->sedangCuti ? "Cuti" : "Tidak Cuti")
         << "|" << endl;

    tampilInorder(root->anak_kanan);
}

void deletekaryawan(Karyawan* &root, int nip_hapus) {
    if (root == nullptr) {
        cout << "Karyawan tidak ditemukan!\n";
        return;
    }
    if (nip_hapus < root->nip) {
        deletekaryawan(root->anak_kiri, nip_hapus);
    } else if (nip_hapus > root->nip) {
        deletekaryawan(root->anak_kanan, nip_hapus);
    } else {
		if (root->anak_kiri == NULL && root->anak_kanan == NULL) {
            delete root;
            root = NULL;
		} else if (root->anak_kiri == NULL) {
			Karyawan* temp = root;
			root = root->anak_kanan;
			delete temp;
		} else if (root->anak_kanan == NULL) {
			Karyawan* temp = root;
			root = root->anak_kiri;
			delete temp;
		} else {
			Karyawan* succ = root->anak_kanan;
            while (succ->anak_kiri != nullptr) {
				succ = succ->anak_kiri;
			}
			root->nip = succ->nip;
			root->nama = succ->nama;
			root->divisi = succ->divisi;
			root->sedangCuti = succ->sedangCuti;
			deletekaryawan(root->anak_kanan, succ->nip);
		}
	} cout << "Data karyawan berhasil dihapus\n";
} 

void pause() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.get();
    system ("cls");
}


int main() {
    int pilihan;
    do {
        cout << setfill('=') << setw(40) << "" << endl;

		cout << setfill(' ')
			 << "|" << right << setw(25) << "PT. SYUDUDU" << setw(14) << "|" << endl;

		cout << setfill('=') << setw(40) << "" << endl;

		cout << setfill(' ');
		cout  << "| 1.|"
			 << left << setw(34) << " Input Data Karyawan" 
			 << setw(10) << "|" << endl;
		cout  << "| 2.|"
			 << left << setw(34) << " Lihat Data Karyawan" 
			 << setw(10) << "|" << endl;
		cout  << "| 3.|"
			 << left << setw(34) << " Pengajuan Cuti Data Karyawan" 
			 << setw(10) << "|" << endl;
		cout  << "| 4.|"
			 << left << setw(34) << " Selesai Cuti Karyawan" 
			 << setw(10) << "|" << endl;
		cout  << "| 5.|"
			 << left << setw(34) << " Hapus Data Karyawan" 
			 << setw(10) << "|" << endl;
		cout  << "| 6.|"
			 << left << setw(34) << " Undo status cuti" 
			 << setw(10) << "|" << endl;
	    cout  << "| 7.|"
			 << left << setw(34) << " Tampil Antrian Cuti" 
			 << setw(10) << "|" << endl;
		cout  << "| 8.|"
			 << left << setw(34) << " Keluar" 
			 << setw(10) << "|" << endl;
			 
		cout << setfill('-') << setw(40) << "" << endl;
		cout << setfill(' ');
			
		cout << "\nPilih Menu : ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            int nip; string nama, divisi;
            cout << "\nInput NIP : "; cin >> nip; cin.ignore();
            cout << "Input Nama : "; getline(cin, nama);
            cout << "Input Divisi : "; getline(cin, divisi);
            insert(root, nip, nama, divisi);
        }
        else if (pilihan == 2) {
            cout << "\n";
			cout << setfill('=') << setw(69) << "" << endl;

			cout << setfill(' ');
			cout << "|" << right << setw(41) << "DAFTAR KARYAWAN" <<setw(27) <<"|"<< endl;

			cout << setfill('=') << setw(69) << "" << endl;

			cout << setfill(' ') << left;

			cout << "| " << setw(12)  << "NIP"
				 << "| " << setw(18) << "Nama"
				 << "| " << setw(15) << "Divisi"
				 << "| " << setw(15) << "Status"
				 << "|" << endl;

			cout << setfill('=') << setw(69) << "" << endl;
			tampilInorder(root);
			cout << setfill('=') << setw(69) << "" << endl;
		} else if (pilihan == 3) {
            int nip;
            cout << "Masukkan NIP : "; cin >> nip; cin.ignore();
            Karyawan* kary = search(root, nip);
            if (kary == NULL) {
                cout << "Karyawan tidak ditemukan!\n";
            } 
            else if (adaYangCuti(root)) {  
                cout << "Karyawan sedang cuti, pengajuan masuk ke antrian\n";
                enqueue(nip, kary->nama);
                pushUndo("pengajuan_antrian", nip, kary->nama);
            } 
            else {
                kary->sedangCuti = true;
                cout << "Pengajuan cuti berhasil\n";
                pushUndo("pengajuan", nip, kary->nama);
            }
        
        } else if (pilihan == 4) {
            int nip;
            cout << "Masukkan NIP : "; cin >> nip; cin.ignore();
            Karyawan* kary = search(root, nip);
            if (kary == NULL) {
                cout << "Karyawan tidak ditemukan!\n";
            } else if (!kary->sedangCuti) {
                cout << "Karyawan tidak sedang cuti!\n";
            } else {
                kary->sedangCuti = false;
                cout << "Cuti berhasil diselesaikan\n";
                pushUndo ("selesai", nip, kary->nama);
                
                if (depan != NULL) {
                    int nextNip = depan->nip;
                    dequeue();
                    Karyawan* nextkary = search(root, nextNip);
                    if (nextkary) {
                        nextkary->sedangCuti = true;
                        cout << "Pengajuan cuti berikutnya langsung diproses dari antrian\n";
                    }
                }
            }
        }
        else if (pilihan == 5) {
            int nip;
            cout << "Masukkan NIP yang dihapus : "; cin >> nip; cin.ignore();
            deletekaryawan(root, nip);
        }
        else if (pilihan == 6) {
            if (stackkosong() ) {
                cout << "Tidak ada aksi untuk di-undo\n";
            } else {
                string jenis = awal->jenis;
                int nip = awal->nip;
                popUndo();
                
                Karyawan* kary = search(root, nip);
                if (kary) {
                    if (jenis == "pengajuan") {
                        kary->sedangCuti = false;
                        cout << "Undo: Status cuti karyawan dibatalkan\n";
                    } else if (jenis == "selesai") {
                        kary->sedangCuti = true;
                        cout << "Undo: Status cuti karyawan dikembalikan menjadi cuti\n";
                    } else if (jenis == "pengajuan_antrian") {
						if (depan != NULL) {
							queue* hapus = depan;
							depan = depan->next;
							if (depan == NULL) {
								belakang = NULL;
							}
							delete hapus;
						}
						cout << "Undo: Pengajuan antrian dibatalkan\n";
					}
                }
            }
        }
        else if (pilihan == 7) {
            tampilAntrian();
        }
        else if (pilihan == 8) {
            cout << "Program selesai. Terima kasih!\n";
            break;
        } else {
            cout << "Menu tidak tersedia!\n";
        }
        if(pilihan != 8) pause();
        
    } while (pilihan != 8);

    return 0;
}
