#ifndef HELPER_H
#define HELPER_H

#include <QDesktopWidget>
#include <QApplication>

class Helper : public QObject
{
    Q_OBJECT

public:
    Helper() {
        m_desktopWidget = QApplication::desktop();
    }

    ~Helper() {
        delete m_desktopWidget;
    }

public slots:
    int getScreenWidth()
    {
// Giving a mobile-like size if not running on an embedded device
#if defined(Q_OS_SYMBIAN) || defined(Q_WS_MAEMO_5)
        return m_desktopWidget->geometry().width();
#else
        return 360;
#endif

    };
    int getScreenHeight()
    {
#if defined(Q_OS_SYMBIAN) || defined(Q_WS_MAEMO_5)
        return m_desktopWidget->geometry().height();
#else
        return 640;
#endif
    };

    void quit() { exit(0); };

private:
    QDesktopWidget *m_desktopWidget;

};

#endif // HELPER_H
