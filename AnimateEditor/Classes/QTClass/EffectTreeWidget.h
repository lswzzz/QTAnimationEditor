#pragma once
#include <QTreeWidget>

class EffectTreeWidget : public QTreeWidget
{
	Q_OBJECT
public:
	EffectTreeWidget(QWidget* parent = 0);
	~EffectTreeWidget();
};

