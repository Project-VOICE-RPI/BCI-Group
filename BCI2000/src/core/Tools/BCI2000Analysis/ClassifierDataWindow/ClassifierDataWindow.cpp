////////////////////////////////////////////////////////////////////////////////
// $Id: ClassifierDataWindow.cpp 8270 2024-07-23 19:34:53Z mellinger $
// Author: mellinger@neurotechcenter.org
// Description: Classifier data window class for BCI2000Analysis.
//
// $BEGIN_BCI2000_LICENSE$
//
// This file is part of BCI2000, a platform for real-time bio-signal research.
// [ Copyright (C) 2000-2023: BCI2000 team and many external contributors ]
//
// BCI2000 is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// BCI2000 is distributed in the hope that it will be useful, but
//                         WITHOUT ANY WARRANTY
// - without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
//
// $END_BCI2000_LICENSE$
////////////////////////////////////////////////////////////////////////////////
#include "ClassifierDataWindow.h"

#include "AnalysisData.h"
#include "ChannelPlotsWindow.h"
#include "ClassifierParamWidget.h"
#include "ClassifierWindow.h"
#include "EditMenu.h"
#include "FileDialog.h"
#include "HelpMenu.h"
#include "LDAClassifier.h"
#include "SVMClassifier.h"
#include "SWLDAClassifier.h"
#include "ManualClassifier.h"
#include "SignalWidget.h"
#include "Statistics.h"
#include "TopoplotWindow.h"
#include "WindowMenu.h"
#include "WindowSettings.h"
#include "WindowFactory.h"

#include <QApplication>
#include <QBoxLayout>
#include <QDockWidget>
#include <QGroupBox>
#include <QInputDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QProgressDialog>
#include <QToolBar>
#include <QActionGroup>
#include <QMouseEvent>

#include <fstream>

struct ClassifierDataWindow::Private : QObject
{
    QMainWindow *mpSelf;
    AnalysisWindow *mpAnalysisWindow;
    QString mFile;
    QAction *mpTrainingMethodLDAItem, *mpTrainingMethodSWLDAItem, *mpTrainingMethodSVMItem,
        *mpTrainingMethodManualItem;
    QAction *mpTrainClassifier1, *mpTrainClassifier2;
    AnalysisData mAnalysisData;
    GenericSignal mRsq, mMean1, mMean2, mManualWeights;
    ClassifierParamWidget *mpClassifierParams;

    Private(QMainWindow *);

    void setWindowTitleFromFile(const QString&);

    void setAnalysisData(const AnalysisData &);
    void onOpenAnalysisData();
    void onSaveAnalysisData();

    void onShowCurvesAtChannel();
    void onShowDistributionAtElement();
    void onShowCurvesAt(int);
    void onShowDistributionAt(int);
    void onAddToContextMenu(int, int, QString, QString, QMenu*);
    void onEnterClassificationWeight();

    void onTrainingMethodManualToggled(bool);

    void train();
};

ClassifierDataWindow::Private::Private(QMainWindow *p) : QObject(p), mpSelf(p)
{
}

void ClassifierDataWindow::Private::setWindowTitleFromFile(const QString& file)
{
    mFile = file;
    mpSelf->setWindowTitle(WindowMenu::windowTitleFromFile("Analysis Data", file));
}

void ClassifierDataWindow::Private::setAnalysisData(const AnalysisData &data)
{
    mAnalysisData = data;
    mMean1 = Statistics::mean(data.trainingData1);
    mMean2 = Statistics::mean(data.trainingData2);
    mRsq = Statistics::rsq(data.trainingData1, data.trainingData2);
    mManualWeights = GenericSignal(mMean1.Properties());
    delete mpSelf->centralWidget();

    size_t n1 = data.trainingData1.size(), n2 = data.trainingData2.size();
    auto prop = data.signalProperties();
    size_t ndim = prop ? prop->Channels() * prop->Elements() : 0;

    auto pWidget = new EditMenu::CopyWidget(mpSelf);
    auto pLayout = new QHBoxLayout;
    pLayout->setContentsMargins(0, 0, 0, 0);
    pWidget->setLayout(pLayout);
    auto pGroup = new QGroupBox(QString("Training data r\xc2\xb2 map (N\xE2\x82\x81=%1, N\xE2\x82\x82=%2, dim=%3)").arg(n1).arg(n2).arg(ndim));
    pWidget->layout()->addWidget(pGroup);
    auto pLayout2 = new QVBoxLayout;
    pLayout2->setContentsMargins(0, 0, 0, 0);
    pGroup->setLayout(pLayout2);
    auto pSignalWidget = new SignalWidget(mRsq, mpSelf);
    pLayout2->addWidget(pSignalWidget);
    pSignalWidget->setContextMenu(true);
    connect(pSignalWidget, &SignalWidget::showCurvesAt, this, &Private::onShowCurvesAt);
    connect(pSignalWidget, &SignalWidget::showDistributionAt, this, &Private::onShowDistributionAt);
    connect(pSignalWidget, &SignalWidget::addToContextMenu, this, &Private::onAddToContextMenu);

    mpSelf->setCentralWidget(pWidget);
    mpClassifierParams->setParams(ClassifierParamWidget::ClassifierParams::createFromData(mAnalysisData));
}

