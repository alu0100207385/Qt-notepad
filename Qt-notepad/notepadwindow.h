#ifndef NOTEPADWINDOW_H
#define NOTEPADWINDOW_H

#include <QMainWindow>

//Esta clase permite permite crear texto plano en una ventana
#include <QPlainTextEdit>

//Introducimos las librerias de los menus
#include <QMenu>
#include <QMenuBar>

//Acciones
#include <QAction>

//Permite abrir archivos (cadenas)
#include <QFileDialog>


#include <QFile>
#include <QFontDialog>
#include <QClipboard>
#include <QKeySequence>


class NotepadWindow : public QMainWindow
{
    Q_OBJECT

    //Slots son las funciones q deseamos q se ejecuten al pulsar
    //un boton (programcion orientada a eventos)
private slots:
    void alAbrir();
    void alGuardar();
    void alFuente();

public:
    NotepadWindow(QWidget *parent = 0);
    ~NotepadWindow();

//Por convenio, las var privadas acaban en guion bajo (_)
private:
    QPlainTextEdit* txtEditor_;

    //Variables de menu
    QMenu* mnuArchivo_;
    QMenuBar* mainMenu_;

    //Var de accion
    QAction* actArchivoAbrir_;
    QAction* actArchivoGuardar_;

    QMenu* mnuFormato_;
    QAction* actFormatoFuente_;
    QMenu* mnuEditar_;
    QAction* actEditarCopiar_;
    QAction* actEditarPegar_;
    QClipboard * portapapeles_;
};

#endif // NOTEPADWINDOW_H
