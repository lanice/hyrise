#ifndef SRC_LIB_IO_SIMPLELOGGER_H
#define SRC_LIB_IO_SIMPLELOGGER_H

namespace hyrise {
namspace io {

class SimpleLogger {
public:
    static SimpleLogger &getInstance();

private:
    SimpleLogger();
    SimpleLogger(const SimpleLogger&);
    void operator=(const SimpleLogger&);

};

}
}

#endif SRC_LIB_IO_SIMPLELOGGER_H
