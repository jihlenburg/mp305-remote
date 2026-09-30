/* Address: ram:000083c0; name: FUN_ram_000083c0; body bytes: 66 */

undefined4 FUN_ram_000083c0(undefined4 param_1,undefined4 param_2,undefined1 *param_3,int param_4)

{
  undefined1 *puVar1;
  int iVar2;
  
  gp = &DAT_ram_20002000;
  puVar1 = param_3 + param_4;
  do {
    if (param_3 == puVar1) {
      gp = &DAT_ram_20002000;
      return 0;
    }
    iVar2 = FUN_ram_00008396(param_1,*param_3,param_2);
    param_3 = param_3 + 1;
  } while (iVar2 != -1);
  return 0xffffffff;
}

