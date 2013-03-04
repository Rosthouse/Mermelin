############################################################################################
#      NSIS Installation Script created by NSIS Quick Setup Script Generator v1.09.18
#               Entirely Edited with NullSoft Scriptable Installation System                
#              by Vlasis K. Barkas aka Red Wine red_wine@freemail.gr Sep 2006               
############################################################################################

!define APP_NAME "Mermelin"
!define COMP_NAME "CPVR Games"
!define VERSION "1.00.00.00"
!define COPYRIGHT "CPVR Games"
!define DESCRIPTION "Game"
!define INSTALLER_NAME "mermelin.exe"
!define MAIN_APP_EXE "Engine.exe"
!define INSTALL_TYPE "SetShellVarContext all"
!define REG_ROOT "HKLM"
!define REG_APP_PATH "Software\Microsoft\Windows\CurrentVersion\App Paths\${MAIN_APP_EXE}"
!define UNINSTALL_PATH "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}"

######################################################################

VIProductVersion  "${VERSION}"
VIAddVersionKey "ProductName"  "${APP_NAME}"
VIAddVersionKey "CompanyName"  "${COMP_NAME}"
VIAddVersionKey "LegalCopyright"  "${COPYRIGHT}"
VIAddVersionKey "FileDescription"  "${DESCRIPTION}"
VIAddVersionKey "FileVersion"  "${VERSION}"

######################################################################

SetCompressor ZLIB
Name "${APP_NAME}"
Caption "${APP_NAME}"
OutFile "${INSTALLER_NAME}"
BrandingText "${APP_NAME}"
XPStyle on
InstallDirRegKey "${REG_ROOT}" "${REG_APP_PATH}" ""
InstallDir "$PROGRAMFILES\Mermelin"

######################################################################

!include "MUI.nsh"

!define MUI_ABORTWARNING
!define MUI_UNABORTWARNING

!define MUI_LANGDLL_REGISTRY_ROOT "${REG_ROOT}"
!define MUI_LANGDLL_REGISTRY_KEY "${UNINSTALL_PATH}"
!define MUI_LANGDLL_REGISTRY_VALUENAME "Installer Language"

!define MUI_ICON "${PROJECT_DIR}\Deployment\mermelin.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\classic-uninstall.ico"

!insertmacro MUI_PAGE_WELCOME

!ifdef LICENSE_TXT
!insertmacro MUI_PAGE_LICENSE "${LICENSE_TXT}"
!endif

!insertmacro MUI_PAGE_DIRECTORY

!ifdef REG_START_MENU
!define MUI_STARTMENUPAGE_NODISABLE
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "Mermelin"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "${REG_ROOT}"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${UNINSTALL_PATH}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${REG_START_MENU}"
!insertmacro MUI_PAGE_STARTMENU Application $SM_Folder
!endif

!insertmacro MUI_PAGE_INSTFILES

!define MUI_FINISHPAGE_RUN "$INSTDIR\${MAIN_APP_EXE}"
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM

!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_UNPAGE_FINISH

!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "German"

!insertmacro MUI_RESERVEFILE_LANGDLL

######################################################################

Function .onInit
!insertmacro MUI_LANGDLL_DISPLAY
FunctionEnd

######################################################################

Section -MainProgram
	${INSTALL_TYPE}
	SetOverwrite ifnewer
	
	#Prerequisite
	SetOutPath $TEMP
	File "${PROJECT_DIR}\Deployment\Windows\vcredist_x86.exe"
	ExecWait "$TEMP\vcredist_x86.exe /q /norestart"
	Delete "$TEMP\vcredist_x86.exe "

	SetOutPath "$INSTDIR"
	#Engine
	File "${PROJECT_DIR}\bin\release\Engine.exe"
	
	#OGRE
	File "${OGRE_HOME}\bin\release\OgreMain.dll"
	File "${OGRE_HOME}\bin\release\Plugin_BSPSceneManager.dll"
	File "${OGRE_HOME}\bin\release\RenderSystem_GL.dll"
	
	#OpenAL
	File "${OGRE_HOME}\bin\release\libsndfile-1.dll"
	File "${OGRE_HOME}\bin\release\openal32.dll"
	
	#OIS
	File "${OGRE_HOME}\bin\release\OIS.dll"
	
	#Rocket
	File "${OGRE_HOME}\bin\release\RocketControls.dll"
	File "${OGRE_HOME}\bin\release\RocketCore.dll"
	File "${OGRE_HOME}\bin\release\RocketDebugger.dll"
	
	#Config
	File "${PROJECT_DIR}\Deployment\resources.cfg"
	File "${PROJECT_DIR}\Deployment\plugins.cfg"
	File "${PROJECT_DIR}\Deployment\ogre.cfg"
	
	#Media
	SetOutPath "$INSTDIR\media"
	File /r "${PROJECT_DIR}\media\*"
	
