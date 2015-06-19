#pragma once

#include <QtWidgets/QWidget>

class Graph : public QWidget
{
	Q_OBJECT
public:
	explicit Graph( QWidget * parent, const QString & dependenceType );
	~Graph();

protected:
	virtual void paintEvent( QPaintEvent * event );

private:
	void drawPlot( int x, int y, int number );
	void drawColorTable( int n );

	double	_period;
	double	_gridStepX;
	double	_gridStepY;
	bool	_dataDefined;
	int		_countOfFuncPoints;
	QString _depX;
	QString _depY;

	std::vector<std::vector<double> >	_X;
	std::vector<std::vector<double> >	_V;
	std::vector<QColor>					_colors;
};
