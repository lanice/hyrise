#include "testing/test.h"
#include "io/BufferedLogger.h"

namespace hyrise {
namespace io {

class BufferedLoggerTests : public ::hyrise::Test {};

TEST_F(BufferedLoggerTests, simple_log_test) {
  BufferedLogger::getInstance().logDictionary('a', 1, (int64_t)2, 3);
  BufferedLogger::getInstance().logDictionary('a', 1, 2.0f, 3);
  BufferedLogger::getInstance().logDictionary('a', 1, "zwei", 3);
  BufferedLogger::getInstance().logValue(1,'a',2,3,4,{5,6,7});
  BufferedLogger::getInstance().logCommit(1);
}

}
}
