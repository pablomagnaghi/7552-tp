#include "Utils.h"

#include <algorithm>
#include <cstring>

// Biblioteca POSIX para los nombres de Archivos
#include <libgen.h>

#include <cstdio>  /* defines FILENAME_MAX */
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

std::string Utils::toLowerCase(const std::string& cadena) {
	std::string aux = cadena;

	// Hace lower case de los caraceteres A-Z:
	std::transform(aux.begin(), aux.end(), aux.begin(), ::tolower);

	// Suponiendo que el string viene en UTF-8, hace lower case de acentos y ñ:
	for (unsigned int i = 0; i < aux.length(); i++) {
		if (aux[i] == (char) 0xc3) {
			if (aux[i + 1] == (char) 0x81) {
				// Á c3 81 -> á c3 a1
				aux[i + 1] = 0xa1;
				i++;
			} else if (aux[i + 1] == (char) 0x89) {
				// É c3 89 -> é c3 a9
				aux[i + 1] = 0xa9;
				i++;
			} else if (aux[i + 1] == (char) 0x8d) {
				// Í c3 8d -> í c3 ad
				aux[i + 1] = 0xad;
				i++;
			} else if (aux[i + 1] == (char) 0x93) {
				// Ó c3 93 -> ó c3 b3
				aux[i + 1] = 0xb3;
				i++;
			} else if (aux[i + 1] == (char) 0x9a) {
				// Ú c3 9a -> ú c3 ba
				aux[i + 1] = 0xba;
				i++;
			} else if (aux[i + 1] == (char) 0x91) {
				// Ñ c3 91 -> ñ c3 b1
				aux[i + 1] = 0xb1;
				i++;
			}
		}
	}
	return aux;
}

std::string Utils::getDirname(const std::string & path) {
	return ::dirname((char *) path.c_str());
}

std::string Utils::getBasename(const std::string & path) {
	return ::basename((char *) path.c_str());
}

std::string Utils::getCurrentDirectory() {

	std::string cwd;

	char cCurrentPath[FILENAME_MAX];

	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))) {
		//return errno;
		return "";
	}

	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

	//printf("The current working directory is %s\n", cCurrentPath);

	cwd.assign(cCurrentPath);

	return cwd;
}

std::string Utils::fillNumber(int numero){
	std::stringstream ss;
	ss << numero;
	std::string s = ss.str();
	if (s.length() == 1){
		s = "0" + s;
	}
	return s;
}

std::string Utils::getDate(){
	time_t t = time(0);
	struct tm* now = localtime(&t);
	std::stringstream ss;
	ss 	<< (now->tm_year + 1900)
		<< Utils::fillNumber(now->tm_mon + 1)
		<< Utils::fillNumber(now->tm_mday);
	return ss.str();
}
