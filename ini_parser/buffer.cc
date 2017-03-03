#include "buffer.h"
#include "ini_utility.h"

namespace qh {
/**
 * Get the next line
 * @param line_sperator - line sperator
 * @return the next line in the buffer
 */
std::string Buffer::getNextLine(const std::string &line_seperator) {
  std::string line;
  bool isInString = false;
  char stringDelimiter;
  while (posCur_ < posEnd_) {

    // Determine whether we are in quote enclosed string
    if (data_[posCur_] == '"' || data_[posCur_] == '\'') {
      if (isInString && data_[posCur_] == stringDelimiter) {
        isInString = false;
      } else if (!isInString) {
        isInString = true;
        stringDelimiter = data_[posCur_];
      }
      line.push_back(data_[posCur_]);
    } else if (!isInString && data_[posCur_] == line_seperator[0] &&
               data_.substr(posCur_, line_seperator.size()) == line_seperator) {
      // Not in string and meet the line_sperator
      posCur_ += line_seperator.size();
      break;
    } else {
      line.push_back(data_[posCur_]);
    }

    ++posCur_;
  }
  trim(line);
  return line;
}

};
