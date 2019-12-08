/****************************************************************************/
//    copyright 2012 -2019  Chris Rizzitello <sithlord48@gmail.com>         //
//                                                                          //
//    This file is part of FF7tk                                            //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    FF7tk is distributed in the hope that it will be useful,              //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include "MenuListWidget.h"
#include <QVBoxLayout>

MenuListWidget::MenuListWidget(QWidget *parent) :
    QWidget(parent)
    , cb_item(new DoubleCheckBox)
    , cb_magic(new DoubleCheckBox)
    , cb_materia(new DoubleCheckBox)
    , cb_equip(new DoubleCheckBox)
    , cb_status(new DoubleCheckBox)
    , cb_order(new DoubleCheckBox)
    , cb_limit(new DoubleCheckBox)
    , cb_config(new DoubleCheckBox)
    , cb_phs(new DoubleCheckBox)
    , cb_save(new DoubleCheckBox)
    , lbl_title(new QLabel)
{
    updateText();
    init_display();
    connectAll();
}
void MenuListWidget::changeEvent(QEvent *e)
{
    if (e->type() != QEvent::LanguageChange) {
        QWidget::changeEvent(e);
    }

    updateText();
}

void MenuListWidget::init_display()
{
    lbl_title->setStyleSheet(QString("text-decoration: underline;"));
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(3);
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(lbl_title);
    layout->addWidget(cb_item);
    layout->addWidget(cb_magic);
    layout->addWidget(cb_materia);
    layout->addWidget(cb_equip);
    layout->addWidget(cb_status);
    layout->addWidget(cb_order);
    layout->addWidget(cb_limit);
    layout->addWidget(cb_config);
    layout->addWidget(cb_phs);
    layout->addWidget(cb_save);
    setLayout(layout);
}
void MenuListWidget::updateText()
{
    QString aString = tr("Allowed");
    QString vString = tr("Visible");

    lbl_title->setText(tr("Menu Manager"));
    cb_item->setText(tr("Item"));
    cb_item->setBoxToolTip(1, aString);
    cb_item->setBoxToolTip(2, vString);

    cb_magic->setText(tr("Magic"));
    cb_magic->setBoxToolTip(1, aString);
    cb_magic->setBoxToolTip(2, vString);

    cb_materia->setText(tr("Materia"));
    cb_materia->setBoxToolTip(1, aString);
    cb_materia->setBoxToolTip(2, vString);

    cb_equip->setText(tr("Equip"));
    cb_equip->setBoxToolTip(1, aString);
    cb_equip->setBoxToolTip(2, vString);

    cb_status->setText(tr("Status"));
    cb_status->setBoxToolTip(1, aString);
    cb_status->setBoxToolTip(2, vString);

    cb_order->setText(tr("Order"));
    cb_order->setBoxToolTip(1, aString);
    cb_order->setBoxToolTip(2, vString);

    cb_limit->setText(tr("Limit"));
    cb_limit->setBoxToolTip(1, aString);
    cb_limit->setBoxToolTip(2, vString);

    cb_config->setText(tr("Config"));
    cb_config->setBoxToolTip(1, aString);
    cb_config->setBoxToolTip(2, vString);

    cb_phs->setText(tr("P.H.S"));
    cb_phs->setBoxToolTip(1, aString);
    cb_phs->setBoxToolTip(2, vString);

    cb_save->setText(tr("Save"));
    cb_save->setBoxToolTip(1, aString);
    cb_save->setBoxToolTip(2, vString);
}

