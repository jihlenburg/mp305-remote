/* Address: ram:0005d7f0; name: FUN_ram_0005d7f0; body bytes: 342 */

undefined4 FUN_ram_0005d7f0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  gp = 0x20004000;
  iVar1 = DAT_ram_20001e1c;
  iVar4 = 0;
  while( true ) {
    iVar3 = iVar1;
    if (iVar3 == 0) {
      iVar1 = FUN_ram_20000040(0x40,0x204);
      uVar2 = 7;
      if (iVar1 != 0) {
        *(undefined1 *)(iVar1 + 3) = *(undefined1 *)(param_1 + 3);
        tmos_memcpy(iVar1 + 4,param_1 + 4,6);
        iVar3 = tmos_isbufset(param_1 + 0x1a,0,0x10);
        if (iVar3 == 0) {
          FUN_ram_20000298(iVar1 + 0x1a,param_1 + 0x1a,0x10);
          *(undefined1 *)(iVar1 + 10) = 1;
          *(byte *)(iVar1 + 0xb) = *(byte *)(iVar1 + 3) | 2;
          FUN_ram_000529ae(iVar1 + 0x1a,iVar1 + 0xc);
        }
        else {
          *(undefined1 *)(iVar1 + 10) = 0;
        }
        iVar3 = tmos_isbufset(param_1 + 0x2a,0,0x10);
        if (iVar3 == 0) {
          FUN_ram_20000298(iVar1 + 0x2a,param_1 + 0x2a,0x10);
          *(undefined1 *)(iVar1 + 0x12) = 1;
          *(byte *)(iVar1 + 0x13) = *(byte *)(iVar1 + 3) | 2;
          FUN_ram_000529ae(iVar1 + 0x2a,iVar1 + 0x14);
        }
        else {
          *(undefined1 *)(iVar1 + 0x12) = 0;
        }
        *(undefined1 *)(iVar1 + 1) = 0;
        FUN_ram_0005d77e(iVar1,DAT_ram_20001d94);
        iVar3 = iVar1;
        if (iVar4 != 0) {
          *(int *)(iVar4 + 0x3c) = iVar1;
          iVar3 = DAT_ram_20001e1c;
        }
        DAT_ram_20001e1c = iVar3;
        *(undefined4 *)(iVar1 + 0x3c) = 0;
        uVar2 = 0;
        DAT_ram_20001e18 = DAT_ram_20001e18 + '\x01';
      }
      return uVar2;
    }
    if ((*(char *)(iVar3 + 3) == *(char *)(param_1 + 3)) &&
       (iVar1 = tmos_memcmp(iVar3 + 4,param_1 + 4,0x10), iVar1 == 1)) break;
    iVar1 = *(int *)(iVar3 + 0x3c);
    iVar4 = iVar3;
  }
  gp = 0x20004000;
  return 0x12;
}

