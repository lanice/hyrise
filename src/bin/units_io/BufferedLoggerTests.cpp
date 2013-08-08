#include "testing/test.h"
#include "io/BufferedLogger.h"

#include <thread>
#include <vector>

namespace hyrise {
namespace io {

class BufferedLoggerTests : public ::hyrise::Test {};

void bufferedLoggerTestWorker(uint64_t tx) {
  BufferedLogger::getInstance().logDictionary('a', 1, (int64_t)2, 3);
  BufferedLogger::getInstance().logDictionary('a', 1, 2.0f, 3);
  BufferedLogger::getInstance().logDictionary('a', 1, "zwei", 3);
  BufferedLogger::getInstance().logValue(tx,'a',2,3,4,{5,6,7});
  BufferedLogger::getInstance().logCommit(tx);
}

TEST_F(BufferedLoggerTests, simple_log_test) {
  std::vector<std::thread> threadpool;
  uint64_t tx = 1;
  for(int i=0; i<100; i++)
    threadpool.push_back(std::thread(bufferedLoggerTestWorker, tx++));
  for(auto it=threadpool.begin(); it!=threadpool.end(); ++it)
    it->join();
}

}
}
