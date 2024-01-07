#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

#include <QVector>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>


class Widget : public QOpenGLWidget,public QOpenGLExtraFunctions
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void initializeGL() override;
    void resizeGL(int w,int h) override;
    void paintGL() override;

private slots:

private:
    Ui::Widget *ui;
    QVector<float> vertices;
    QOpenGLShaderProgram shaderprogram;
    QOpenGLBuffer VBO;
    QOpenGLVertexArrayObject VAO;
    QOpenGLTexture texture;
    QOpenGLTexture texture1;
};
#endif // WIDGET_H
