#include "ini_utility.h"

namespace qh {
	/**
	 * trim leading and trailing whitespace;
	 * @param s - string to be trimming
	 * @return return the string after trimming
	 */
	std::string& trim(std::string &s) {
		size_t pos = s.find_first_not_of(WhiteSpace);
		if (pos != std::string::npos)
			s.erase(0, pos);
		else
			s.erase(0, s.size());
		pos = s.find_last_not_of(WhiteSpace);
		if (pos != std::string::npos)
			s.erase(pos + 1);
		return s;
	}
}
