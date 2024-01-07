#include "opengl_widget.h"

OpenGL_Widget::OpenGL_Widget(QWidget* parent)
    : QOpenGLWidget(parent)
    , VBO_MeshLine(QOpenGLBuffer::VertexBuffer)
    , VBO_Axis(QOpenGLBuffer::VertexBuffer)
{
    x_rotate = -30.0;
    z_rotate = 100.0;
    x_trans = 0.0;
    y_trans = 0.0;
    zoom = 45.0;
    first_mouse = true;
    leftMousePress = false;
    MidMousePress = false;

    //抗锯齿
    QSurfaceFormat format;
    format.setAlphaBufferSize(24);  //设置alpha缓冲大小
    format.setVersion(3,3);         //设置版本号
    format.setSamples(10);          //设置重采样次数，用于反走样
    //...
    this->setFormat(format);

}

OpenGL_Widget::~OpenGL_Widget()
{

}

void OpenGL_Widget::initializeGL()
{
    this->initializeOpenGLFunctions();

    // enable depth_test
    this->glEnable(GL_DEPTH_TEST);

    // link meshline shaders
    if(!shaderProgram_mesh.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Vertex_mesh.vert"))
    {
        qDebug() <<"ERROR:" << shaderProgram_mesh.log();
    }
    if(!shaderProgram_mesh.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Fragment_mesh.frag"))
    {
        qDebug() <<"ERROR:" << shaderProgram_mesh.log();
    }

    if(!shaderProgram_mesh.link())
    {
        qDebug() <<"ERROR:" << shaderProgram_mesh.log();
    }

    // link coordinate axis shaders
    if(!shaderProgram_axis.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Vertex_axis.vert"))
    {
        qDebug() <<"ERROR:" << shaderProgram_axis.log();
    }
    if(!shaderProgram_axis.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Fragment_axis.frag"))
    {
    qDebug() <<"ERROR:" << shaderProgram_axis.log();
    }
    if(!shaderProgram_axis.link())
    {
        qDebug() <<"ERROR:" << shaderProgram_axis.log();
    }

    vertex_count = draw_meshline(1.0, 10);
    draw_cooraxis(1.0);
}

void OpenGL_Widget::paintGL()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 projection, view, model;
    projection.perspective(zoom, (float)width() / (float)height(), 1.0f, 100.0f);

    view.lookAt(QVector3D(0.0, 0.0, 10.0), QVector3D(0.0, 0.0, 1.0), QVector3D(0.0, 1.0, 0.0));

    model.translate(x_trans, y_trans, 0.0);
    model.rotate(x_rotate, 1.0, 0.0, 0.0);
    model.rotate(z_rotate, 0.0, 0.0, 1.0);

    shaderProgram_mesh.bind();
    shaderProgram_mesh.setUniformValue("projection", projection);
    shaderProgram_mesh.setUniformValue("view", view);
    shaderProgram_mesh.setUniformValue("model", model);

    shaderProgram_axis.bind();
    shaderProgram_axis.setUniformValue("projection", projection);
    shaderProgram_axis.setUniformValue("view", view);
    shaderProgram_axis.setUniformValue("model", model);

    shaderProgram_mesh.bind();
    VAO_MeshLine.bind();

    glLineWidth(1.0f);
    glDrawArrays(GL_LINES, 0, vertex_count);

    shaderProgram_axis.bind();
    VAO_Axis.bind();

    glLineWidth(5.0f);
    glDrawArrays(GL_LINES, 0, 6);
}

void OpenGL_Widget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void OpenGL_Widget::mouseMoveEvent(QMouseEvent* event)
{
    static QPoint lastPos;
    auto currentPos = event->pos();
    QPoint deltaPos;

    if (leftMousePress == true)
    {
        if (first_mouse == true)
        {
            lastPos = currentPos;
            first_mouse = false;
        }

        deltaPos = currentPos - lastPos;
        lastPos = currentPos;

        x_rotate = x_rotate + 0.3 * deltaPos.y();
        z_rotate = z_rotate + 0.3 * deltaPos.x();

        if (x_rotate > 30.0f)
            x_rotate = 30.0f;
        if (x_rotate < -120.0f)
            x_rotate = -120.0f;
    }
    else if (MidMousePress == true)
    {
        if (first_mouse == true)
        {
            lastPos = currentPos;
            first_mouse = false;
        }

        deltaPos = currentPos - lastPos;
        lastPos = currentPos;

        x_trans = x_trans + 0.01 * deltaPos.x();
        y_trans = y_trans - 0.01 * deltaPos.y();
    }
    update();
}

void OpenGL_Widget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        first_mouse = true;
        leftMousePress = true;
    }

    else if (event->button() == Qt::MiddleButton)
    {
        first_mouse = true;
        MidMousePress = true;
    }
}

void OpenGL_Widget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        leftMousePress = false;
    }
    else if (event->button() == Qt::MiddleButton)
    {
        MidMousePress = false;
    }
}

