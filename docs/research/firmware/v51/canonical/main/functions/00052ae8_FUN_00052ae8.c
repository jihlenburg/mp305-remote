/* Address: 00052ae8; name: FUN_00052ae8; body bytes: 76 */

uint * FUN_00052ae8(undefined4 param_1,uint *param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = (param_3 - 8U) - (param_3 - 8U & 3);
  if ((((uint)param_2 & 3) == 0) && (uVar2 - 0xc < 0x3fff5)) {
    *param_2 = ((byte)*param_2 & 3 | uVar2) & 0xfffffffd | 1;
    FUN_00024b6a(param_1,param_2 + -1);
    iVar1 = FUN_00024bd4(param_2 + -1);
    *(undefined4 *)(iVar1 + 4) = 2;
    return param_2;
  }
  return (uint *)0x0;
}

