#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <sstream>
#include <vector>
#include <dirent.h>

class Utils {
private:

	Utils();
	virtual ~Utils();

	static int selecc_arch(const struct dirent *entry);

public:

	static std::string toLowerCase(const std::string &);

	static std::string getDirname(const std::string & path);
	static std::string getBasename(const std::string & path);

	static std::string getCurrentDirectory();

	static std::string fillNumber(int);
	static std::string getDate();
	static std::vector<std::string> getFiles(const std::string & folder);
	static bool file_exists(const std::string & path);
	static std::string intToString(int numero);
	static std::string floatToString(float numero);
};

#endif /* UTILS_H_ */
