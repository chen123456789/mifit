; Script generated by the HM NIS Edit Script Wizard.

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "MIFit"
; Dynamically defined by the super-script
!define PRODUCT_VERSION "${VERSION}"
!define PRODUCT_PUBLISHER "Open Source MIFit"
!define PRODUCT_WEB_SITE "http://code.google.com/p/mifit"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\MIFit.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define MIFitRootKey "Software\MIFit"

SetCompressor bzip2

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "license.txt"
; Components page
!insertmacro MUI_PAGE_DIRECTORY
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\MIFit.exe"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"

; Reserve files
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "MIFit ${VERSION} Installer.exe"
InstallDir "$PROGRAMFILES\MIFit"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

Section "MIFit" Section1
  SetOutPath "$INSTDIR"
  SetOverwrite on
  File "MIFit.exe"
  File "mingwm10.dll"
  File "QtCore4.dll"
  File "QtGui4.dll"
  File "QtOpenGL4.dll"
  File "QtXml4.dll"
  File "license.txt"
  File "qt.conf"
  CreateDirectory "$SMPROGRAMS\MIFit"
  CreateShortCut "$SMPROGRAMS\MIFit\MIFit.lnk" "$INSTDIR\MIFit.exe"
  CreateShortCut "$DESKTOP\MIFit.lnk" "$INSTDIR\MIFit.exe"
  SetOutPath "$INSTDIR\data\fonts"
  File "data\fonts\*"
  SetOutPath "$INSTDIR\data\images"
  File "data\images\*"
  SetOutPath "$INSTDIR\data"
  SetOverwrite ifnewer
  File "data\*"
  SetOutPath "$INSTDIR\data\fragment_library"
  File "data\fragment_library\*"
  SetOutPath "$INSTDIR\data\pdbvec"
  File "data\pdbvec\*"
  SetOutPath "$INSTDIR\data\xtal_info"
  SetOverwrite ifnewer
  File "data\xtal_info\*"
  SetOutPath "$INSTDIR\examples"
  File "examples\*"
  SetOutPath "$INSTDIR\MIExpert"
  File "MIExpert\*"
  SetOutPath "$INSTDIR\plugins\imageformats"
  File "plugins\imageformats\*"
  SetOutPath "$INSTDIR\plugins\accessible"
  File "plugins\accessible\*"
SectionEnd

Section -AdditionalIcons
  SetOutPath $INSTDIR
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\MIFit\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\MIFit\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\MIFit.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\MIFit.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
SectionEnd

Function .onInit
 System::Call 'kernel32::CreateMutexA(i 0, i 0, t "myMutex") i .r1 ?e'
 Pop $R0

 StrCmp $R0 0 +3
   MessageBox MB_OK|MB_ICONEXCLAMATION "The installer is already running."
   Abort
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  RMDir /r "$INSTDIR\plugins"
  RMDir /r "$INSTDIR\MIExpert"
  RMDir /r "$INSTDIR\examples"
  RMDir /r "$INSTDIR\data\fonts"
  RMDir /r "$INSTDIR\data\images"
  Delete "$INSTDIR\data\xtal_info\sirhp"
  Delete "$INSTDIR\data\xtal_info\fdx"
  Delete "$INSTDIR\data\xtal_info\cvccp"
  Delete "$INSTDIR\data\xtal_info\cua"
  Delete "$INSTDIR\data\xtal_info\iep"
  Delete "$INSTDIR\data\symlib"
  Delete "$INSTDIR\data\ScatteringFactors"
  Delete "$INSTDIR\data\pdbvec\README"
  Delete "$INSTDIR\data\pdbvec\pdbvec.list"
  Delete "$INSTDIR\data\pdbvec\genlist"
  Delete "$INSTDIR\data\pdbvec\ecoli_ptx.pdb"
  Delete "$INSTDIR\data\pdbvec\cuznsod.pdb"
  Delete "$INSTDIR\data\pdbvec\5mbn.pdb"
  Delete "$INSTDIR\data\pdbvec\5cpa.pdb"
  Delete "$INSTDIR\data\pdbvec\4fd1.pdb"
  Delete "$INSTDIR\data\pdbvec\4cpv.pdb"
  Delete "$INSTDIR\data\pdbvec\3lzm.pdb"
  Delete "$INSTDIR\data\pdbvec\3ebx.pdb"
  Delete "$INSTDIR\data\pdbvec\2tim.pdb"
  Delete "$INSTDIR\data\pdbvec\2cyp.pdb"
  Delete "$INSTDIR\data\pdbvec\2ccy.pdb"
  Delete "$INSTDIR\data\pdbvec\1ycc.pdb"
  Delete "$INSTDIR\data\pdbvec\1mbd.pdb"
  Delete "$INSTDIR\data\pdbvec\1amt.pdb"
  Delete "$INSTDIR\data\pdbvec\1alc.pdb"
  Delete "$INSTDIR\data\fragment_library\beta2.pdb"
  Delete "$INSTDIR\data\fragment_library\alpha2.pdb"
  Delete "$INSTDIR\data\dict_nucleic.pdb"
  Delete "$INSTDIR\data\dict.polarh.pdb"
  Delete "$INSTDIR\data\dict.noh.pdb"
  Delete "$INSTDIR\data\dict.allh.pdb"
  Delete "$INSTDIR\data\rama500-general.data"
  Delete "$INSTDIR\data\rama500-gly-sym-nosec.data"
  Delete "$INSTDIR\data\rama500-prepro.data"
  Delete "$INSTDIR\data\rama500-pro.data"

  Delete "$INSTDIR\MIFit.exe"
  Delete "$INSTDIR\mingwm10.dll"
  Delete "$INSTDIR\QtCore4.dll"
  Delete "$INSTDIR\QtGui4.dll"
  Delete "$INSTDIR\QtOpenGL4.dll"
  Delete "$INSTDIR\QtXml4.dll"
  Delete "$INSTDIR\license.txt"
  Delete "$INSTDIR\qt.conf"

  Delete "$SMPROGRAMS\MIFit\Uninstall.lnk"
  Delete "$SMPROGRAMS\MIFit\Website.lnk"
  Delete "$DESKTOP\MIFit.lnk"
  Delete "$SMPROGRAMS\MIFit\MIFit.lnk"

  RMDir "$SMPROGRAMS\MIFit"

  RMDir "$INSTDIR\examples\xplor"
  RMDir "$INSTDIR\examples\mirdemo"
  RMDir "$INSTDIR\examples\cua_mad"
  RMDir "$INSTDIR\examples\ccp4"
  RMDir "$INSTDIR\examples"
  RMDir "$INSTDIR\data\xtal_info"
  RMDir "$INSTDIR\data\pdbvec"
  RMDir "$INSTDIR\data\fragment_library"
  RMDir "$INSTDIR\data"
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  DeleteRegKey HKCU "${MIFitRootKey}"
  SetAutoClose true
SectionEnd
