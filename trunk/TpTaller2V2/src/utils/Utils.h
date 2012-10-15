
#ifndef UTILS_H_
#define UTILS_H_

#include <string>

class Utils {
private:

	Utils();
	virtual ~Utils();

public:

	static std::string toLowerCase(const std::string &);

	static std::string getDirname(const std::string & path);
	static std::string getBasename(const std::string & path);

	static std::string getCurrentDirectory();
};


#endif /* UTILS_H_ */
