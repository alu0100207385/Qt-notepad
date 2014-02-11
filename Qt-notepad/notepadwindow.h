#ifndef NOTEPADWINDOW_H
#define NOTEPADWINDOW_H

#include <QMainWindow>

//Esta clase permite permite crear texto plano en una ventana
#include <QPlainTextEdit>
#include <QTextEdit>

//Introducimos las librerias de los menus
#include <QMenu>
#include <QMenuBar>

//Menu: ToolBar
#include <QToolBar>

//Acciones
#include <QAction>

//Permite abrir archivos (cadenas)
#include <QFileDialog>

#include <QFile>
#include <QFontDialog>
//#include <QFont>
#include <QClipboard>
#include <QKeySequence>

//Lo utilizamos cm ventana emergente
#include <QMessageBox>

//COntrol debug: controlar valores de salida
#include <QDebug>

class NotepadWindow : public QMainWindow
{
    Q_OBJECT

    //Slots son las funciones q deseamos q se ejecuten al pulsar
    //un boton (programcion orientada a eventos)
private slots:
    void alAbrir();
    void alGuardar();
    void alFuente();
    void alAcercaDe();
    void alSalir();
    void alNegrita();
    void alCursiva();
    void alSubrayado();

public:
    NotepadWindow(QWidget *parent = 0);
    ~NotepadWindow();

//Por convenio, las var privadas acaban en guion bajo (_)
private:
//    QPlainTextEdit* txtEditor_;
    QTextEdit* txtEditor_;

    //Variables de menu
    QMenu* mnuArchivo_;
    QMenuBar* mainMenu_;

    //Var de accion
    QAction* actArchivoAbrir_;
    QAction* actArchivoGuardar_;
    QAction* actArchivoSalir_;

    QMenu* mnuFormato_;
    QAction* actFormatoFuente_;

    QMenu* mnuEditar_;
    QAction* actEditarCopiar_;
    QAction* actEditarPegar_;
    QAction* actEditarCortar_;
    QAction* actEditarDeshacer_;
    QAction* actEditarRehacer_;

    QMenu* mnuAyuda_;
    QAction* actAyudaAcerca_;

    QClipboard * portapapeles_;

    //Variables del Toolbar
    QToolBar* mnuToolBar_;
    QAction* actToolBarAbrir_;
    QAction* actToolBarCortar_;
    QAction* actToolBarCopiar_;
    QAction* actToolBarPegar_;
    QAction* actToolBarFuente_;

    QAction* actToolBarNegrita_;
    QAction* actToolBarCursiva_;
    QAction* actToolBarSubrayado_;
};

#endif // NOTEPADWINDOW_H
