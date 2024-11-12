/* PRIVMSG <client> :DCC SEND <filename> <host> <port> (<tamaño>)
    <filename>: nombre del archivo; <host>: IP pública del remitente; <port>: puerto del remitente.
    Hay dos partes: el usuario que intenta mandar el fichero, y el que lo recibe.
    El usuario que recibe debe recibir una request para acpetar o ignorar la transferencia.
    Atraves del PRIVMSG, el buffer será = DCC SEND <fn> <host> <port>
    A lo mejor, en vex de un vector con el nombre de los ficheros, hago un map con la ruta y el nombre del fichero
    Yo debería mandar un NOTICE <target> :Aceptar o ignorar la transferencia
    El remitente deberia de ser algo como PRIVMSG <target>:!accept fichero
*/

static  int    validateFile(std::string filename, Server *server){
    int         pos = 0;
    ifstream    file(filename.c_str());
    
    if (file.fail())
        return (999);
    if (filename.find_last_of('/') != buffer.npos)
        pos = filename.find_last_of('/');
    if (server->files.find(filename.substr(pos + 1)) != this->files.end())
        return (996);
    return (0);
}

void    Server::parseFileTransfer(std::string buffer, Client &sender, Client &receiver){
    std::vector<std::string> arguments = split(buffer, ' ');
    
    try {
        if (arguments.size() < 5)
            //Falta algun parametro 461
        else if (arguments.size() > 5)
            //Extra parametros
        else {
            if (arguments[0].compare(":DCC") != 0)
                // Este parámetro está mal. Supongo que mensaje personalizado
            if (arguments[1].compare("SEND") != 0)
                // Este parámetro está mal
            if (!validateFile(arguments[2]))
                // Fichero no válido
            if (arguments[3].compare(receiver->getHotsname()) != 0)
                // No es el Hostanme del usuario final
            if (arguments[4].compare(itoa(this->port)) != 0)
                // No es el puerto del usuario final
            //crear clase File
            this->files.insert(std::pair<ts::string, File>(filename, file));
            // PRIVMSG o NOTICE
        }
    } catch (int code){}
}