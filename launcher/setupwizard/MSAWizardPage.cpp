#include "MSAWizardPage.h"
#include <GenericMC.h>

#include <QVBoxLayout>

MSAWizardPage::MSAWizardPage(QWidget *parent)
    :BaseWizardPage(parent)
{
    setupUi();
}

void MSAWizardPage::setupUi()
{
    setObjectName(QStringLiteral("javaPage"));
    QVBoxLayout * layout = new QVBoxLayout(this);

    setLayout(layout);

    retranslate();
}

void MSAWizardPage::retranslate()
{
    setTitle(tr("Microsoft OAuth"));
    setSubTitle(tr("You do not have a an available Microsoft OAuth path set up.\n"
                   "Please configure Microsoft OAuth"
                   ));
}

void MSAWizardPage::initializePage()
{

}

void MSAWizardPage::refresh()
{

}

bool MSAWizardPage::validatePage()
{
    auto settings = GMC->settings();
    return false;
}
