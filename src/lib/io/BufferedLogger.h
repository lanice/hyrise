#ifndef SRC_LIB_IO_BUFFEREDLOGGER_H
#define SRC_LIB_IO_BUFFEREDLOGGER_H

#include <atomic>
#include <cstdio>
#include <cstring>
#include <mutex>

#include "storage/storage_types.h"
#include "helper/types.h"

namespace hyrise {
namespace io {

class BufferedLogger {
public:
    BufferedLogger(const BufferedLogger&) = delete;
    BufferedLogger &operator=(const BufferedLogger&) = delete;

    static BufferedLogger &getInstance();

    template<typename T>
    void logDictionary(storage::table_id_t table_id,
                       storage::field_t column,
                       const T &value,
                       storage::value_id_t value_id);
    void logValue(tx::transaction_id_t transaction_id,
                  storage::table_id_t table_id,
                  storage::pos_t row,
                  storage::pos_t invalidated_row,
                  uint64_t field_bitmask,
                  const ValueIdList *value_ids);
    void logCommit(tx::transaction_id_t transaction_id);

private:
    BufferedLogger();

    void _append(const char *str, const unsigned int len);
    void _flush();

    FILE *_logfile;
    char *_buffer;
    char *_head;
    char *_tail;
    char *_last_write;
    uint64_t _buffer_size;

    std::mutex _bufferMutex;
    std::mutex _fileMutex;
    std::atomic<int> _writing;
    std::atomic<uint64_t> _size;
};

/*template<>
void BufferedLogger::logDictionary<storage::hyrise_int_t>(storage::table_id_t table_id,
                                                          storage::field_t column,
                                                          const storage::hyrise_int_t &value,
                                                          storage::value_id_t value_id) {
  char entry[90];
  unsigned int len = sprintf(entry, "(d,%u,%lu,%li,%u)", (int)table_id, column, value, value_id);
  _append(entry, len);
}

template<>
void BufferedLogger::logDictionary<storage::hyrise_float_t>(storage::table_id_t table_id,
                                                            storage::field_t column,
                                                            const storage::hyrise_float_t &value,
                                                            storage::value_id_t value_id) {
  char entry[90];
  unsigned int len = sprintf(entry, "(d,%u,%lu,%f,%u)", (int)table_id, column, value, value_id);
  _append(entry, len);
}

template<>
void BufferedLogger::logDictionary<storage::hyrise_string_t>(storage::table_id_t table_id,
                                                             storage::field_t column,
                                                             const storage::hyrise_string_t &value,
                                                             storage::value_id_t value_id) {
  char entry[200];
  unsigned int len = sprintf(entry, "(d,%u,%lu,%s,%u)", (int)table_id, column, value.c_str(), value_id);
  _append(entry, len);
}*/

}
}

#endif // SRC_LIB_IO_BUFFEREDLOGGER_H
