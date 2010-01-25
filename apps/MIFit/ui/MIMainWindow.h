#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QMenu;
class QMdiArea;
class QMdiSubWindow;
class MIGLWidget;
class QSignalMapper;
class QListWidget;
class QTextEdit;
class QDockWidget;
class QLabel;
class QCursor;

class MIActionEvent;
class MIMenuBar;
class MIToolBar;
class GLOverviewCanvas;
class BatchJobManager;
class RamaPlotMgr;
class DependantActions;

namespace chemlib
{
    class MIMolInfo;
}

#include "MIEventHandler.h"

//cursor constants
const unsigned int imhCross = 0; // Cross cursor used to pick on canvas.
const unsigned int imhTranslate = 1; // Translate cursor used to indicate a translation operation.
const unsigned int imhRotate = 2; // Rotate cursor used to indicate a rotation operation.
const unsigned int imhZRotate = 3; // Z rotation cursor used to indicate a Z-rotation operation.
const unsigned int imhZCursor = 4; // Indicates cursor in the z rotation area which ids the top 30 pixels of the canvas.
const unsigned int imhTorsion = 5; // Torsion operation cusor indicating a bond is being twisted.
const unsigned int imhCenter = 6; // Centering operation cursor.
const unsigned int imhScale = 7; // Scale/zoom operation cursor.
const unsigned int imhSlab = 8; // Slab operation cursor indicating the slab plane is being moved.
const unsigned int imhWait1 = 9; // Animated wait cursor.
const unsigned int imhWait2 = 10; // Animated wait cursor.
const unsigned int imhWait3 = 11; // Animated wait cursor.
const unsigned int imhWait4 = 12; // Animated wait cursor.
const unsigned int imhWait5 = 13; // Animated wait cursor.
const unsigned int imhWait6 = 14; // Animated wait cursor.
const unsigned int imhSlabDrag = 15; // Slab drag operation
const unsigned int imhCount = 16; // Number of cursors


class ViewSyncedPanel;

class MIMainWindow : public QMainWindow, public MIEventHandler
{
    Q_OBJECT

    static MIMainWindow *_instance;
    MIMainWindow();

    QDockWidget *modelsDock;
    QDockWidget *displayDock;
    QDockWidget *jobsDock;
    QDockWidget *logDock;
    QDockWidget *navigatorDock;
    QDockWidget *ramaDock;

    MIMenu *canvas_menu;
    DependantActions *refineDependantActions;

public:
    static MIMainWindow *instance();
    ~MIMainWindow();

public slots:
    void Log(const std::string &str);
    void Debug(const std::string &str);
    void RightFooter(const std::string &str);
    void MiddleFooter(const std::string &str);
    void LeftFooter(const std::string &str, int timeout = 0);
    void UpdateToolBar();

public:
    MIGLWidget *currentMIGLWidget();
    QMdiArea *getMdiArea();
    void setActiveMIGLWidget(MIGLWidget *w);

    QDockWidget *AddAsDockWidget(QWidget *w, const std::string &name, Qt::DockWidgetArea area);

    MIMenuBar *getMenuBar()
    {
        return menu_bar;
    }

    // if widget is 0, set on the whole app
    // if id < 0, restore default cursor
    void SetCursor(int id, QWidget *widget = 0);

    void fill_surf_menu(QMenu*);

    void OpenFiles(const std::vector<std::string> &files, bool newWindow = false);

    BatchJobManager *GetJobManager();
    bool isJobLimit();

    void updateNavigator();
    RamaPlotMgr *RamaPlotManager();

    ViewSyncedPanel *GetModelsTree()
    {
        return modelsView;
    }

    void addRecentFileActions(QMenu*);
    void setCurrentFile(const std::string &fname);

private slots:
    void OnClose();
    void OnExit();
    void OnNew();
    void OnFileOpen();
    void OnFileOpenNew();

    void OnFileSave();
    void OnFileSaveAs();
    void OnExportModel();
    void OnPrint();
    void OnEditCopy();
    void OnExportImage();

    void OnScript();

