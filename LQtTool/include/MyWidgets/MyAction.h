#ifndef MY_ACTION_H
#define MY_ACTION_H

#include <QAction>


class CMyAction: public QAction
{
    Q_OBJECT
public:
    CMyAction(QObject *parent = 0);
    CMyAction(const QString & text, QObject * parent = 0);
    CMyAction(const QIcon & icon, const QString & text, QObject * parent = 0);
private:

};


///
/// \brief The Menu class
///





#endif // MY_ACTION_H