void MenuListWidget::setChecked(int row, int box, bool checked)
{
    disconnectAll();
    switch (row) {
    case 0: cb_item->setChecked(box, checked); break;
    case 1: cb_magic->setChecked(box, checked); break;
    case 2: cb_materia->setChecked(box, checked); break;
    case 3: cb_equip->setChecked(box, checked); break;
    case 4: cb_status->setChecked(box, checked); break;
    case 5: cb_order->setChecked(box, checked); break;
    case 6: cb_limit->setChecked(box, checked); break;
    case 7: cb_config->setChecked(box, checked); break;
    case 8: cb_phs->setChecked(box, checked); break;
    case 9: cb_save->setChecked(box, checked); break;
    };
    connectAll();
}
void MenuListWidget::cb_item_one_toggled(bool checked)
{
    emit(visibleToggled(0, checked));
}
void MenuListWidget::cb_item_two_toggled(bool checked)
{
    emit(lockedToggled(0, checked));
}
void MenuListWidget::cb_magic_one_toggled(bool checked)
{
    emit(visibleToggled(1, checked));
}
void MenuListWidget::cb_magic_two_toggled(bool checked)
{
    emit(lockedToggled(1, checked));
}
void MenuListWidget::cb_materia_one_toggled(bool checked)
{
    emit(visibleToggled(2, checked));
}
void MenuListWidget::cb_materia_two_toggled(bool checked)
{
    emit(lockedToggled(2, checked));
}
void MenuListWidget::cb_equip_one_toggled(bool checked)
{
    emit(visibleToggled(3, checked));
}
void MenuListWidget::cb_equip_two_toggled(bool checked)
{
    emit(lockedToggled(3, checked));
}
void MenuListWidget::cb_status_one_toggled(bool checked)
{
    emit(visibleToggled(4, checked));
}
void MenuListWidget::cb_status_two_toggled(bool checked)
{
    emit(lockedToggled(4, checked));
}
void MenuListWidget::cb_order_one_toggled(bool checked)
{
    emit(visibleToggled(5, checked));
}
void MenuListWidget::cb_order_two_toggled(bool checked)
{
    emit(lockedToggled(5, checked));
}
void MenuListWidget::cb_limit_one_toggled(bool checked)
{
    emit(visibleToggled(6, checked));
}
void MenuListWidget::cb_limit_two_toggled(bool checked)
{
    emit(lockedToggled(6, checked));
}
void MenuListWidget::cb_config_one_toggled(bool checked)
{
    emit(visibleToggled(7, checked));
}
void MenuListWidget::cb_config_two_toggled(bool checked)
{
    emit(lockedToggled(7, checked));
}
void MenuListWidget::cb_phs_one_toggled(bool checked)
{
    emit(visibleToggled(8, checked));
}
void MenuListWidget::cb_phs_two_toggled(bool checked)
{
    emit(lockedToggled(8, checked));
}
void MenuListWidget::cb_save_one_toggled(bool checked)
{
    emit(visibleToggled(9, checked));
}
void MenuListWidget::cb_save_two_toggled(bool checked)
{
    emit(lockedToggled(9, checked));
}