void ClassifierDataWindow::Private::onOpenAnalysisData()
{
    QString file = FileDialog::getOpenFileName(mpSelf, "Open Analysis Data",
                                               "BCI2000 Analysis Data File (*.bcianalysis)", "output");
    if (!file.isEmpty())
    {
        std::ifstream stream(file.toLocal8Bit().constData(), std::ios::binary);
        AnalysisData data;
        try
        {
            data = AnalysisData::unserialize(stream);
        }
        catch (const std::exception &e)
        {
            QMessageBox::critical(
                mpSelf, "Error reading file",
                QString("An error occurred when reading from file\n\"%1\":\n%2").arg(file).arg(e.what()));
            return;
        }
        if (data.kind.find("LinearClassifier") != std::string::npos)
        {
            setAnalysisData(data);
            setWindowTitleFromFile(file);
            mpAnalysisWindow = nullptr;
        }
        else
        {
            auto pWindow = WindowFactory::create(nullptr, data, file);
            if (pWindow)
                pWindow->show();
        }
    }
}

void ClassifierDataWindow::Private::onSaveAnalysisData()
{
    QString file = FileDialog::getSaveFileName(mpSelf, "Save Analysis Data",
                                               "BCI2000 Analysis Data File (*.bcianalysis)", "output");
    if (!file.isEmpty())
    {
        std::ofstream stream(file.toLocal8Bit().constData(), std::ios::binary);
        if (!stream)
        {
            QMessageBox::critical(mpSelf, "Error writing file",
                                  QString("Error opening file\n%1\nfor writing").arg(file));
            return;
        }
        try
        {
            mAnalysisData.serialize(stream);
            setWindowTitleFromFile(file);
        }
        catch (const std::exception &e)
        {
            QMessageBox::critical(
                mpSelf, "Error writing file",
                QString("An error occurred when writing to file\n\"%1\":\n%2").arg(file).arg(e.what()));
        }
    }
}

void ClassifierDataWindow::Private::onShowCurvesAtChannel()
{
    int ch = ChannelPlotsWindow::askForChannel(mAnalysisData.signalProperties());
    if (ch >= 0)
        onShowCurvesAt(ch);
}

void ClassifierDataWindow::Private::onShowDistributionAtElement()
{
    int el = TopoplotWindow::askForElement(mAnalysisData.signalProperties());
    if (el >= 0)
        onShowDistributionAt(el);
}

void ClassifierDataWindow::Private::onShowCurvesAt(int channel)
{
    auto pWindow = new ChannelPlotsWindow(mMean1, mMean2, mRsq, channel, mpSelf);
    pWindow->show();
}

void ClassifierDataWindow::Private::onShowDistributionAt(int element)
{
    auto pWindow = new TopoplotWindow(mRsq, element, mpSelf);
    pWindow->resize(400, 400);
    pWindow->show();
}

void ClassifierDataWindow::Private::onAddToContextMenu(int ch, int el, QString chName, QString elName, QMenu* pMenu)
{
    if (mpTrainingMethodManualItem->isChecked() && ch >= 0 && el >= 0)
    {
        QString desc = chName + "@" + elName;
        auto pEntry = pMenu->addAction("Enter classification weight for " + desc + "...");
        pEntry->setProperty("ch", ch);
        pEntry->setProperty("el", el);
        pEntry->setProperty("desc", desc);
        connect(pEntry, &QAction::triggered, this, &Private::onEnterClassificationWeight);
    }
}

