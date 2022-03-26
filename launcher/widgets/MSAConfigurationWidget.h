#ifndef MSACONFIGURATIONWIDGET_H
#define MSACONFIGURATIONWIDGET_H

#include <QWidget>

class QVBoxLayout;
class QButtonGroup;
class QRadioButton;
class QLineEdit;
class QPushButton;
class QLabel;

class MSAConfigurationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MSAConfigurationWidget(QWidget *parent = 0);
    virtual ~MSAConfigurationWidget() { };

    void retranslate();
    void validate();

private:
    bool goodInput = false;
    void setupUi();
    bool validateProxyURL();
    bool validateClientID(const QString& str);
    void validateClient();
    void setMessage(const char* text);
    void clearMessage();

    void on_pButtonCheckProxy_clicked();
    void on_lineEditProxyURL_textEdited(const QString& text);
    void on_lineEditProxyClId_textEdited(const QString& text);

    const char* m_msg = nullptr;
    bool m_msg_set = false;

    QButtonGroup *m_rButtonGroup = nullptr;

    QVBoxLayout *m_vLayout = nullptr;
    QVBoxLayout *m_vLayoutLocal = nullptr;
    QVBoxLayout *m_vLayoutProxy = nullptr;

    QLabel *m_labelMsg = nullptr;
    QRadioButton *m_rButtonNone = nullptr;

    QRadioButton *m_rButtonLocal = nullptr;
    QLineEdit *m_lineEditLocalClId = nullptr;
    QLineEdit *m_lineEditLocalClSec = nullptr;

    QRadioButton *m_rButtonProxy = nullptr;
    QLineEdit *m_lineEditProxyURL = nullptr;
    QLineEdit *m_lineEditProxyClId = nullptr;
    QPushButton *m_pButtonCheckProxy = nullptr;
};

#endif // MSACONFIGURATIONWIDGET_H
