#include "preference.h"
#include "ui_preference.h"

Preference::Preference(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Preference)
{
    ui->setupUi(this);
}

Preference::~Preference()
{
    delete ui;
}
