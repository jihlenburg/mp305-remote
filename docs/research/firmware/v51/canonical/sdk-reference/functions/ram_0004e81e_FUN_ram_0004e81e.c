/* Address: ram:0004e81e; name: FUN_ram_0004e81e; body bytes: 62 */

void FUN_ram_0004e81e(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined1 auStack_54 [4];
  undefined4 uStack_50;
  undefined4 uStack_4c;
  
  gp = 0x20004000;
  if ((DAT_ram_20001a70 != (undefined4 *)0x0) && ((code *)*DAT_ram_20001a70 != (code *)0x0)) {
    uStack_50 = *param_2;
    uStack_4c = param_2[1];
    iVar1 = (*(code *)*DAT_ram_20001a70)(param_1,1,&uStack_50);
    if (iVar1 != 0) {
      auStack_54[0] = (undefined1)iVar1;
      FUN_ram_0004e7e6(*(undefined2 *)(param_1 + 2),auStack_54);
    }
    return;
  }
  return;
}

