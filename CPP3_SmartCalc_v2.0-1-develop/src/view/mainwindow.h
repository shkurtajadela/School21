#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void switchPage();
  void quit();
  void resetIcons();

 private:
  Ui::MainWindow *ui;
  void connectSignals();
  void setDefaultSizes();
};
#endif  // MAINWINDOW_H