SectionEnd

######################################################################

Section -Icons_Reg
	SetOutPath "$INSTDIR"
	WriteUninstaller "$INSTDIR\uninstall.exe"

	!ifdef REG_START_MENU
	!insertmacro MUI_STARTMENU_WRITE_BEGIN Application
	CreateDirectory "$SMPROGRAMS\$SM_Folder"
	CreateShortCut "$SMPROGRAMS\$SM_Folder\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
	!ifdef WEB_SITE
	WriteIniStr "$INSTDIR\${APP_NAME} website.url" "InternetShortcut" "URL" "${WEB_SITE}"
	CreateShortCut "$SMPROGRAMS\$SM_Folder\${APP_NAME} Website.lnk" "$INSTDIR\${APP_NAME} website.url"
	!endif
	!insertmacro MUI_STARTMENU_WRITE_END
	!endif

	!ifndef REG_START_MENU
	CreateDirectory "$SMPROGRAMS\Mermelin"
	CreateShortCut "$SMPROGRAMS\Mermelin\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
	!ifdef WEB_SITE
	WriteIniStr "$INSTDIR\${APP_NAME} website.url" "InternetShortcut" "URL" "${WEB_SITE}"
	CreateShortCut "$SMPROGRAMS\Mermelin\${APP_NAME} Website.lnk" "$INSTDIR\${APP_NAME} website.url"
	!endif
	!endif

	WriteRegStr ${REG_ROOT} "${REG_APP_PATH}" "" "$INSTDIR\${MAIN_APP_EXE}"
	WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayName" "${APP_NAME}"
	WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "UninstallString" "$INSTDIR\uninstall.exe"
	WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayIcon" "$INSTDIR\${MAIN_APP_EXE}"
	WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayVersion" "${VERSION}"
	WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "Publisher" "${COMP_NAME}"

	!ifdef WEB_SITE
	WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "URLInfoAbout" "${WEB_SITE}"
	!endif
SectionEnd

######################################################################

Section Uninstall
	${INSTALL_TYPE}
	
	#Remove install directory
	RMDir /r $INSTDIR
	
	 
	Delete "$INSTDIR\uninstall.exe"
	!ifdef WEB_SITE
	Delete "$INSTDIR\${APP_NAME} website.url"
	!endif

	RmDir "$INSTDIR"

	!ifdef REG_START_MENU
	!insertmacro MUI_STARTMENU_GETFOLDER "Application" $SM_Folder
	Delete "$SMPROGRAMS\$SM_Folder\${APP_NAME}.lnk"
	!ifdef WEB_SITE
	Delete "$SMPROGRAMS\$SM_Folder\${APP_NAME} Website.lnk"
	!endif
	RmDir "$SMPROGRAMS\$SM_Folder"
	!endif

	!ifndef REG_START_MENU
	Delete "$SMPROGRAMS\Mermelin\${APP_NAME}.lnk"
	!ifdef WEB_SITE
	Delete "$SMPROGRAMS\Mermelin\${APP_NAME} Website.lnk"
	!endif
	RmDir "$SMPROGRAMS\Mermelin"
	!endif

	DeleteRegKey ${REG_ROOT} "${REG_APP_PATH}"
	DeleteRegKey ${REG_ROOT} "${UNINSTALL_PATH}"
SectionEnd

######################################################################

Function un.onInit
	!insertmacro MUI_UNGETLANGUAGE
FunctionEnd

######################################################################

