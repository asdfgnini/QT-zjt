#include "opengl_widget.h"

OpenGL_Widget::OpenGL_Widget(QWidget* parent)
    : QOpenGLWidget(parent)
{
    x_rotate = -30.0;
    z_rotate = 100.0;
    x_trans = 0.0;
    y_trans = 0.0;
    zoom = 45.0;
    first_mouse = true;
    leftMousePress = false;
    MidMousePress = false;
}

OpenGL_Widget::~OpenGL_Widget()
{
    makeCurrent();
    glDeleteBuffers(1, &VBO_MeshLine);
    glDeleteVertexArrays(1, &VAO_MeshLine);

    glDeleteBuffers(1, &VBO_Axis);
    glDeleteVertexArrays(1, &VAO_Axis);

    shaderProgram_mesh.release();
    shaderProgram_axis.release();
    doneCurrent();
}

void OpenGL_Widget::initializeGL()
{
    initializeOpenGLFunctions();

    // enable depth_test
    glEnable(GL_DEPTH_TEST);

    // link meshline shaders
    shaderProgram_mesh.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Vertex_mesh.vert");
    shaderProgram_mesh.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Fragment_mesh.frag");
    shaderProgram_mesh.link();

    // link coordinate axis shaders
    shaderProgram_axis.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Vertex_axis.vert");
    shaderProgram_axis.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Fragment_axis.frag");
    shaderProgram_axis.link();

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
    glBindVertexArray(VAO_MeshLine);

    glLineWidth(1.0f);
    glDrawArrays(GL_LINES, 0, vertex_count);

    shaderProgram_axis.bind();
    glBindVertexArray(VAO_Axis);

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

    glGenVertexArrays(1, &VAO_MeshLine);
    glGenBuffers(1, &VBO_MeshLine);

    glBindVertexArray(VAO_MeshLine);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_MeshLine);
    glBufferData(GL_ARRAY_BUFFER, mesh_vertexs.size() * sizeof(float), &mesh_vertexs[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

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

    glGenVertexArrays(1, &VAO_Axis);
    glGenBuffers(1, &VBO_Axis);

    glBindVertexArray(VAO_Axis);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Axis);
    glBufferData(GL_ARRAY_BUFFER, axis_vertexs.size() * sizeof(float), &axis_vertexs[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}