    //dictionary menu handlers
    void OnSaveDict();
    void OnLoadLigCif();
    void OnLoadLigMol();
    void OnLoadLigPdb();
    void OnLoadLigSmi();
    void OnLoadDictAppend();
    void OnLoadDictReplace();
    void OnEditDictResidue();

    void OnBackgroundColor();
    void OnSideChainTool();
    void OnHideTool();
    void OnColorTool();
    void OnShowTool();

    void OnUpdateStereoToggle(const MIUpdateEvent&);
    void OnUpdateHardwareStereo(const MIUpdateEvent&);
    void OnStereoToggle();
    void OnHardwareStereo();
    void OnAbout();
    void OnGLFormat();
    void OnHelp();
    void OnMenuValidate();
    void OnDefineAtomColors();
    void OnDefineBValueColors();
    void OnManageCrystals();
    void OnPreferences();

    void HasCurrentMIGLWidget(const MIUpdateEvent&);

    void fileOpen();
    void newWindow();
    void updateMenus();
    void childActivated(QMdiSubWindow*);
    void updateWindowMenu();
    QWidget *createMIGLWidget();
    void switchLayoutDirection();
    void setActiveSubWindow(QWidget *window);
    void AfterInit();

    void openRecentFile();

    void updateShowMenu();
    void updateIsRefining(bool isRefining);

    void updateFileMenu();

    void setRenderLineThickness(int thickness);
    void updateRenderMenu();

private:
    enum { MaxRecentFiles = 6 };
    QAction *recentFileActs[MaxRecentFiles];
    void updateRecentFileActions();

    std::string OnLoadLigand(std::string wildcard, std::string filename, std::string smiles, std::string code);
    void ShowDictEditor(const char *type);
    bool LoadSmiles(std::string &smiles, std::string &tlcode, chemlib::MIMolInfo &mi);

    void closeEvent(QCloseEvent *event);
    void saveLayout();

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockWindows();
    void initMenuHandlers();

    void fill_file_menu(QMenu *file_menu);
    void fill_view_menu(MIMenu *view_menu);

    QMdiSubWindow *findMIGLWidget(const QString &fileName);

    MIMenuBar *menu_bar;
    MIToolBar *tool_bar;

    QMdiArea *mdiArea;
    QSignalMapper *windowMapper;

    QTextEdit *logWindow;

    MIMenu *side_menu;
    MIMenu *hide_menu;
    MIMenu *color_menu;
    MIMenu *view_menu;
    MIMenu *show_menu;
    QMenu *render_menu;
    MIMenu *model_menu;
    MIMenu *fit_menu;
    MIMenu *refi_menu;
    MIMenu *analyze_menu;
    QAction *solidSurfMenuAction;
    QMenu *windowMenu;
    QMenu *viewMenu;

    // file menu actions;
    QAction *fileNewAction;
    QAction *fileOpenAction;
    QAction *fileSaveAction;
    QAction *fileSaveAsAction;
    QAction *exportModelAction;
    QAction *filePrintAction;
    QAction *copyCanvasAction;
    QAction *exportImageAction;
    QAction *closeAction;

    // window menu actions
    QAction *closeAct;
    QAction *closeAllAct;
    QAction *tileAct;
    QAction *cascadeAct;
    QAction *nextAct;
    QAction *previousAct;

    // edit menu actions
    //QAction *cutAct;
    //QAction *copyAct;
    //QAction *pasteAct;

    QAction *refineResidueAction;
    QAction *acceptRefineAction;

    QLabel *middleFooter;
    QLabel *rightFooter;

    QCursor *cursors[imhCount];


    GLOverviewCanvas *navigator;

    BatchJobManager *JobManager;
    ViewSyncedPanel *modelsView;
    RamaPlotMgr *ramaPlotMgr;

    QMenu *renderLineThicknessMenu_;
};

//some shortcuts for MIMainWindow::instance()->Log, etc
void MIMainWindowLog(const std::string&);
void MIMainWindowDebug(const std::string&);
void MIMainWindowLeftFooter(const std::string&, int timeout = 0);
void MIMainWindowMiddleFooter(const std::string&);
void MIMainWindowRightFooter(const std::string&);

#endif // ifndef MAINWINDOW_H
