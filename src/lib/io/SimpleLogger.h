#ifndef SRC_LIB_IO_SIMPLELOGGER_H
#define SRC_LIB_IO_SIMPLELOGGER_H

#include <fstream>
#include <mutex>
#include <string>

#include "helper/types.h"

namespace hyrise {
namespace io {

class SimpleLogger {
public:
    static SimpleLogger &getInstance();

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
                  const std::vector<storage::value_id_t> &value_ids);
    void logCommit(const tx::transaction_id_t transaction_id);

private:
    SimpleLogger();
    SimpleLogger(const SimpleLogger&);
    void operator=(const SimpleLogger&);

    std::ofstream _logfile;
    std::mutex _mutex;
};

}
}

#endif // SRC_LIB_IO_SIMPLELOGGER_H
