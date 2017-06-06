#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>

namespace Ui {
class InputDialog;
}

class InputDialog : public QDialog
{
  Q_OBJECT

public:
  explicit InputDialog(QWidget *parent = 0);
  ~InputDialog();
  void set_title(const QString &title, int selection);

signals:
  void user_input(int user_selection, int user_input);

private slots:
  void set_number();
  void delete_number();
  void check_user_input();

private:
  Ui::InputDialog *ui;
  int m_selection;
  int m_runs;
  int m_preparation_time;
  int m_shoot_time;

  bool check_number_of_runs();
  bool check_preparation_time();
  bool check_shoot_time();
};

#endif // INPUTDIALOG_H
