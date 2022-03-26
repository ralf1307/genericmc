#pragma once

#include "BaseWizardPage.h"

class MSAWizardPage : public BaseWizardPage
{
    Q_OBJECT
public:
    explicit MSAWizardPage(QWidget *parent = Q_NULLPTR);
    
    virtual ~MSAWizardPage()
    {
    };
    
    void initializePage() override;
    void refresh() override;
    bool validatePage() override;


    
protected: /* methods */
    void setupUi();
    void retranslate() override;
    
};
