#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include "Hacks.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow* ui;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setHacks(Hacks* hacks);
    void setStatus(QString status);
    void setStatusColour(uint32_t colour);
    void enableAllCheckboxes();
    void disableAllCheckboxes();

public slots:
    void enabletriggerBot();
    void enableglowEsp();
    void enableBhop();
    void enableAntiflash();
    void enableTeammatesGlowing();
    void enableEnemiesGlowing();
    void setEnemyGlowingColours();
    void setTeamMateGlowingColours();

private:
    Hacks* hacks;
};
#endif // MAINWINDOW_H
