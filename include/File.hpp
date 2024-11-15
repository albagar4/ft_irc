#ifndef FILE_HPP
#define FILE_HPP

#include <ircserv.hpp>

class File {
   private:
    std::string filename;
    std::string path;
    std::string senderNick;
    std::string receiverNick;

   public:
    File();
    File(std::string filename, std::string path, std::string senderNick, std::string receiverNick);
    File(const File &src);
    ~File();
    File &operator=(const File &copy);
    std::string getFilename() const;
    std::string getPath() const;
    std::string getSenderNick() const;
    std::string getReceiverNick() const;
};

#endif
