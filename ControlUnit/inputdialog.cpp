#include "inputdialog.h"
#include "ui_inputdialog.h"

#include <QDebug>

InputDialog::InputDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::InputDialog)
{
  ui->setupUi(this);
  m_selection = 0;
  m_runs = 0;
  m_preparation_time = 0;
  m_shoot_time = 0;

  connect(ui->b_0, SIGNAL(clicked()), this, SLOT(set_number()));
  connect(ui->b_1, SIGNAL(clicked()), this, SLOT(set_number()));
  connect(ui->b_2, SIGNAL(clicked()), this, SLOT(set_number()));
  connect(ui->b_3, SIGNAL(clicked()), this, SLOT(set_number()));
  connect(ui->b_4, SIGNAL(clicked()), this, SLOT(set_number()));
  connect(ui->b_5, SIGNAL(clicked()), this, SLOT(set_number()));
  connect(ui->b_6, SIGNAL(clicked()), this, SLOT(set_number()));
  connect(ui->b_7, SIGNAL(clicked()), this, SLOT(set_number()));
  connect(ui->b_8, SIGNAL(clicked()), this, SLOT(set_number()));
  connect(ui->b_9, SIGNAL(clicked()), this, SLOT(set_number()));
  connect(ui->b_ok, SIGNAL(clicked()), this, SLOT(check_user_input()));
  connect(ui->b_cancel, SIGNAL(clicked()), this, SLOT(close()));
  connect(ui->b_del, SIGNAL(clicked()), this, SLOT(delete_number()));
  ui->l_number->setText("");
}

InputDialog::~InputDialog()
{
  delete ui;
}

void InputDialog::set_title(const QString &title, int selection)
{
  if ((!title.isEmpty()) && (!title.isNull()))
  {
    ui->l_title->setText(title);
    if ((selection > 0) && (selection < 4))
    {
      m_selection = selection;
    }
  }
  else
  {
    qDebug() << objectName() << " Function: setTitle - parameter is a nullpointer";
  }
}

void InputDialog::set_number()
{
  QString *sender_number = nullptr;
  QString number;
  switch (m_selection)
  {
  case 1: // Runs has only 1 sign
    sender_number = new QString(sender()->objectName());
    number = sender_number->mid(2,1);
    break;
  case 2: // PreparationTime
    sender_number = new QString(sender()->objectName());
    if (ui->l_number->text().size() < 2)
    {
      number = ui->l_number->text() + sender_number->mid(2,1);
    }
    else
    {
      number = sender_number->mid(2,1);
    }
    break;
  case 3: // ShootTime
    sender_number = new QString(sender()->objectName());
    if (ui->l_number->text().size() < 3)
    {
      number = ui->l_number->text() + sender_number->mid(2,1);
    }
    else
    {
      number = sender_number->mid(2,1);
    }
    break;
  default:

    break;
  }
  ui->l_number->setText(number);
}

void InputDialog::delete_number() {
	QString text;

	text = ui->l_number->text();
	if (text.length() == 1) {
		ui->l_number->setText("0");
	}
	else {
		if (text.length() > 1) {
			ui->l_number->setText(text.mid(0, text.length() - 1));
		}
	}
}

void InputDialog::check_user_input()
{
  bool user_input_ok;

  switch (m_selection)
  {
  case 1:
    user_input_ok = check_number_of_runs();
    if (user_input_ok)
    {
      emit user_input(m_selection, m_runs);
      close();
    }
    break;
  case 2:
    user_input_ok = check_preparation_time();
    if (user_input_ok)
    {
      emit user_input(m_selection, m_preparation_time);
      close();
    }
    break;
  case 3:
    user_input_ok = check_shoot_time();
    if (user_input_ok)
    {
      emit user_input(m_selection, m_shoot_time);
      close();
    }
    break;
  default:
    qDebug() << "no valid selected";
    user_input_ok = false;
    break;
  }
}

bool InputDialog::check_number_of_runs()
{
  int runs;

  runs = ui->l_number->text().toInt();
  if (runs > 0)
  {
    m_runs = runs;
    return true;
  }
  else
  {
    return false;
  }
}

bool InputDialog::check_preparation_time()
{
  int preparation_time;

  preparation_time = ui->l_number->text().toInt();
  // TODO: check minimum of preparation time
  if (preparation_time > 2)
  {
    m_preparation_time = preparation_time;
    return true;
  }
  else
  {
    return false;
  }
}

bool   InputDialog::check_shoot_time()
{
  int shoot_time;

  shoot_time = ui->l_number->text().toInt();
  // TODO: check minimum of preparation time
  if (shoot_time > 2)
  {
    m_shoot_time = shoot_time;
    return true;
  }
  else
  {
    return false;
  }
}