void OpenGL_Widget::wheelEvent(QWheelEvent* event)
{
    auto scroll_offest = event->angleDelta().y() / 120;
    zoom = zoom - (float)scroll_offest;

    if (zoom < 10.0f)
    {
        zoom = 10.0f;
    }

    if (zoom > 80.0f)
    {
        zoom = 80.0f;
    }

    update();
}

unsigned int OpenGL_Widget::draw_meshline(float size, int count)
{
    std::vector<float> mesh_vertexs;
    unsigned int vertex_count = 0;

    float start = count * (size / 2);
    float posX = start, posZ = start;

    for (int i = 0; i <= count; ++i)
    {
        mesh_vertexs.push_back(posX);
        mesh_vertexs.push_back(start);
        mesh_vertexs.push_back(0);

        mesh_vertexs.push_back(posX);
        mesh_vertexs.push_back(-start);
        mesh_vertexs.push_back(0);

        mesh_vertexs.push_back(start);
        mesh_vertexs.push_back(posZ);
        mesh_vertexs.push_back(0);

        mesh_vertexs.push_back(-start);
        mesh_vertexs.push_back(posZ);
        mesh_vertexs.push_back(0);

        posX = posX - size;
        posZ = posZ - size;
    }

    VAO_MeshLine.create();
    VAO_MeshLine.bind();

    VBO_MeshLine.create();
    VBO_MeshLine.bind();

    VBO_MeshLine.allocate(mesh_vertexs.data(),(int)sizeof(float)*mesh_vertexs.size());

    shaderProgram_mesh.setAttributeBuffer("aPos",GL_FLOAT,0,3,sizeof(float)*3);
    shaderProgram_mesh.enableAttributeArray("aPos");


    vertex_count = mesh_vertexs.size() / 3;

    return vertex_count;
}

void OpenGL_Widget::draw_cooraxis(float length)
{
    std::vector<float> axis_vertexs(36, 0.0);
    axis_vertexs[3] = 1.0;
    axis_vertexs[9] = 1.0;
    axis_vertexs[16] = 1.0;
    axis_vertexs[22] = 1.0;
    axis_vertexs[29] = 1.0;
    axis_vertexs[35] = 1.0;

    axis_vertexs[6] = length;
    axis_vertexs[19] = length;
    axis_vertexs[32] = length;

    VAO_Axis.create();
    VAO_Axis.bind();

    VBO_Axis.create();
    VBO_Axis.bind();

    VBO_Axis.allocate(axis_vertexs.data(),(int)sizeof(float)*axis_vertexs.size());

    shaderProgram_axis.setAttributeBuffer("aPos",GL_FLOAT,0,3,sizeof(float) * 6);
    shaderProgram_axis.enableAttributeArray("aPos");

    shaderProgram_axis.setAttributeBuffer("aColor",GL_FLOAT,sizeof(float)*3,3,sizeof(float) * 6);
    shaderProgram_axis.enableAttributeArray("aColor");

}
