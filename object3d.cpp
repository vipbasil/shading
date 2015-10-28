#include "object3d.h"

Object3D::Object3D()
{
    this->ScaleX = 1;
    this->ScaleY = 1;
    this->ScaleZ = 1;

    this->TranslationX = 0;
    this->TranslationY = 0;
    this->TranslationZ = 0;

    this->RotationX = 0;
    this->RotationY = 0;
    this->RotationZ = 0;


}

QMatrix4x4 Object3D::get_transformations()
{
    QMatrix4x4 result;
    result.setToIdentity();
    //glTexImage2D();
    result.translate(this->TranslationX, this->TranslationY, this->TranslationZ);

    result.rotate(this->RotationX, 1, 0, 0);
    result.rotate(this->RotationY, 0, 1, 0);
    result.rotate(this->RotationZ, 0, 0, 1);

    result.scale(this->ScaleX, this->ScaleY, this->ScaleZ);



    return result;


}

void Object3D::set_color(float R, float G, float B)
{
    unsigned int array_length = this->vertices.size();

    unsigned int i = 0;
    while (i < array_length){
        this->colors[i + 0] = R;
        this->colors[i + 1] = G;
        this->colors[i + 2] = B;

        this->frame_colors[i + 0] = R * 0.9f;
        this->frame_colors[i + 1] = G * 0.9f;
        this->frame_colors[i + 2] = B * 0.9f;
        i += 3;
    }

}

void Object3D::loadObjFile(QString filename)
{
    QFile object(filename);

    if(!object.open(QIODevice::ReadOnly))
    {
        qDebug() << "error read file";
        return;
    }

    while (!object.atEnd())
        record(object.readLine());

    object.close();
     std::vector<float>::iterator it = std::max_element(faces.begin(), faces.end());
     float scale_to = faces[std::distance(faces.begin(), it)];


    ScaleX = 1 / scale_to;
    ScaleY = 1 / scale_to;
    ScaleZ = 1 / scale_to;
}

void Object3D::record(const QString &line)
{
    if(line.at(0) == 'v' && line.at(1) == ' ')      // v ... ... ...
        readlVertices(get_corret_line(line));
    else if(line.at(0) == 'v' && line.at(1) == 't') // vt ... ...
        readTexturCord(get_corret_line(line));
    else if(line.at(0) == 'v' && line.at(1) == 'n') // vn
        readNormals(get_corret_line(line));
    else if(line.at(0) == 'v' && line.at(1) == 'p') // vp
        readSpaceVert(get_corret_line(line));
    else if(line.at(0) == 'f')                      // f
        readFace(get_corret_line(line));
    else if(line.at(0) == 'm')                      // mtl
        readMtl(get_corret_line(line));
    else if(line.at(0) == 'u')
        readUseMtl(get_corret_line(line));

}

void Object3D::readlVertices(const QString &line)
{
    QStringList list;
    QVector3D vertex;

    list = line.split(QRegExp(" ")); // разделяем по пробелу.


    // 0 1 2 3 4 5
    // v x y z w
    vertex.operator [](0) = list.at(1).toFloat(); // считываем 1 значение
    vertex.operator [](1) = list.at(2).toFloat();
    vertex.operator [](2) = list.at(3).toFloat();

    //if(list.size() == 5)            // есть 5 значение, size считает от 1.
      // vertex. push_back(list.at(4).toFloat());
    Vert3D.push_back(vertex);

}

void Object3D::readTexturCord(const QString &line)
{
    // Активируем флаг, сообщающий, что обьект имеет текстурные координаты.
     // Теперь мы знаем, что строки полигонов будут содержать индексы не только
     // вершин, но и текст. координат ("f 1/1 2/2 3/3")
    /* m_texture_coordinates = true;

     QStringList list;
     TexturCord tc;

     list = line.split(QRegExp(" ")); // разделяем по пробелу.


     textures.push_back(list.at(1).toFloat());
     textureUV = list.size() - 1;
     if(list.size() > 2)
        textures.push_back(list.at(2).toFloat());

     if(list.size() > 3)
        textures.push_back(list.at(3).toFloat());

*/

}

