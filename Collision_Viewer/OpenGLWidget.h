#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QVector3D>
#include <QTimer>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

public:
    void updateSimulation();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    QTimer *simulationTimer;
    QVector3D debrisPosition;
    QVector3D debrisVelocity;
    QVector3D ringPosition;
    float ringRadius;

    void drawSaturnRing();
    void drawDebris();
    bool checkCollision();

private slots:
    void updateSimulationSlot();
};

#endif // OPENGLWIDGET_H
