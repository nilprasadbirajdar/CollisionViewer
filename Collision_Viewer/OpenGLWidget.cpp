#include "stdafx.h"
#include "OpenGLWidget.h"
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

OpenGLWidget::OpenGLWidget(QWidget* parent) : QOpenGLWidget(parent) {
    debrisPosition = QVector3D(0.0f, 0.0f, 0.0f);
    debrisVelocity = QVector3D(0.02f, 0.0f, 0.0f);
    ringPosition = QVector3D(0.0f, 0.0f, 0.0f);
    ringRadius = 1.0f;

    simulationTimer = new QTimer(this);
    connect(simulationTimer, SIGNAL(timeout()), this, SLOT(updateSimulationSlot()));
    simulationTimer->start(16); // Update every 16 milliseconds (60 FPS)
}

OpenGLWidget::~OpenGLWidget() {}

void OpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
}

void OpenGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void OpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawSaturnRing();
    drawDebris();
}

void OpenGLWidget::updateSimulationSlot() {
    updateSimulation();
    update();
}

void OpenGLWidget::updateSimulation() {
    // Update debris position based on velocity
    debrisPosition += debrisVelocity;

    // Check for collision with Saturn's ring
    if (checkCollision()) {
        // Implement collision response (e.g., change direction)
        debrisVelocity *= -1.0;
    }
}

void OpenGLWidget::drawSaturnRing() {
    QOpenGLShaderProgram program;
    program.addShaderFromSourceCode(QOpenGLShader::Vertex,
        "attribute vec2 posAttr;\n"
        "varying vec4 color;\n"
        "uniform mat4 matrix;\n"
        "void main() {\n"
        "   gl_Position = matrix * vec4(posAttr, 0.0, 1.0);\n"
        "   color = vec4(0.6, 0.6, 0.6, 1.0);\n"
        "}\n");

    program.addShaderFromSourceCode(QOpenGLShader::Fragment,
        "varying vec4 color;\n"
        "void main() {\n"
        "   gl_FragColor = color;\n"
        "}\n");

    program.link();
    program.bind();

    QMatrix4x4 matrix;
    matrix.ortho(-1.5, 1.5, -1.5, 1.5, -1.0, 1.0); // Adjust projection matrix based on your scene

    program.setUniformValue("matrix", matrix);

    GLfloat vertices[] = {
        0.0f, -ringRadius,
        0.0f, ringRadius
        // Add more vertices to create a ring shape
    };

    glVertexAttribPointer(program.attributeLocation("posAttr"), 2, GL_FLOAT, GL_FALSE, 0, vertices);
    program.enableAttributeArray(program.attributeLocation("posAttr"));
    glDrawArrays(GL_LINES, 0, 2); // Adjust based on the number of vertices

    program.disableAttributeArray(program.attributeLocation("posAttr"));
    program.release();
}

void OpenGLWidget::drawDebris() {
    QOpenGLShaderProgram program;
    program.addShaderFromSourceCode(QOpenGLShader::Vertex,
        "attribute vec2 posAttr;\n"
        "varying vec4 color;\n"
        "uniform mat4 matrix;\n"
        "void main() {\n"
        "   gl_Position = matrix * vec4(posAttr, 0.0, 1.0);\n"
        "   color = vec4(1.0, 0.0, 0.0, 1.0);\n" // Red color for debris
        "}\n");

    program.addShaderFromSourceCode(QOpenGLShader::Fragment,
        "varying vec4 color;\n"
        "void main() {\n"
        "   gl_FragColor = color;\n"
        "}\n");

    program.link();
    program.bind();

    QMatrix4x4 matrix;
    matrix.translate(debrisPosition);

    program.setUniformValue("matrix", matrix);

    GLfloat vertices[] = {
        -0.1f, -0.1f,
        0.1f, -0.1f,
        0.1f, 0.1f,
        -0.1f, 0.1f
    };

    glVertexAttribPointer(program.attributeLocation("posAttr"), 2, GL_FLOAT, GL_FALSE, 0, vertices);
    program.enableAttributeArray(program.attributeLocation("posAttr"));
    glDrawArrays(GL_QUADS, 0, 4);

    program.disableAttributeArray(program.attributeLocation("posAttr"));
    program.release();
}

bool OpenGLWidget::checkCollision() {
    // Simple collision check based on distance between debris and the center of the ring
    float distance = QVector3D(debrisPosition - ringPosition).length();
    return distance < ringRadius;
}
