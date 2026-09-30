/* Address: ram:0006808c; name: FUN_ram_0006808c; body bytes: 104 */

undefined4
FUN_ram_0006808c(undefined4 param_1,uint param_2,uint param_3,int param_4,int param_5,
                undefined2 param_6)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_00057ba2();
  uVar2 = 2;
  if (iVar1 != 0) {
    uVar2 = 0x12;
    if (((int)(param_2 + param_3) < 0x100) && (param_3 <= param_2)) {
      if (param_4 + param_5 <= (int)(param_2 - param_3)) {
        *(char *)(iVar1 + 0x16b) = (char)param_2;
        *(byte *)(iVar1 + 0x16a) = *(byte *)(iVar1 + 0x16a) | 4;
        *(char *)(iVar1 + 0x16c) = (char)param_3;
        *(char *)(iVar1 + 0x16d) = (char)param_4;
        *(char *)(iVar1 + 0x16e) = (char)param_5;
        *(undefined2 *)(iVar1 + 0x170) = param_6;
        uVar2 = 0;
      }
    }
  }
  return uVar2;
}

