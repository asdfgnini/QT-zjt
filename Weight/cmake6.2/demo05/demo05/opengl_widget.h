#ifndef OPENGL_WIDGET_H
#define OPENGL_WIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShader>
#include <QOpenGLTexture>

#include <iostream>
#include <vector>
#include <QMouseEvent>

class opengl_widget : public QOpenGLWidget,QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit opengl_widget(QWidget *parent = nullptr);
    ~opengl_widget();

protected:
    void initializeGL()override;
    void paintGL()override;
    void resizeGL(int width, int height)override;

    //Ʋܱ
    void mouseMoveEvent(QMouseEvent* event)override;
    void mousePressEvent(QMouseEvent* event)override;
    void mouseReleaseEvent(QMouseEvent* event)override;
    void wheelEvent(QWheelEvent* event)override;

private:
    QOpenGLShaderProgram shaderProgram;
    QOpenGLTexture* testTexture;

    unsigned int VBO;
    unsigned int VAO;

    float x_rotate;
    float z_rotate;
    float x_trans;
    float y_trans;
    float zoom;

    bool first_mouse;
    bool leftMousePress;
    bool MidMousePress;

};

#endif // OPENGL_WIDGET_H
