#ifndef ARGUMENTOINVALIDO_H_
#define ARGUMENTOINVALIDO_H_

#include <exception>
#include <string>

class ArgumentoInvalido: public std::exception {
private:
	std::string explicacion;
public:
	ArgumentoInvalido(const std::string & explicacion);
	virtual ~ArgumentoInvalido()throw();

	virtual const char * what()const throw();
};

#endif /* ARGUMENTOINVALIDO_H_ */
