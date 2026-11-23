#include "mainwindow.h"
#include <cmath>
#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QCheckBox>
#include <QLocale>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(560, 540);
    setWindowTitle("Калькулятор ИМТ");
    setWindowIcon(QIcon(":/img/00.png"));

    QWidget* widget_center = new QWidget(this);
    setCentralWidget(widget_center);
    QLabel* label_title = new QLabel("Калькулятор ИМТ", widget_center);
    QFont font_title = label_title->font();
    font_title.setBold(true);
    font_title.setPointSize(16);
    label_title->setFont(font_title);
    label_title->setAlignment(Qt::AlignCenter);

    QLabel* label_name = new QLabel("Имя:", widget_center);
    line_name = new QLineEdit(widget_center);
    line_name->setPlaceholderText("Введите имя");

    QLabel* label_height = new QLabel("Рост в метрах:", widget_center);
    spin_height = new QDoubleSpinBox(widget_center);
    spin_height->setDecimals(2);
    spin_height->setRange(0.50, 2.50);
    spin_height->setSingleStep(0.01);

    QLabel* label_weight = new QLabel("Вес в килограммах:", widget_center);
    QSlider* slider_weight = new QSlider(Qt::Horizontal, widget_center);
    slider_weight->setRange(20, 200);
    spin_weight = new QSpinBox(widget_center);
    spin_weight->setRange(20, 200);
    spin_weight->setReadOnly(true);
    spin_weight->setFixedWidth(60);
    QHBoxLayout* layout_weight = new QHBoxLayout;
    layout_weight->addWidget(slider_weight);
    layout_weight->addWidget(spin_weight);

    QCheckBox* check_help = new QCheckBox("Показать справку", widget_center);
    QLabel* label_help = new QLabel(
        "недостаток веса - меньше 18,5\n"
        "норма - 18,5-24,9\n"
        "избыток - 25-29,9\n"
        "ожирение - 30 и больше", widget_center);
    label_help->setWordWrap(true);
    label_help->hide();

    QGridLayout* layout_form = new QGridLayout;
    layout_form->setHorizontalSpacing(12);
    layout_form->setVerticalSpacing(12);
    layout_form->setColumnStretch(1, 1);
    layout_form->addWidget(label_name, 0, 0);
    layout_form->addWidget(line_name, 0, 1);
    layout_form->addWidget(label_height, 1, 0);
    layout_form->addWidget(spin_height, 1, 1);
    layout_form->addWidget(label_weight, 2, 0);
    layout_form->addLayout(layout_weight, 2, 1);

    QPushButton* button_calc = new QPushButton("Рассчитать", widget_center);

    label_result = new QLabel(widget_center);
    label_result->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layout_main = new QVBoxLayout(widget_center);
    layout_main->setContentsMargins(40, 30, 40, 30);
    layout_main->addWidget(label_title);
    layout_main->addSpacing(20);
    layout_main->addLayout(layout_form);
    layout_main->addWidget(check_help);
    layout_main->addWidget(label_help);
    layout_main->addStretch();
    layout_main->addWidget(button_calc, 0, Qt::AlignCenter);
    layout_main->addWidget(label_result);

    connect(slider_weight, &QSlider::valueChanged, spin_weight, &QSpinBox::setValue);
    connect(check_help, &QCheckBox::toggled, label_help, &QLabel::setVisible);
    connect(button_calc, &QPushButton::clicked, this, &MainWindow::calculateBmi);
}

MainWindow::~MainWindow() = default;

void MainWindow::calculateBmi()
{
    double height = spin_height->value();
    double weight = spin_weight->value();
    double bmi = std::round(weight / (height * height) * 10.0) / 10.0;

    QString category;
    if (bmi < 18.5)
        category = "недостаток веса";
    else if (bmi < 25.0)
        category = "норма";
    else if (bmi < 30.0)
        category = "избыток";
    else
        category = "ожирение";

    QString result = "ИМТ: " + QLocale(QLocale::Russian).toString(bmi, 'f', 1)
                     + " (" + category + ")";
    if (!line_name->text().isEmpty())
        result = line_name->text() + ", ваш " + result;
    label_result->setText(result);
}