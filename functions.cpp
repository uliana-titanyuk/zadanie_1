#include "Header.h"
#include "Class.h"
using namespace std;

void prepr(ifstream* filename, List *lst, string name) {
    int num_of_str = 1;
    ofstream fout;
    string str;
    while (1) {
        getline(*filename, str, '\n');
        sprtr(&str, num_of_str, lst, name);
        num_of_str++;
        if ((*filename).eof()) break;
    }

    fout.close();
}

void sprtr(string* str, int num, List *lst, string name) {    //ïðèíèìàåì â îáðàáîòêó ñòðîêó


    stringstream str_stream;     //ïðåâðàùàåì ñòðîêó â ïîòîê, ÷òîáû èìåòü âîçìîæíîñòü ïîëüçîâàòüñÿ getline
    str_stream << *str;
    string str1, tmpstr_name, tmpstr_value;
    bool ok_1 = 0; //åñëè çíà÷åíèå 1, òî èìÿ ïàðàìåòðà â ñòðîêå íàéäåíî
    bool ok_2 = 0; // çíàê "=" íàéäåí
    bool ok_3 = 0; // çíà÷åíèå ïàðàìåòðà íàéäåíî

    while (!str_stream.eof()) {
        getline(str_stream, str1, ' ');
        if (str1 == "") {
            continue;
        }
        if (str1[0] == '#') {
            if (ok_1 == 1 && ok_2 == 1 && ok_3 == 0) {
                cout << "V stroke " << num << " config- fayla " << name << " net znacheniya\n";
            }
            if (ok_1 == 0 || ok_2 == 0 || ok_3 == 0) {
                break;
            }
            continue;
        }
        if (str1[0] == '=') {
            if (ok_1 == 0) {
                cout << "V stroke " << num << " config- fayla " << name << " net imeni parametra\n" << endl;
            }
            if (ok_1 == 1) {
                ok_2 = 1;
            }
        }
        if (str1[0] != '=') {
            if (ok_1 == 0) {
                tmpstr_name = str1;
                ok_1 = 1;
                continue;
            }
            if (ok_1 == 1 && ok_2 == 1) {
                tmpstr_value = str1;
                ok_3 = 1;
            }
            if (ok_1 == 1 && ok_2 == 0) {
                cout << "Necorrectnaya stroka " << num << " config- fayla " << name << endl;
                break;
            }
        }
        if (ok_1 == 1 && ok_2 == 1 && ok_3 == 1) {
            (*lst).push_back(tmpstr_name, tmpstr_value);
        }
    }
    obrabotka(lst);
}

void start() {
    List lst;
    open_file(&lst);
    menu(&lst);
}

void mnplt_review(List *lst) {
    cout << "Spisok nastroek" << endl;
   /* for (int i = 0; i < (*lst).GetSize(); i++) {
        cout << (*lst)[i] << " = " << (*lst)[(*lst)[i]] << endl;
    }*/
    (*lst).Print();
}

void open_file(List *lst) {
    string name;
    cout << "Vvedite imya config- fayla" << endl;
    cin >> name;
    ifstream fin(name);
    if (fin) {
        prepr(&fin, lst, name);
    }
    else {
        int a = 0;
        cout << "Fayla s takim imenem net" << endl;
        cout << "1. vvesti imya zanovo" << endl;
        cout << "0. viyty iz programmy" << endl;
        cin >> a;
        if (a == 1) {
            open_file(lst);
        }
        if (a == 0) {
            cout << "Programma zavershena" << endl;
            exit;
        }
        if (a != 1 && a != 0) {
            cout << "Vvedite korrektnoe znachenie" << endl;
            menu(lst);
        }
    }
}

void vyvod_menu() {
    cout << endl;
    cout << "1. poluchit' obrabotaniy spisok nastroek" << endl;
    cout << "2. poluchit' znacheniye zadannogo imeni" << endl;
    cout << "3. ob'edinit' parametry" << endl;
    cout << "4. viyti iz programmy" << endl;
    cout << endl;
}

void menu(List *lst) {
    int a = 0;
    vyvod_menu();
    cin >> a;
    if (a == 1) {
        mnplt_review(lst);
        menu(lst);
    }
    if (a == 2) {
        znach_po_im(lst);
    }
    if (a == 3) {
        open_file(lst);
        menu(lst);
    }
    if (a == 4) {
        cout << "Programma zavershena" << endl;
        exit;
    }
    if (a != 1 && a != 2 && a != 3 && a != 4) {
        cout << "Vvedite korrektnoe znachenie" << endl;
        menu(lst);
    }

}

void obrabotka(List *lst) {
    for (int i = 0; i < (*lst).GetSize(); i++) {
        for (int j = 0; j < (*lst).GetSize(); j++) {
            if ((*lst)[(*lst)[i]].find("$" + (*lst)[j] + "$") != -1) {
                (*lst)[(*lst)[i]].replace((*lst)[(*lst)[i]].find("$" + (*lst)[j] + "$"), ("$" + (*lst)[j] + "$").size(), (*lst)[(*lst)[j]]);
            }
        }
    }
}

void znach_po_im(List *lst) {
    string str;
    bool flag = 0;
    cout << "Vvedite imya parametra" << endl;
    cin >> str;
    for (int i = 0; i < (*lst).GetSize(); i++) {
        if ((*lst)[i] == str) {
            flag = 1;
            cout << (*lst)[i] << " = " << (*lst)[(*lst)[i]] << endl;
            menu(lst);
        }
    }
    if (flag == 0) {
        int a = 0;
        cout << "Net parametra s takim imenem" << endl;
        cout << "1. vvesti imya zanovo" << endl;
        cout << "2. viyti v menu" << endl;
        cout << "0. viyty iz programmy" << endl;
        cin >> a;
        if (a == 1) {
            znach_po_im(lst);
        }
        if (a == 2) {
            menu(lst);
        }
        if (a == 0) {
            cout << "Programma zavershena" << endl;
            exit;
        }
        if (a != 1 && a != 2 && a != 0) {
            cout << "Vvedite korrektnoe znachenie" << endl;
            menu(lst);
        }

    }
}

void function() {
    int a = 0;
    cout << "1. nachat' rabotu" << endl;
    cout << "2. zapustit' avtotest" << endl;
    cout << "0. viyti iz programmy" << endl;
    cin >> a;
    if (a == 1) {
        start();
    }
    if (a == 2) {
        autotest();
        function();
    }
    if (a == 0) {
        cout << "Programma zavershena" << endl;
        system("pause");
        exit;
    }
    if (a != 1 && a != 2 && a != 0) {
        cout << "Vvedite korrektnoe znachenie" << endl;
        function();
        exit;
    }
}

void autotest() {
    List lst;
    open_file(&lst);
    if (lst["par2"] == "212MAWVAKPW" && lst["par4"] == "wrvejrwarc212MAWVAKPWnjndsCNO") {
        cout << "avtotest sdan" << endl;
    }
    else {
        cout << "autotest provalen" << endl;
    }
}
