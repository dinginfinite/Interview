#ifndef QIHOO_INI_UTILITY_H_
#define QIHOO_INI_UTILITY_H_

#include <string>

namespace qh {

	const std::string WhiteSpace = " \t\r\n";

	/**
	 * trim leading and trailing whitespace;
	 * @param s - string to be trimming
	 * @return return the string after trimming
	 */
	std::string& trim(std::string &s);
}

#endif
