#include <iostream>

using namespace std;


//http://localhost/cgi-enabled/HelloWorldWebPage.cgi


void printWeb()
{
		std::cout << "Content-type:text/html\n\n";
		std::cout << "<html>\n";
		std::cout << "<head>\n";
		std::cout << " <title>Hello World - First C++ Web Program</title>\n";
		std::cout << "</head>\n";
		std::cout << "<body>\n";
		std::cout << "<div style=\"width: 100%; font-size: 36px; font-weight: bold; text-align: center; color: blue;\">\n";
		std::cout << " <h2>Hello World!</h2> \n";
		std::cout << " This is my C++ Web Programming Test Page";
		std::cout << "</div>\n";
		std::cout << "</body>\n";
		std::cout << "</html>\n";
}

int main()
{
	printWeb();

	return 0;
}

/*

Kroki do skonfigurowania skryptu CGI w XAMPP :
Zmie� nazw� pliku :

Aby Apache prawid�owo zidentyfikowa� Tw�j plik jako skrypt CGI, 
zaleca si�, aby plik mia� rozszerzenie.cgi.Zmie� nazw� pliku z 
Hello World Web Page.exe na HelloWorldWebPage.cgi.

Umie�� plik w katalogu cgi - bin :

Przenie� plik HelloWorldWebPage.cgi do katalogu C : / xampp / cgi - bin / 

Sprawd� konfiguracj� Apache(plik httpd.conf) :

Otw�rz plik konfiguracyjny Apache(C : / xampp / apache / conf / httpd.conf) i upewnij si�, �e masz skonfigurowany odpowiedni ScriptAlias oraz dyrektywy dla cgi - bin :

	apache
	Skopiuj kod
	ScriptAlias / cgi - enabled / "C:/xampp/cgi-bin/"
	< Directory "C:/xampp/cgi-bin" >
	AllowOverride None
	Options + ExecCGI
	Require all granted
	AddHandler cgi - script.cgi.exe
	< / Directory>
	Upewnij si�, �e dyrektywy AllowOverride, Options, Require, i AddHandler s� poprawnie ustawione.Dzi�ki temu Apache b�dzie wiedzia�, �e mo�e uruchamia� pliki z tymi rozszerzeniami jako skrypty CGI.

Zrestartuj Apache :

Po wprowadzeniu jakichkolwiek zmian w pliku httpd.conf, 
zrestartuj serwer Apache w panelu kontrolnym XAMPP, klikaj�c "Stop", a nast�pnie "Start".
Sprawd� uprawnienia pliku :

Upewnij si�, �e plik HelloWorldWebPage.cgi ma odpowiednie uprawnienia do wykonania.
W systemie Windows uprawnienia s� domy�lnie ustawione na umo�liwienie wykonywania, 
ale warto to sprawdzi�.

Sprawd� adres URL w przegl�darce :
Otw�rz przegl�dark� i wpisz adres URL do skryptu CGI :


http ://localhost/cgi-enabled/HelloWorldWebPage.cgi

Powiniene� zobaczy� stron� HTML wygenerowan� przez Tw�j program.
Je�li tak si� nie stanie, upewnij si�, �e nie ma b��d�w w logach Apache, 
kt�re mog� wskazywa�, dlaczego skrypt nie dzia�a.

Upewnij si�, �e Tw�j plik wykonywalny generuje poprawn� zawarto�� HTML.
Sprawd�, czy w kodzie C++ jest poprawnie ustawiony nag��wek HTTP(np.Content - type: text / html).

B��dy w logach : Je�li nadal otrzymujesz b��d 404 lub inny, sprawd� logi Apache(znajdziesz je w C : / xampp / apache / logs / error.log), aby zidentyfikowa� problem.
Podsumowuj�c, zmiana nazwy pliku na.cgi, upewnienie si�, �e plik jest w odpowiednim katalogu, a tak�e sprawdzenie konfiguracji Apache, powinny rozwi�za� problem z wy�wietlaniem Twojej strony.

*/