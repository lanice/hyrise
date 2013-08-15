#include "io/BufferedLogger.h"

namespace hyrise {
namespace io {

constexpr uint64_t LOG_BUFFER_SIZE = 16384;
constexpr char LOG_FILE_NAME[] = "logfile";

BufferedLogger &BufferedLogger::getInstance() {
  static BufferedLogger instance;
  return instance;
}

void BufferedLogger::logValue(const tx::transaction_id_t transaction_id,
                              const storage::table_id_t table_id,
                              const storage::pos_t row,
                              const storage::pos_t invalidated_row,
                              const uint64_t field_bitmask,
                              const ValueIdList *value_ids) {
  char entry[200];
  unsigned int len = sprintf(entry, "(v,%li,%u,%lu,%lu,%lu,(", transaction_id, (int)table_id, row, invalidated_row, field_bitmask);
  if(value_ids != nullptr) {
    len += sprintf(&entry[len], "%u", (*value_ids)[0].valueId);
    for(auto it = ++value_ids->cbegin(); it != value_ids->cend(); ++it)
      len += sprintf(&entry[len], ",%u", it->valueId);
  }
  len += sprintf(&entry[len], "))");
  _append(entry, len);
}

void BufferedLogger::logCommit(const tx::transaction_id_t transaction_id) {
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

  uint64_t s = _size.fetch_add(len);
  if(s > LOG_BUFFER_SIZE/2)
    _flush();
}

void BufferedLogger::_flush() {
  char *head = NULL;
  uint64_t written = 0;

  _fileMutex.lock();

  _bufferMutex.lock();
  while(_writing > 0);
  head = _head;
  _bufferMutex.unlock();

  if(head > _last_write) {
    written = head - _last_write;
    fwrite(_last_write, sizeof(char), written, _logfile);
  } else if(head < _last_write) {
    uint64_t part1 = _tail - _last_write;
    uint64_t part2 = head - _buffer;
    written = part1 + part2;
    fwrite(_last_write, sizeof(char), part1, _logfile);
    fwrite(_buffer, sizeof(char), part2, _logfile);
  } else {
    _fileMutex.unlock();
    return;
  }
  _size -= written;
  _last_write = head;
  fflush(_logfile);

  _fileMutex.unlock();
}

BufferedLogger::BufferedLogger() {
  _logfile = fopen(LOG_FILE_NAME, "w");

  _buffer_size = LOG_BUFFER_SIZE;
  _buffer = (char*) malloc(_buffer_size);
  _head = _buffer;
  _last_write = _buffer;
  _tail = _buffer + _buffer_size;
  _writing = 0;
  _size = 0;
}

}
}
