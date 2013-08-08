#include "io/BufferedLogger.h"

#include <atomic>
#include <cstring>

#define LOG_BUFFER_SIZE 16384

namespace hyrise {
namespace io {

BufferedLogger &BufferedLogger::getInstance() {
  static BufferedLogger instance;
  return instance;
}

void BufferedLogger::logDictionary(const storage::table_id_t &table_id,
                                   const storage::field_t &column,
                                   const storage::hyrise_int_t &value,
                                   const storage::value_id_t &value_id) {
  char entry[90];
  unsigned int len = sprintf(entry, "(d,%c,%lu,%li,%u)", table_id, column, value, value_id);
  _append(entry, len);
}

void BufferedLogger::logDictionary(const storage::table_id_t &table_id,
                                   const storage::field_t &column,
                                   const storage::hyrise_float_t &value,
                                   const storage::value_id_t &value_id) {
  char entry[90];
  unsigned int len = sprintf(entry, "(d,%c,%lu,%f,%u)", table_id, column, value, value_id);
  _append(entry, len);
}

void BufferedLogger::logDictionary(const storage::table_id_t &table_id,
                                   const storage::field_t &column,
                                   const storage::hyrise_string_t &value,
                                   const storage::value_id_t &value_id) {
  char entry[200];
  unsigned int len = sprintf(entry, "(d,%c,%lu,%s,%u)", table_id, column, value.c_str(), value_id);
  _append(entry, len);
}

void BufferedLogger::logValue(const tx::transaction_id_t &transaction_id,
                              const storage::table_id_t &table_id,
                              const storage::pos_t &row,
                              const storage::pos_t &invalidated_row,
                              const uint64_t &field_bitmask,
                              const std::vector<storage::value_id_t> &value_ids) {
  char entry[200];
  unsigned int len = sprintf(entry, "(v,%li,%c,%lu,%lu,%lu,(%u", transaction_id, table_id, row, invalidated_row, field_bitmask, value_ids[0]);
  for(auto it = ++value_ids.cbegin(); it != value_ids.cend(); ++it)
    len += sprintf(&entry[len], ",%u", *it);
  len += sprintf(&entry[len], "))");
  _append(entry, len);
}

void BufferedLogger::logCommit(const tx::transaction_id_t &transaction_id) {
  char entry[24];
  unsigned int len = sprintf(entry, "(t,%li)", transaction_id);
  _append(entry, len);
  _flush();
}

void BufferedLogger::_append(const char *str, const unsigned int len) {
  char *head = NULL;

  _bufferMutex.lock();
  head = _head;
  _head = _buffer + ((_head - _buffer + len) % LOG_BUFFER_SIZE);
  ++_writing;
  _bufferMutex.unlock();

  if(head + len < _tail) {
    memcpy(head, str, len);
  } else {
    uint64_t part1 = _tail - head;
    uint64_t part2 = len - part1;
    memcpy(head, str, part1);
    memcpy(_buffer, str+part1, part2);
  }

  --_writing;
}

void BufferedLogger::_flush() {
  char *head = NULL;

  _fileMutex.lock();

  _bufferMutex.lock();
  while(_writing > 0);
  head = _head;
  _bufferMutex.unlock();

  if(head > _last_write) {
    fwrite(_last_write, sizeof(char), head-_last_write, _logfile);
  } else if(head < _last_write) {
    uint64_t part1 = _tail - _last_write;
    uint64_t part2 = head - _buffer;
    fwrite(_last_write, sizeof(char), part1, _logfile);
    fwrite(_buffer, sizeof(char), part2, _logfile);
  } else {
    _fileMutex.unlock();
    return;
  }
  _last_write = head;
  fflush(_logfile);

  _fileMutex.unlock();
}

BufferedLogger::BufferedLogger() {
  _logfile = fopen("logfile", "w");

  _buffer_size = LOG_BUFFER_SIZE;
  _buffer = (char*) malloc(_buffer_size);
  _head = _buffer;
  _last_write = _buffer;
  _tail = _buffer + _buffer_size;
  _writing = 0;
}

}
}
