#pragma once

#include "../shvvisuglobal.h"

#include <QScrollArea>

namespace shv {
namespace visu {
namespace timeline {

class SHVVISU_DECL_EXPORT GraphView : public QScrollArea
{
	Q_OBJECT

	using Super = QScrollArea;
public:
	GraphView(QWidget *parent = nullptr);

	void makeLayout();
protected:
	void resizeEvent(QResizeEvent *event) override;
};

}}}

