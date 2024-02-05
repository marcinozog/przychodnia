#include "przychodnia.h"

/*
~Przychodnia()
*/
Przychodnia::~Przychodnia() {
    if(cDB) {
        cDB->disconnect();
        delete cDB;
    }
}

/*
init()
*/
int Przychodnia::init() {
    cDB = new ConnectorDB("przychodnia.db", "user", "pass");

    if(cDB->connect())
        return -1;

    return 0;
}

/*
wyswietl_response(Response *response)
wysyła i wyświetla wynik zapytania
*/
void Przychodnia::wyswietl_response(string sql) {
    Response *response = new Response();

    if(cDB->send_recvQuery(sql, response) > 0) {
        int col_num = response->getColNum();
        int row_num = response->getRowNum();
        string separator = "\n";
        int i;

        for(i = 0; i < col_num; i++) {
            separator += "----------------------";
        }
        separator += "\n";
        for(i = 0; i < col_num; i++) {
            cout << "|\t" <<response->getHeader()[i] << "\t";
        }
        
        cout << separator;


        for(i = 0; i < row_num; i++) {
            for(int j = 0; j < col_num; j++) {
                cout << "|\t" <<response->getResponse()[i][j] << "\t";
            }
            cout << endl;
        }
        cout << separator;
        cout << "[Rows: " << row_num << "]\n\n";
    }

    delete response;
}

/*
wyswietl_lekarzy()
*/
void Przychodnia::wyswietl_lekarzy(){
    string sql = "SELECT * FROM Lekarz;";
    wyswietl_response(sql);
}

void Przychodnia::dodaj_lekarza() {
    int pesel;
    string imie, nazwisko, nrtelefonu;
    int ret = 0;

    cout << "DODAWANIE LEKARZA\n";
    cout << "Podaj pesel: ";
    cin >> pesel;
    cout << "Podaj imie: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cout << "Podaj numer telefonu: ";
    cin >> nrtelefonu;

    string sql = "insert into Lekarz(PESEL, Imie, Nazwisko, NrTelefonu) values(";
                sql += to_string(pesel);
                sql += ",'";
                sql += imie;
                sql += "', '";
                sql += nazwisko;
                sql += "', '";
                sql += nrtelefonu;
                sql += "');";
    ret = cDB->sendQuery(sql);

    // -1 błąd w sendQuery
    if(ret >= 0)
        cout << "Dodano: " << ret << " pozycji.";
}

/*
usun_lekarza()
*/
void Przychodnia::usun_lekarza(){
    string pesel;
    int ret = 0;
    cout << "USUWANIE LEKARZA\n";
    cout << "Podaj pesel: ";
    cin >> pesel;
    string sql = "delete from Lekarz where PESEL=";
            sql += pesel;
            sql += ";";
    ret = cDB->sendQuery(sql);

    cout << "Usunięto: " << ret << " pozycji.";
}

/*
wyswietl_pacjentow()
*/
void Przychodnia::wyswietl_pacjentow(){
    string sql = "SELECT * FROM Pacjent;";
    wyswietl_response(sql);
}

/*
dodaj_pacjenta()
*/
void Przychodnia::dodaj_pacjenta(){
    string pesel, imie, nazwisko, miejscowosc;
    string kodpocztowy, ulicanumer, nrtelefonu, email;
    int ret;

    cout << "DODAWANIE PACJENTA" << endl;
    cout << "Podaj pesel: ";
    getline(cin, pesel);
    cout << "Podaj imie: ";
    getline(cin, imie);
    cout << "Podaj nazwisko: ";
    getline(cin, nazwisko);
    cout << "Podaj miejscowość: ";
    getline(cin, miejscowosc);
    cout << "Podaj kod pocztowy: ";
    getline(cin, kodpocztowy);
    cout << "Podaj ulicę i numer: ";
    getline(cin, ulicanumer);
    cout << "Podaj email: ";
    getline(cin, email);
    cout << "Podaj numer telefonu: ";
    getline(cin, nrtelefonu);

    string sql = "insert into Pacjent(PESEL, Imie, Nazwisko, Miejscowosc, KodPocztowy, UlicaNumer, NrTelefonu, Email) values(";
                sql += pesel;
                sql += ",'";
                sql += imie;
                sql += "', '";
                sql += nazwisko;
                sql += "', '";
                sql += miejscowosc;
                sql += "', '";
                sql += kodpocztowy;
                sql += "', '";
                sql += ulicanumer;
                sql += "', '";
                sql += email;
                sql += "', '";
                sql += nrtelefonu;
                sql += "');";

    ret = cDB->sendQuery(sql);

    // -1 błąd w sendQuery
    if(ret >= 0)
        cout << "Dodano: " << ret << " pozycji.";
}

/*
usun_pacjenta()
*/
void Przychodnia::usun_pacjenta(){
    string pesel;
    int ret = 0;
    cout << "USUWANIE PACJENTA\n";
    cout << "Podaj pesel: ";
    cin >> pesel;
    string sql = "delete from Pacjent where PESEL=";
            sql += pesel;
            sql += ";";
    
    ret = cDB->sendQuery(sql);

    cout << "Usunięto: " << ret << " pozycji.";
}

/*
wyswietl_wizyty(bool wszystkie)
*/
void Przychodnia::wyswietl_wizyty(bool wszystkie){
    string sql;
    string od_daty;
    if(wszystkie)
        od_daty = "w";
    else {
        cout << "WYSWIETLANIE WIZYT\n";
        cout << "Podaj datę od (np. '2022-01-01' lub 'w' -> wszystkie): ";
        cin >> od_daty;
    }

    if(od_daty == "w")
        sql = "select Imie, Nazwisko, DataWizyty, Wizyta.Status "
            "from Pacjent join Wizyta "
            "on Pacjent.PESEL = Wizyta.PacjentPESEL;";
    else if((od_daty.length() >= 10) && (od_daty.length() <=11)) {
        sql += "select Imie, Nazwisko, DataWizyty,  Wizyta.Status "
            "from Pacjent join Wizyta "
            "on Pacjent.PESEL = Wizyta.PacjentPESEL "
            "where DataWizyty >= '";
        sql += od_daty;
        sql += "';";
    }
    else {
        cout << "Blędny format!!!" << endl;
        return;
    }
    wyswietl_response(sql);
}

/*
dodaj_wizyte()
*/
void Przychodnia::dodaj_wizyte(){

}

/*
usun_wizyte()
*/
void Przychodnia::usun_wizyte(){

}

/*
wyswietl_poradnie()
*/
void Przychodnia::wyswietl_poradnie(){
    string sql = "SELECT * FROM Poradnia;";
    wyswietl_response(sql);
}

/*
wyswietl_leki()
*/
void Przychodnia::wyswietl_leki(){
    string sql = "SELECT * FROM Leki;";
    wyswietl_response(sql);
}