void MenuListWidget::connectAll()
{
    connect(cb_item, SIGNAL(box1_toggled(bool)), this, SLOT(cb_item_one_toggled(bool)));
    connect(cb_item, SIGNAL(box2_toggled(bool)), this, SLOT(cb_item_two_toggled(bool)));
    connect(cb_magic, SIGNAL(box1_toggled(bool)), this, SLOT(cb_magic_one_toggled(bool)));
    connect(cb_magic, SIGNAL(box2_toggled(bool)), this, SLOT(cb_magic_two_toggled(bool)));
    connect(cb_materia, SIGNAL(box1_toggled(bool)), this, SLOT(cb_materia_one_toggled(bool)));
    connect(cb_materia, SIGNAL(box2_toggled(bool)), this, SLOT(cb_materia_two_toggled(bool)));
    connect(cb_equip, SIGNAL(box1_toggled(bool)), this, SLOT(cb_equip_one_toggled(bool)));
    connect(cb_equip, SIGNAL(box2_toggled(bool)), this, SLOT(cb_equip_two_toggled(bool)));
    connect(cb_status, SIGNAL(box1_toggled(bool)), this, SLOT(cb_status_one_toggled(bool)));
    connect(cb_status, SIGNAL(box2_toggled(bool)), this, SLOT(cb_status_two_toggled(bool)));
    connect(cb_order, SIGNAL(box1_toggled(bool)), this, SLOT(cb_order_one_toggled(bool)));
    connect(cb_order, SIGNAL(box2_toggled(bool)), this, SLOT(cb_order_two_toggled(bool)));
    connect(cb_limit, SIGNAL(box1_toggled(bool)), this, SLOT(cb_limit_one_toggled(bool)));
    connect(cb_limit, SIGNAL(box2_toggled(bool)), this, SLOT(cb_limit_two_toggled(bool)));
    connect(cb_config, SIGNAL(box1_toggled(bool)), this, SLOT(cb_config_one_toggled(bool)));
    connect(cb_config, SIGNAL(box2_toggled(bool)), this, SLOT(cb_config_two_toggled(bool)));
    connect(cb_phs, SIGNAL(box1_toggled(bool)), this, SLOT(cb_phs_one_toggled(bool)));
    connect(cb_phs, SIGNAL(box2_toggled(bool)), this, SLOT(cb_phs_two_toggled(bool)));
    connect(cb_save, SIGNAL(box1_toggled(bool)), this, SLOT(cb_save_one_toggled(bool)));
    connect(cb_save, SIGNAL(box2_toggled(bool)), this, SLOT(cb_save_two_toggled(bool)));
}
void MenuListWidget::disconnectAll()
{
    disconnect(cb_item, SIGNAL(box1_toggled(bool)), this, SLOT(cb_item_one_toggled(bool)));
    disconnect(cb_item, SIGNAL(box2_toggled(bool)), this, SLOT(cb_item_two_toggled(bool)));
    disconnect(cb_magic, SIGNAL(box1_toggled(bool)), this, SLOT(cb_magic_one_toggled(bool)));
    disconnect(cb_magic, SIGNAL(box2_toggled(bool)), this, SLOT(cb_magic_two_toggled(bool)));
    disconnect(cb_materia, SIGNAL(box1_toggled(bool)), this, SLOT(cb_materia_one_toggled(bool)));
    disconnect(cb_materia, SIGNAL(box2_toggled(bool)), this, SLOT(cb_materia_two_toggled(bool)));
    disconnect(cb_equip, SIGNAL(box1_toggled(bool)), this, SLOT(cb_equip_one_toggled(bool)));
    disconnect(cb_equip, SIGNAL(box2_toggled(bool)), this, SLOT(cb_equip_two_toggled(bool)));
    disconnect(cb_status, SIGNAL(box1_toggled(bool)), this, SLOT(cb_status_one_toggled(bool)));
    disconnect(cb_status, SIGNAL(box2_toggled(bool)), this, SLOT(cb_status_two_toggled(bool)));
    disconnect(cb_order, SIGNAL(box1_toggled(bool)), this, SLOT(cb_order_one_toggled(bool)));
    disconnect(cb_order, SIGNAL(box2_toggled(bool)), this, SLOT(cb_order_two_toggled(bool)));
    disconnect(cb_limit, SIGNAL(box1_toggled(bool)), this, SLOT(cb_limit_one_toggled(bool)));
    disconnect(cb_limit, SIGNAL(box2_toggled(bool)), this, SLOT(cb_limit_two_toggled(bool)));
    disconnect(cb_config, SIGNAL(box1_toggled(bool)), this, SLOT(cb_config_one_toggled(bool)));
    disconnect(cb_config, SIGNAL(box2_toggled(bool)), this, SLOT(cb_config_two_toggled(bool)));
    disconnect(cb_phs, SIGNAL(box1_toggled(bool)), this, SLOT(cb_phs_one_toggled(bool)));
    disconnect(cb_phs, SIGNAL(box2_toggled(bool)), this, SLOT(cb_phs_two_toggled(bool)));
    disconnect(cb_save, SIGNAL(box1_toggled(bool)), this, SLOT(cb_save_one_toggled(bool)));
    disconnect(cb_save, SIGNAL(box2_toggled(bool)), this, SLOT(cb_save_two_toggled(bool)));
}
