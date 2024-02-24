#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QMainWindow>
#include <QOpenGLWidget>

extern "C" {
#include "../ddd_viewer.h"
}

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
  void wtimer();
  QString filepath;

 private slots:
  void on_loadFile_clicked();
  void on_projectionCombo_currentIndexChanged(int index);
  void on_backgroundButton_clicked();
  void on_vertexCombo_currentIndexChanged(int index);
  void on_vertexSpinner_valueChanged(int value);
  void on_vertexButton_clicked();
  void on_edgeCombo_currentIndexChanged(int index);
  void on_edgeSpinner_valueChanged(int value);
  void on_edgeButton_clicked();
  void on_rotateX_valueChanged(int value);
  void on_rotateY_valueChanged(int value);
  void on_rotateZ_valueChanged(int value);
  void on_translateX_valueChanged(int value);
  void on_translateY_valueChanged(int value);
  void on_translateZ_valueChanged(int value);
  void on_scale_valueChanged(int value);
  void on_bmpButton_clicked();
  void on_jpegButton_clicked();
  void on_gifButton_clicked();

 private:
  void sincSettings();
  Ui::MainWindow *ui;
  QOpenGLWidget *m_glWidget;
  bool timer_ready = true;

 public slots:
  void make_gif();
};

#endif  // MAINWINDOW_H