void ClassifierDataWindow::Private::onEnterClassificationWeight()
{
    QVariant ch_ = sender()->property("ch"), el_ = sender()->property("el"),
             desc_ = sender()->property("desc");
    if (ch_.isValid() && el_.isValid() && desc_.isValid())
    {
        int ch = ch_.toInt(), el = el_.toInt();
        QString desc = desc_.toString();
        Assert(ch >= 0 && el >=0);
        bool ok = false;
        double result = QInputDialog::getDouble(
            mpSelf, "Enter weight",
            "Enter manual classification weight for " + desc + ":",
            mManualWeights(ch, el), -1e10, 1e10, 4, &ok);
        if (ok)
            mManualWeights(ch, el) = result;
    }
}

void ClassifierDataWindow::Private::onTrainingMethodManualToggled(bool checked)
{
    QString text = checked ? "&Create manual Classifier" : "&Train Classifier";
    mpTrainClassifier1->setText(text);
    mpTrainClassifier2->setText(text);
    if (!checked)
        mManualWeights.SetAllValues(0.0);
}

void ClassifierDataWindow::Private::train()
{
    Classifier *pClassifier = nullptr;
    ClassifierParamWidget::ClassifierParams params = mpClassifierParams->params();

    if (mpTrainingMethodLDAItem->isChecked())
    {
        pClassifier = new LDAClassifier;
    }
    else if (mpTrainingMethodSWLDAItem->isChecked())
    {
        auto pSWLDAClassifier = new SWLDAClassifier;
        pSWLDAClassifier->setPenter(params.penter);
        pSWLDAClassifier->setPremove(params.premove);
        pSWLDAClassifier->setMaxIterations(params.maxIterations);
        pClassifier = pSWLDAClassifier;
    }
    else if (mpTrainingMethodSVMItem->isChecked())
    {
        pClassifier = new SVMClassifier;
    }
    else if (mpTrainingMethodManualItem->isChecked())
    {
        auto pManualClassifier = new ManualClassifier;
        pManualClassifier->setWeights(mManualWeights);
        mManualWeights.SetAllValues(0.0);
        pClassifier = pManualClassifier;
    }
    Assert(pClassifier);
    pClassifier->setDownsamplingFactor(params.downsampling);
    pClassifier->setOutputDimension(params.outputDimension);

    const auto &data1 = mAnalysisData.trainingData1, &data2 = mAnalysisData.trainingData2;
    size_t totalCount = data1.size() + data2.size();

    QString title = QString("Training %1 classifier...").arg(pClassifier->method());
    QProgressDialog progress(title, "Cancel", 0, totalCount, mpSelf);
    progress.setWindowModality(Qt::WindowModal);
    progress.setWindowFlags(progress.windowFlags() & ~Qt::WindowCloseButtonHint & ~Qt::WindowContextHelpButtonHint);
    progress.show();

    struct Updater
    {
        static void callback(int count, void *data)
        {
            static_cast<Updater *>(data)->update(count);
        }
        void update(int count)
        {
            if (progress.wasCanceled())
                throw ProgressCanceled();
            if (count >= progress.maximum())
            {
                progress.setRange(0, 0);
                progress.setCancelButton(nullptr);
            }
            progress.setValue(count);
            QApplication::processEvents();
        }
        class ProgressCanceled : std::exception
        {
        };
        QProgressDialog &progress;
    } updater = {progress};

    bool canceled = false;

    pClassifier->setTrainingCallback(&Updater::callback, &updater);
    try
    {
        pClassifier->train(data1, data2);
        if (params.normalize)
            pClassifier->normalizeVariance();
    }
    catch (const Updater::ProgressCanceled &)
    {
        canceled = true;
    }
    catch (const std::exception &e)
    {
        QMessageBox::critical(mpSelf, "Classifier training error", QString("Classifier training: ") + e.what());
        canceled = true;
    }

    progress.close();

    if (!canceled)
    {
        auto pWindow = new ClassifierWindow(mpAnalysisWindow, mAnalysisData, *pClassifier, mFile);
        pWindow->show();
    }

    delete pClassifier;
}

