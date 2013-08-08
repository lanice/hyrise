#include "io/SimpleLogger.h"

namespace hyrise {
namespace io {

SimpleLogger &SimpleLogger::getInstance() {
    static SimpleLogger instance;
    return instance;
}

void SimpleLogger::logDictionary(const storage::table_id_t table_id,
                                 const storage::field_t column,
                                 const storage::hyrise_int_t value,
                                 const storage::value_id_t value_id) {
    _mutex.lock();
    _logfile << "(d," << table_id << "," << column << "," << value << "," << value_id << ")";
    _mutex.unlock();
}

void SimpleLogger::logDictionary(const storage::table_id_t table_id,
                                 const storage::field_t column,
                                 const storage::hyrise_float_t value,
                                 const storage::value_id_t value_id) {
    _mutex.lock();
    _logfile << "(d," << table_id << "," << column << "," << value << "," << value_id << ")";
    _mutex.unlock();
}

void SimpleLogger::logDictionary(const storage::table_id_t table_id,
                                 const storage::field_t column,
                                 const storage::hyrise_string_t &value,
                                 const storage::value_id_t value_id) {
    _mutex.lock();
    _logfile << "(d," << table_id << "," << column << "," << value << "," << value_id << ")";
    _mutex.unlock();
}

void SimpleLogger::logValue(const tx::transaction_id_t transaction_id,
                            const storage::table_id_t table_id,
                            const storage::pos_t row,
                            const storage::pos_t invalidated_row,
                            const uint64_t field_bitmask,
                            const std::vector<storage::value_id_t> &value_ids) {
    _mutex.lock();
    _logfile << "(v," << transaction_id << "," << table_id << "," << row << "," << invalidated_row << "," << field_bitmask << ",(" << value_ids[0];
    for(auto it = ++value_ids.cbegin(); it != value_ids.cend(); it++)
        _logfile << "," << *it;
    _logfile << "))";
    _mutex.unlock();
}

void SimpleLogger::logCommit(const tx::transaction_id_t transaction_id) {
    _mutex.lock();
    _logfile << "(t," << transaction_id << ")";
    _logfile.flush();
    _mutex.unlock();
}

SimpleLogger::SimpleLogger() {
    _logfile.open("logfile");
}

}
}
