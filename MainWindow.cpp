#include "MainWindow.h"
#include "TailView.h"
#include <QFileDialog>

MainWindow::MainWindow()
{
    ui.setupUi(this);
    m_tailView = new TailView(this);
    setCentralWidget(m_tailView);
    ui.action_FullLayout->setChecked(m_tailView->isFullLayout());
}

void MainWindow::setFile(const QString & filename)
{
    setWindowTitle(filename + " -- Yata");
    m_tailView->setFile(filename);
}


void MainWindow::on_action_Open_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this);
    if(!filename.isEmpty()) {
        setFile(filename);
    }
}

void MainWindow::on_action_Exit_triggered()
{
    qApp->exit();
}

void MainWindow::on_action_FullLayout_triggered(bool isChecked)
{
    m_tailView->setFullLayout(isChecked);
}