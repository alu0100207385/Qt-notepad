#include "notepadwindow.h"

NotepadWindow::NotepadWindow(QWidget *parent)
    : QMainWindow(parent)
{

    //Establecemos el tamaño inicial de la ventana
     this->setGeometry(30, 30, 800, 600);

    //Establecemos el título de la ventana
    this->setWindowTitle(tr("Super editor de texto"));

    //Instanciamos en la var
    txtEditor_ = new QPlainTextEdit(this);
    //No hay necesidad de librar memoria, Qt lo hace por nosotros

    //Colocas en el centro lo q hemos creado
    setCentralWidget(txtEditor_);

    //Inicializamos los menus
    mainMenu_= new QMenuBar(this);

    //Constructor QMenu(cad d txt q va a mostrar, padre)
    //tr traduce esa cad de txt al idioma deseado
    //El & marca el guion bajo, por ej, &Editar, pone el guion bajo la E
    mnuArchivo_= new QMenu(tr("&Archivo"),this);

    //-> pq es un puntero
    mainMenu_->addMenu(mnuArchivo_);

    //Colocamos Archivo en la barra de menu
    setMenuBar(mainMenu_);

    //Instanciamos una var para abrir
    actArchivoAbrir_ = new QAction(tr("&Abrir"),this);
    actArchivoAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    mnuArchivo_->addAction(actArchivoAbrir_);

    //Instanciamos una var para guardar
    actArchivoGuardar_ = new QAction(tr("&Guardar"),this);
    actArchivoGuardar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_G));
    mnuArchivo_->addAction(actArchivoGuardar_);

    mnuEditar_ = new QMenu(tr("&Editar"));
    mainMenu_->addMenu(mnuEditar_);

    actEditarCopiar_ = new QAction(tr("&Copiar"), this);
    actEditarCopiar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    mnuEditar_->addAction(actEditarCopiar_);

    actEditarPegar_ = new QAction(tr("&Pegar"), this);
    actEditarPegar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    mnuEditar_->addAction(actEditarPegar_);

    mnuFormato_ = new QMenu(tr("&Formato"));
    mainMenu_->addMenu(mnuFormato_);

    actFormatoFuente_ = new QAction(tr("&Fuente"), this);
    mnuFormato_->addAction(actFormatoFuente_);

    //Conectamos las acciones de los menus con nuestros slots (funciones)
    connect(actArchivoAbrir_, SIGNAL(triggered()),this,SLOT(alAbrir()));
    connect(actArchivoGuardar_, SIGNAL(triggered()),this,SLOT(alGuardar()));
    connect(actEditarCopiar_, SIGNAL(triggered()), txtEditor_, SLOT(copy()));
    connect(actEditarPegar_, SIGNAL(triggered()), txtEditor_, SLOT(paste()));
    connect(actFormatoFuente_, SIGNAL(triggered()), this, SLOT(alFuente()));


}

NotepadWindow::~NotepadWindow()
{
    //Liberamos los recursos
    mainMenu_->deleteLater();
    actArchivoAbrir_->deleteLater();
    actArchivoGuardar_->deleteLater();
    mnuArchivo_->deleteLater();
    actEditarCopiar_->deleteLater();
    actEditarPegar_->deleteLater();
    mnuEditar_->deleteLater();
    actFormatoFuente_->deleteLater();
    mnuFormato_->deleteLater();
    txtEditor_->deleteLater();
}


void NotepadWindow::alAbrir()
{
    //Mostramos un dialogo de apertura de ficheros y almacenamos
    //la selecciones (ruta) en
    QString nombreArchivo;
    nombreArchivo= QFileDialog::getOpenFileName(this, tr("Abrir archivo de texto plano"),
                                "",tr("Archivos de texto plano (*.txt)"));

    //Comprobamos si el user selecciono un archivo o pulso cancelar
    if (nombreArchivo != "")
    {
        QFile archivo;
        archivo.setFileName(nombreArchivo);
        if (archivo.open(QFile::ReadOnly))
        {
            //Si se pudo abrrir el archivo, lo leemos y lo colocamos
            txtEditor_->setPlainText(archivo.readAll());

            //Se cierra el fichero
            archivo.close();
        }
    }

}

void NotepadWindow::alGuardar()
{
    //Mostramos un dialogo de guardado de ficheros y almacenamos
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getSaveFileName(this,
                                                 tr("Guardar archivo de texto plano"),
                                                 "",
                                                 tr("Archivos de texto plano (*.txt)"));
    if (nombreArchivo!="")
    {
        //Intentamos abrir el archivo
        QFile archivo;
        archivo.setFileName(nombreArchivo + ".txt");
        if (archivo.open(QFile::WriteOnly | QFile::Truncate))
        {
            //Si se pudo abrir el archivo, escribimos el contenido del editor
            archivo.write(txtEditor_->toPlainText().toUtf8());

            //Se cierra el fichero
            archivo.close();
        }
    }
}

void NotepadWindow::alFuente()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, txtEditor_->font(), this);
    if (ok)
    {
        // Si el usuario hizo click en OK, se establece la fuente seleccionada
        txtEditor_->setFont(font);
    }
}

