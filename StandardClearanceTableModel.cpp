#include "StandardClearanceTableModel.h"

void StandardClearanceTableModel::refresh()
{
	emit layoutChanged();
}

StandardClearanceTableModel::StandardClearanceTableModel(const Repository& Repository, QObject* parent)
	:
	QAbstractTableModel(parent),
	repository(Repository)
{
};

int StandardClearanceTableModel::rowCount(const QModelIndex& parent) const
{
	return repository.Size();
}

int StandardClearanceTableModel::columnCount(const QModelIndex& parent) const
{
	return 5; // number of fields in Evidence.h
}

QVariant StandardClearanceTableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row(), column = index.column();
	if (role == Qt::DisplayRole)
		return QString::fromStdString(to_string(repository.AtIndex(row))).split(
			",", Qt::SplitBehaviorFlags::SkipEmptyParts)[column];
	if (role == Qt::SizeHintRole)
		return Qt::SizeHint::NSizeHints;
	return QVariant();
}

QVariant StandardClearanceTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
			return QStringList{"ID", "Measurement", "Image Clarity Level", "Quantity", "Photograph"}[section];
		return section;
	}
	return QVariant();
}
