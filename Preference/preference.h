#ifndef PREFERENCE_H
#define PREFERENCE_H

#include <QWidget>
#include <QSettings>
#include <vector>
#include <memory>
#include "feature.h"

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

    std::vector<std::shared_ptr<StringProcess>> Features()
    {
        std::shared_ptr<StringProcess> rld = std::make_shared<ReplaceLinefeed>();
        features.push_back(rld);
        return features;
    }

private:
    Ui::Preference *ui;
    QSettings *settings;
    std::vector<std::shared_ptr<StringProcess>> features;

};

#endif // PREFERENCE_H
