#include "DatabaseGUI.h"
#include <commctrl.h>
#include <string>
#include <sstream>

#pragma comment(lib, "comctl32.lib")

// Идентификаторы элементов управления
#define ID_LIST_BOX             1001
#define ID_BTN_ADD              1002
#define ID_BTN_EDIT             1003
#define ID_BTN_DELETE           1004
#define ID_BTN_REFRESH          1005
#define ID_TAB_CONTROL          1006

DatabaseGUI::DatabaseGUI(DatabaseManager& db) : dbManager(db), hMainWindow(nullptr), hListBox(nullptr), currentMode(MODE_OFFICE_EQUIPMENT) {}

DatabaseGUI::~DatabaseGUI() {}

void DatabaseGUI::Run() {
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = "DatabaseGUI";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    
    RegisterClassEx(&wc);
    
    hMainWindow = CreateWindowEx(0, "DatabaseGUI", "Management Office Equipment",
                                  WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                                  900, 600, nullptr, nullptr, wc.hInstance, this);
    
    if (!hMainWindow) return;
    
    ShowWindow(hMainWindow, SW_SHOW);
    UpdateWindow(hMainWindow);
    
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK DatabaseGUI::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    DatabaseGUI* pThis = nullptr;
    
    if (msg == WM_NCCREATE) {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        pThis = reinterpret_cast<DatabaseGUI*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    } else {
        pThis = reinterpret_cast<DatabaseGUI*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }
    
    if (pThis) {
        return pThis->HandleMessage(msg, wParam, lParam);
    }
    
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT DatabaseGUI::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            CreateControls();
            RefreshList();
            break;
            
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case ID_BTN_ADD:
                    ShowAddDialog();
                    break;
                case ID_BTN_EDIT:
                    if (SendMessage(hListBox, LB_GETCURSEL, 0, 0) != LB_ERR) {
                        ShowEditDialog();
                    }
                    break;
                case ID_BTN_DELETE:
                    if (SendMessage(hListBox, LB_GETCURSEL, 0, 0) != LB_ERR) {
                        int id = (int)SendMessage(hListBox, LB_GETITEMDATA, SendMessage(hListBox, LB_GETCURSEL, 0, 0), 0);
                        ShowDeleteConfirm(id);
                    }
                    break;
                case ID_BTN_REFRESH:
                    RefreshList();
                    break;
            }
            break;
            
        case WM_NOTIFY:
            if (LOWORD(wParam) == ID_TAB_CONTROL) {
                NMHDR* nmhdr = (NMHDR*)lParam;
                if (nmhdr->code == TCN_SELCHANGE) {
                    int sel = TabCtrl_GetCurSel(hTabControl);
                    currentMode = static_cast<Mode>(sel);
                    RefreshList();
                }
            }
            break;
            
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
            
        default:
            return DefWindowProc(hMainWindow, msg, wParam, lParam);
    }
    return 0;
}

