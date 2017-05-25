#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ControlUnit.h"

class ControlUnit : public QMainWindow
{
	Q_OBJECT

public:
	ControlUnit(QWidget *parent = Q_NULLPTR);

private:
	Ui::ControlUnitClass ui;
};
