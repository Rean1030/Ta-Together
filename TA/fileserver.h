#ifndef FILESERVER_H
#define FILESERVER_H

#include <QObject>
#include <QStandardPaths>

class FileServer : public QObject
{
    Q_OBJECT

public:
    explicit FileServer(QObject *parent = 0);

signals:

public slots:

};

#endif // FILESERVER_H
