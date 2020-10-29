#pragma once

#include <QStyledItemDelegate>

class EvidenceImageViewerDelegate : public QStyledItemDelegate
{
Q_OBJECT
private:
	int column;
public:
	EvidenceImageViewerDelegate(int Column, QObject* parent = Q_NULLPTR);
	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option,
	                 const QModelIndex& index) override;
};
