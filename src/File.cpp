#include <File.hpp>

File::File() {}

File::File(std::string filename, std::string path, std::string senderNick, std::string receiverNick){
    this->filename = filename;
    this->path = path;
    this->senderNick = senderNick;
    this->receiverNick = receiverNick;
}
File::File(const File &src){
    if (this != &src)
        *this = src;
}

File    &File::operator = (const File &copy){
    if (this != &copy)
    {
        this->filename = getFilename();
        this->path = getPath();
        this->senderNick = getSenderNick();
        this->receiverNick = getReceiverNick();
    }
}

File::~File() {}

std::string File::getFilename() const { return this->filename; }
std::string File::getPath() const { return this->path; }
std::string File::getSenderNick() const { return this->senderNick; }
std::string File::getReceiverNick() const { return this->receiverNick; }
