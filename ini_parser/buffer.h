#ifndef BUFFER_H_
#define BUFFER_H_

#include <string>

namespace qh {
  class Buffer {
  public:
    typedef std::string::size_type sz;
    Buffer() : posEnd_(0), posCur_(0){};
    Buffer(const std::string &s)
        :posEnd_(s.size()), posCur_(0), data_(s) {}

    /**
     * Get the next line
     * @param line_sperator - line sperator
     * @return the next line in the buffer
     */
    std::string getNextLine(const std::string &line_seperator = "\n");

    /**
     * Determine whether the buffer has more lines
     * @return return <code>true</code> if has more lines
     * otherwise reutrn <code>false</code>
     */
    bool hasMoreLine() {
      return posCur_ < posEnd_;
    }

  private:
    sz posEnd_;
    sz posCur_;
    std::string data_;
  };
}

#endif
