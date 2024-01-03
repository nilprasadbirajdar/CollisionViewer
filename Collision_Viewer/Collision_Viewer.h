#pragma once

#include <QtWidgets/QMainWindow>
#include <QTimer>

#include "ui_Collision_Viewer.h"
#include "openglwidget.h"

class Collision_Viewer : public QMainWindow {
    Q_OBJECT

public:
    Collision_Viewer(QWidget* parent = nullptr);
    ~Collision_Viewer();

private:
    OpenGLWidget* glWidget;
    QTimer* simulationTimer;

    void setupUI();
    void setupSimulation();

private slots:
    void updateSimulation();
};


