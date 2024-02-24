#include "mainwindow.h"

#include "glwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  sincSettings();
}

void MainWindow::sincSettings() {
  if (ui->openGLWidget->settings.value("proection_type", "parallel")
          .toString() == "parallel")
    ui->projectionCombo->setCurrentIndex(1);
  else
    ui->projectionCombo->setCurrentIndex(0);
  if (ui->openGLWidget->settings.value("vertex_type", "circle").toString() ==
      "circle")
    ui->vertexCombo->setCurrentIndex(1);
  else if (ui->openGLWidget->settings.value("vertex_type").toString() ==
           "square")
    ui->vertexCombo->setCurrentIndex(2);
  else
    ui->vertexCombo->setCurrentIndex(0);
  if (ui->openGLWidget->settings.value("line_type", "solid").toString() ==
      "solid")
    ui->edgeCombo->setCurrentIndex(0);
  else
    ui->edgeCombo->setCurrentIndex(1);
  ui->edgeSpinner->setValue(
      ui->openGLWidget->settings.value("line_width", 1.0).toDouble());
  ui->vertexSpinner->setValue(
      ui->openGLWidget->settings.value("vertex_size", 1.0).toDouble());
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_projectionCombo_currentIndexChanged(int index) {
  if (index == 0) {
    ui->openGLWidget->proection_type = "central";
  } else if (index == 1) {
    ui->openGLWidget->proection_type = "parallel";
  }
  ui->openGLWidget->update();
}

void MainWindow::on_backgroundButton_clicked() {
  QColor color = QColorDialog::getColor(Qt::yellow, this);
  if (color.isValid()) {
    ui->openGLWidget->background_red = color.redF();
    ui->openGLWidget->background_green = color.greenF();
    ui->openGLWidget->background_blue = color.blueF();
    ui->openGLWidget->background_alpha = color.alphaF();
    ui->openGLWidget->update();
  }
}

void MainWindow::on_vertexCombo_currentIndexChanged(int index) {
  if (index == 0) {
    ui->openGLWidget->vertex_type = "none";
  } else if (index == 1) {
    ui->openGLWidget->vertex_type = "circle";
  } else {
    ui->openGLWidget->vertex_type = "square";
  }
  ui->openGLWidget->update();
}

void MainWindow::on_vertexSpinner_valueChanged(int value) {
  ui->openGLWidget->vertex_size = (double)value;
  ui->openGLWidget->update();
}

void MainWindow::on_vertexButton_clicked() {
  QColor color = QColorDialog::getColor(Qt::yellow, this);
  if (color.isValid()) {
    ui->openGLWidget->vertex_red = color.redF();
    ui->openGLWidget->vertex_green = color.greenF();
    ui->openGLWidget->vertex_blue = color.blueF();
    ui->openGLWidget->vertex_alpha = color.alphaF();
    ui->openGLWidget->update();
  }
}

void MainWindow::on_edgeCombo_currentIndexChanged(int index) {
  if (index == 0) {
    ui->openGLWidget->line_type = "solid";
  } else if (index == 1) {
    ui->openGLWidget->line_type = "dashed";
  }
  ui->openGLWidget->update();
}

void MainWindow::on_edgeSpinner_valueChanged(int value) {
  ui->openGLWidget->line_width = (double)value;
  ui->openGLWidget->update();
}

void MainWindow::on_edgeButton_clicked() {
  QColor color = QColorDialog::getColor(Qt::yellow, this);
  if (color.isValid()) {
    ui->openGLWidget->edge_red = color.redF();
    ui->openGLWidget->edge_green = color.greenF();
    ui->openGLWidget->edge_blue = color.blueF();
    ui->openGLWidget->edge_alpha = color.alphaF();
    ui->openGLWidget->update();
  }
}

void MainWindow::on_bmpButton_clicked() {
  QString file = QFileDialog::getSaveFileName(
      this, "Save as...", "3dViewer.bmp", "BMP (*.bmp);; JPEG (*.jpeg)");
  if (file != "") {
    ui->openGLWidget->grabFramebuffer().save(file, NULL, 100);
  }
}

void MainWindow::on_jpegButton_clicked() {
  QString file = QFileDialog::getSaveFileName(
      this, "Save as...", "3dViewer.jpeg", "JPEG (*.jpeg);; BMP (*.bmp)");
  if (file != "") {
    ui->openGLWidget->grabFramebuffer().save(file, NULL, 100);
  }
}

void MainWindow::on_gifButton_clicked() {
  filepath = QFileDialog::getSaveFileName(this, "Save as...", "3dViewer.gif",
                                          "GIF (*.gif)");
  if (filepath != "") {
    if (timer_ready) {
      ui->openGLWidget->gif = new QGifImage();
      ui->openGLWidget->timer = new QTimer();
    }
    wtimer();
    timer_ready = false;
  }
}

void MainWindow::wtimer() {
  ui->openGLWidget->timer->start(100);
  connect(ui->openGLWidget->timer, SIGNAL(timeout()), this, SLOT(make_gif()));
}

void MainWindow::make_gif() {
  ui->openGLWidget->time++;
  QImage image = ui->openGLWidget->grabFramebuffer().scaled(640, 480);
  ui->openGLWidget->gif->setDefaultDelay(10);
  ui->openGLWidget->gif->addFrame(image);
  if (ui->openGLWidget->time == 50) {
    ui->openGLWidget->time = 0;
    ui->openGLWidget->timer->stop();
    ui->openGLWidget->gif->save(filepath);
    image.QImage::bits();
    timer_ready = true;
    delete ui->openGLWidget->timer;
    delete ui->openGLWidget->gif;
  }
}

void MainWindow::on_rotateX_valueChanged(int value) {
  if (ui->openGLWidget->object) {
    rotate_object(ui->openGLWidget->object,
                  (double)value - ui->openGLWidget->angle_x_last, 0, 0);
    ui->openGLWidget->angle_x_last = (double)value;
    ui->openGLWidget->update();
  }
}

void MainWindow::on_rotateY_valueChanged(int value) {
  if (ui->openGLWidget->object) {
    rotate_object(ui->openGLWidget->object, 0,
                  (double)value - ui->openGLWidget->angle_y_last, 0);
    ui->openGLWidget->angle_y_last = (double)value;
    ui->openGLWidget->update();
  }
}

void MainWindow::on_rotateZ_valueChanged(int value) {
  if (ui->openGLWidget->object) {
    rotate_object(ui->openGLWidget->object, 0, 0,
                  (double)value - ui->openGLWidget->angle_z_last);
    ui->openGLWidget->angle_z_last = (double)value;
    ui->openGLWidget->update();
  }
}

void MainWindow::on_translateX_valueChanged(int value) {
  if (ui->openGLWidget->object) {
    move_object(ui->openGLWidget->object,
                (double)value - ui->openGLWidget->x_last_move, 0, 0);
    ui->openGLWidget->x_last_move = (double)value;
    ui->openGLWidget->update();
  }
}

void MainWindow::on_translateY_valueChanged(int value) {
  if (ui->openGLWidget->object) {
    move_object(ui->openGLWidget->object, 0,
                (double)value - ui->openGLWidget->y_last_move, 0);
    ui->openGLWidget->y_last_move = (double)value;
    ui->openGLWidget->update();
  }
}

void MainWindow::on_translateZ_valueChanged(int value) {
  if (ui->openGLWidget->object) {
    move_object(ui->openGLWidget->object, 0, 0,
                (double)value - ui->openGLWidget->z_last_move);
    ui->openGLWidget->z_last_move = (double)value;
    ui->openGLWidget->update();
  }
}

void MainWindow::on_scale_valueChanged(int value) {
  if (ui->openGLWidget->object) {
    scale_object(ui->openGLWidget->object,
                 (double)value / ui->openGLWidget->scale_last);
    ui->openGLWidget->scale_last = (double)value;
    ui->openGLWidget->update();
  }
}

void MainWindow::on_loadFile_clicked() {
  QString file =
      QFileDialog::getOpenFileName(this, "Upload file ", "", "OBJ (*.obj)");
  if (file != "") {
    ui->fileName->setText(file);
    QFileInfo fileInfo(file);
    QString filename(fileInfo.fileName());
    ui->fileName->setText(filename);
    ui->openGLWidget->upload_file(file);
    ui->lcdVertices->display(
        QString::number(ui->openGLWidget->object->count_of_vertexes));
    ui->lcdEdges->display(
        QString::number(ui->openGLWidget->object->count_of_edges));
  }
}