#include "io/SimpleLogger.h"

namespace hyrise {
namspace io {

SimpleLogger::getInstance() {
    static SimpleLogger instance;
    return instance;
}

SimpleLogger::SimpleLogger() {
    // open log file etc.
}

}
}