void Object3D::readNormals(const QString &line)
{
    m_normal = true; // ("f 1/1/1 2/2/2 3/3/3")

    QStringList list;

    list = line.split(QRegExp(" ")); // разделяем по пробелу.

    normals.push_back(list.at(1).toFloat()); // считываем 1 значение
    normals.push_back(list.at(2).toFloat());
    normals.push_back(list.at(3).toFloat());

}

void Object3D::readSpaceVert(const QString &line)
{
    /* QStringList list;
     SpaceV sv;

     list = line.split(QRegExp(" ")); // разделяем по пробелу.


     sv.u = list.at(1).toFloat();

     if(list.size() > 2)
        sv.v = list.at(2).toFloat();

     if(list.size() > 3)
        sv.w = list.at(3).toFloat();

     space_vertices.push_back(sv);*/
}

void Object3D::readFace(const QString &line)
{
    QStringList list;
    //Face f;

    //f.id_mtl = usemtl.size();

    list = line.split(QRegExp(" "));

    for(int i = 1; i < list.size(); ++i)
    {
        QStringList list_value;
        if(!list.at(i).at(0).isSpace())
        {
            if(i >= 4)
            {
                list_value = list.at(1).split(QRegExp("/"));
                faces.push_back(Vert3D[list_value.at(0).toInt() - 1][0]);
                faces.push_back(Vert3D[list_value.at(0).toInt() - 1][1]);
                faces.push_back(Vert3D[list_value.at(0).toInt() - 1][2]);

                list_value = list.at(i-1).split(QRegExp("/"));
                faces.push_back(Vert3D[list_value.at(0).toInt() - 1][0]);
                faces.push_back(Vert3D[list_value.at(0).toInt() - 1][1]);
                faces.push_back(Vert3D[list_value.at(0).toInt() - 1][2]);

                list_value = list.at(i).split(QRegExp("/"));
                faces.push_back(Vert3D[list_value.at(0).toInt() - 1][0]);
                faces.push_back(Vert3D[list_value.at(0).toInt() - 1][1]);
                faces.push_back(Vert3D[list_value.at(0).toInt() - 1][2]);
            }
            else
            {
                list_value = list.at(i).split(QRegExp("/"));
                faces.push_back(Vert3D[list_value.at(0).toInt() - 1][0]);
                faces.push_back(Vert3D[list_value.at(0).toInt() - 1][1]);
                faces.push_back(Vert3D[list_value.at(0).toInt() - 1][2]);
            }
        }
    }

  /*  if(m_texture_coordinates && !m_normal)
    {
        // f 1/1 2/2 3/3
        QStringList list_value;

        for(int i = 1; i < list.size(); ++i)
        {
            if(!list.at(i).at(0).isSpace())
            {
                if(i >= 4)
                {
                    list_value = list.at(1).split(QRegExp("/"));
                    faces.push_back(vertices[list_value.at(0).toInt()]);
                    //f.id_vertices = get_normal_index(list_value.at(0).toInt(), "id_vertices");
                    //f.id_textur_coordinat = get_normal_index(list_value.at(1).toInt(), "id_textur_coordinat");



                    list_value = list.at(i-1).split(QRegExp("/"));
                    faces.push_back(vertices[list_value.at(0).toInt()]);
                    //f.id_vertices = get_normal_index(list_value.at(0).toInt(), "id_vertices");
                    //f.id_textur_coordinat = get_normal_index(list_value.at(1).toInt(), "id_textur_coordinat");

                   // face.push_back(f);

                    list_value = list.at(i).split(QRegExp("/"));
                    faces.push_back(vertices[list_value.at(0).toInt()]);

                    //f.id_vertices = get_normal_index(list_value.at(0).toInt(), "id_vertices");
                    //f.id_textur_coordinat = get_normal_index(list_value.at(1).toInt(), "id_textur_coordinat");

                    //face.push_back(f);
                }
                else
                {
                    list_value = list.at(i).split(QRegExp("/"));
                    faces.push_back(vertices[list_value.at(0).toInt()]);
                }
            }
        }

    }
    else if(m_texture_coordinates && m_normal)
    {
        // ("f 1/1/1 2/2/2 3/3/3")

        QStringList list_value;

        for(int i = 1; i < list.size(); ++i)
        {
            if(!list.at(i).at(0).isSpace())
            {
                if(i >= 4)
                {
                    list_value = list.at(1).split(QRegExp("/"));

                    f.id_vertices = get_normal_index(list_value.at(0).toInt(), "id_vertices");
                    f.id_textur_coordinat = get_normal_index(list_value.at(1).toInt(), "id_textur_coordinat");
                    f.id_normal = get_normal_index(list_value.at(2).toInt(), "id_normal");

                    face.push_back(f);

                    list_value = list.at(i-1).split(QRegExp("/"));

                    f.id_vertices = get_normal_index(list_value.at(0).toInt(), "id_vertices");
                    f.id_textur_coordinat = get_normal_index(list_value.at(1).toInt(), "id_textur_coordinat");
                    f.id_normal = get_normal_index(list_value.at(2).toInt(), "id_normal");

                    face.push_back(f);

                    list_value = list.at(i).split(QRegExp("/"));

                    f.id_vertices = get_normal_index(list_value.at(0).toInt(), "id_vertices");
                    f.id_textur_coordinat = get_normal_index(list_value.at(1).toInt(), "id_textur_coordinat");
                    f.id_normal = get_normal_index(list_value.at(2).toInt(), "id_normal");

                    face.push_back(f);
                }
                else
                {
                    list_value = list.at(i).split(QRegExp("/"));

                    f.id_vertices = get_normal_index(list_value.at(0).toInt(), "id_vertices");
                    f.id_textur_coordinat = get_normal_index(list_value.at(1).toInt(), "id_textur_coordinat");
                    f.id_normal = get_normal_index(list_value.at(2).toInt(), "id_normal");

                    face.push_back(f);
                }
            }
        }
    }
    else
    {
        for(int i = 1; i < list.size(); ++i)
        {
            if(!list.at(i).at(0).isSpace())
            {
                if(i >= 4)
                {
                    f.id_vertices = get_normal_index(list.at(1).toInt(), "id_vertices");
                    face.push_back(f);

                    f.id_vertices = get_normal_index(list.at(i-1).toInt(), "id_vertices");
                    face.push_back(f);

                    f.id_vertices = get_normal_index(list.at(i).toInt(), "id_vertices");
                    face.push_back(f);
                }
                else
                {
                    f.id_vertices = get_normal_index(list.at(i).toInt(), "id_vertices");

                    face.push_back(f);
                }
            }
        }
    }*/
}

void Object3D::readMtl(const QString &line)
{
    QStringList list;

    list = line.split(QRegExp(" "));

    mtl.push_back(list.at(1));
}

void Object3D::readUseMtl(const QString &line)
{
    QStringList list;

    list = line.split(QRegExp(" "));

    usemtl.push_back(list.at(1));
}

QString Object3D::get_corret_line(const QString &line)
{
    QString new_line;

    for(int i = 0; i < line.size(); ++i)
    {
        if(isblank(line.at(i)))
        {
            new_line.push_back(' ');

            while(isblank(line.at(i)) && isblank(line.at(i+1)))
                ++i;
        }
        else
            new_line.push_back(line.at(i));
    }

    return new_line;
}

bool Object3D::isblank(const QChar &ch)
{
    return (ch == ' ' || ch == '\t');
}

int Object3D::get_normal_index(int index, QString name)
{
    /*if(index < 0)
    {
        if(name == "id_vertices")
            return list_vertices.size() - ((index * -1) - 1);
        else if(name == "id_textur_coordinat")
            return textur_coordinates.size() - ((index * -1) - 1);
        else if(name == "id_normal")
            return normals.size() - ((index * -1) - 1);
    }

    return index;*/

}

