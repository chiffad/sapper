#pragma once

#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)

#include <QDebug>
#include <QString>

#define LOG_DBG (qDebug().noquote()<< '<' << "DBG" << '>' \
                           << '<' << __FILENAME__ << ':' << __LINE__ << "><" << __FUNCTION__ << ">: ")

