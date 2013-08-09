#include "testing/test.h"
#include "io/SimpleLogger.h"

#include <thread>
#include <vector>

namespace hyrise {
namespace io {

class SimpleLoggerTests : public ::hyrise::Test {};

void simpleLoggerTestWorker(uint64_t tx) {
  SimpleLogger::getInstance().logDictionary('a', 1, (int64_t)2, 3);
  SimpleLogger::getInstance().logDictionary('a', 1, 2.0f, 3);
  SimpleLogger::getInstance().logDictionary('a', 1, "zwei", 3);
  std::vector<ValueId> vids;
  vids.push_back(ValueId(0, 0));
  vids.push_back(ValueId(1, 0));
  vids.push_back(ValueId(2, 0));
  SimpleLogger::getInstance().logValue(tx,'a',2,3,4,&vids);
  SimpleLogger::getInstance().logCommit(tx);
}

TEST_F(SimpleLoggerTests, simple_log_test) {
  std::vector<std::thread> threadpool;
  uint64_t tx = 1;
  for(int i=0; i<100; i++)
    threadpool.push_back(std::thread(simpleLoggerTestWorker, tx++));
  for(auto it=threadpool.begin(); it!=threadpool.end(); ++it)
    it->join();
}

}
}
