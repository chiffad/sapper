#pragma once

#ifdef DEBUG_ON
#include <iostream>
#include <sstream>
#include <QDebug>
#include <QString>

namespace sapper
{

class logger_t
{
public:
  enum class LEVEL {trace, debug, warning, error, fatal};

  logger_t(LEVEL l, const char *file, int line, const char *func);

  ~logger_t()
  {
    qDebug()<<ss.str().c_str();
  }

  template <typename T>
  logger_t& operator<<([[maybe_unused]] const T& value)
  {
    ss<<value;
    return *this;
  }

  template <typename T>
  logger_t& operator<<([[maybe_unused]] const T* value)
  {
    ss<<value;
    return *this;
  }

private:
  std::stringstream ss;
};

template <typename os_t, typename T>
os_t& operator<<(os_t& os, [[maybe_unused]] const std::vector<T> &values)
{
  for(auto v : values) os<<" "<<v;
  return os;
}

template <typename os_t>
os_t& operator<<(os_t& os, [[maybe_unused]] logger_t::LEVEL l)
{
  switch(l)
  {
    case logger_t::LEVEL::trace  : return os<<"TRACE";
    case logger_t::LEVEL::debug  : return os<<"DBG"  ;
    case logger_t::LEVEL::warning: return os<<"WARN" ;
    case logger_t::LEVEL::error  : return os<<"ERR"  ;
    case logger_t::LEVEL::fatal  : return os<<"FATAL";
  }
  return os;
}

inline logger_t::logger_t([[maybe_unused]] LEVEL l, [[maybe_unused]] const char *file, [[maybe_unused]] int line, [[maybe_unused]] const char *func)
{
  ss<<"<"<<l<<"><"<<file<<"::"<<line<<"><"<<func<<"> ";
}

#define LOGGER_FILENAME (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)

#define LOG_DBG \
   logger_t(logger_t::LEVEL::debug, LOGGER_FILENAME, __LINE__, __FUNCTION__)

} //namespace sapper


#else
namespace sapper
{

struct logger_t
{
  template <typename T>
  logger_t& operator<<(const T&)
  {
    return *this;
  }

  template <typename T>
  logger_t& operator<<(const T*)
  {
    return *this;
  }
};

#define LOG_DBG \
        logger_t()
}//namespace sapper
#endif
