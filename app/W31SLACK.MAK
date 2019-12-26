# Microsoft Visual C++ generated build script - Do not modify

PROJ = W31SLACK
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = test
DLLS = 
D_RCDEFINES = /d_DEBUG 
R_RCDEFINES = /dNDEBUG 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = Z:\APP\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = ABOUTDLG.C  
FIRSTCPP =             
RC = rc
CFLAGS_D_WEXE = /nologo /W3 /Gf /Zi /Od /D "WINVER"="0x0300" /D "_DEBUG" /FR /GA /GEs /GEm /Fd"w31slack.PDB"
CFLAGS_R_WEXE = /nologo /W3 /Gf /O1 /D "WINVER"="0x0300" /D "NDEBUG" /FR /GA /GEs /GEm
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = oldnames libw slibcew winsock commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WEXE = oldnames libw slibcew winsock commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo 
RESFLAGS = /nologo /30 
RUNFLAGS = 
DEFFILE = W31SLACK.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = ABOUTDLG.SBR \
		MAINWND.SBR \
		WINMAIN.SBR \
		NETWORK.SBR \
		RESTAPI.SBR \
		JSNPARSE.SBR


ABOUTDLG_DEP = z:\app\aboutdlg.h \
	z:\app\globals.h


MAINWND_DEP = z:\app\aboutdlg.h \
	z:\app\globals.h \
	z:\app\mainwnd.h


RESOURCE_RCDEP = z:\app\app.ico \
	z:\app\w31slack.ver


WINMAIN_DEP = z:\app\globals.h \
	z:\app\mainwnd.h


all:	$(PROJ).EXE $(PROJ).BSC

ABOUTDLG.OBJ:	ABOUTDLG.C $(ABOUTDLG_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c ABOUTDLG.C

MAINWND.OBJ:	MAINWND.C $(MAINWND_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c MAINWND.C

RESOURCE.RES:	RESOURCE.RC $(RESOURCE_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r RESOURCE.RC

WINMAIN.OBJ:	WINMAIN.C $(WINMAIN_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c WINMAIN.C

NETWORK.OBJ:	NETWORK\NETWORK.C $(NETWORK_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c NETWORK\NETWORK.C

RESTAPI.OBJ:	RESTAPI\RESTAPI.C $(RESTAPI_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c RESTAPI\RESTAPI.C

JSNPARSE.OBJ:	JSNPARSE\JSNPARSE.C $(JSNPARSE_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c JSNPARSE\JSNPARSE.C


$(PROJ).EXE::	RESOURCE.RES

$(PROJ).EXE::	ABOUTDLG.OBJ MAINWND.OBJ WINMAIN.OBJ NETWORK.OBJ RESTAPI.OBJ JSNPARSE.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
ABOUTDLG.OBJ +
MAINWND.OBJ +
WINMAIN.OBJ +
NETWORK.OBJ +
RESTAPI.OBJ +
JSNPARSE.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) RESOURCE.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	RESOURCE.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) RESOURCE.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
