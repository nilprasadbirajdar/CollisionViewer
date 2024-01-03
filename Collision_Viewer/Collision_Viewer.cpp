#include "stdafx.h"
#include "Collision_Viewer.h"
#include "OpenGLWidget.h"

Collision_Viewer::Collision_Viewer(QWidget* parent) : QMainWindow(parent) {
    setupUI();
    setupSimulation();
}

Collision_Viewer::~Collision_Viewer() {}

void Collision_Viewer::setupUI() {
    glWidget = new OpenGLWidget(this);
    setCentralWidget(glWidget);
}

void Collision_Viewer::setupSimulation() {
    simulationTimer = new QTimer(this);
    connect(simulationTimer, SIGNAL(timeout()), this, SLOT(updateSimulation()));
    simulationTimer->start(3); // Update every 16 milliseconds (60 FPS)
}

void Collision_Viewer::updateSimulation() {
    // Update simulation logic here
    glWidget->updateSimulation(); // Call the simulation update directly
}
