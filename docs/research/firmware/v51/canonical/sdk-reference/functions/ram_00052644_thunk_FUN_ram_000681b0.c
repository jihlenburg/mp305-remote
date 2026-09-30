/* Address: ram:00052644; name: thunk_FUN_ram_000681b0; body bytes: 4 */

undefined4 thunk_FUN_ram_000681b0(undefined4 param_1,undefined1 param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00057ba2();
  if (iVar1 == 0) {
    uVar2 = 2;
  }
  else {
    if (param_3 == 0) {
      DAT_ram_20001a77 = '\x01';
    }
    else {
      if (DAT_ram_20001a77 == '\x01') {
        DAT_ram_20001a77 = '\0';
        param_2 = 2;
      }
      puVar3 = (undefined4 *)FUN_ram_00057bbc(0xff54);
      if (puVar3 == (undefined4 *)0x0) {
        if (DAT_ram_20001bec == (code *)0x0) {
          gp = 0x20004000;
          return 7;
        }
        (*DAT_ram_20001bec)(1,0x5555);
        gp = 0x20004000;
        return 7;
      }
      *(ushort *)((int)puVar3 + 10) = (ushort)*(byte *)((int)puVar3 + 10);
      if (*(int *)(iVar1 + 0x118) == 0) {
        *(undefined4 **)(iVar1 + 0x118) = puVar3;
      }
      else {
        **(undefined4 **)(iVar1 + 0x11c) = puVar3;
      }
      *(undefined4 **)(iVar1 + 0x11c) = puVar3;
      *puVar3 = 0;
      *(short *)(puVar3 + 3) = (short)param_3;
      *(undefined1 *)((int)puVar3 + 9) = 0x81;
      *(undefined1 *)(puVar3 + 2) = param_2;
      puVar3[1] = param_4 + -2;
    }
    uVar2 = 0;
  }
  return uVar2;
}

