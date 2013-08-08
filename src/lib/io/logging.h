#ifndef SRC_LIB_IO_LOGGING_H
#define SRC_LIB_IO_LOGGING_H

#include "io/SimpleLogger.h"
#include "io/BufferedLogger.h"

namespace hyrise {
namespace io {

  // Uncomment to use SimpleLogger
  //typedef SimpleLogger Logger;

  // Uncomment to use BufferedLogger
  typedef BufferedLogger Logger;

}
}

#endif // SRC_LIB_IO_LOGGING_H
