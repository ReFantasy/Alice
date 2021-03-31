#ifndef PREFERENCE_H
#define PREFERENCE_H

#include <QWidget>
#include <QSettings>

namespace Ui {
class Preference;
}

class Preference : public QWidget
{
    Q_OBJECT

public:
    explicit Preference(QWidget *parent = nullptr);
    ~Preference();

    void Settings(QSettings *set)
    {
        settings = set;
    }

private:
    Ui::Preference *ui;
    QSettings *settings;

};

#endif // PREFERENCE_H
