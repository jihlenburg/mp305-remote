/* Address: ram:0004bd42; name: FUN_ram_0004bd42; body bytes: 116 */

void FUN_ram_0004bd42(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined2 uStack_12;
  
  gp = 0x20004000;
  if ((param_2 == 1) || ((param_2 == 2 && (iVar1 = linkDB_State(param_1,1), iVar1 == 0)))) {
    iVar1 = FUN_ram_0004a124(param_1);
    if (iVar1 != 0) {
      FUN_ram_0004a0d4();
    }
    for (iVar1 = FUN_ram_0004aaf8(1,0xffff,&DAT_ram_0006c644,2,&uStack_12); iVar1 != 0;
        iVar1 = FUN_ram_0004afa0(iVar1,0xffff,uStack_12,0)) {
      GATTServApp_InitCharCfg(param_1,*(undefined4 *)(iVar1 + 0xc));
    }
  }
  return;
}

