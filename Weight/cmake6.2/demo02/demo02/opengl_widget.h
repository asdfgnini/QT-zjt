#ifndef OPENGL_WIDGHT_H
#define OPENGL_WIDGHT_H

#include <QMouseEvent>

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include <iostream>
#include <vector>

class OpenGL_Widget : public QOpenGLWidget, QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    OpenGL_Widget(QWidget* parent);
    ~OpenGL_Widget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    //Ʋܱ
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

private:
    QOpenGLShaderProgram shaderProgram_mesh;
    QOpenGLShaderProgram shaderProgram_axis;

    unsigned int VBO_MeshLine;
    unsigned int VAO_MeshLine;

    unsigned int VBO_Axis;
    unsigned int VAO_Axis;

    unsigned int vertex_count;

    float x_rotate;
    float z_rotate;
    float x_trans;
    float y_trans;
    float zoom;

    bool first_mouse;
    bool leftMousePress;
    bool MidMousePress;

    unsigned int draw_meshline(float size, int count);
    void draw_cooraxis(float length);
};
#endif
