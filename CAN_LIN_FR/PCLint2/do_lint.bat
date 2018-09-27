@rem The arguments for this batch file: 
@rem %1: The path to the project folder
@rem ------------------------------------------------------
@rem Path to my project folder
SET PROJ_PATH=D:\CANFDGwMcuFirmRH850F1x\code\CANFDGwMcuFirmRH850F1x
@rem Path to my local lint folder inside the project
SET PROJ_LINT_PATH=%PROJ_PATH%\PCLint2
@rem Path to lint-nt.exe
SET LINT_EXE=C:\PClint9\lint-nt.exe
@rem --------------- Run PC-lint ---------------------------
%LINT_EXE% %PROJ_LINT_PATH%\proj_options.lnt %PROJ_LINT_PATH%\proj_files.lnt -vf