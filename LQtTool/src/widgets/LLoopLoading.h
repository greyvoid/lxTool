#ifndef CLLOOPLOADING_H
#define CLLOOPLOADING_H

#include <QWidget>

class CLLoopLoading : public QWidget
{
    Q_OBJECT
public:
    explicit CLLoopLoading(QWidget *parent = 0);

signals:

public:
    void start(const QString & strTip);
    void stop();



public slots:
    void rotate();

protected:
    void paintEvent(QPaintEvent *paintEvent);

private:
    QString m_strTip;
    QTimer *m_timer;
    unsigned int m_unAngle;
};

#endif // CLLOOPLOADING_H
