#include "Szyfrator.h"

int main()
{
	setlocale(LC_CTYPE, "Polish");

	int klucz{ 0 };
	std::string slowo{ "" };
	while (true) {
		
		system("cls");

		std::cout << "Źrodło tekstu:  " << std::endl;
		std::cout << "Z pliku      -> 1 " << std::endl;
		std::cout << "Z klawiatury -> 2 " << std::endl;
		std::cin >> klucz;

		if (klucz == 1)
		{
			slowo = inPlik();
		}
		else
		{
			std::cout << std::endl;
			std::cout << "Podaj frazę: " << std::endl;
			std::getline(std::cin >> std::ws, slowo);
		}

		std::cout << "*******************" << std::endl;
		std::cout << "gadery_poluki -> 1 " << std::endl;
		std::cout << "malinowe_buty -> 2 " << std::endl;
		std::cout << "Alfabet Morsa -> 3 " << std::endl;
		std::cout << "Szyfr Cezar   -> 4 " << std::endl;
		std::cout << "Koniec        -> 0 " << std::endl;
		std::cout << "Wybierz szyfr: ";

		std::cin >> klucz;

		if (!(klucz == 1 || klucz == 2 || klucz == 3 || klucz == 4))
		{
			std::cout << "zły wybór" << std::endl;
			break;
		}
		else if (klucz == 1 || klucz == 2 || klucz == 3 || klucz == 4)
		{
			std::unique_ptr <cSzyfr> uKodo;
			switch (klucz)
			{
			case gadery_poluki:
				uKodo = std::make_unique<cGadery>();
				slowo = uKodo->szyfrowanie(slowo);
				break;

			case malinowe_buty:
				uKodo = std::make_unique<cMalinowe>();
				slowo = uKodo->szyfrowanie(slowo);
				break;

			case mors:
				uKodo = std::make_unique<cMorse>();
				slowo = uKodo->szyfrowanie(slowo);
				break;

			case cezar:
				uKodo = std::make_unique<cCezar>();
				slowo = uKodo->szyfrowanie(slowo);
				break;
			}

		}
		else {
			std::cout << "zly wybor" << std::endl;
		}

		std::cout << slowo << std::endl;
		std::cout << "Czy zapisać do pliku? (tak / nie) ";
		std::string zapisDoPlik;
		std::cin >> zapisDoPlik;

		if (zapisDoPlik == "tak")
		{
			outPlik(slowo);
		}

		system("pause");
	}
}