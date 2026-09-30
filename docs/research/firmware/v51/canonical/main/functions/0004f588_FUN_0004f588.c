/* Address: 0004f588; name: FUN_0004f588; body bytes: 116 */

undefined4 * FUN_0004f588(undefined4 *param_1,int param_2)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  
  if (param_2 == 0) {
    FUN_00046bec();
    return &DAT_2003a484;
  }
  if (param_1 != &DAT_2003a484) {
    iVar3 = FUN_00052b38();
    puVar2 = (undefined4 *)FUN_00052c1c(DAT_2003a5d8,param_1,param_2);
    uVar1 = DAT_2003a5e0;
    if (puVar2 != (undefined4 *)0x0) {
      DAT_2003a5dc = DAT_2003a5dc - iVar3;
      iVar3 = FUN_00052b38(puVar2);
      DAT_2003a5dc = iVar3 + DAT_2003a5dc;
      uVar1 = DAT_2003a5dc;
      if (DAT_2003a5dc <= DAT_2003a5e0) {
        uVar1 = DAT_2003a5e0;
      }
    }
    DAT_2003a5e0 = uVar1;
    return puVar2;
  }
  puVar2 = (undefined4 *)FUN_0004a318(param_2);
  return puVar2;
}

