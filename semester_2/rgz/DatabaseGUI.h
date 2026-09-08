#ifndef DATABASE_GUI_H
#define DATABASE_GUI_H

#include <windows.h>
#include <commctrl.h>
#include "DatabaseManager.h"

class DatabaseGUI {
private:
    DatabaseManager& dbManager;
    HWND hMainWindow;
    HWND hListBox;
    HWND hTabControl;
    
    // Текущий режим
    enum Mode { MODE_OFFICE_EQUIPMENT, MODE_PRINTER, MODE_FAX } currentMode;
    
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);
    
    void CreateControls();
    void RefreshList();
    void ShowAddDialog();
    void ShowEditDialog();
    void ShowDeleteConfirm(int id);
    
public:
    DatabaseGUI(DatabaseManager& db);
    ~DatabaseGUI();
    
    void Run();
};

#endif // DATABASE_GUI_H