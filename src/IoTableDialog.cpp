//
// Created by chiparon on 25-10-3.
//

#include "IoTableDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QDoubleValidator>

IoTableDialog::IoTableDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("炼金磨损计算器");

    // 主体：左侧表格 + 右侧统计/输出
    auto *root = new QHBoxLayout(this);

    // 表格（10 行 x 4 列）
    table = new QTableWidget(10, 4, this);
    QStringList headers; headers << "磨损" << "皮肤" << "所属收藏品" << "价格";
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setVisible(false);
    table->verticalHeader()->setDefaultSectionSize(28);
    // 设置最小高度，确保完整显示 10 行
    int minTableHeight = table->horizontalHeader()->height()
                         + table->verticalHeader()->defaultSectionSize() * 10 + 6;
    table->setMinimumHeight(minTableHeight);

    // 左侧：表格 + 输入区
    auto *left = new QVBoxLayout();
    left->addWidget(table);

    // 输入 B12 / C12
    b12Edit = new QLineEdit(this);
    c12Edit = new QLineEdit(this);
    auto *validator = new QDoubleValidator(this);
    b12Edit->setValidator(validator);
    c12Edit->setValidator(validator);
    auto *inputs = new QHBoxLayout();
    inputs->addWidget(new QLabel("需求产物最低磨损:", this));
    inputs->addWidget(b12Edit);
    inputs->addSpacing(12);
    inputs->addWidget(new QLabel("需求产物最高磨损:", this));
    inputs->addWidget(c12Edit);
    left->addLayout(inputs);

    root->addLayout(left, 3);

    // 右侧：统计 + 公式输出
    out1 = new QLabel("", this);
    out2 = new QLabel("", this);
    out3 = new QLabel("", this);
    out4 = new QLabel("", this);
    out5 = new QLabel("", this);
    sumWear = new QLabel("0", this);
    sumPrice = new QLabel("0", this);

    auto *right = new QVBoxLayout();
    right->addWidget(new QLabel("磨损合计(A列):", this));
    right->addWidget(sumWear);
    right->addSpacing(8);
    right->addWidget(new QLabel("价格合计(D列):", this));
    right->addWidget(sumPrice);
    right->addSpacing(16);
    right->addWidget(new QLabel("崭新:", this)); right->addWidget(out1);
    right->addWidget(new QLabel("略磨:", this)); right->addWidget(out2);
    right->addWidget(new QLabel("酒精:", this)); right->addWidget(out3);
    right->addWidget(new QLabel("破损:", this)); right->addWidget(out4);
    right->addWidget(new QLabel("出炉磨损:", this)); right->addWidget(out5);
    right->addStretch(1);
    root->addLayout(right, 1);

    connect(b12Edit, &QLineEdit::textChanged, this, &IoTableDialog::updateOutputs);
    connect(c12Edit, &QLineEdit::textChanged, this, &IoTableDialog::updateOutputs);
    connect(table, &QTableWidget::itemChanged, this, &IoTableDialog::updateOutputs);
}

double IoTableDialog::readNumber(const QString &text) const {
    bool ok=false; double v=text.toDouble(&ok); return ok? v : 0.0;
}

void IoTableDialog::updateOutputs() {
    const double b12 = readNumber(b12Edit->text());
    const double c12 = readNumber(c12Edit->text());
    const double denom = (c12 - b12);

    auto safeRatio = [denom](double target, double b){
        if (qFuzzyIsNull(denom)) return 0.0;
        return (target - b) / denom * 10.0;
    };

    const double c13 = safeRatio(0.07, b12);
    const double c14 = safeRatio(0.15, b12);
    const double c15 = safeRatio(0.39, b12);
    const double c16 = safeRatio(0.45, b12);

    // SUM(A2:A11) / 10 * (C12 - B12) + B12，同时统计 A 列、D 列合计
    double sumA = 0.0;
    double sumD = 0.0;
    for (int r=0; r<10; ++r) {
        QTableWidgetItem *it = table->item(r, 0);
        if (!it) continue;
        sumA += readNumber(it->text());
        QTableWidgetItem *itD = table->item(r, 3);
        if (itD) sumD += readNumber(itD->text());
    }
    const double c17 = (sumA / 10.0) * (c12 - b12) + b12;

    out1->setText(QString::number(c13));
    out2->setText(QString::number(c14));
    out3->setText(QString::number(c15));
    out4->setText(QString::number(c16));
    out5->setText(QString::number(c17));
    sumWear->setText(QString::number(sumA));
    sumPrice->setText(QString::number(sumD));
}


