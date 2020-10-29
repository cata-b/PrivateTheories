#pragma once
#include <qabstractitemmodel.h>
#include "Repository.h"

class StandardClearanceTableModel : public QAbstractTableModel
{
private:
	const Repository& repository;

public:
	StandardClearanceTableModel(const Repository& Repository, QObject* parent = nullptr);
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	void refresh();

	~StandardClearanceTableModel()
	{
	};
};
