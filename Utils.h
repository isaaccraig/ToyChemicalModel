
#include <iostream>
#include <string>

namespace Utils{
  /* base Error to give message and halt */
inline void Error( const std::string *msg ) {
  std::cout << "Error :" << msg << std::endl;
  exit(-1);
  }
  /* Warning to give message and continue */
inline void Warning( const std::string *msg ) {
  std::cout << "Warning :" << msg << std::endl;
}
inline void Error( const char *msg ) {
  std::cout << "Error :" << msg << std::endl;
  exit(-1);
  }
  /* Warning to give message and continue */
inline void Warning( const char *msg ) {
  std::cout << "Warning :" << msg << std::endl;
}

};
