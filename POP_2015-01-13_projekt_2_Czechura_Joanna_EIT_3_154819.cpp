/*
POP_2015-01-13_projekt_2_Czechura_Joanna_EIT_3_154819. Do utworzenia oraz kompilowania u¿yto Dev-C++ 5.2.0.3
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

const int IL_PIKSELI = 8;
const int WYJSCIE_Z_PROGRAMU = 0;
const int SKALA_SZAROSCI = 1;
const int WYODREBNIENIE_KOLORU = 2;
const int ROZMYCIE_KOLORU = 3;
const int NIEBIESKI = 1;
const int ZIELONY = 2;
const int CZERWONY = 3;
const int BLAD_OTWARCIA = 0;
const int BLAD_ODCZYTU = 1;
const int BLAD_ZAPISU = 2;
const int BLAD_WSKAZNIKA = 3;

#pragma pack(push, 1) // Wyrownanie pol struktury do jednego bajta

struct BITMAPFILEHEADER
{ 
  short bfType; 
  int   bfSize; 
  short bfReserved1; 
  short bfReserved2; 
  int   bfOffBits; 
};
 
struct BITMAPINFOHEADER
{
  int   biSize; 
  int   biWidth; 
  int   biHeight; 
  short biPlanes; 
  short biBitCount; 
  int   biCompression; 
  int   biSizeImage; 
  int   biXPelsPerMeter; 
  int   biYPelsPerMeter; 
  int   biClrUsed; 
  int   biClrImportant; 
};

struct Piksel{
  unsigned char blue;
  unsigned char green;
  unsigned char red;
}kolorPiksela, pikselRozmycia[IL_PIKSELI];

#pragma pack(pop)      // Koniec wyrownywania pol struktury

void opcjeProgramu()
{
    cout << endl << " R O D Z A J E  O P E R A C J I" << endl;
    cout <<         " ------------------------------" << endl;
    cout << "       OPCJE WYBORU:" << endl;
    cout << " [1] - przejscie do skali szarosci" << endl;
    cout << " [2] - wyodrebnienie koloru" << endl;
    cout << " [3] - rozmycie koloru" << endl;
    cout << " [0] - wyjscie z programu" << endl;
 return;
}

void opcjeWyodrebnianiaKoloru()
{
    cout << endl << " K O L O R Y  W Y O D R E B N I E N I A" << endl;
    cout <<         " --------------------------------------" << endl;
    cout << "       OPCJE WYBORU:" << endl;
    cout << " [1] - wyodrebnienie koloru niebieskiego \"blue\"" << endl;
    cout << " [2] - wyodrebnienie koloru zielonego \"green\"" << endl;
    cout << " [3] - wyodrebnienie koloru czerwonego \"red\"" << endl;
    cout << " [0] - powrot do wyboru innej operacji" << endl;
 return;
}

void obslugaBleduOtwarcia(string opisBledu)
{
  cout << endl;
  cout << " -------------------------------------------------" << endl;
  cout << "             KOMUNIKAT O BLEDACH" << endl;
  cout << " Operacja zakonczyla sie niepowodzeniem z powudu:" <<  endl;
  cout << " " << opisBledu <<  endl;
  cout << " -------------------------------------------------" << endl;
  cout << endl;
  system( "pause" );
 return;
}

void obslugaBledu(string opisBledu, ifstream *plikIn, ofstream *plikOut, char *nazwaPlikuOut)
{
  cout << endl;
  cout << " -------------------------------------------------" << endl;
  cout << "             KOMUNIKAT O BLEDACH" << endl;
  cout << " Operacja zakonczyla sie niepowodzeniem z powudu:" <<  endl;
  cout << " " << opisBledu <<  endl;
  cout << " -------------------------------------------------" << endl;
  cout << endl;
  plikIn->close();          // zamkniecie pliku wejsciowego
  plikOut->close();         // zamkniecie pliku wyjsciowego
  system( "pause" );
  remove(nazwaPlikuOut);    // usuniecie pliku wyjsciowego
 return;
}

int main()
{
  // deklaracja funkcji i zmiennych
  void opcjeProgramu();
  void opcjeWyodrebnianiaKoloru();
  void wykonanieOperacji(int rodzajOperacji, int kolorWyodrebnienia);
  void obslugaBleduOtwarcia(string opisBledu);
  void obslugaBledu(string opisBledu, ifstream *plikIn, ofstream *plikOut, char* nazwaPlikuOut);
  int rodzajOperacji;
  int kolorWyodrebnienia;
  
     do  // petla obsluga menu programu
    {
		system( "cls" );   // wyczyszczenie ekranu konsoli
        opcjeProgramu();   // wykonanie funkcji "opcjeProgramu"
        cout << endl;
        cout << " -------------------------------------------------" << endl;
        cout << " Do dzialania programu wymagana jest obecnosc" << endl;
        cout << " w katalogu biezacym programu - pliku wejsciowego." << endl;
        cout << " Program obsluguje wylacznie format \"bmp\"." << endl;
        cout << " W dalszej czesci programu podasz wlasna nazwe pliku" << endl;
        cout << " albo zaakceptujesz domyslna nazwe - \"obraz.bmp\"" << endl;
        cout << " -------------------------------------------------" << endl;
        cout << endl << " Nacisnij [cyfra], a nastepnie \"Enter\")" << endl;
        cout << " Wybierz rodzaj operacji: ";
        cin.clear();              // czyszczenie flagi bledu
        cin.sync();               // czyszczenie bufora strumienia
        cin >> rodzajOperacji;    // wybor rodzaju operacji
        switch( rodzajOperacji )
        {
        case WYODREBNIENIE_KOLORU:
			system( "cls" );
            cout << endl << " Wybrana operacja: " << rodzajOperacji << " - wymaga wyboru koloru wyodrebnienia" << endl;
      	    opcjeWyodrebnianiaKoloru();
            cout << endl << " Nacisnij [cyfra], a nastepnie \"Enter\")" << endl;
            cout << " Wybierz kolor wyodrebnienia: ";
            cin.clear();
            cin.sync();
            cin >> kolorWyodrebnienia;  // wybor koloru wypelnienia
			if(kolorWyodrebnienia != NIEBIESKI && kolorWyodrebnienia != ZIELONY && kolorWyodrebnienia != CZERWONY) {
			   break;
			}
        case SKALA_SZAROSCI:
        case ROZMYCIE_KOLORU:
            wykonanieOperacji(rodzajOperacji, kolorWyodrebnienia);  // wykonanie funkcji "wykonanieOperacji"
            break;
        default:
        	rodzajOperacji = WYJSCIE_Z_PROGRAMU;
            system( "cls" );
            cout << endl << " ----------------------------------------------";
            cout << endl << " Dziekuje i zapraszam ponownie: Joanna Czechura";
            cout << endl << " ----------------------------------------------" << endl;
            cout << endl;
            system( "pause" );
            break;
        }
    } while( rodzajOperacji != WYJSCIE_Z_PROGRAMU);

 return 0;
}

void wykonanieOperacji(int rodzajOperacji, int kolorWyodrebnienia)
{
  // deklaracja zmiennych
  int kolorPiksela_szary, pusteBajty, bajtyPiksela, suma_blue, suma_green, suma_red;
  int i, x, y, przesuniecie, wskaznik;
  char nazwaPlikuIn_char[20];
  string nazwaPlikuIn_str;
  string nazwaPlikuOut_str;
  string opisBledu[4][4] = {
	 {
	 "Blad otwarcia pliku wejsciowego - ", 
	 "Blad otwarcia pliku wyjsciowego - ",
	 },
	 {
	 "Blad odczytu struktury naglowka z pliku wejsciowego - ",
   "Blad odczytu opisu naglowka z pliku wejsciowego - ",
	 "Blad odczytu bajtow piksela z pliku wejsciowego - ",
	 "Blad odczytu pustych bajtow piksela z pliku wejsciowego - ",
	 },
	 {
	 "Blad zapisu struktury naglowka do pliku wyjsciowego - ",
	 "Blad zapisu opisu naglowka do pliku wyjsciowego - ",
	 "Blad zapisu bajtow piksela do pliku wyjsciowego - ",
	 "Blad zapisu pustych bajtow piksela do pliku wyjsciowego - ",
	 },
	 {
	 "Blad pozycjonowania wskaznika czytania pliku wejsciowego - ",
	 },
  };

  cout << endl;
  cout << " -------------------------------------------------" << endl;
  cout << " Mozesz wpisac wlasna nazwe pliku wejsciowego albo" << endl;
  cout << " naciskajac \"Enter\" zaakceptowac nazwe - \"obraz.bmp\"" << endl;
  cout << " -------------------------------------------------" << endl;
  cout << " Podaj nazwe pliku bez rozszerzenia: ";

  cin.clear();
  cin.sync();
  cin.getline(nazwaPlikuIn_char, 20);                           // pobranie z klawiatury nazwy pliku wejsciowego
  nazwaPlikuIn_str = string(nazwaPlikuIn_char);                 // zamiana char na string
  if(nazwaPlikuIn_str == "")                                    // jezeli pobrany tekst jest pusty - wcisnieto tylko "Enter"
    nazwaPlikuIn_str = "obraz";                                 // przypisanie nazwy domyslnej
   else                                                         // jezeli pobrany tekst nie jest pusty
  {
	while(nazwaPlikuIn_str.find(" ") != string::npos)           // przeszukanie tekstu metoda find klasy string na obecnosc spacji
		nazwaPlikuIn_str.erase(nazwaPlikuIn_str.find(" "), 1);	// usuniecie ewentualnych spacji z tekstu
  }
  
  switch( rodzajOperacji )  // okreslenie nazwy pliku wyjsciowego w zaleznosci od rodzaju operacji
  {
  case SKALA_SZAROSCI:
	nazwaPlikuOut_str = nazwaPlikuIn_str + "_szary";
	break;

  case WYODREBNIENIE_KOLORU:
	switch( kolorWyodrebnienia )
	{
	case NIEBIESKI:
		nazwaPlikuOut_str = nazwaPlikuIn_str + "_blue";
		break;
	case ZIELONY:
		nazwaPlikuOut_str = nazwaPlikuIn_str + "_green";
		break;
	case CZERWONY:
		nazwaPlikuOut_str = nazwaPlikuIn_str + "_red";
		break;
	default:
		break;
	}
	break;
  case ROZMYCIE_KOLORU:
	nazwaPlikuOut_str = nazwaPlikuIn_str + "_rozmyty";
	break;
  default:
	break;
  }

  nazwaPlikuIn_str += ".bmp";                    // dopisanie do tekstu nazwy rozszerzenia pliku wejsciowego ".bmp"
  nazwaPlikuOut_str += ".bmp";                   // dopisanie do tekstu nazwy rozszerzenia pliku wyjsciowego ".bmp"
  
  const char* nazwaPlikuIn = nazwaPlikuIn_str.c_str();    // zmiana string "nazwaPlikuIn_str" na char "nazwaPlikuIn" - wymaga tego ifstream
  ifstream plikIn(nazwaPlikuIn, ios::binary);      // utworzenie obiektu o nazwie "plikIn" - strumienia wejsciowego pliku
  if(!plikIn) {                                    // jezeli blad otwarcia pliku wyjsciowego - wywolanie funkcji obslugi bledow
    obslugaBleduOtwarcia(opisBledu[BLAD_OTWARCIA][0] + nazwaPlikuIn);
    return;             // przerwanie operacji powrot do menu
  };
    
  const char* nazwaPlikuOut = nazwaPlikuOut_str.c_str();  // zmiana string "nazwaPlikuOut_str" na char "nazwaPlikuOut" - wymaga tego ofstream
  ofstream plikOut(nazwaPlikuOut, ios::binary);    // utworzenie obiektu o nazwie "plikOut" - strumienia wyjsciowego pliku
  if(!plikOut) {                                   // jezeli blad otwarcia pliku wyjsciowego - wywolanie funkcji obslugi bledow
    obslugaBleduOtwarcia(opisBledu[BLAD_OTWARCIA][1] + nazwaPlikuOut);
    plikIn.close();     // zamkniecie pliku wejsciowego
    return;             // przerwanie operacji powrot do menu
  };

  BITMAPFILEHEADER StrukturaNaglowka;                                        // utworzenie obiektu "StrukturaNaglowka" struktury "BITMAPFILEHEADER"
  if(!plikIn.read((char*)&StrukturaNaglowka, sizeof(BITMAPFILEHEADER))) {    // odczyt z "nazwaPlikuIn" do "StrukturaNaglowka", jezeli blad - obslugaBledu()
    obslugaBledu(opisBledu[BLAD_ODCZYTU][0] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
    return;
  };
  if(!plikOut.write((char*)&StrukturaNaglowka, sizeof(BITMAPFILEHEADER))) {  // zapis "StrukturaNaglowka" do "nazwaPlikuOut", jezeli blad - obslugaBledu()
    obslugaBledu(opisBledu[BLAD_ZAPISU][0] + nazwaPlikuOut, &plikIn, &plikOut, (char*) nazwaPlikuOut);
    return;
  };
  
  BITMAPINFOHEADER OpisNaglowka;                                             // utworzenie obiektu "OpisNaglowka" struktury "BITMAPINFOHEADER"
  if(!plikIn.read((char*)&OpisNaglowka, sizeof(BITMAPINFOHEADER))) {         // odczyt z "nazwaPlikuIn" do "OpisNaglowka", jezeli blad - obslugaBledu()
    obslugaBledu(opisBledu[BLAD_ODCZYTU][1] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
    return;
  };
  if(!plikOut.write((char*)&OpisNaglowka, sizeof(BITMAPINFOHEADER))) {       // zapis "OpisNaglowka" do "nazwaPlikuOut", jezeli blad - obslugaBledu()
    obslugaBledu(opisBledu[BLAD_ZAPISU][1] + nazwaPlikuOut, &plikIn, &plikOut, (char*) nazwaPlikuOut);
    return;
  };
  
  bajtyPiksela = sizeof(Piksel);                             // przypisanie zmiennej "bajtyPiksela" rozmiaru struktury "Piksel" (3-bajty) 
  pusteBajty = ((OpisNaglowka.biWidth * 3) % 4);             // obliczenie i przypisanie zmiennej "pusteBajty" ilosci pustych bajtow w wierszu obrazu 
  przesuniecie = ((OpisNaglowka.biWidth * 3) + pusteBajty);  // obliczenie i przypisanie zmiennej "przesuniecie" ilosci bajtow w wierszu obrazu 
  if(!plikIn.seekg(StrukturaNaglowka.bfOffBits, ios::beg)) { // ustawienie wskaznika czytania na pocz¹teku danych obrazka, jezeli blad - obslugaBledu()
    obslugaBledu(opisBledu[BLAD_WSKAZNIKA][0] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
    return;
  };

  cout << endl << "Prosze czekac ... ";                      // wypisanie na consoli informacji dla uzytkownika
  
  for(x = 0; x < OpisNaglowka.biHeight; x++)                 // ustawienie petli for dla wierszy obrazu x=wiersz
  {
     for(y = 0; y < OpisNaglowka.biWidth; y++)               // ustawienie petli for dla kolumn obrazu y=kolumna
     {

        switch( rodzajOperacji )                             // instrukcja wyboru switch wykonywana na podstawie warunku "rodzajOperacji"
        {
        case SKALA_SZAROSCI:                                 // od "case" do "break" wykonywane dla operacji "SKALA_SZAROSCI"

           if(!plikIn.read((char*)&kolorPiksela, bajtyPiksela)) {    // odczyt piksela z "nazwaPlikuIn" do "kolorPiksela", jezeli blad - obslugaBledu()
             obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
             return;
           };
           kolorPiksela_szary = (( ( int ) kolorPiksela.blue + ( int ) kolorPiksela.green + ( int ) kolorPiksela.red) / 3 ); // obliczenie sredniej 
           kolorPiksela.blue = kolorPiksela_szary;                   // przypisanie "kolorPiksela" usrednionej wartosci "kolorPiksela_szary"
           kolorPiksela.green = kolorPiksela_szary;
           kolorPiksela.red = kolorPiksela_szary;
           break;
		   
        case WYODREBNIENIE_KOLORU:                                   // od "case" do "break" wykonywane dla operacji "WYODREBNIENIE_KOLORU"
           if(!plikIn.read((char*)&kolorPiksela, bajtyPiksela)) {    // odczyt piksela z "nazwaPlikuIn" do "kolorPiksela", jezeli blad - obslugaBledu()
             obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
             return;
           };
           kolorPiksela.blue = (kolorWyodrebnienia == NIEBIESKI ? kolorPiksela.blue : 0); // przypisanie "kolorPiksela" wartosci wg warunku
           kolorPiksela.green = (kolorWyodrebnienia == ZIELONY ? kolorPiksela.green : 0);
           kolorPiksela.red = (kolorWyodrebnienia == CZERWONY ? kolorPiksela.red : 0);
           break;
		   
        case ROZMYCIE_KOLORU:          // od "case" do "break" wykonywane dla operacji "ROZMYCIE_KOLORU" (matryca:3X3 9-pikseli)
	       wskaznik = plikIn.tellg();  // przypisanie zmiennej "wskaznik" biezacego polozenia wskaznika czytania pliku "nazwaPlikuIn"
	       if (x == 0 && y == 0) {     // jezeli pierwszy piksel
	           if(!plikIn.read((char*)&kolorPiksela, bajtyPiksela)) {       // odczyt piksela z "nazwaPlikuIn" do "kolorPiksela", jezeli blad - obslugaBledu()
                 obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           pikselRozmycia[4] = pikselRozmycia[0] = pikselRozmycia[1] = pikselRozmycia[3] = kolorPiksela; // przypisanie odczytanych wartosci
	           if(!plikIn.read((char*)&kolorPiksela, bajtyPiksela)) {       // odczyt kolejnego piksela
                 obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           pikselRozmycia[5] = pikselRozmycia[2] = kolorPiksela;        // przypisanie odczytanych wartosci do 2 i 5 piksela matrycy
	           if(!plikIn.seekg(wskaznik + przesuniecie, ios::beg)) {       // przesuniecie wskaznika czytania do kolejnego piksela matrycy rozmycia
                 obslugaBledu(opisBledu[BLAD_WSKAZNIKA][0] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           if(!plikIn.read((char*)&kolorPiksela, bajtyPiksela)) {       // odczyt kolejnego piksela
                 obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           pikselRozmycia[7] = pikselRozmycia[6] = kolorPiksela;        // przypisanie odczytanych wartosci do 6 i 7 piksela matrycy
	           if(!plikIn.read((char*)&pikselRozmycia[8], bajtyPiksela)) {  // odczyt kolejnego piksela i zapis do 8-piksela matrycy
                 obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
           }
	       else if (x == 0 && (y > 0 && y < OpisNaglowka.biWidth - 1)) {    // jezeli pierwszy wiersz kolumny od 2 do przedostatniej 
	           if(!plikIn.seekg(wskaznik + bajtyPiksela, ios::beg)) {       // przesuniecie wskaznika czytania do okreslonego piksela matrycy rozmycia
                 obslugaBledu(opisBledu[BLAD_WSKAZNIKA][0] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           if(!plikIn.read((char*)&kolorPiksela, bajtyPiksela)) {       // odczyt piksela
                 obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           pikselRozmycia[5] = pikselRozmycia[2] = kolorPiksela;        // przypisanie odczytanych wartosci do 2 i 5 piksela matrycy
	           if(!plikIn.seekg(wskaznik + przesuniecie + bajtyPiksela, ios::beg)) {  // przesuniecie wskaznika
                 obslugaBledu(opisBledu[BLAD_WSKAZNIKA][0] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           if(!plikIn.read((char*)&pikselRozmycia[8], bajtyPiksela)) {  // odczyt piksela i zapis do 8-piksela matrycy
                 obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
		   }
	       else if ((x > 0 && x < OpisNaglowka.biHeight - 1) && y == 0) {   // jezeli pierwsza kolumna, wiersz od 2 do przedostatniego 
	           if(!plikIn.read((char*)&kolorPiksela, bajtyPiksela)) {       // odczyt piksela
                 obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           pikselRozmycia[4] = pikselRozmycia[3] = kolorPiksela;        // przypisanie odczytanych wartosci do 3 i 4 piksela matrycy
	           if(!plikIn.seekg(wskaznik - przesuniecie, ios::beg)) {
                 obslugaBledu(opisBledu[BLAD_WSKAZNIKA][0] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           if(!plikIn.read((char*)&kolorPiksela, bajtyPiksela)) {       // odczyt piksela
                 obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           pikselRozmycia[1] = pikselRozmycia[0] = kolorPiksela;        // przypisanie odczytanych wartosci do 0 i 1 piksela matrycy
	           if(!plikIn.read((char*)&pikselRozmycia[2], bajtyPiksela)) {  // odczyt piksela i zapis do 2-piksela matrycy
                 obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           if(!plikIn.seekg(wskaznik + bajtyPiksela, ios::beg)) {       // przesuniecie wskaznika czytania
                 obslugaBledu(opisBledu[BLAD_WSKAZNIKA][0] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           if(!plikIn.read((char*)&pikselRozmycia[5], bajtyPiksela)) {  // odczyt piksela i zapis do 5-piksela matrycy
                 obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           if(!plikIn.seekg(wskaznik + przesuniecie, ios::beg)) {       // przesuniecie wskaznika czytania
                 obslugaBledu(opisBledu[BLAD_WSKAZNIKA][0] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           if(!plikIn.read((char*)&kolorPiksela, bajtyPiksela)) {       // odczyt piksela
                 obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           pikselRozmycia[7] = pikselRozmycia[6] = kolorPiksela;        // przypisanie odczytanych wartosci do 6 i 7 piksela matrycy
	           if(!plikIn.read((char*)&pikselRozmycia[8], bajtyPiksela)) {  // odczyt piksela i zapis do 8-piksela matrycy
                 obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
		   }
	       else if ((x > 0 && x < OpisNaglowka.biHeight - 1) && (y > 0 && y < OpisNaglowka.biWidth - 1)) { // jezeli wiersze i kolumy nie 1 i nie ostatnie
	           if(!plikIn.seekg(wskaznik - przesuniecie + bajtyPiksela, ios::beg)) {  // przesuniecie wskaznika czytania
                 obslugaBledu(opisBledu[BLAD_WSKAZNIKA][0] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           if(!plikIn.read((char*)&pikselRozmycia[2], bajtyPiksela)) {  // odczyt piksela i zapis do 2-piksela matrycy
                 obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           if(!plikIn.seekg(wskaznik + bajtyPiksela, ios::beg)) {  // przesuniecie wskaznika czytania
                 obslugaBledu(opisBledu[BLAD_WSKAZNIKA][0] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           if(!plikIn.read((char*)&pikselRozmycia[5], bajtyPiksela)) {  // odczyt piksela i zapis do 5-piksela matrycy
                 obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           if(!plikIn.seekg(wskaznik + przesuniecie + bajtyPiksela, ios::beg)) {  // przesuniecie wskaznika czytania
                 obslugaBledu(opisBledu[BLAD_WSKAZNIKA][0] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           if(!plikIn.read((char*)&pikselRozmycia[8], bajtyPiksela)) {  // odczyt piksela i zapis do 8-piksela matrycy
                 obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
		   }
	       else if ((x == OpisNaglowka.biHeight - 1) && y == 0) {  // jezeli pierwsza kolumna, ostatni wiersz
	           if(!plikIn.read((char*)&kolorPiksela, bajtyPiksela)) {  // odczyt piksela
                 obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           pikselRozmycia[4] = pikselRozmycia[3] = pikselRozmycia[6] = pikselRozmycia[7] = kolorPiksela;   // przypisanie odczytanych wartosci
	           if(!plikIn.seekg(wskaznik - przesuniecie, ios::beg)) {  // przesuniecie wskaznika czytania
                 obslugaBledu(opisBledu[BLAD_WSKAZNIKA][0] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           if(!plikIn.read((char*)&kolorPiksela, bajtyPiksela)) {  // odczyt piksela
                 obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           pikselRozmycia[1] = pikselRozmycia[0] = kolorPiksela;  // przypisanie odczytanych wartosci do 0 i 1 piksela matrycy
	           if(!plikIn.read((char*)&pikselRozmycia[2], bajtyPiksela)) {  // odczyt piksela i zapis do 2-piksela matrycy
                 obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           if(!plikIn.seekg(wskaznik + bajtyPiksela, ios::beg)) {  // przesuniecie wskaznika czytania
                 obslugaBledu(opisBledu[BLAD_WSKAZNIKA][0] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           if(!plikIn.read((char*)&kolorPiksela, bajtyPiksela)) {  // odczyt piksela
                 obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           pikselRozmycia[5] = pikselRozmycia[8] = kolorPiksela;  // przypisanie odczytanych wartosci do 5 i 8 piksela matrycy
		   }
	       else if ((x == OpisNaglowka.biHeight - 1) && (y > 0 && y < OpisNaglowka.biWidth - 1)) {  // jezeli ostatni wiersz kolumny od 2 do przedostatniej
	           if(!plikIn.seekg(wskaznik - przesuniecie + bajtyPiksela, ios::beg)) {  // przesuniecie wskaznika czytania
                 obslugaBledu(opisBledu[BLAD_WSKAZNIKA][0] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           if(!plikIn.read((char*)&pikselRozmycia[2], bajtyPiksela)) {  // odczyt piksela i zapis do 2-piksela matrycy
                 obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           if(!plikIn.seekg(wskaznik + bajtyPiksela, ios::beg)) {  // przesuniecie wskaznika czytania
                 obslugaBledu(opisBledu[BLAD_WSKAZNIKA][0] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           if(!plikIn.read((char*)&kolorPiksela, bajtyPiksela)) {  // odczyt piksela
                 obslugaBledu(opisBledu[BLAD_ODCZYTU][2] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
                 return;
               };
	           pikselRozmycia[5] = pikselRozmycia[8] = kolorPiksela;  // przypisanie odczytanych wartosci do 5 i 8 piksela matrycy
		   }
			 
	       if(!plikIn.seekg(wskaznik + bajtyPiksela, ios::beg)) {  // przesuniecie wskaznika czytania na kolejny piksel, jezeli blad - obslugaBledu()
                 obslugaBledu(opisBledu[BLAD_WSKAZNIKA][0] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
              return;
           };
	
		   suma_blue = suma_green = suma_red = 0;                  // wyzerowanie sum po kazdej petli
		   for(i = 0; i <= IL_PIKSELI; i++) {                      // zliczenie sum poszczegojnych kolorow wszystkich pikseli matrycy
			  suma_blue += ( int ) pikselRozmycia[i].blue;
			  suma_green += ( int ) pikselRozmycia[i].green;
			  suma_red += ( int ) pikselRozmycia[i].red;
		   }
	
		   kolorPiksela.blue = (suma_blue / (IL_PIKSELI + 1));     // przypisanie usrednionej wartosci koloru wszystkich pikseli matrycy
		   kolorPiksela.green = (suma_green / (IL_PIKSELI + 1));
		   kolorPiksela.red = (suma_red / (IL_PIKSELI + 1));
	
		   for(i = 1; i <= IL_PIKSELI; i++) {                      //  przesuniecie elementow - ustawienie matrycy do nastepnej petli
		      if (i == 3 || i == 6) {
		         i++;}
			  pikselRozmycia[i-1] = pikselRozmycia[i];
	       }
           break;
		}

		if(!plikOut.write((char*)&kolorPiksela, bajtyPiksela)) {   // zapis zmodyfikowanych bajtow piksela do pliku wyjsciowego, jezeli blad - obslugaBledu()
           obslugaBledu(opisBledu[BLAD_ZAPISU][2] + nazwaPlikuOut, &plikIn, &plikOut, (char*) nazwaPlikuOut);
           return;
		   
        };
     }

     if(!plikIn.read((char*)&kolorPiksela, pusteBajty)) {          // odczyt pustych bajtow piksela z pliku wejsciowego, jezeli blad - obslugaBledu()
                 obslugaBledu(opisBledu[BLAD_ODCZYTU][3] + nazwaPlikuIn, &plikIn, &plikOut, (char*) nazwaPlikuOut);
        return;
     };
     if(!plikOut.write((char*)&kolorPiksela, pusteBajty)) {        // zapis pustych bajtow piksela do pliku wyjsciowego, jezeli blad - obslugaBledu()
        obslugaBledu(opisBledu[BLAD_ZAPISU][3] + nazwaPlikuOut, &plikIn, &plikOut, (char*) nazwaPlikuOut);
        return;
     };
  }

  plikIn.close();    // zamkniecie pliku wejsciowego
  plikOut.close();   // zamkniecie pliku wyjsciowego
  
  // wypisanie na consoli informacji z przebiegu procesu
  system( "cls" );   // czyszczenie ekranu konsoli
  cout << endl << " ----------------------------------------------------";
  cout << endl << "    INFORMACJA Z PRZEBIEGU PROCESU";
  cout << endl << " Operacja zakonczyla sie powodzeniem";
  cout << endl << " Utworzony zostal plik wynikowy - " << "\"" << nazwaPlikuOut << "\"";
  cout << endl << " ----------------------------------------------------" << endl;
  cout << endl << " Struktura pliku wejsciowego:";
  cout << endl << "  Nazwa pliku            : " << nazwaPlikuIn;
  cout << endl << "  Rozmiar pliku          : " << StrukturaNaglowka.bfSize << "B";
  cout << endl << "  Poczatek danych obrazka: " << StrukturaNaglowka.bfOffBits << "B" << endl;
 
  cout << endl << " Opis pliku:";
  cout << endl << "  Wysokosc obrazu        : " << OpisNaglowka.biHeight << "px";
  cout << endl << "  Szerokosc obrazu       : " << OpisNaglowka.biWidth << "px";
  cout << endl << "  Wielkosc obrazu        : " << OpisNaglowka.biSizeImage << "B";
  cout << endl << "  Liczba bitow na piksel : " << OpisNaglowka.biBitCount;
  cout << endl << endl;
  system("pause");
 return;
}
