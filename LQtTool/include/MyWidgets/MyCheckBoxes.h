#ifndef MYCHECKBOX_H
#define MYCHECKBOX_H

#include <QCheckBox>
#include <QPaintEvent>
#define SPACE_TEXT 5
class MyCheckBox : public QWidget
{
    Q_OBJECT
public:
    explicit MyCheckBox(QWidget * parent = 0);
    explicit MyCheckBox(const QString & text, QWidget * parent = 0);
    explicit MyCheckBox(const QString &strText, QString strImgBg, QString strImgChecked, QWidget *parent = 0);
    ~MyCheckBox();

public:
    void setChecked(bool bChecked);

    bool isChecked()
    {
        return m_bChecked;
    }

protected:
    void paintEvent(QPaintEvent *e);

    //void event(QEvent *e);

    void mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);
signals:
    void clicked(bool);

public slots:

private:
    void init();

private:
    QRect m_RectImg;
    QString m_strText;
    bool m_bChecked;
    QString m_strImgBg;
    QString m_strImgChecked;
};

#endif // MYCHECKBOX_H
