#ifndef MYLALBEL_H
#define MYLALBEL_H

#include <QLabel>

class myLabel : public QLabel
{
    Q_OBJECT
    public:
    myLabel(QWidget * parent = 0 );
    ~myLabel(){}

    QString getFileName() const;
    void setFileName(const QString &value);

signals:
    void clicked();
    void clickFile();

public slots:
    void slotClicked();

    protected:
    void mousePressEvent ( QMouseEvent * event ) ;

private:
    QString fileName;

};

#endif // MYLALBEL_H