ClassifierDataWindow::ClassifierDataWindow(AnalysisWindow* pAnalysisWindow, const AnalysisData &data, const QString& file)
: QMainWindow(nullptr), p(new Private(this))
{
    p->mpAnalysisWindow = pAnalysisWindow;
    setAttribute(Qt::WA_DeleteOnClose, true);
    p->setWindowTitleFromFile(file);
    QMenu *pMenu = QMainWindow::menuBar()->addMenu("&File");
    QAction *pAction = pMenu->addAction("&Open Analysis Data...");
    connect(pAction, &QAction::triggered, p, &Private::onOpenAnalysisData);
    pAction->setShortcut(Qt::CTRL | Qt::Key_O);
    pAction = pMenu->addAction("&Save Analysis Data...");
    connect(pAction, &QAction::triggered, p, &Private::onSaveAnalysisData);
    pAction->setShortcut(Qt::CTRL | Qt::Key_S);
    pMenu->addSeparator();
    pAction = pMenu->addAction("&Close Window");
    pAction->setShortcut(Qt::CTRL | Qt::Key_W);
    connect(pAction, &QAction::triggered, this, &QMainWindow::close);

    EditMenu::addToMenuBar(menuBar());

    pMenu = QMainWindow::menuBar()->addMenu("&Classifier");
    auto pMenu2 = pMenu->addMenu("&Training Method");
    p->mpTrainingMethodLDAItem = pMenu2->addAction("&LDA");
    p->mpTrainingMethodLDAItem->setToolTip("Linear Discriminant Analysis");
    p->mpTrainingMethodSWLDAItem = pMenu2->addAction("&SWLDA");
    p->mpTrainingMethodSWLDAItem->setToolTip("Stepwise LDA");
    p->mpTrainingMethodSVMItem = pMenu2->addAction("S&VM");
    p->mpTrainingMethodSVMItem->setToolTip("Linear Support Vector Machine");
    p->mpTrainingMethodManualItem = pMenu2->addAction("&Manual");
    p->mpTrainingMethodManualItem->setToolTip("Manual selection of classifier weights\n"
                                                "Right-click into the r\xc2\xb2 plot to assign weights");
    pMenu2->setToolTipsVisible(true);
    auto pGroup = new QActionGroup(this);
    pGroup->addAction(p->mpTrainingMethodLDAItem);
    p->mpTrainingMethodLDAItem->setCheckable(true);
    p->mpTrainingMethodLDAItem->setChecked(true);
    pGroup->addAction(p->mpTrainingMethodSWLDAItem);
    p->mpTrainingMethodSWLDAItem->setCheckable(true);
    pGroup->addAction(p->mpTrainingMethodSVMItem);
    p->mpTrainingMethodSVMItem->setCheckable(true);
    pGroup->addAction(p->mpTrainingMethodManualItem);
    p->mpTrainingMethodManualItem->setCheckable(true);
    connect(p->mpTrainingMethodManualItem, &QAction::toggled, p, &Private::onTrainingMethodManualToggled);

    pMenu->addSeparator();
    p->mpTrainClassifier1 = pMenu->addAction("&Train Classifier...", p, &Private::train);
    p->mpTrainClassifier1->setShortcut(Qt::CTRL | Qt::Key_T);

    pMenu = QMainWindow::menuBar()->addMenu("&View");
    pMenu->addAction("Show &Curves for Channel...", p, &Private::onShowCurvesAtChannel);
    pMenu->addAction("Show &Distribution at Time/Frequency...", p, &Private::onShowDistributionAtElement);

    WindowMenu::addWindow(this);
    HelpMenu::addToMenuBar(menuBar());

    auto pToolBar = QMainWindow::addToolBar("Actions");
    pToolBar->addAction(p->mpTrainingMethodLDAItem);
    pToolBar->addAction(p->mpTrainingMethodSWLDAItem);
    pToolBar->addAction(p->mpTrainingMethodSVMItem);
    pToolBar->addAction(p->mpTrainingMethodManualItem);
    p->mpTrainClassifier2 = pToolBar->addAction("Train Classifier", p, &Private::train);

    QDockWidget *pDockWidget = new QDockWidget("Classifier parameters", this);
    pDockWidget->setFeatures(pDockWidget->features() & ~QDockWidget::DockWidgetClosable);
    p->mpClassifierParams = new ClassifierParamWidget;
    p->mpClassifierParams->enableSWLDAParams(false);
    connect(p->mpTrainingMethodSWLDAItem, &QAction::toggled, p->mpClassifierParams,
            &ClassifierParamWidget::enableSWLDAParams);
    pDockWidget->setWidget(p->mpClassifierParams);
    addDockWidget(Qt::LeftDockWidgetArea, pDockWidget);

    p->setAnalysisData(data);

    setMinimumHeight(240);
    setMinimumWidth(320);
    WindowSettings::read(this);
}

ClassifierDataWindow::~ClassifierDataWindow()
{
    WindowSettings::write(this);
    WindowMenu::removeWindow(this);
}
