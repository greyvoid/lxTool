#ifndef CLPROGRESSINDICATOR_H
#define CLPROGRESSINDICATOR_H

#include <QWidget>
#include <QColor>

///
/// \brief The CLProgressIndicator class 进程指示器
///
class CLProgressIndicator : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int delay READ animationDelay WRITE setAnimationDelay)
    Q_PROPERTY(bool displayedWhenStopped READ isDisplayedWhenStopped WRITE setDisplayedWhenStopped)
    Q_PROPERTY(QColor color READ color WRITE setColor)
public:
    CLProgressIndicator(QWidget* parent = 0);

    int animationDelay() const { return m_nDelay; }

    bool isAnimated () const;

    bool isDisplayedWhenStopped() const;

    const QColor & color() const { return m_color; }

    //virtual QSize sizeHint() const;

    void setBackground(const QString& _icon) {
        m_pixCurrent = QPixmap(_icon);
    }
signals:
    void Finished(void);
public slots:

    void startAnimation();

    void stopAnimation();

    void setAnimationDelay(int delay);

    void setDisplayedWhenStopped(bool state);

    void setColor(const QColor & color);

    void onProgress(short progress) { m_nProgress = progress; }
protected:

    virtual void timerEvent(QTimerEvent * event);
    virtual void paintEvent(QPaintEvent * event);

private:
    QRect rectDraw();
private:

    unsigned int m_unAngle;
    int m_nIdTimer;
    int m_nDelay;
    bool m_bDisplayedWhenStopped;
    QColor m_color;
    short m_nProgress;
    QPixmap m_pixCurrent;
};



#endif 
