#ifndef SRC_LIB_IO_LOGGING_H
#define SRC_LIB_IO_LOGGING_H

#include "io/BufferedLogger.h"
#include "io/NoLogger.h"
#include "io/SimpleLogger.h"

namespace hyrise {
namespace io {

  // Uncomment to disable logging
  typedef NoLogger Logger;

  // Uncomment to use SimpleLogger
  //typedef SimpleLogger Logger;

  // Uncomment to use BufferedLogger
  //typedef BufferedLogger Logger;

}
}

#endif // SRC_LIB_IO_LOGGING_H
