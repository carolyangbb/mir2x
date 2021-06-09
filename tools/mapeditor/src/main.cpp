/*
 * =====================================================================================
 *
 *       Filename: main.cpp
 *        Created: 08/31/2015 08:52:57 PM
 *    Description: 
 *
 *        Version: 1.0
 *       Revision: none
 *       Compiler: gcc
 *
 *         Author: ANHONG
 *          Email: anhonghe@gmail.com
 *   Organization: USTC
 *
 * =====================================================================================
 */

#include <string>
#include <cstdint>
#include <FL/Fl.H>

#include "imagedb.hpp"
#include "editormap.hpp"
#include "mainwindow.hpp"
#include "imagecache.hpp"
#include "animationdb.hpp"
#include "aboutwindow.hpp"
#include "animationdraw.hpp"
#include "progressbarwindow.hpp"
#include "layereditorwindow.hpp"
#include "layerbrowserwindow.hpp"
#include "cropconfigurewindow.hpp"
#include "selectsettingwindow.hpp"
#include "animationselectwindow.hpp"
#include "attributeselectwindow.hpp"

MainWindow                      *g_MainWindow               = nullptr;
SelectSettingWindow             *g_SelectSettingWindow      = nullptr;
AnimationSelectWindow           *g_AnimationSelectWindow    = nullptr;
AboutWindow                     *g_AboutWindow              = nullptr;
AttributeSelectWindow           *g_AttributeGridWindow      = nullptr;
AttributeSelectWindow           *g_AttributeSelectWindow    = nullptr;
ProgressBarWindow               *g_ProgressBarWindow        = nullptr;
LayerEditorWindow               *g_LayerEditorWindow        = nullptr;
LayerBrowserWindow              *g_LayerBrowserWindow       = nullptr;
CropConfigureWindow             *g_CropConfigureWindow      = nullptr;
EditorMap                        g_EditorMap;
ImageDB                         *g_ImageDB                  = nullptr;
ImageCache                       g_ImageCache;
AnimationDB                      g_AnimationDB;
AnimationDraw                    g_AnimationDraw;
std::string                      g_WilFilePathName;
std::string                      g_WorkingPathName;

int main()
{
    fl_register_images();

    g_WilFilePathName       = "";
    g_WorkingPathName       = "";

    g_MainWindow            = new MainWindow();
    g_SelectSettingWindow   = new SelectSettingWindow();
    g_AnimationSelectWindow = new AnimationSelectWindow();
    g_AboutWindow           = new AboutWindow();
    g_AttributeSelectWindow = new AttributeSelectWindow();
    g_AttributeGridWindow   = new AttributeSelectWindow();
    g_ProgressBarWindow     = new ProgressBarWindow();
    g_LayerEditorWindow     = new LayerEditorWindow();
    g_LayerBrowserWindow    = new LayerBrowserWindow();
    g_CropConfigureWindow   = new CropConfigureWindow();

    g_MainWindow->ShowAll();
    return Fl::run();
}
