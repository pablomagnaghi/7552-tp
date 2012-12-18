#ifndef NULLPOINTEREXCEPCTION_H_
#define NULLPOINTEREXCEPCTION_H_

#include <exception>
#include <string>

class NullPointer : public std::exception {
private:
	std::string explicacion;
public:
	NullPointer(const std::string & explicacions);
	virtual ~NullPointer()throw();

	virtual const char * what()const throw();
};

#endif /* NULLPOINTEREXCEPCTION_H_ */
