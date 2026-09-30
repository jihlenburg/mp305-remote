/* Address: 000115b4; name: FUN_000115b4; body bytes: 158 */

uint FUN_000115b4(char *param_1,undefined4 *param_2,int param_3)

{
  bool bVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  undefined4 *puVar5;
  char *pcVar6;
  char *pcVar7;
  uint uVar8;
  uint uVar9;
  
  cVar3 = *param_1;
  bVar1 = false;
  pcVar6 = param_1 + 1;
  bVar2 = false;
  if (cVar3 == '0') {
    pcVar7 = param_1 + 2;
    cVar3 = *pcVar6;
    bVar1 = true;
    pcVar6 = pcVar7;
    if ((cVar3 == 'x') || (cVar3 == 'X')) {
      if ((param_3 == 0) || (param_3 == 0x10)) {
        bVar1 = false;
        param_3 = 0x10;
        cVar3 = *pcVar7;
        pcVar6 = param_1 + 3;
      }
    }
    else if (param_3 == 0) {
      param_3 = 8;
    }
  }
  else if (param_3 == 0) {
    param_3 = 10;
  }
  uVar8 = 0;
  uVar9 = 0;
  while (iVar4 = FUN_00010bfc(cVar3,param_3), -1 < iVar4) {
    uVar9 = param_3 * uVar9 + iVar4;
    bVar1 = true;
    uVar8 = param_3 * uVar8 + (uVar9 >> 0x10);
    uVar9 = uVar9 & 0xffff;
    if (0xffff < uVar8) {
      bVar2 = true;
    }
    cVar3 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  }
  if (param_2 != (undefined4 *)0x0) {
    if (bVar1) {
      param_1 = pcVar6 + -1;
    }
    *param_2 = param_1;
  }
  if (bVar2) {
    puVar5 = (undefined4 *)FUN_00020158();
    *puVar5 = 2;
    uVar9 = 0xffffffff;
  }
  else {
    uVar9 = uVar9 | uVar8 << 0x10;
  }
  return uVar9;
}

