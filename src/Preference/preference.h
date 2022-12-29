#ifndef PREFERENCE_H
#define PREFERENCE_H

#include <QSettings>
#include <QWidget>
#include <map>

namespace Ui
{
class Preference;
}

class Preference : public QWidget
{
    Q_OBJECT

  public:
    explicit Preference(QWidget *parent = nullptr);
    explicit Preference(QWidget *parent = nullptr, QSettings *set = nullptr);
    ~Preference();

    void Settings(QSettings *set);

    // private slots:
    //     void on_com_src_currentIndexChanged(const QString &arg1);

    //    void on_com_target_currentIndexChanged(const QString &arg1);

  private:
    Ui::Preference *ui;
    QSettings *settings;
    std::map<QString, QString> _languages;
};

#endif // PREFERENCE_H
