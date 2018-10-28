#include "renderarea.h"
#include "jarvis_march.h"

#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>

#include <ctime>
#include <cstdlib>

using namespace std;

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{
  auto pal = palette();
  pal.setColor(QPalette::Background, Qt::black);
  setPalette(pal);
  setAutoFillBackground(true);

  selected = points.end();
  srand(time(nullptr));
}

auto RenderArea::minimumSizeHint() const -> QSize
{
  return QSize(100, 100);
}

auto RenderArea::sizeHint() const -> QSize
{
  return QSize(600, 1000);
}

void RenderArea::setPen(const QPen& pen)
{
  this->pen = pen;
  update();
}

void RenderArea::setBrush(const QBrush& brush)
{
  this->brush = brush;
  update();
}

void RenderArea::clearArea()
{
  points.clear();
  poly_mode = false;
  update();
}

void RenderArea::findHull()
{
    if (points.size() > 0)
    {
      poly_mode = true;
      hull.compute_hull(points);
      points.swap(hull.points);
      update();
    }
}

void RenderArea::paintEvent(QPaintEvent*)
{
  QPainter painter(this);

  if (poly_mode)
      drawHull(painter);

  for (auto& point: points)
    drawPoint(painter, point);
}

void RenderArea::drawHull(QPainter& painter)
{
  painter.setPen(QPen(Qt::blue, 2));
  QPainterPath path;
  auto& ps = points;
  for (auto i=0; i<hull.count; i++)
  {
    i == 0 ? path.moveTo(ps[i].x, ps[i].y)
           : path.lineTo(ps[i].x, ps[i].y);
  }

  path.closeSubpath();
  painter.drawPath(path);
}

void RenderArea::drawPoint(QPainter& painter, const Point& point)
{
  auto x = point.x;
  auto y = point.y;

  painter.setPen(QPen(QColor(255,165,0), 2));

  painter.setBrush(point.color);
  painter.drawRect(QRect(x - SZ , y - SZ, SZ * 2, SZ * 2));

  QPainterPath r;
  r.moveTo(x - SZ, y - SZ);
  r.lineTo(x - SZ, y + SZ);
  r.lineTo(x + SZ, y + SZ);
  r.lineTo(x + SZ, y - SZ);
  r.closeSubpath();

  painter.drawPath(r);
}

void RenderArea::mousePressEvent(QMouseEvent* event)
{
  if (event->button() != Qt::LeftButton)
      return;

  auto x = event->x();
  auto y = event->y();

  selected = find_if (points.begin(), points.end(),
                     [&](auto& p) { return p.located_near(x, y, SZ); });

  if (selected == points.end())
    points.emplace_back(x, y, randomColor());

  update();
}

void RenderArea::mouseReleaseEvent(QMouseEvent* event)
{
  if (event->button() == Qt::LeftButton)
    selected = points.end();
}

void RenderArea::mouseMoveEvent(QMouseEvent* event)
{
  if (selected != points.end())
  {
     auto index = distance(points.begin(), selected);
     points[index].x = event->x();
     points[index].y = event->y();
     update();
  }
}

auto RenderArea::randomColor() -> QColor
{
  static std::vector<QColor> colors = {
    Qt::black,   Qt::darkGray,  Qt::lightGray,
    Qt::white,   Qt::gray,      Qt::red,
    Qt::green,   Qt::blue,      Qt::cyan,
    Qt::yellow,  Qt::magenta,
    QColor(255,165,0),
    QColor(128,0,218),
    QColor(0,128,128)
  };

  auto r = rand() % 256;
  auto g = rand() % 256;
  auto b = rand() % 256;

  return QColor(r, g, b);
}