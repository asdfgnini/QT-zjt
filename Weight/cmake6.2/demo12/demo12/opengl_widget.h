#ifndef OPENGL_WIDGET_H
#define OPENGL_WIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QSurfaceFormat>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class OpenGL_Widget : public QOpenGLWidget,QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit OpenGL_Widget(QWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(int w,int h) override;
    void paintGL() override;

private:
    QOpenGLShaderProgram shaderprogram;
    QOpenGLBuffer VBO;
    QOpenGLBuffer IBO;

    QOpenGLVertexArrayObject VAO;
    QVector<float> vertexs;

    QVector<unsigned int> vertex_inx;

};

#endif // OPENGL_WIDGET_H
