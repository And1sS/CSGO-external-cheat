#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->bhop_chckbx, SIGNAL(clicked()), this, SLOT(enableBhop()));
    QObject::connect(ui->glow_chckbx, SIGNAL(clicked()), this, SLOT(enableglowEsp()));
    QObject::connect(ui->triggerbot_chckbx, SIGNAL(clicked()), this, SLOT(enabletriggerBot()));
    QObject::connect(ui->antiflash_chckbx, SIGNAL(clicked()), this, SLOT(enableAntiflash()));
    QObject::connect(ui->teammate_glow_chckbx, SIGNAL(clicked()), this, SLOT(enableTeammatesGlowing()));
    QObject::connect(ui->enemy_glow_chckbx, SIGNAL(clicked()), this, SLOT(enableEnemiesGlowing()));
    QObject::connect(ui->enemy_glow_r, SIGNAL(valueChanged(int)), this, SLOT(setEnemyGlowingColours()));
    QObject::connect(ui->enemy_glow_g, SIGNAL(valueChanged(int)), this, SLOT(setEnemyGlowingColours()));
    QObject::connect(ui->enemy_glow_b, SIGNAL(valueChanged(int)), this, SLOT(setEnemyGlowingColours()));
    QObject::connect(ui->enemy_glow_a, SIGNAL(valueChanged(int)), this, SLOT(setEnemyGlowingColours()));
    QObject::connect(ui->teammate_glow_r, SIGNAL(valueChanged(int)), this, SLOT(setTeamMateGlowingColours()));
    QObject::connect(ui->teammate_glow_g, SIGNAL(valueChanged(int)), this, SLOT(setTeamMateGlowingColours()));
    QObject::connect(ui->teammate_glow_b, SIGNAL(valueChanged(int)), this, SLOT(setTeamMateGlowingColours()));
    QObject::connect(ui->teammate_glow_a, SIGNAL(valueChanged(int)), this, SLOT(setTeamMateGlowingColours()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setHacks(Hacks *hacks)
{
    this->hacks = hacks;
}

void MainWindow::setStatus(QString status)
{
    ui->status_lbl->setText(status);
}

void MainWindow::setStatusColour(uint32_t colour)
{
    if (colour == Qt::red)
        ui->status_lbl->setStyleSheet("color: red");
    else
        ui->status_lbl->setStyleSheet("color: green");
}

void MainWindow::enableAllCheckboxes()
{
    ui->bhop_chckbx->setEnabled(true);
    ui->triggerbot_chckbx->setEnabled(true);
    ui->antiflash_chckbx->setEnabled(true);
    ui->glow_chckbx->setEnabled(true);
}

void MainWindow::disableAllCheckboxes()
{
    ui->bhop_chckbx->setEnabled(false);
    ui->triggerbot_chckbx->setEnabled(false);
    ui->antiflash_chckbx->setEnabled(false);
    ui->glow_chckbx->setEnabled(false);
}

void MainWindow::enableBhop()
{
    hacks->setBunnyHop(ui->bhop_chckbx->isChecked());

#ifdef DEBUG
    std::cout << "bhop " << (ui->bhop_chckbx->isChecked() ? "enabled." : "disabled.") << std::endl;
#endif
}

void MainWindow::enableglowEsp()
{
    hacks->setGlowEsp(ui->glow_chckbx->isChecked());
    ui->enemies_glow_colors->setEnabled(ui->glow_chckbx->isChecked());
    ui->teammates_glow_colors->setEnabled(ui->glow_chckbx->isChecked());

#ifdef DEBUG
    std::cout << "glowEsp " << (ui->glow_chckbx->isChecked() ? "enabled." : "disabled.") << std::endl;
#endif
}

void MainWindow::enabletriggerBot()
{
    hacks->setTriggerBot(ui->triggerbot_chckbx->isChecked());

#ifdef DEBUG
    std::cout << "triggerBot " <<
                 (ui->triggerbot_chckbx->isChecked() ? "enabled." : "disabled.") << std::endl;
#endif
}

void MainWindow::enableAntiflash()
{
    hacks->setAntiflash(ui->antiflash_chckbx->isChecked());

#ifdef DEBUG
    std::cout << "antiflash " << (ui->antiflash_chckbx->isChecked() ? "enabled." : "disabled.") << std::endl;
#endif
}

void MainWindow::enableTeammatesGlowing()
{
    hacks->setTeamMatesGlowing(ui->teammate_glow_chckbx->isChecked());
#ifdef DEBUG
    std::cout << "teammates glowing " <<
                 (ui->teammate_glow_chckbx->isChecked() ? "enabled." : "disabled.") << std::endl;
#endif
}

void MainWindow::enableEnemiesGlowing()
{
    hacks->setEnemiesGlowing(ui->enemy_glow_chckbx->isChecked());

#ifdef DEBUG
    std::cout << "enemies glowing " <<
                 (ui->enemy_glow_chckbx->isChecked() ? "enabled." : "disabled.") << std::endl;
#endif
}

void MainWindow::setEnemyGlowingColours()
{
    colours temp = { (float)ui->enemy_glow_r->value() / 100.0f, (float) ui->enemy_glow_g->value() / 100.0f,
                     (float)ui->enemy_glow_b->value() / 100.0f, (float) ui->enemy_glow_a->value() / 100.0f};
    hacks->setEnemyGlowingColours(temp);
}

void MainWindow::setTeamMateGlowingColours()
{
    colours temp = { (float)ui->teammate_glow_r->value() / 100.0f, (float) ui->teammate_glow_g->value() / 100.0f,
                     (float)ui->teammate_glow_b->value() / 100.0f, (float) ui->teammate_glow_a->value() / 100.0f};
    hacks->setTeamMateGlowingColours(temp);
}
