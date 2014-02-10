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

    //Constructor QMenu(cad d txt q va a mostrar, padre)
    //tr traduce esa cad de txt al idioma deseado
    //El & marca el guion bajo, por ej, &Editar, pone el guion bajo la E
    mnuArchivo_= new QMenu(tr("&Archivo"),this);

    //Inicializamos los menus
    mainMenu_= new QMenuBar(this);

    //-> pq es un puntero
    mainMenu_->addMenu(mnuArchivo_);

    //Colocamos Archivo en la barra de menu
    setMenuBar(mainMenu_);

    //Instanciamos una var para abrir
    actArchivoAbrir_ = new QAction(QIcon(":/new/prefix1/Folder-Open-icon.png"),tr("&Abrir"),this);
    actArchivoAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    mnuArchivo_->addAction(actArchivoAbrir_);

    //Instanciamos una var para guardar
    actArchivoGuardar_ = new QAction(QIcon(":/new/prefix1/Save-icon.png"),tr("&Guardar"),this);
    actArchivoGuardar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_G));
    mnuArchivo_->addAction(actArchivoGuardar_);

    actArchivoSalir_ = new QAction(QIcon(":/new/prefix1/Button-Close-icon.png"),tr("&Salir"),this);
    actArchivoSalir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    mnuArchivo_->addAction(actArchivoSalir_);

    //Submenu Editar
    mnuEditar_ = new QMenu(tr("&Editar"));
    mainMenu_->addMenu(mnuEditar_);

    actEditarDeshacer_ = new QAction(QIcon(":/new/prefix1/undo-icon.png"),tr("&Deshacer"), this);
    actEditarDeshacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
    mnuEditar_->addAction(actEditarDeshacer_);

    actEditarRehacer_ = new QAction(QIcon(":/new/prefix1/Redo-icon.png"),tr("&Rehacer"), this);
    actEditarRehacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    mnuEditar_->addAction(actEditarRehacer_);

    actEditarCortar_ = new QAction(QIcon(":/new/prefix1/Actions-edit-cut-icon.png"),tr("&Cortar"), this);
    actEditarCortar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    mnuEditar_->addAction(actEditarCortar_);

    actEditarCopiar_ = new QAction(QIcon(":/new/prefix1/copy-icon.png"),tr("&Copiar"), this);
    actEditarCopiar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    mnuEditar_->addAction(actEditarCopiar_);

    actEditarPegar_ = new QAction(QIcon(":/new/prefix1/Paste-icon.png"),tr("&Pegar"), this);
    actEditarPegar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    mnuEditar_->addAction(actEditarPegar_);

    //Submenu Formato
    mnuFormato_ = new QMenu(tr("&Formato"));
    mainMenu_->addMenu(mnuFormato_);

    actFormatoFuente_ = new QAction(QIcon(":/new/prefix1/preferences-desktop-font.png"),tr("F&uente"), this);
    actFormatoFuente_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_U));
    mnuFormato_->addAction(actFormatoFuente_);

    //Submenu Ayuda
    mnuAyuda_ = new QMenu(tr("A&yuda"));
    mainMenu_->addMenu(mnuAyuda_);

    actAyudaAcerca_ = new QAction(QIcon(":/new/prefix1/Info-icon.png"),tr("Acerca de"), this);
    actAyudaAcerca_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F1));
    mnuAyuda_->addAction(actAyudaAcerca_);

    //Conectamos las acciones de los menus con nuestros slots (funciones)
    connect(actArchivoAbrir_, SIGNAL(triggered()),this,SLOT(alAbrir()));
    connect(actArchivoGuardar_, SIGNAL(triggered()),this,SLOT(alGuardar()));
    connect(actArchivoSalir_, SIGNAL(triggered()),this,SLOT(alSalir()));
    connect(actEditarCopiar_, SIGNAL(triggered()), txtEditor_, SLOT(copy()));
    connect(actEditarPegar_, SIGNAL(triggered()), txtEditor_, SLOT(paste()));
    connect(actEditarCortar_, SIGNAL(triggered()), txtEditor_, SLOT(cut()));
    connect(actEditarDeshacer_, SIGNAL(triggered()), txtEditor_, SLOT(undo()));
    connect(actEditarRehacer_, SIGNAL(triggered()), txtEditor_, SLOT(redo()));
    connect(actFormatoFuente_, SIGNAL(triggered()), this, SLOT(alFuente()));
    connect(actAyudaAcerca_, SIGNAL(triggered()), this, SLOT(alAcercaDe()));



    //Inicializamos el ToolBar
    mnuToolBar_ = new QToolBar(this);
    mnuToolBar_->setWindowTitle("My super ToolBar");
    addToolBar(mnuToolBar_);

    //TOOLBAR
    actToolBarAbrir_ = new QAction(QIcon(":/new/prefix1/Folder-Open-icon.png"),tr("Abrir"),this);
    mnuToolBar_->addAction(actToolBarAbrir_);
    connect(actToolBarAbrir_, SIGNAL(triggered()), this, SLOT(alAbrir()));

    actToolBarCopiar_ = new QAction(QIcon(":/new/prefix1/copy-icon.png"),tr("Copiar"),this);
    mnuToolBar_->addAction(actToolBarCopiar_);
    connect(actToolBarCopiar_, SIGNAL(triggered()), txtEditor_, SLOT(copy()));

    actToolBarCortar_ = new QAction(QIcon(":/new/prefix1/Actions-edit-cut-icon.png"),tr("Cortar"),this);
    mnuToolBar_->addAction(actToolBarCortar_);
    connect(actToolBarCortar_, SIGNAL(triggered()), txtEditor_, SLOT(cut()));

    actToolBarPegar_ = new QAction(QIcon(":/new/prefix1/Paste-icon.png"),tr("Pegar"),this);
    mnuToolBar_->addAction(actToolBarPegar_);
    connect(actToolBarPegar_, SIGNAL(triggered()), txtEditor_, SLOT(paste()));

