#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cairomm/context.h>
#include <cmath>
#include <glibmm/main.h>
#include <gtkmm/drawingarea.h>
#include <tuple>
#include <vector>

namespace KOROKU {

enum BrushSelect {
  ERASER_BRUSH = 0,
  PRIMARY_BRUSH = 1,
};

// class
class BrushParam {
public:
  BrushParam();
  ~BrushParam();
  double width;
  double red;
  double green;
  double blue;
  double alpha;
};

BrushParam::BrushParam() {
  this->width = 1;
  this->red = 0;
  this->green = 0;
  this->blue = 0;
  this->alpha = 1;
}

BrushParam::~BrushParam() {}

// class
class Brush {
public:
  Brush(double, double, double, double, double);
  bool addPoint(double, double);
  bool isEraser;
  virtual ~Brush();
  KOROKU::BrushParam brushParam;
  std::vector<std::tuple<double, double>> stroke;
};

Brush::Brush(double width, double red, double green, double blue,
             double alpha) {
  this->brushParam.width = width;
  this->brushParam.red = red;
  this->brushParam.green = green;
  this->brushParam.blue = blue;
  this->brushParam.alpha = alpha;
  this->isEraser = false;
}

// add point to Brush
bool Brush::addPoint(double x, double y) {
  this->stroke.push_back(std::make_tuple(x, y));
  return true;
}

Brush::~Brush() {}

// class
class Canvas : public Gtk::DrawingArea {
public:
  // Constructor
  Canvas();
  virtual ~Canvas();

  // BrushColor & width
  KOROKU::BrushParam primaryBrushParam, eraserBrushParam;
  void setPrimaryBrushRGB(double, double, double);
  void setPrimaryBrushWidth(double);
  void setEraserBrushWidth(double);
  // redo & undo
  void undo();
  void redo();

  void setBrushSelect(int);
  void eraseAll();

private:
  bool canUndo();
  bool canRedo();
  void resetRedoBrush();
  int brushSelect;
  int mouseX;
  int mouseY;

protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;
  virtual bool on_mouse_move(GdkEventMotion *event);
  virtual bool on_mouse_press(GdkEventButton *event);

private:
  std::vector<Brush> Brushes;     // Process
  std::vector<Brush> redoBrushes; // redoProcess
};

Canvas::Canvas() {
  add_events(Gdk::BUTTON_PRESS_MASK | Gdk::POINTER_MOTION_MASK |
             Gdk::BUTTON_RELEASE_MASK);
  signal_button_press_event().connect(
      sigc::mem_fun(*this, &Canvas::on_mouse_press));
  signal_motion_notify_event().connect(
      sigc::mem_fun(*this, &Canvas::on_mouse_move));
  brushSelect = PRIMARY_BRUSH;
  eraserBrushParam.width = 10;
  this->mouseX = -50;
  this->mouseY = -50;
}

Canvas::~Canvas() {}

bool Canvas::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
  cr->set_source_rgba(1.0, 1.0, 1.0, 0.5);
  cr->paint();
  for (auto BrushesItr = this->Brushes.begin();
       BrushesItr != this->Brushes.end(); ++BrushesItr) {
    if (BrushesItr->isEraser) {
      cr->set_operator(Cairo::OPERATOR_SOURCE);
    } else {
      cr->set_operator(Cairo::OPERATOR_OVER);
    }
    cr->set_source_rgba(
        BrushesItr->brushParam.red, BrushesItr->brushParam.green,
        BrushesItr->brushParam.blue, BrushesItr->brushParam.alpha);
    cr->set_line_width(BrushesItr->brushParam.width);
    cr->set_line_cap(Cairo::LINE_CAP_ROUND);
    cr->set_line_join(Cairo::LINE_JOIN_ROUND);

    for (auto PointItr = BrushesItr->stroke.begin();
         PointItr != BrushesItr->stroke.end(); ++PointItr) {
      cr->line_to(std::get<0>(*PointItr), std::get<1>(*PointItr));
    }
    cr->stroke();
  }
  // if (brushSelect == PRIMARY_BRUSH) {
  cr->set_line_width(1);
  cr->set_source_rgba(0, 0, 0, 1);
  cr->arc(mouseX, mouseY, primaryBrushParam.width / 2, 0, 2 * M_PI);
  cr->stroke();
  //}
  return true;
}

bool Canvas::on_mouse_move(GdkEventMotion *event) {
  this->mouseX = event->x;
  this->mouseY = event->y;
  if (event->state & Gdk::EventMask::BUTTON_PRESS_MASK) {
    Brush *CurrentBrush = &this->Brushes.back();
    CurrentBrush->addPoint(event->x, event->y);
  }
  queue_draw();
  return true;
}

bool Canvas::on_mouse_press(GdkEventButton *event) {
  if (event->button == 1) {
    if (brushSelect == PRIMARY_BRUSH) {
      Brush brush = Brush(
          this->primaryBrushParam.width, this->primaryBrushParam.red,
          this->primaryBrushParam.green, this->primaryBrushParam.blue, 1.0);
      brush.addPoint(event->x, event->y);
      this->Brushes.push_back(brush);
    } else {
      Brush brush = Brush(this->eraserBrushParam.width, 1.0, 1.0, 1.0, 0.5);
      brush.isEraser = true;
      brush.addPoint(event->x, event->y);
      this->Brushes.push_back(brush);
    }

    this->resetRedoBrush();
    queue_draw();
  }
  return true;
}

void Canvas::undo() {
  if (this->canUndo()) {
    this->redoBrushes.push_back(this->Brushes.back());
    this->Brushes.pop_back();
    this->queue_draw();
  }
}
void Canvas::redo() {
  if (this->canRedo()) {
    this->Brushes.push_back(this->redoBrushes.back());
    this->redoBrushes.pop_back();
    this->queue_draw();
  }
}

bool Canvas::canUndo() { return !this->Brushes.empty(); }
bool Canvas::canRedo() { return !this->redoBrushes.empty(); }

void Canvas::resetRedoBrush() { this->redoBrushes.clear(); }

void Canvas::setPrimaryBrushRGB(double red, double green, double blue) {
  this->primaryBrushParam.red = red;
  this->primaryBrushParam.green = green;
  this->primaryBrushParam.blue = blue;
}

void Canvas::setPrimaryBrushWidth(double width) {
  this->primaryBrushParam.width = width;
}

void Canvas::setEraserBrushWidth(double width) {
  this->eraserBrushParam.width = width;
}

void Canvas::setBrushSelect(int brush) { this->brushSelect = brush; }

void Canvas::eraseAll() {
  this->Brushes.clear();
  this->redoBrushes.clear();
  this->queue_draw();
}

} // namespace KOROKU
