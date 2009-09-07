#ifndef mifit_ui_ViewSyncedPanel_h
#define mifit_ui_ViewSyncedPanel_h

#include <QWidget>
#include <map>

#include "core/MIData.h"

class MIGLWidget;
class QStackedLayout;

class ViewSyncedPanel : public QWidget {
  Q_OBJECT

protected:
  QStackedLayout* stackedLayout;
  typedef std::map<MIGLWidget*, QWidget*> ViewToPanelMap;
  ViewToPanelMap viewToPanel;

  void createViewPanel(MIGLWidget* view);
  void createDefaultNullPanel();
  void setViewPanel(MIGLWidget* view);
  bool panelForViewExists(MIGLWidget* view);

  virtual QWidget* createPanelForView(MIGLWidget* view, QWidget* parent) = 0;
  virtual void destroyContentsForView(MIGLWidget* view, QWidget* panel) = 0;

protected slots:
  virtual void viewActivated(MIGLWidget* view);
  virtual void viewDeactivated(MIGLWidget* view);

public:

  ViewSyncedPanel(QWidget* parent);
  virtual ~ViewSyncedPanel();

  virtual bool HandleHistory(MIData&) {
    return false;
  }

  virtual bool RandomTest() {
    return false;
  }

};

#endif
