#include <QMap>
#include "tooltip.h"
#include "gearratiographitem.h"

GearRatioGraphItem::GearRatioGraphItem(const Graph &graph, GraphType type,
  QGraphicsItem *parent) : GraphItem(graph, type, parent), _top(NAN)
{
	qreal val = NAN;

	for (int j = 1; j < graph.size(); j++) {
		const GraphPoint &p = graph.at(j);
		qreal val = _map.value(p.y());
		_map.insert(p.y(), val + (p.s() - graph.at(j-1).s()));
	}

	for (QMap<qreal, qreal>::const_iterator it = _map.constBegin();
	  it != _map.constEnd(); ++it) {
		if (it == _map.constBegin()) {
			val = it.value();
			_top = it.key();
		} else if (it.value() > val) {
			val = it.value();
			_top = it.key();
		}
	}

	setToolTip(toolTip());
}

QString GearRatioGraphItem::toolTip() const
{
	ToolTip tt;

	tt.insert(tr("Minimum"), QString::number(min(), 'f', 2));
	tt.insert(tr("Maximum"), QString::number(max(), 'f', 2));
	tt.insert(tr("Most used"), QString::number(top(), 'f', 2));

	return tt.toString();
}
