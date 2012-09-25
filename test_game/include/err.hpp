/*
Поток вывода для сообщений об ошибках
По умолчанию выводит туда же куда и std::cerr

перенаправить в файл:
 std::ofstream file("sfml-log.txt");
 std::streambuf* previous = sf::err().rdbuf(file.rdbuf());
 // Redirect to nothing
 sf::err().rdbuf(NULL);
 // Restore the original output
 sf::err().rdbuf(previous);
*/
#ifndef ERR_H
#define ERR_H

#include <ostream>

extern std::ostream& error();

#endif // ERR_H