void DatabaseGUI::CreateControls() {
    // Создание вкладок
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_TAB_CLASSES;
    InitCommonControlsEx(&icex);
    
    hTabControl = CreateWindow(WC_TABCONTROL, "", WS_CHILD | WS_VISIBLE | TCS_FIXEDWIDTH,
                                10, 10, 300, 40, hMainWindow, (HMENU)ID_TAB_CONTROL, GetModuleHandle(nullptr), nullptr);
    
    TCITEM tie = {};
    tie.mask = TCIF_TEXT;
    
    char text1[] = "Equipment";
    char text2[] = "Printers";
    char text3[] = "Faxes";
    
    tie.pszText = text1;
    TabCtrl_InsertItem(hTabControl, 0, &tie);
    tie.pszText = text2;
    TabCtrl_InsertItem(hTabControl, 1, &tie);
    tie.pszText = text3;
    TabCtrl_InsertItem(hTabControl, 2, &tie);
    
    // Создание списка
    hListBox = CreateWindow("LISTBOX", "", WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY | LBS_HASSTRINGS | WS_VSCROLL,
                            10, 60, 500, 450, hMainWindow, (HMENU)ID_LIST_BOX, GetModuleHandle(nullptr), nullptr);
    
    // Кнопки
    CreateWindow("BUTTON", "Add", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 530, 60, 100, 35, hMainWindow, (HMENU)ID_BTN_ADD, GetModuleHandle(nullptr), nullptr);
    
    CreateWindow("BUTTON", "Edit", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 530, 105, 100, 35, hMainWindow, (HMENU)ID_BTN_EDIT, GetModuleHandle(nullptr), nullptr);
    
    CreateWindow("BUTTON", "Delete", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 530, 150, 100, 35, hMainWindow, (HMENU)ID_BTN_DELETE, GetModuleHandle(nullptr), nullptr);
    
    CreateWindow("BUTTON", "Refresh", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 530, 195, 100, 35, hMainWindow, (HMENU)ID_BTN_REFRESH, GetModuleHandle(nullptr), nullptr);
    
    // Информационная метка
    CreateWindow("STATIC", "Select an item from the list", WS_CHILD | WS_VISIBLE,
                 10, 520, 500, 20, hMainWindow, nullptr, GetModuleHandle(nullptr), nullptr);
}

void DatabaseGUI::RefreshList() {
    SendMessage(hListBox, LB_RESETCONTENT, 0, 0);
    
    std::stringstream ss;
    
    if (currentMode == MODE_OFFICE_EQUIPMENT) {
        auto items = dbManager.getAllOfficeEquipment();
        int id = 1;
        for (const auto& item : items) {
            ss.str("");
            ss << "ID:" << id << " | " << item.getModel() << " | " 
               << static_cast<int>(item.getManufacturerEnum()) << " | " 
               << item.getYearOfManufacture() << " | $" << item.getPrice();
            std::string str = ss.str();
            int idx = SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)str.c_str());
            SendMessage(hListBox, LB_SETITEMDATA, idx, id);
            id++;
        }
    } else if (currentMode == MODE_PRINTER) {
        auto items = dbManager.getAllPrinters();
        int id = 1;
        for (const auto& item : items) {
            ss.str("");
            ss << "ID:" << id << " | " << item.getModel() << " | " 
               << item.getPrintSpeedPPM() << " PPM | " << item.getPrintResolutionDPI() << " DPI";
            std::string str = ss.str();
            int idx = SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)str.c_str());
            SendMessage(hListBox, LB_SETITEMDATA, idx, id);
            id++;
        }
    } else if (currentMode == MODE_FAX) {
        auto items = dbManager.getAllFaxes();
        int id = 1;
        for (const auto& item : items) {
            ss.str("");
            ss << "ID:" << id << " | " << item.getModel() << " | " 
               << item.getTransmissionSpeedBPS() << " bps | " << item.getMemoryCapacityPages() << " pages";
            std::string str = ss.str();
            int idx = SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)str.c_str());
            SendMessage(hListBox, LB_SETITEMDATA, idx, id);
            id++;
        }
    }
}

void DatabaseGUI::ShowAddDialog() {
    MessageBox(hMainWindow, "Add function via console", "Information", MB_OK);
}

void DatabaseGUI::ShowEditDialog() {
    MessageBox(hMainWindow, "Edit function via console", "Information", MB_OK);
}

void DatabaseGUI::ShowDeleteConfirm(int id) {
    char msg[256];
    sprintf(msg, "Delete item ID: %d?", id);
    
    if (MessageBox(hMainWindow, msg, "Confirm deletion", MB_YESNO) == IDYES) {
        if (currentMode == MODE_OFFICE_EQUIPMENT) {
            dbManager.deleteOfficeEquipment(id);
        } else if (currentMode == MODE_PRINTER) {
            dbManager.deletePrinter(id);
        } else if (currentMode == MODE_FAX) {
            dbManager.deleteFax(id);
        }
        RefreshList();
    }
}