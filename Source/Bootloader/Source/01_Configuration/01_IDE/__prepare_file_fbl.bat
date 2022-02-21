
rem 0. Copy output file to the temporary location
copy ..\..\ATC\Configuration\NEC_1843\Release\Exe\GAC_AL_FCP.hex  .\process\GAC_Appl_Edit.hex

rem 0. Copy output file to the temporary location
copy ..\..\FBL_GAC_1843\Configuration\NEC_1843\Release\Exe\FBL_GAC.hex  .\process\GAC_Fbl.hex

rem 1. Fill all hex file
.\HexView\hexview.exe .\process\GAC_Appl_Edit.hex	/s /AD80 /AL /XS -o .\process\App_Append_Edit.hex
del .\process\GAC_Appl_Edit.hex

rem 2. del fbl address
.\HexView\hexview.exe .\process\App_Append_Edit.hex  /s /CR:0x0-0x7FFF /XS -o .\process\GAC_Appl.hex
copy .\process\GAC_Appl.hex  .\output\GAC_Appl.hex
del .\process\App_Append_Edit.hex

rem 3. checksum calculate
.\HexView\hexview.exe .\output\GAC_Appl.hex	/s /CS9:GAC_Appl.crc
copy GAC_Appl.crc  .\output\GAC_Appl.crc
del GAC_Appl.crc

rem 4. delete fbl appl address
.\HexView\hexview.exe .\process\GAC_Fbl.hex	/s /CR:0x8000-0x9000 /XS -o GAC_Fbl_edit.hex

rem 5. merge
.\HexView\hexview.exe GAC_Fbl_edit.hex	/s /MO:GAC_Appl.hex;0x00+.\process\GAC_Appl.hex /XS -o GAC_Fbl_Merge.hex

rem 6. valid block
.\HexView\hexview.exe GAC_Fbl_Merge.hex /s /FR:0x1ff50,16 /FP:FFFFFFFF62537CAEFFFFFFFFEFFFFFFFF  /AD:4 /AL /XS -o .\output\GAC_AL_Low(FCP)_BX.X_S.X_0xXXXX.hex

rem 7. export bin

.\HexView\hexview.exe .\output\GAC_Appl.hex /s /P:GAC_FBL.ini /xgac

rem 8. renamed
set "Ymd=%date:~,4%%date:~5,2%%date:~8,2%"
copy .\output\GAC_Appl.bin  .\output\GAC_AL_FCP_APP1_S.A_ET1_A.A_%ymd%.bin

del GAC_Fbl_Merge.hex
del GAC_Fbl_edit.hex
del GAC_Appl.hex

