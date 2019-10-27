#include "./ui/mainwindow.h"
#include "./ui_mainwindow.h"
#include "./ui/qcustomplot/qcustomplot.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->plotData();
    this->initEcg();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plotData()
{
    // Set u s e r i n t e r a c t i o n : zoom and drag
    ui->qcpwidget->setInteraction(QCP::iRangeDrag, true);
    ui->qcpwidget->setInteraction(QCP::iRangeZoom, true);
    connect(ui->qcpwidget, SIGNAL(mouseDoubleClick(QMouseEvent *)),
            ui->qcpwidget, SLOT(rescaleAxes()));
    // Add Graph and s e t some p r o p e r t i e s
    ui->qcpwidget->addGraph();
    ui->qcpwidget ->xAxis->setLabel("X");
    ui->qcpwidget ->yAxis->setLabel("Y");
    ui->qcpwidget ->xAxis->grid()->setSubGridVisible(true);
    // Cr e a t e data : f ( x ) = x^2
    std::vector < double > X(101) ;
    std::iota(X. begin(), X. end(), -50);
    std::vector < double > Y(101) ;
    std::transform(X. begin(), X. end(),
                   Y. begin(),
                   [](double x)
    {
        return x * x ;
    });
    // Pl o t data
    ui->qcpwidget->graph(0)->setData(QVector<double>::fromStdVector(X),
                                     QVector<double>::fromStdVector(Y));
    //
    ui->qcpwidget->rescaleAxes();
    ui->qcpwidget->replot();
}

void MainWindow::initEcg()
{
    connect(ui->loadButton, &QPushButton::clicked, [this]()
    {
        auto fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("ecg file (*.txt);;All Files (*)"));
        std::ifstream stream(fileName.toUtf8().constData());
        this->ui->pathLabel->setText("Loaded file: " + fileName);
        this->plotEcg(stream);
    });
}

void MainWindow::plotEcg(std::ifstream &stream)
{
    // Set u s e r i n t e r a c t i o n : zoom and drag
    ui->ecgwidget->setInteraction(QCP::iRangeDrag, true);
    ui->ecgwidget->setInteraction(QCP::iRangeZoom, true);
    connect(ui->ecgwidget, SIGNAL(mouseDoubleClick(QMouseEvent *)),
            ui->ecgwidget, SLOT(rescaleAxes()));
    // Add Graph and s e t some p r o p e r t i e s
    ui->ecgwidget->addGraph();
    ui->ecgwidget ->xAxis->setLabel("Time [s]");
    ui->ecgwidget ->yAxis->setLabel("Signal [au]");
    ui->ecgwidget ->xAxis->grid()->setSubGridVisible(true);

    //load data
    std::vector<double> data;
    std::copy(std::istream_iterator <int>(stream), std::istream_iterator <int>(), std::back_inserter(data));

    std::vector<double> time;
    time.resize(data.size());
    std::generate(time.begin(), time.end(), []()
    {
        static unsigned long long i = 0;
        return i++ / 360.0;
    });

    std::vector<double> signal;
    signal.resize(data.size(), 0);

    std::vector<double> f;
    f.resize(data.size(), 0);

    //filter signal
    unsigned long long M = 51;
    unsigned long long length = static_cast<unsigned long long>(data.size());
    //average filter
    for(unsigned long long i = 0; i < length - 1; ++i)
    {
        unsigned long long i_ = i + 1;
        for(unsigned long long j = 0; j < M; ++j)
        {
            unsigned long long j_ = j + 1;
            if((i + j_) < length)
                f[i_] = f[i_] + data[i + j_];
        }
        f[i_] = f[i_] / M;
        signal[i_] = (data[i_] - f[i_]) / 240;
    }

    signal.resize(length - M);

    ui->ecgwidget->addGraph();
    ui->ecgwidget->graph(1)->setPen(QPen(Qt::red));
    ui->ecgwidget->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->ecgwidget->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 7));

    std::vector<double> time_peaks;
    std::vector<double> peaks;
    double threshold = 0.9;
    double window = 200;
    for(unsigned long long i = 1; i <= (signal.size() / window); ++i)
    {
        auto it = std::max_element(signal.begin() + static_cast<long long>(((i - 1) * window)), signal.begin() + static_cast<long long>((i * window)));
        auto index = static_cast<unsigned long long>(std::distance(signal.begin(), it));
        if(signal[index] > threshold)
        {
            time_peaks.push_back(time[index]);
            peaks.push_back(signal[index]);
        }
    }


    //plot data
    ui->ecgwidget->graph(0)->setData(QVector<double>::fromStdVector(time),
                                     QVector<double>::fromStdVector(signal));
    ui->ecgwidget->graph(1)->setData(QVector<double>::fromStdVector(time_peaks),
                                     QVector<double>::fromStdVector(peaks));
    //
    ui->ecgwidget->rescaleAxes();
    ui->ecgwidget->replot();

    //Set info label
    QString rate = QString::number(peaks.size() / (time.size() / 360.0 / 60));
    ui->infoLabel->setText("Average hart rate: " + rate);

}


