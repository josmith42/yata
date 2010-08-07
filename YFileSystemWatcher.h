#ifndef YFILESYSTEMWATCHER_H
#define YFILESYSTEMWATCHER_H

#include <QObject>

class QFileSystemWatcher;
class QTimer;

class YFileSystemWatcher: public QObject {
    Q_OBJECT
public:
    YFileSystemWatcher(const QString & filename);
    ~YFileSystemWatcher();

signals:
    void fileChanged();
    void fileDeleted();

private slots:
    void on_timer_timeout();
    void on_watcher_fileChanged(const QString & filepath);
private:
    QScopedPointer<QFileSystemWatcher> m_watcher;
    QScopedPointer<QTimer> m_timer;

    enum Status {
        NoActivity,
        FileChanged,
        FileDeleted
    };

    Status m_status;
    QString m_filename;

};

#endif // YFILESYSTEMWATCHER_H