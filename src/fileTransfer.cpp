#include <File.hpp>
#include <Server.hpp>
/* PRIVMSG <client> :DCC SEND <filename> <host> <port> (<tamaño>)
    <filename>: nombre del archivo; <host>: IP pública del remitente; <port>: puerto del remitente.
    Hay dos partes: el usuario que intenta mandar el fichero, y el que lo recibe.
    El usuario que recibe debe recibir una request para acpetar o ignorar la transferencia.
    Atraves del PRIVMSG, el buffer será = DCC SEND <fn> <host> <port>
    A lo mejor, en vex de un vector con el nombre de los ficheros, hago un map con la ruta y el nombre del fichero
    Yo debería mandar un NOTICE <target> :Aceptar o ignorar la transferencia
    El remitente deberia de ser algo como PRIVMSG <target>:!accept fichero
*/
static  std::string itoa(int number){
    std::stringstream   str;
    
    str << number;
    return (str.str());
}

static  int    validateFile(std::string filename, Server *server, std::string &aux){
    std::ifstream   file(filename.c_str());
    
    aux.clear();
    if (file.fail())
        return (101);
    aux = filename.substr(filename.find_last_of('/') + 1, filename.size());
    for (size_t i = 0; i < aux.size(); i++){
        if (!isalnum(aux[i]) && aux[i] != '.' && aux[i] != '_')
            return (102);
        if (server->getFiles()[i].getFilename().compare(aux) == 0)
            return (103);
    }
    return (0);
}

static  File    getFile(std::string file, std::string sender, std::string receiver, Server *server){
  (void)server;
   std::string  path;
   std::string  filename;

   path = file.substr(0, file.find_last_of('/'));
   filename = file.substr(file.find(file.find_last_of('/') + 1, file.size()));
   return (File(filename, path, sender, receiver));
}

void    Server::parseFileTransfer(std::string buffer, Client &sender, Client &receiver){
    std::vector<std::string> arguments = split(buffer, ' ');
    std::string aux = "";
    
    try {
        if (arguments.size() < 5) throw 461;
        else if (arguments.size() > 5) throw 1;
        else {
            if (validateFile(arguments[2], this, aux)) throw validateFile(arguments[2], this, aux);
            if (arguments[3].compare(receiver.getHostname()) != 0) throw 104;
            if (arguments[4].compare(itoa(this->port)) != 0) throw 105;
            this->files.push_back(getFile(arguments[2], sender.getNick(), receiver.getNick(), this));
            sender.setResponse("NOTICE: " + sender.getNick() + " wants to send you a file: " + aux + ". PRIVMSG user whit 'DCC ACCEPT <filename>' to get the file or 'DCC IGNORE <filename>' to decline.\r\n");
        }
    } catch (int code){
        if (code == 1)
            sender.setResponse(sender.getHostname() + " DDC SEND :Extra parameters.\r\n");
        if (code == 461)
            sender.setResponse(sender.getHostname() + " DDC SEND :Not enough parameters.");
        if (code == 101)
            sender.setResponse(sender.getHostname() + " DDC SEND :No such file.\r\n");
        if (code == 102)
            sender.setResponse(sender.getHostname() + " " + aux + " :Erroneus file.\r\n");
        if (code == 103)
            sender.setResponse(sender.getHostname() + " " + aux + " :File already send.\r\n");
        if (code == 104)
            sender.setResponse(sender.getHostname() + " " + arguments[3] + " :The specified ip does not match the target ip.\r\n");
        if (code == 105)
            sender.setResponse(sender.getHostname() + " " + arguments[4] + " :The specified port does not match the target connection port.\r\n");
    }
}
