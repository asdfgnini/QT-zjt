#ifndef OPENGL_WIDGET_H
#define OPENGL_WIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QTimer>
#include <QTime>
#include <QtMath>

class opengl_widget : public QOpenGLWidget,QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit opengl_widget(QWidget *parent = nullptr);
    ~opengl_widget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w,int h) override;


private:
    QOpenGLShaderProgram shaderProgram;

    QOpenGLBuffer VBO;

    QOpenGLVertexArrayObject VAO;
    QVector<float> vertices;
    QOpenGLTexture texture;
    QOpenGLTexture texture01;
    QTimer timer;

    QVector<QVector3D> cubePositions;

};

#endif // OPENGL_WIDGET_H
