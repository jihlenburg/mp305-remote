/* Address: 0004f364; name: FUN_0004f364; body bytes: 52 */

undefined8 FUN_0004f364(uint param_1,int param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  iVar1 = 0;
  uVar3 = 1;
  for (; param_3 != 0; param_3 = (int)param_3 >> 1) {
    uVar2 = uVar3;
    if ((param_3 & 1) != 0) {
      uVar2 = (uint)((ulonglong)uVar3 * (ulonglong)param_1);
      iVar1 = uVar3 * param_2 +
              iVar1 * param_1 + (int)((ulonglong)uVar3 * (ulonglong)param_1 >> 0x20);
    }
    param_2 = param_1 * param_2 +
              param_2 * param_1 + (int)((ulonglong)param_1 * (ulonglong)param_1 >> 0x20);
    param_1 = (uint)((ulonglong)param_1 * (ulonglong)param_1);
    uVar3 = uVar2;
  }
  return CONCAT44(iVar1,uVar3);
}

