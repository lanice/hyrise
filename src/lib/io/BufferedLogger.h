#ifndef SRC_LIB_IO_BUFFEREDLOGGER_H
#define SRC_LIB_IO_BUFFEREDLOGGER_H

#include <atomic>
#include <cstdio>
#include <mutex>

#include "storage/storage_types.h"
#include "helper/types.h"

namespace hyrise {
namespace io {

class BufferedLogger {
public:
    static BufferedLogger &getInstance();

    void logDictionary(const storage::table_id_t table_id,
                       const storage::field_t column,
                       const storage::hyrise_int_t value,
                       const storage::value_id_t value_id);
    void logDictionary(const storage::table_id_t table_id,
                       const storage::field_t column,
                       const storage::hyrise_float_t value,
                       const storage::value_id_t value_id);
    void logDictionary(const storage::table_id_t table_id,
                       const storage::field_t column,
                       const storage::hyrise_string_t &value,
                       const storage::value_id_t value_id);
    void logValue(const tx::transaction_id_t transaction_id,
                  const storage::table_id_t table_id,
                  const storage::pos_t row,
                  const storage::pos_t invalidated_row,
                  const uint64_t field_bitmask,
                  const ValueIdList *value_ids);
    void logCommit(const tx::transaction_id_t transaction_id);

private:
    BufferedLogger();
    BufferedLogger(const BufferedLogger&);
    void operator=(const BufferedLogger&);

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

}
}

#endif // SRC_LIB_IO_BUFFEREDLOGGER_H
