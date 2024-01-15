#ifndef UTILS_PARSEUTILS_H_
#define UTILS_PARSEUTILS_H_

#include <QString>
#include <QDateTime>
#include <QDebug>

#include <cstdlib>

/// take the timestamp used by S3 and turn it into QDateTime
QDateTime timeFromS3Time(QString str);

/// take a timestamp and convert it into an S3 timestamp
QString timeToS3Time(QDateTime time);

#endif // !UTILS_PARSEUTILS_H_
