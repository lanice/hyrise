#include "io/SimpleLogger.h"

namespace hyrise {
namespace io {

SimpleLogger &SimpleLogger::getInstance() {
    static SimpleLogger instance;
    return instance;
}

void SimpleLogger::logValue(const tx::transaction_id_t transaction_id,
                            const storage::table_id_t table_id,
                            const storage::pos_t row,
                            const storage::pos_t invalidated_row,
                            const uint64_t field_bitmask,
                            const ValueIdList *value_ids) {
    _mutex.lock();
    _logfile << "(v," << (int)transaction_id << "," << (int)table_id << "," << (int)row << "," << (int)invalidated_row << "," << field_bitmask << ",(";
    if(value_ids != nullptr) {
        _logfile << (*value_ids)[0].valueId;
        for(auto it = ++value_ids->cbegin(); it != value_ids->cend(); it++)
            _logfile << "," << it->valueId;
    }
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
