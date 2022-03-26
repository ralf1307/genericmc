#include "MSAConfigurationWidget.h"

#include <QVBoxLayout>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLineEdit>
#include <QUrl>
#include <QPushButton>
#include <QLabel>

typedef enum {
    NONE = 0,
    LOCAL = 1,
    PROXY = 2,
} BUTTON_ID;

MSAConfigurationWidget::MSAConfigurationWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUi();

    connect(m_lineEditProxyURL, &QLineEdit::textEdited, this, &MSAConfigurationWidget::on_lineEditProxyURL_textEdited);
    connect(m_lineEditProxyClId, &QLineEdit::textEdited, this, &MSAConfigurationWidget::on_lineEditProxyClId_textEdited);
}

void MSAConfigurationWidget::setupUi(){
    // This constructor is verbose and that's good.
    m_vLayout = new QVBoxLayout(this);
    m_vLayout->setObjectName(QStringLiteral("verticalLayout"));

    m_rButtonGroup = new QButtonGroup(this);
    m_rButtonGroup->setExclusive(true);

    // Message
    m_labelMsg = new QLabel(this);
    m_vLayout->addWidget(m_labelMsg);

    // None
    m_rButtonNone = new QRadioButton(this);
    m_vLayout->addWidget(m_rButtonNone);
    m_rButtonGroup->addButton(m_rButtonNone, NONE);

    // Local
    m_vLayoutLocal = new QVBoxLayout(this);
    m_vLayout->addLayout(m_vLayoutLocal);

    m_rButtonLocal = new QRadioButton(this);
    m_vLayoutLocal->addWidget(m_rButtonLocal);
    m_rButtonGroup->addButton(m_rButtonLocal, LOCAL);

    m_lineEditLocalClId = new QLineEdit(this);
    m_vLayoutLocal->addWidget(m_lineEditLocalClId);

    m_lineEditLocalClSec = new QLineEdit(this);
    m_lineEditLocalClSec->setEchoMode(m_lineEditLocalClSec->Password);
    m_vLayoutLocal->addWidget(m_lineEditLocalClSec);

    // Proxy
    /* NOTE(@ralf1307): ClientID is used as a shared secret
     *                  between the proxy and the client
    */
    m_vLayoutProxy = new QVBoxLayout(this);
    m_vLayout->addLayout(m_vLayoutProxy);

    m_rButtonProxy = new QRadioButton(this);
    m_vLayoutProxy->addWidget(m_rButtonProxy);
    m_rButtonGroup->addButton(m_rButtonProxy, PROXY);

    m_lineEditProxyURL = new QLineEdit(this);
    m_vLayoutProxy->addWidget(m_lineEditProxyURL);

    m_lineEditProxyClId = new QLineEdit(this);
    m_lineEditProxyClId->setEchoMode(m_lineEditProxyClId->Password);
    m_vLayoutProxy->addWidget(m_lineEditProxyClId);

    m_pButtonCheckProxy = new QPushButton(this);
    m_pButtonCheckProxy->setObjectName("pButtonCheckProxy");
    m_vLayoutProxy->addWidget(m_pButtonCheckProxy);

    // Layout stuff
    m_vLayout->setContentsMargins(0,0,0,0);
    m_vLayoutLocal->setContentsMargins(0,0,0,0);
    m_vLayoutProxy->setContentsMargins(0,0,0,0);

    retranslate();
}

void MSAConfigurationWidget::retranslate()
{
    m_rButtonNone->setText(tr("No Microsoft login"));
    m_rButtonLocal->setText(tr("Use client-stored secrets"));
    m_rButtonProxy->setText(tr("Use authentification proxy"));

    m_lineEditLocalClId->setText(tr("Client-ID"));
    m_lineEditLocalClSec->setText(tr("Client-Secret"));

    m_lineEditProxyURL->setText(tr("Proxy-URL: https://genericmc-oauth.example.org"));
    m_lineEditProxyClId->setText(tr("Client-ID"));

    if(m_msg_set){
        m_labelMsg->setText(tr(m_msg));
    }
}


void MSAConfigurationWidget::on_pButtonCheckProxy_clicked()
{

}

void MSAConfigurationWidget::on_lineEditProxyURL_textEdited(const QString& text){
    if(this->validateProxyURL()){
        this->clearMessage();
        return;
    } else {
        this->setMessage("Invalid proxy url");
    }
}

void MSAConfigurationWidget::on_lineEditProxyClId_textEdited(const QString& text){
    if(this->validateClientID(text)){
        this->clearMessage();
        return;
    } else {
        this->setMessage("Invalid proxy client-id");
        return;
    }
}

bool MSAConfigurationWidget::validateProxyURL()
{
    QString string_url = this->m_lineEditProxyURL->text();
    QString string_clid = this->m_lineEditLocalClId->text();

    // Is this a URL?
    QUrl *url = new QUrl(string_url);
    return url->isValid();
}

bool MSAConfigurationWidget::validateClientID(const QString& str)
{
    // TODO(@ralf1307): test client id!
    return true;
}

void MSAConfigurationWidget::clearMessage()
{
    this->m_msg_set = false;
    this->m_msg = nullptr;
    this->m_labelMsg->setText("");
}

void MSAConfigurationWidget::setMessage(const char* text)
{
    this->m_msg_set = true;
    this->m_msg = text;
    this->m_labelMsg->setText(tr(text));
}
