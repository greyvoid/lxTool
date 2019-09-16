#ifndef LPICTOOL_H
#define LPICTOOL_H

#include <QObject>

class LPicTool : public QObject
{
    Q_OBJECT
public:
    explicit LPicTool(QObject *parent = 0);
    ~LPicTool();

signals:

public slots:

public:
    static void picToData(QString fromPic,QString toData,QString myformat);

    static void dataToPic(QString fromData,QString toPic,QString myformat);

};

#endif // LPICTOOL_H
