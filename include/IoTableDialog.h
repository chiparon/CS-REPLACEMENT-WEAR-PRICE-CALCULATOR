//
// Created by chiparon on 25-10-3.
//

#pragma once
#include <QDialog>
#include <QTableWidget>
#include <QLineEdit>
#include <QLabel>

class IoTableDialog : public QDialog {
    Q_OBJECT
public:
    explicit IoTableDialog(QWidget *parent=nullptr);

private slots:
    void updateOutputs();

private:
    QTableWidget *table; // A2:D11 (10 rows x 4 columns)
    QLineEdit *b12Edit;  // input B12
    QLineEdit *c12Edit;  // input C12
    QLabel *out1;        // C13
    QLabel *out2;        // C14
    QLabel *out3;        // C15
    QLabel *out4;        // C16
    QLabel *out5;        // C17
    QLabel *sumWear;     // sum of A2..A11
    QLabel *sumPrice;    // sum of D2..D11
    double readNumber(const QString &text) const;
};


