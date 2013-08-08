#include "testing/test.h"
#include "io/SimpleLogger.h"

namespace hyrise {
namespace io {

class SimpleLoggerTests : public ::hyrise::Test {};

TEST_F(SimpleLoggerTests, simple_log_test) {
  SimpleLogger::getInstance().logDictionary('a', 1, (int64_t)2, 3);
  SimpleLogger::getInstance().logDictionary('a', 1, 2.0f, 3);
  SimpleLogger::getInstance().logDictionary('a', 1, "zwei", 3);
  std::vector<ValueId> vids;
  vids.push_back(ValueId(0, 0));
  vids.push_back(ValueId(1, 0));
  vids.push_back(ValueId(2, 0));
  SimpleLogger::getInstance().logValue(1,'a',2,3,4,&vids);
  SimpleLogger::getInstance().logCommit(1);
}

}
}
