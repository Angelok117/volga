#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class QLineEdit;
class QDoubleSpinBox;
class QSpinBox;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    QLineEdit* line_name;
    QDoubleSpinBox* spin_height;
    QSpinBox* spin_weight;
    QLabel* label_result;
};
#endif // MAINWINDOW_H