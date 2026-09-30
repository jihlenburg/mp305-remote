/* Address: ram:0004a2f4; name: FUN_ram_0004a2f4; body bytes: 90 */

undefined4 FUN_ram_0004a2f4(uint param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  
  gp = 0x20004000;
  piVar3 = DAT_ram_20001a48;
  piVar1 = (int *)0x0;
  do {
    piVar2 = piVar1;
    piVar1 = piVar3;
    if (piVar1 == (int *)0x0) {
      gp = 0x20004000;
      return 1;
    }
    piVar3 = (int *)*piVar1;
  } while (*(ushort *)(piVar1[2] + 10) != param_1);
  if (piVar2 != (int *)0x0) {
    *piVar2 = (int)piVar3;
    piVar3 = DAT_ram_20001a48;
  }
  DAT_ram_20001a48 = piVar3;
  if (param_2 != 0) {
    tmos_memcpy(param_2,piVar1 + 1,8);
  }
  FUN_ram_20000104(piVar1);
  return 0;
}

