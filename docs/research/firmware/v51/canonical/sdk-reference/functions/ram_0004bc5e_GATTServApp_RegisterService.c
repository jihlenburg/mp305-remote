/* Address: ram:0004bc5e; name: GATTServApp_RegisterService; body bytes: 126 */

int GATTServApp_RegisterService(int param_1,undefined2 param_2,undefined1 param_3,int param_4)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined2 uStack_18;
  undefined1 uStack_16;
  int iStack_14;
  
  gp = 0x20004000;
  if (param_1 != 0) {
    uStack_18 = param_2;
    uStack_16 = param_3;
    iStack_14 = param_1;
    iVar2 = FUN_ram_0004bb50(&uStack_18);
    if (iVar2 != 0) {
      gp = 0x20004000;
      return iVar2;
    }
    if (param_4 == 0) {
      gp = 0x20004000;
      return 0;
    }
    if (*(short *)(param_1 + 10) != 0) {
      puVar3 = (undefined4 *)FUN_ram_20000040(0xc,0x4705);
      if (puVar3 == (undefined4 *)0x0) {
        gp = 0x20004000;
        return 0x13;
      }
      uVar1 = *(undefined2 *)(param_1 + 10);
      *puVar3 = 0;
      puVar3[2] = param_4;
      *(undefined2 *)(puVar3 + 1) = uVar1;
      puVar5 = DAT_ram_20001a54;
      if (DAT_ram_20001a54 == (undefined4 *)0x0) {
        gp = 0x20004000;
        DAT_ram_20001a54 = puVar3;
        return 0;
      }
      do {
        puVar4 = puVar5;
        puVar5 = (undefined4 *)*puVar4;
      } while (puVar5 != (undefined4 *)0x0);
      *puVar4 = puVar3;
      gp = 0x20004000;
      return 0;
    }
  }
  return 2;
}

