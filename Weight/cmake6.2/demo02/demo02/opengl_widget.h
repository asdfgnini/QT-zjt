#ifndef OPENGL_WIDGET_H
#define OPENGL_WIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include <iostream>

class OpenGL_Widget : public QOpenGLWidget,QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit OpenGL_Widget(QWidget *parent = nullptr);
    ~OpenGL_Widget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    QOpenGLShaderProgram shaderProgram;

    QOpenGLBuffer VBO;
    QOpenGLVertexArrayObject VAO;
    QVector<float> vertices;

};

#endif // OPENGL_WIDGET_H
