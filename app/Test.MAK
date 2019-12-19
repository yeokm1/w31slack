# Microsoft Visual C++ generated build script - Do not modify

PROJ = Test
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
CFLAGS_D_WEXE = /nologo /W3 /Gf /Zi /Od /D "WINVER"="0x0300" /D "_DEBUG" /FR /GA /GEs /GEm /Fd"Test.PDB"
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
SBRS = TestMain.SBR

RESOURCE_RCDEP = z:\app\app.ico \
	z:\app\w31slack.ver


TestMain_DEP = z:\app\globals.h \
	z:\app\mainwnd.h


all:	$(PROJ).EXE $(PROJ).BSC

RESOURCE.RES:	RESOURCE.RC $(RESOURCE_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r RESOURCE.RC

TestMain.OBJ:	TESTMAIN.C $(TestMain_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c TESTMAIN.C

Network.OBJ:	network\NETWORK.C $(Network_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c NETWORK.C

RESTAPI.OBJ:	restapi\RESTAPI.C $(RESTAPI_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c RESTAPI.C

JSNPARSE.OBJ:	jsnparse\JSNPARSE.C $(JSNPARSE_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c JSNPARSE.C



$(PROJ).EXE::	RESOURCE.RES

$(PROJ).EXE::	NETWORK.OBJ RESTAPI.OBJ TestMain.OBJ JSNPARSE.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
TestMain.OBJ +
Network.OBJ +
RestApi.obj +
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
