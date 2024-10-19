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
Zmieñ nazwê pliku :

Aby Apache prawid³owo zidentyfikowa³ Twój plik jako skrypt CGI, 
zaleca siê, aby plik mia³ rozszerzenie.cgi.Zmieñ nazwê pliku z 
Hello World Web Page.exe na HelloWorldWebPage.cgi.

Umieœæ plik w katalogu cgi - bin :

Przenieœ plik HelloWorldWebPage.cgi do katalogu C : / xampp / cgi - bin / 

SprawdŸ konfiguracjê Apache(plik httpd.conf) :

Otwórz plik konfiguracyjny Apache(C : / xampp / apache / conf / httpd.conf) i upewnij siê, ¿e masz skonfigurowany odpowiedni ScriptAlias oraz dyrektywy dla cgi - bin :

	apache
	Skopiuj kod
	ScriptAlias / cgi - enabled / "C:/xampp/cgi-bin/"
	< Directory "C:/xampp/cgi-bin" >
	AllowOverride None
	Options + ExecCGI
	Require all granted
	AddHandler cgi - script.cgi.exe
	< / Directory>
	Upewnij siê, ¿e dyrektywy AllowOverride, Options, Require, i AddHandler s¹ poprawnie ustawione.Dziêki temu Apache bêdzie wiedzia³, ¿e mo¿e uruchamiaæ pliki z tymi rozszerzeniami jako skrypty CGI.

Zrestartuj Apache :

Po wprowadzeniu jakichkolwiek zmian w pliku httpd.conf, 
zrestartuj serwer Apache w panelu kontrolnym XAMPP, klikaj¹c "Stop", a nastêpnie "Start".
SprawdŸ uprawnienia pliku :

Upewnij siê, ¿e plik HelloWorldWebPage.cgi ma odpowiednie uprawnienia do wykonania.
W systemie Windows uprawnienia s¹ domyœlnie ustawione na umo¿liwienie wykonywania, 
ale warto to sprawdziæ.

SprawdŸ adres URL w przegl¹darce :
Otwórz przegl¹darkê i wpisz adres URL do skryptu CGI :


http ://localhost/cgi-enabled/HelloWorldWebPage.cgi

Powinieneœ zobaczyæ stronê HTML wygenerowan¹ przez Twój program.
Jeœli tak siê nie stanie, upewnij siê, ¿e nie ma b³êdów w logach Apache, 
które mog¹ wskazywaæ, dlaczego skrypt nie dzia³a.

Upewnij siê, ¿e Twój plik wykonywalny generuje poprawn¹ zawartoœæ HTML.
SprawdŸ, czy w kodzie C++ jest poprawnie ustawiony nag³ówek HTTP(np.Content - type: text / html).

B³êdy w logach : Jeœli nadal otrzymujesz b³¹d 404 lub inny, sprawdŸ logi Apache(znajdziesz je w C : / xampp / apache / logs / error.log), aby zidentyfikowaæ problem.
Podsumowuj¹c, zmiana nazwy pliku na.cgi, upewnienie siê, ¿e plik jest w odpowiednim katalogu, a tak¿e sprawdzenie konfiguracji Apache, powinny rozwi¹zaæ problem z wyœwietlaniem Twojej strony.

*/