//    actToolBarFuente_ = new QAction(tr("Fuente"),this);
    actToolBarFuente_ = new QAction(QIcon(":/new/prefix1/preferences-desktop-font.png"),tr("Fuente"),this);
    mnuToolBar_->addAction(actToolBarFuente_);
    connect(actToolBarFuente_, SIGNAL(triggered()), this, SLOT(alFuente()));

    actToolBarCursiva_ = new QAction(tr("Cursiva"),this);
    mnuToolBar_->addAction(actToolBarCursiva_);
    connect(actToolBarCursiva_, SIGNAL(triggered()), txtEditor_, SLOT(alCursiva()));

}

NotepadWindow::~NotepadWindow()
{
    //Liberamos los recursos
    mainMenu_->deleteLater();
    actArchivoAbrir_->deleteLater();
    actArchivoGuardar_->deleteLater();
    actArchivoSalir_->deleteLater();
    mnuArchivo_->deleteLater();
    actEditarCopiar_->deleteLater();
    actEditarPegar_->deleteLater();
    actEditarDeshacer_->deleteLater();
    actEditarRehacer_->deleteLater();
    mnuEditar_->deleteLater();
    actFormatoFuente_->deleteLater();
    mnuFormato_->deleteLater();

    mnuAyuda_->deleteLater();
    actAyudaAcerca_->deleteLater();

    txtEditor_->deleteLater();

    mnuToolBar_->deleteLater();
    actToolBarAbrir_->deleteLater();
    actToolBarCopiar_->deleteLater();
    actToolBarCortar_->deleteLater();
    actToolBarPegar_->deleteLater();
    actToolBarFuente_->deleteLater();

    actToolBarCursiva_->deleteLater();
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
//        QImage img(":/new/prefix1/libreoffice-oasis-presentation-template.png");
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

void NotepadWindow::alCursiva()
{
    QTextEdit* aux;
    aux = new QTextEdit(this);
    aux->setFontItalic(true);
/*    bool ok=true;
    QFont font = QFontDialog::getFont(xt&ok, txtEditor_->font(), this);
    txtEditor_->setItalic(font);
    //txtEditor_->setFont(QFontDialog::getFont(0, txtEditor_->font()));
    */
}

void NotepadWindow::alAcercaDe()
{
    QMessageBox msg(this);
    msg.setWindowTitle(tr("Acerca de"));
    msg.setInformativeText("NotePad's Aaron (in Qt!) v 1.0");
    msg.addButton("Aceptar",QMessageBox::AcceptRole);

    if (msg.exec())
        close();
}


void NotepadWindow::alSalir()
{
    QMessageBox msg(this);
    msg.setInformativeText("¿Esta seguro de salir?");
    msg.addButton("Si",QMessageBox::YesRole);
    msg.addButton("No",QMessageBox::NoRole);

    if (!msg.exec())
        close();
    //Muestra el valor de salida
//    qDebug() << msg.exec();
}



