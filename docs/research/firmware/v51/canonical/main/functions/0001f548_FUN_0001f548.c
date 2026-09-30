/* Address: 0001f548; name: FUN_0001f548; body bytes: 102 */

void FUN_0001f548(code *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  
  if ((int)param_1 < 0) {
    param_1 = (code *)0x0;
  }
  else if (0x4f588 < (int)param_1) {
    param_1 = FUN_0004f588;
  }
  uVar3 = FUN_000103ea((int)((longlong)(int)param_1 * 0xfffff),
                       (int)((ulonglong)((longlong)(int)param_1 * 0xfffff) >> 0x20),0xce4,0);
  uVar1 = FUN_000103ea((int)uVar3,(int)((ulonglong)uVar3 >> 0x20),100,0);
  if ((int)param_1 < 0x1389) {
    if (2999 < (int)param_1) goto LAB_0001f59c;
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  FUN_0001416c(&DAT_40041000,0,uVar2);
LAB_0001f59c:
  FUN_0001ce80((uVar1 >> 9) * 2 & 0xffff);
  FUN_0001cea8(uVar1 & 0x1ff);
  DAT_1fffa958 = param_1;
  return;
}

