#include "testing/test.h"
#include "io/SimpleLogger.h"

namespace hyrise {
namespace io {

class SimpleLoggerTests : public ::hyrise::Test {};

TEST_F(SimpleLoggerTests, simple_log_test) {
  SimpleLogger::getInstance().logDictionary('a', 1, (int64_t)2, 3);
  SimpleLogger::getInstance().logDictionary('a', 1, 2.0f, 3);
  SimpleLogger::getInstance().logDictionary('a', 1, "zwei", 3);
  SimpleLogger::getInstance().logValue(1,'a',2,3,4,{5,6,7});
  SimpleLogger::getInstance().logCommit(1);
}

}
}
