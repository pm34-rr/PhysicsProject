#pragma once

#include <QtWidgets/QMainWindow>

namespace Ui {
	class manual;
}

class Manual : public QMainWindow
{
    Q_OBJECT
    
public:
	explicit Manual( QWidget * parent = 0 );
	~Manual();
    
private:
    Ui::manual *ui;
};
