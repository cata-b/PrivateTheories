#include "EvidenceImageViewerDelegate.h"
#include <QPicture>
#include <QPainter>
#include <QFileInfo>
#include <QLabel>
#include <QEvent>
#include <QApplication>
#include <QDesktopWidget>

EvidenceImageViewerDelegate::EvidenceImageViewerDelegate(int Column, QObject* parent)
	: QStyledItemDelegate(parent), column(Column)
{
}

void EvidenceImageViewerDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,
                                        const QModelIndex& index) const
{
	if (index.column() == column)
	{
		QString photograph_name = index.data().toString();
		QImage picture;
		if (picture.load(photograph_name))
		{
			painter->save();
			painter->drawImage(option.rect.topLeft(),
			                   picture.scaled(option.rect.width(), option.rect.height(), Qt::KeepAspectRatio));
			painter->restore();
			return;
		}
	}
	QStyledItemDelegate::paint(painter, option, index);
}

bool EvidenceImageViewerDelegate::editorEvent(QEvent* event, QAbstractItemModel* model,
                                              const QStyleOptionViewItem& option, const QModelIndex& index)
{
	if (event->type() == QEvent::Type::MouseButtonDblClick && index.column() == column)
	{
		QString photograph_name = index.data().toString();
		QPixmap picture;
		if (picture.load(photograph_name))
		{
			auto screen_rect = QApplication::desktop()->screenGeometry();
			if (picture.rect().width() > screen_rect.width() || picture.rect().height() > screen_rect.height())
				picture = picture.scaled(screen_rect.size(), Qt::KeepAspectRatio);
			QLabel* picture_frame = new QLabel();
			picture_frame->setPixmap(picture);
			picture_frame->setWindowFlags(Qt::Window);
			picture_frame->show();
			return true;
		}
	}
	return QStyledItemDelegate::editorEvent(event, model, option, index);
}
